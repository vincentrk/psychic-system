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

#include "config.h"
//#define DSP_CALSHIFT
//#define DSP_CALSHIFT_PARTIAL 3

//Scales to that make integer usages possible
#define SCALE 16777216
#define SCALE_SHIFT  24

#define SCALE2 8192
#define SCALE2_SHIFT 13


extern Timer trackTimer;

typedef Int32 __attribute__((__may_alias__)) Int32_alias;
typedef unsigned char __attribute__((__may_alias__)) uchar_alias;


#ifdef NEON_MEMCPY
static inline int neon_memcpy(volatile unsigned char *dst, volatile unsigned char *src, size_t size)
{
    /* NEON needs 4 Byte alligned addresses */
    int offset = (unsigned long)src % 4;
    switch (offset) {
        case 1:
            dst[1] = *src++;
        case 2:
            dst[2] = *src++;
        case 3:
            dst[3] = *src++;
    }
    dst = &dst[4];
    size -=offset;

    /* We move 64 bytes at a time, split the size into a % 64 size 
     * We don't want to make the MMU angry by moving move and not caring,
     * (although it would probably go unnoticed).
     */
    int rem = size % 64;
    if (rem > 0) {
        size = size - rem;
    }

    //"    PLD [%[src], #0xC0]                            \n"
    asm volatile (
            "NEONCopy%=:                                        \n"
            "    VLDM %[src]!,{d0-d7}                           \n"
            "    VSTM %[dst]!,{d0-d7}                           \n"
            "    SUBS %[size],%[size],#0x40                     \n"
            "    BGT NEONCopy%=                                 \n"
            : [dst]"+r"(dst), [src]"+r"(src), [size]"+r"(size)
            :
            : "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "cc", "memory"
            );

    while (rem--) {
        dst[size+rem] = src[size+rem];
    }

    return offset;
}
#endif


MeanShift::MeanShift()
{
    cfg.MaxIter = 8;
    cfg.num_bins = 16;		// Will be rounded up towards the nearest power of 2 (allow bitshift) minimum = 2
    cfg.piexl_range = 256;
    bin_width = cfg.piexl_range / cfg.num_bins;

    bit_shift = floor(log(bin_width)/log(2));
    bin_width = pow(2,bit_shift);
    cfg.num_bins = cfg.piexl_range / bin_width;
}

void  MeanShift::Init_target_frame(const cv::Mat &frame)
{    
	//Initiate private variables
    int pdf_size = cfg.num_bins*3;
    target_model = new int [pdf_size];
	kernel = new int [target_Region[2]*target_Region[3]];

    // Set past position
    old_pos[0] = target_Region[0];
    old_pos[1] = target_Region[1];

    // Calculate kernel
    trackTimer.Start();
    Epanechnikov_kernel();
    trackTimer.Pause();

    // Calculate taget model
    pdf_representation(frame,target_model);
}

void  MeanShift::Epanechnikov_kernel()
{
	// Init
    int w = target_Region[2];
    int h = target_Region[3];
    int h2 = h*h;
    int w2 = w*w;

    // Kernel contstant for immediate normalisation
    float normalized_C = (h*w*0.392699081687683)/SCALE;

    // Loop trough kernel vector
    for(int i=0;i<h;i++)
    {
    	// Offset for kernel position (vector)
    	int offset_ker = i * w;

    	// x-Position with respect to centre (x2)
    	int x = (i<<1) - h;

        for(int j=0;j<w;j++)
        {
        	// y-Position with respect to centre (x2)
            int y = (j<<1) - w;

            // Set kernel value
            float norm_x = static_cast<float>(x*x)/h2+static_cast<float>(y*y)/w2;
            kernel[offset_ker+j] = (norm_x<1?((1.0-norm_x)/normalized_C):0);
        }
    }
    return;
}

void MeanShift::pdf_representation(const cv::Mat &frame,int* pdf)
{
    // Clean content of pdf
    memset(pdf, 0, (cfg.num_bins*3)*sizeof(*pdf));

    // Prepare offset value for pdf location
    unsigned int offset_pdf [] = {cfg.num_bins, cfg.num_bins<<1};

    // Location of rectangle in total frame
    int clo_index = target_Region[0];
    int row_index = target_Region[1];
    int w = target_Region[2];
    int h = target_Region[3];
    

    // Loop trough target
    for(int i=0;i<h;i++)
    {
    	// Offset for kernel
        int offset_ker = i*w;

        // Read the frame as a pointer to speed up reading by not using 'at'
        const unsigned char *frame_data = frame.ptr<unsigned char>(row_index + i);

        for(int j=0;j<w;j++)
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

void MeanShift::CalWeight(int* target_model,int* target_candidate,int* weights)
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
            weights[i] = static_cast<int>(sqrt(static_cast<float>(target_model[i])/target_candidate[i])*SCALE2);
        }
    }
    return;
}

void MeanShift::CalShift(const cv::Mat &frame,int* location,int* weights)
{
    // Init
    Int32 delta_x = 0;  
    Int32 sum_wij = 0;
    Int32 delta_y = 0;


    int clo_index = location[0];
    int row_index = location[1];
    int w = target_Region[2];
    int h = target_Region[3];
    
    // Set offset for weight vector
    Uint32 offset_w [] = {cfg.num_bins, cfg.num_bins<<1};

    // Set postion of centre (x2)
    Int32 centre = h-1;

    // Set check value for SCALED normalized position check
    int check = (centre*centre);

    // Loop trough target matrix
    for(int i=0;i<h;i++)
    {
        // Set weight to zero and y-position with respect to centre (x2)
        int weight_tmp_i = 0;
        int norm_i = (i<<1) - centre;

        // Read the frame as a pointer to speed up reading by not using 'at'
        const unsigned char *frame_data = frame.ptr<unsigned char>(row_index + i);

#if defined(DSP_CALSHIFT)

        /* Get shared memory pointer */
        char *shmem = pool_notify_GetSharedMem();
        uchar_alias *shmem_pixels;
        Int32_alias *shmem_pdf;
        Int32_alias *shmem32 = (Int32_alias *)shmem;
        int length_pixel = 0;

        shmem_pixels = (unsigned char *)&shmem32[IDX_PIXEL_START];

#if defined(DSP_CALSHIFT_PARTIAL)
        int partial = (w / DSP_CALSHIFT_PARTIAL);
        //partial = partial - (partial % 2);
        length_pixel = (partial * 3) * sizeof(unsigned char);
#else
        /* Copy the frame data to shared memory */
        length_pixel = (w * 3) * sizeof(unsigned char);
#endif

        memcpy(shmem_pixels, &frame_data[clo_index * 3], length_pixel);

        /* Fill in meta data into shared memory */
        shmem32[IDX_PIXEL_LENGTH] = (uint32_t)length_pixel; // The length of pixel data
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

        shmem_pdf = &shmem32[IDX_PIXEL_START + ((length_pixel+4) / sizeof(int))];

        /* Copy the PDF into shared memory */
        memcpy(shmem_pdf, weights, (3 * cfg.num_bins) * sizeof(Int32));

        /* Notify DSP to start */
        pool_notify_NotifySharedMem(IDX_PIXEL_START * sizeof(Int32) + length_pixel + 4 + (3 * cfg.num_bins) * sizeof(Int32));

        weight_tmp_i = 0;
        delta_x = 0; // Needed here because the dsp continues with the delta (+=)

#if defined(DSP_CALSHIFT_PARTIAL) /* Do the GPP part if partial is defined */
        for(int j=partial;j<w;j++)
        {
            // Set x-position with respect to centre (x2)
            int32_t norm_j = (j<<1) - centre;

            // Check if current position is within circle that fits in target box
            if(norm_i*norm_i + norm_j*norm_j < check)
            {
                // Get uchar colour vector
                const unsigned char *curr_pixel = &frame_data[(clo_index + j)*3];

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
        /* Wait for DSP to be done */
        pool_notify_WaitDSP();

        /* Read the result */
        delta_x += (Int32)shmem32[IDX_DELTA_X_RES];
        // Accumulate weights
        weight_tmp_i += (Int32)shmem32[IDX_WEIGHT_I_RES];

        (void)check; /* Prevent compiler warning */

#else /* GPP Only */

        for(int j=0;j<w;j++)
        {
            // Set x-position with respect to centre (x2)
            int32_t norm_j = (j<<1) - centre;

            // Check if current position is within circle that fits in target box
            if(norm_i*norm_i + norm_j*norm_j < check)
            {
                // Get uchar colour vector
                const unsigned char *curr_pixel = &frame_data[(clo_index + j)*3];

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
 
        // Calculate shift in y-direction
        delta_y += weight_tmp_i*norm_i;
        // Accumulate weights
        sum_wij += weight_tmp_i;
    }

    // Set resulting location
    location[0] += (delta_x>>1)/sum_wij;
    location[1] += (delta_y>>1)/sum_wij;
    return;
}

cv::Rect MeanShift::track(const cv::Mat &next_frame)
{
	// Set beginning location
	int location [] = {target_Region[0], target_Region[1]};

	// Loop throught iterations
    for(int iter=0;iter<cfg.MaxIter;iter++)
    {
        //trackTimer.Start();
    	// Calculate pdf of target candidate
        int target_candidate[cfg.num_bins*3];
        pdf_representation(next_frame,target_candidate);
        //trackTimer.Pause();
        //trackTimer.Start();
        // Prepare weight summation by sqrt(target_model/target_candidate)
        int weights[cfg.num_bins*3];
        CalWeight(target_model,target_candidate,weights);
        //trackTimer.Pause();
        //trackTimer.Start();
        // Calculate new postition
        CalShift(next_frame,location,weights);
        //trackTimer.Pause();

        // Check how much the new position shifted: if small --> finished iteration
        if(abs(location[0]-target_Region[0])<2 && abs(location[1]-target_Region[1])<2)
        {
        	// Predict next location based on current and past location (measure of speed)
            target_Region[0] = (location[0]<<1) - old_pos[0];
            target_Region[1] = (location[1]<<1) - old_pos[1];

            // Store current position for future prediction
            old_pos[0] = location[0];
            old_pos[1] = location[1];

            return cv::Rect(target_Region[0],target_Region[1],target_Region[2],target_Region[3]);
        }
        else
        {
        	// Set new candidate
            target_Region[0] = location[0];
            target_Region[1] = location[1];
        }
    }
    return cv::Rect(target_Region[0],target_Region[1],target_Region[2],target_Region[3]);
}
