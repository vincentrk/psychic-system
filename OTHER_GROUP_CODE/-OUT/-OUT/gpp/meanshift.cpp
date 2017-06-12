/*
 * Based on paper "Kernel-Based Object Tracking"
 * you can find all the formula in the paper
*/

#include "meanshift.h"
#include "Timer.h"

/* DSP related headers */
#include "dsplink.h"

extern "C" {
#include "pool_notify.h"
}

#include "sharedmem.h"

//Scales to that make integer usages possible
#define SCALE 67108864
#define SCALE_SHIFT  26

#define SCALE2 8192
#define SCALE2_SHIFT 13


extern Timer partialTimer;
extern Timer partialTimer2;

MeanShift::MeanShift()
{
    cfg.MaxIter = 8;
    cfg.num_bins = 16;		// Will be rounded up towards the nearest power of 2 (allow bitshift) minimum = 16
    cfg.piexl_range = 256;

    bit_shift = ceil(log(cfg.num_bins)/log(2));
    cfg.num_bins = pow(2,bit_shift);
    bin_width = cfg.piexl_range / cfg.num_bins;
}

void  MeanShift::Init_target_frame(const cv::Mat &frame,const cv::Rect &rect)
{    
	//Initiate private variables
    int pdf_size = cfg.num_bins*3;
    target_candidate = new int [pdf_size];
    target_model = new int [pdf_size];
    weights = new int [pdf_size];
	kernel = new int [rect.height*rect.width];

    old_pos[0] = rect.x;
    old_pos[1] = rect.y;

    // Set target
    target_Region = rect;
    
    // Calculate kernel
    Epanechnikov_kernel(kernel);

    // Calculate taget model
    pdf_representation(frame,target_Region,target_model);
}

void  MeanShift::Epanechnikov_kernel(int* kernel)
{
	// Init
    int h = target_Region.height;
    int w = target_Region.width;
    int h2 = h*h;
    int w2 = w*w;

    // Kernel contstant for immediate normalisation
    float normalized_C = (h*w*0.392699081687683)/SCALE;

    // Loop trough kernel vector
    for(int i=0;i<h;i++)
    {
    	// Offset for kernel position (vector)
    	int offset_ker = i * w;

    	// x-Position with respect to centre
    	int x = (i<<1) - h;

        for(int j=0;j<w;j++)
        {
        	// y-Position with respect to centre
            int y = (j<<1) - w;

            // Set kernel value
            float norm_x = static_cast<float>(x*x)/h2+static_cast<float>(y*y)/w2;
            kernel[offset_ker+j] = (norm_x<1?((1.0-norm_x)/normalized_C):0);
        }
    }
    return;
}

void MeanShift::pdf_representation(const cv::Mat &frame, const cv::Rect &rect, int* pdf)
{
    // Clean content of pdf
    memset(pdf, 0, (cfg.num_bins*3)*sizeof(*pdf));

    // Prepare offset value for pdf location
    unsigned int offset_pdf [] = {cfg.num_bins, cfg.num_bins<<1};

    // Location of rectangle in total frame
    int clo_index = rect.x;
    int row_index = rect.y;

    // Loop trough target
    for(int i=0;i<rect.height;i++)
    {
    	// Offset for kernel
        int offset_ker = i*rect.width;

        // Read the frame as a pointer to speed up reading by not using 'at'
        const unsigned char *frame_data = frame.ptr<unsigned char>(row_index + i);

        for(int j=0;j<rect.width;j++)
        {
            // Get uchar colour vector
            const unsigned char *curr_pixel = &frame_data[(clo_index + j)*3];

            // Convert pixel value to bin number
            unsigned int bin_value[3];
            bin_value[0] = curr_pixel[0]>>bit_shift;
            bin_value[1] = curr_pixel[1]>>bit_shift;
            bin_value[2] = curr_pixel[2]>>bit_shift;

            // Add kernel value to corresponding bins
            int position = offset_ker + j;
            pdf[bin_value[0]] += kernel[position];
            pdf[offset_pdf[0] + bin_value[1]] += kernel[position];
            pdf[offset_pdf[1] + bin_value[2]] += kernel[position];
        }
    }
    return;
}

void MeanShift::CalWeight(int* target_model,int* target_candidate)
{
	// Calculate size of pdf vector
	int pdf_size = 3 * cfg.num_bins;

	// Loop through pdf vector
    for(int i=0;i<pdf_size;i++)
    {
    	// Divide by zero prevention
        if(target_candidate[i] == 0)
        {
            if(target_model[i] == 0)
            {
            	// Set to zero if model is zero
                weights[i] = 0;
            }
            else
            {
            	// Set to maximum if divide by zeros
                weights[i] = 4*SCALE2;
            }
        }
        else
        {
        	// Otherwise set weight parameter and SCALE for integer usage
            weights[i] = static_cast<int>(sqrt(static_cast<float>(target_model[i])/target_candidate[i]))<<SCALE2_SHIFT;
        }
    }
    return;
}

#define DSP_CALSHIFT_FULL
void MeanShift::CalShift(const cv::Mat &frame,int* index)
{
    // Init
    Int32 delta_x = 0;  
    Int32 sum_wij = 0;
    Int32 delta_y = 0;
    
    // Set offset for weight vector
    Uint32 offset_w [] = {cfg.num_bins, cfg.num_bins<<1};

    // Set postion of centre (x2)
    Int32 centre = target_Region.height-1;

    // Loop trough target matrix
    for(int i=0;i<target_Region.height;i++)
    {
        // Set weight to zero and y-position with respect to centre (x2)
        int weight_tmp_i = 0;
        int norm_i = (i<<1) - centre;

        // Read the frame as a pointer to speed up reading by not using 'at'
        const unsigned char *frame_data = frame.ptr<uint8_t>(target_Region.y + i);

#define DSP_CALSHIFT_FULL
#if defined(DSP_CALSHIFT_FULL)
        /* Get shared memory pointer */
        char *shmem = pool_notify_GetSharedMem();
        unsigned char *shmem_pixels;
        int *shmem_pdf;
        int32_t *shmem32 = (int32_t *)shmem;
        int idx = 0;

        shmem_pixels = (unsigned char *)&shmem32[IDX_PIXEL_START];

        /* Copy the frame data to shared memory */
        idx = (target_Region.width * 3) * sizeof(unsigned char);
        memcpy(shmem_pixels, &frame_data[target_Region.x * 3], idx);

        /* Fill in meta data into shared memory */
        shmem32[IDX_PIXEL_LENGTH] = (uint32_t)idx; // The length of pixel data
	shmem32[IDX_PDF_LENGTH] = (3 * cfg.num_bins); // PDF Size

        /* Copy bit_shift into shared memory */
        shmem32[IDX_BIT_SHIFT] = bit_shift;

        /* Copy norm_i into shared memory */
        shmem32[IDX_NORM_I] = norm_i;

        /* Copy delta_x into shared memory */
        shmem32[IDX_DELTA_X_RES] = delta_x;

        /* Copy centre into shared memory */
        shmem32[IDX_CENTRE] = centre;

        /* Copy offset_w into shared memory */
        shmem32[IDX_OFFSET_W_0] = offset_w[0];
        shmem32[IDX_OFFSET_W_1] = offset_w[1];

        shmem_pdf = &shmem32[IDX_PIXEL_START + ((idx+4) / sizeof(int))];

        /* Copy the PDF into shared memory */
        memcpy(shmem_pdf, weights, (3 * cfg.num_bins) * sizeof(Int32));

        /* Notify DSP to start */
        pool_notify_NotifySharedMem(IDX_PIXEL_START * sizeof(Int32) + idx + 4 + (3 * cfg.num_bins) * sizeof(Int32));
        //pool_notify_NotifySharedMem(-1);

        /* Wait for DSP to be done */
        pool_notify_WaitDSP();

        /* Read the result */
        delta_x = (Int32)shmem32[IDX_DELTA_X_RES];
        // Accumulate weights
        weight_tmp_i = (Int32)shmem32[IDX_WEIGHT_I_RES];

        //std::cout << "DSP delta_x: " << delta_x_new << std::endl;
        //std::cout << "DSP weight_tmp_i: " << weight_tmp_i << std::endl;


#elif defined(DSP_CALSHIFT_PARTIAL)

#else /* GPP only */

        // Set check value for SCALED normalized position check
        Int32 check = (centre*centre);

        weight_tmp_i = 0;
        for(int j=0;j<target_Region.width;j++)
        {
            // Set x-position with respect to centre (x2)
            int32_t norm_j = (j<<1) - centre;

            // Check if current position is within circle that fits in target box
            if(norm_i*norm_i + norm_j*norm_j < check)
            {
                // Get uchar colour vector
                const unsigned char *curr_pixel = &frame_data[(target_Region.x + j)*3];

                // Convert pixel value to bin number
                uint32_t bin_value[3];
                bin_value[0] = curr_pixel[0]>>bit_shift;
                bin_value[1] = curr_pixel[1]>>bit_shift;
                bin_value[2] = curr_pixel[2]>>bit_shift;

                // Sum weights at current pixel location
                int32_t weight_tmp_j = weights[bin_value[0]] + 
                    weights[offset_w[0]+bin_value[1]] + 
                    weights[offset_w[1]+bin_value[2]];

                // Calculate shift in x-direction
                delta_x += norm_j*weight_tmp_j;
                // Accumulate weights
                weight_tmp_i += weight_tmp_j;
            }
        }
#endif

//#endif
        //std::cout << "GPP delta_x: " << delta_x << std::endl;
        //std::cout << "GPP weight_tmp_i: " << weight_tmp_i << std::endl;
        //std::cout << std::endl;

        // Calculate shift in y-direction
        delta_y += weight_tmp_i*norm_i;
        // Accumulate weights
        sum_wij += weight_tmp_i;
    }

    // Set resulting location
    index[0] += (delta_x>>1)/sum_wij;
    index[1] += (delta_y>>1)/sum_wij;
    return;
}

cv::Rect MeanShift::track(const cv::Mat &next_frame)
{
	// Set beginning location
	int index [] = {target_Region.x, target_Region.y};

	// Loop throught iterations
    for(int iter=0;iter<cfg.MaxIter;iter++)
    {
    	// Calculate pdf of target candidate
        pdf_representation(next_frame,target_Region,target_candidate);

        // Prepare weight summation by sqrt(target_model/target_candidate)
        CalWeight(target_model,target_candidate);

        // Calculate new postition
        CalShift(next_frame,index);

        // Check how much the new position shifted: if small --> finished iteration
        if(abs(index[0]-target_Region.x)<2 && abs(index[1]-target_Region.y)<2)
        {
        	// Predict next location based on current and past location (measure of speed)
            target_Region.x = (index[0]<<1) - old_pos[0];
            target_Region.y = (index[1]<<1) - old_pos[1];

            // Store current position for future prediction
            old_pos[0] = index[0];
            old_pos[1] = index[1];

            // Return result
            return cv::Rect(index[0],index[1],target_Region.height,target_Region.width);
        }
        else
        {
        	// Set new candidate
            target_Region.x = index[0];
            target_Region.y = index[1];
        }
    }
    return target_Region;
}
