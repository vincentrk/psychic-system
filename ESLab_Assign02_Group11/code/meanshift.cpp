/*
 * Based on paper "Kernel-Based Object Tracking"
 * you can find all the formula in the paper
*/

#include"meanshift.h"
#include <algorithm>


void print_mat(cv::Mat &mat)
{
    int h = mat.rows;
    int w = mat.cols;
    for (int y=0; y<h; y++) {
        for(int x=0; x<w; x++) {
            std::cout << mat.at<float>(y, x) << " ";
        }
        std::cout << "\n";
    }
}

MeanShift::MeanShift()
{
    cfg.MaxIter = 8;
    cfg.num_bins = 16;
    cfg.piexl_range = 256;
    bin_width = cfg.piexl_range / cfg.num_bins;
    bin_width_pow = 0;
    while (bin_width >>= 1) {
        bin_width_pow++;
    }
    bin_width = cfg.piexl_range / cfg.num_bins;
    if (1 << bin_width_pow != bin_width) {
        std::cerr << "Error: unsupported ratio of piexl_range and num_bins\n";
    }
	bin_width_pow_neon = vneg_s8(vdup_n_s8(bin_width_pow));

}

void  MeanShift::Init_target_frame(const cv::Mat &frame,const cv::Rect &rect)
{
    target_Region = rect;
    float kernel_sum = Epanechnikov_kernel(kernel, rect.height, rect.width);
    kernel /= kernel_sum; // pre-scale kernel
    target_model = pdf_representation(frame,target_Region);
}

float & MeanShift::kernel_elem(int row, int col, int height, int width) {
    int nrow = abs(row - height / 2);
    int ncol = abs(col - width / 2);
    return (kernel.at<float>(nrow, ncol));
}

float  MeanShift::Epanechnikov_kernel(cv::Mat &kernel, int h, int w)
{
    /* Example kernels, with quarter kernel
       0 0 0 0   2 1 0  This needs to keep the zeros
       0 0 1 0   1 0 0
       0 1 2 1   0 0 0
       0 0 1 0

       0 1 0   2 1
       1 2 1   1 0
       0 1 0

       Reading starts from the right of the quarter kernel,
       then turns around on the edge.
     */
    // Halve the size, round up, add one for the zero row
    // (x+1+1)/2 == x/2+1
    kernel.create(h/2+1, w/2+1, CV_32F);
    std::cout << "kernel size: " << h << ";" << w << "\n";

    float kernel_sum = 0.0;
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            float x = static_cast<float>(i - h/2);
            float  y = static_cast<float> (j - w/2);
            float norm_x = x*x/(h*h/4)+y*y/(w*w/4);
            float result =norm_x<1?(1.0-norm_x):0;
            kernel_elem(i, j, h, w) = result;
            kernel_sum += result;
        }
    }
    return kernel_sum;
}

myModel MeanShift::pdf_representation(const cv::Mat &frame, const cv::Rect &rect)
{
//     cv::Mat pdf_model(3,cfg.num_bins,CV_32F,cv::Scalar(1e-10));
	myModel pdf_model;
	
	float32_t plane_a[16];
	float32_t plane_b[16];
	float32_t plane_c[16];
	
	for(int j=0;j<16;j++)
	{
	 	plane_a[j] = 1e-10;
		plane_b[j] = 1e-10;
		plane_c[j] = 1e-10;
	}
    int height = rect.height;
    int width = rect.width;

    int kern_h = height / 2;
    int kern_w = width / 2;
	
//     float * plane_a = pdf_model.ptr<float>(0);
//     float * plane_b = pdf_model.ptr<float>(1);
//     float * plane_c = pdf_model.ptr<float>(2);
	

    if (!kernel.isContinuous()) {
        std::cerr << "Error: kernel is not continuous\n";
        return pdf_model; //TODO Fix this wrong return
    }
    float * kernel_ptr = kernel.ptr<float>(0);
    int kernel_row_size = kernel.cols;

    int row_index = rect.y;
    for(int i=0;i<height;i++)
    {
        int clo_index = rect.x;
        for(int j=0;j<width;j+=2)
        {
            // cv::Vec3b bin_value;
//             cv::Vec3b curr_pixel_value = frame.at<cv::Vec3b>(row_index,clo_index);
            
            uint8x8_t bin_value_n;
            uint8x8_t curr_pixel_value_n;
            curr_pixel_value_n = vld1_u8(& frame.at<cv::Vec3b>(row_index ,clo_index)[0]);


//             bin_value[0] = (curr_pixel_value[0] >> bin_width_pow);
//             bin_value[1] = (curr_pixel_value[1] >> bin_width_pow);
//             bin_value[2] = (curr_pixel_value[2] >> bin_width_pow);

            bin_value_n = vshl_u8(curr_pixel_value_n, bin_width_pow_neon);

            float kernel_element = kernel_ptr[abs(i - kern_h) * kernel_row_size + abs(j - kern_w)];
			float kernel_element_2 = kernel_ptr[abs(i - kern_h) * kernel_row_size + abs(j+1 - kern_w)];

    
			plane_a[vget_lane_u8(bin_value_n,0)] += kernel_element;
            plane_b[vget_lane_u8(bin_value_n,1)] += kernel_element;
            plane_c[vget_lane_u8(bin_value_n,2)] += kernel_element;
            
            
           	plane_a[vget_lane_u8(bin_value_n,3)] += kernel_element_2;
        	plane_b[vget_lane_u8(bin_value_n,4)] += kernel_element_2;
            plane_c[vget_lane_u8(bin_value_n,5)] += kernel_element_2;

      
            
            clo_index+=2;
        }
        row_index++;
    }
	for (int j=0;j<4;j++)
	{
		pdf_model.at[j][0] = vld1q_f32(plane_a + (j*4));
		pdf_model.at[j][1] = vld1q_f32(plane_b + (j*4));
		pdf_model.at[j][2] = vld1q_f32(plane_c + (j*4));
	}

		
    return pdf_model;
}

//Some Neon Intrisincs Copied from pmeerw.net

// approximative quadword float inverse square root
static inline float32x4_t invsqrtv(float32x4_t x) {
    float32x4_t sqrt_reciprocal = vrsqrteq_f32(x);
    sqrt_reciprocal = vrsqrtsq_f32(x * sqrt_reciprocal, sqrt_reciprocal) * sqrt_reciprocal;
    sqrt_reciprocal = vrsqrtsq_f32(x * sqrt_reciprocal, sqrt_reciprocal) * sqrt_reciprocal;
	sqrt_reciprocal = vrsqrtsq_f32(x * sqrt_reciprocal, sqrt_reciprocal) * sqrt_reciprocal;

    return sqrt_reciprocal;
}
        
// approximative quadword float square root
static inline float32x4_t sqrtv(float32x4_t x) {
    return x * invsqrtv(x);
}
            
// approximative quadword float inverse
static inline float32x4_t invv(float32x4_t x) {
    float32x4_t reciprocal = vrecpeq_f32(x);
    reciprocal = vrecpsq_f32(x, reciprocal) * reciprocal;
    reciprocal = vrecpsq_f32(x, reciprocal) * reciprocal;
    reciprocal = vrecpsq_f32(x, reciprocal) * reciprocal;
    reciprocal = vrecpsq_f32(x, reciprocal) * reciprocal;

                            
    return reciprocal;
}
                                    
// approximative quadword float division
static inline float32x4_t divv(float32x4_t x, float32x4_t y) {
//     float32x4_t reciprocal = vrecpeq_f32(y);
//     reciprocal = vrecpsq_f32(y, reciprocal) * reciprocal;
                                                
    return x * invv(y);
}

// accumulate four quadword floats
static inline float accumv(float32x4_t x) {
    static const float32x2_t f0 = vdup_n_f32(0.0f);
    return vget_lane_f32(vpadd_f32(f0, vget_high_f32(x) + vget_low_f32(x)), 1);
}

cv::Rect MeanShift::track(const cv::Mat &next_frame)
{
    int num_bins = cfg.num_bins;

//     cv::Mat target_ratio(3, num_bins, CV_32F);
	myModel target_ratio;
    cv::Rect next_rect;
	float32_t plane[16][3];

    if (!next_frame.isContinuous()) {
        std::cerr << "Error: frame is not continuous\n";
        return next_rect;
    }
    
    for(int iter=0;iter<cfg.MaxIter;iter++)
    {
        myModel target_candidate;
        target_candidate = pdf_representation(next_frame,target_Region);
        for (int k=0; k<3; k++)
        {
            for (int b=0; b<num_bins/4; b++)
            {
                // target_ratio.at<float>(k, b) = sqrt(target_model.at<float>(k, b)
//                                          / target_candidate.at<float>(k, b));

				target_ratio.at[b][k] = 	divv(sqrtv(target_model.at[b][k]),target_candidate.at[b][k]);
				
				 vst1q_f32(& plane[b*4][k], target_ratio.at[b][k]);
				
            }
        }
		
		
		
        float delta_x = 0.0;
        float sum_wij = 0.0;
        float delta_y = 0.0;
        float centre = static_cast<float>((target_Region.height-1)/2.0);

        next_rect.x = target_Region.x;
        next_rect.y = target_Region.y;
        next_rect.width = target_Region.width;
        next_rect.height = target_Region.height;

        int height = target_Region.height;
        // Loop is limited to a circle with a diameter of height
        int width = std::min(height, target_Region.width);

        

        int row_index = target_Region.y;
        for(int i=0;i<height;i++)
        {
            float norm_i = static_cast<float>(i-centre)/centre;
            float norm_i_sqr = norm_i*norm_i;
            const cv::Vec3b * pixels = next_frame.ptr<cv::Vec3b>(row_index) + target_Region.x;
//             const uint8_t * pixels_n = next_frame.ptr<cv::Vec3b>(row_index) + target_Region.x;

            for(int j=0;j<width;j++)
            {
                float norm_j = static_cast<float>(j-centre)/centre;
                if (norm_i_sqr + norm_j * norm_j <= 1.0) {
                    // calculate element of weight matrix (CalWeight)
                    cv::Vec3b bin_value;
                    cv::Vec3b curr_pixel = pixels[j];
//                     uint8x8_t bin_value_n;
//             		uint8x8_t curr_pixel_value_n;
//            			curr_pixel_value_n = vld1_u8(& next_frame.at<cv::Vec3b>(row_index, j + target_Region.x)[0]);
                    //BoopNeon
                    
//                     bin_value_n = vshl_u8(curr_pixel_value_n, bin_width_pow_neon);

                    bin_value[0] = curr_pixel[0] >> bin_width_pow;
                    bin_value[1] = curr_pixel[1] >> bin_width_pow;
                    bin_value[2] = curr_pixel[2] >> bin_width_pow;
           //          float weight = (
//                               plane[vget_lane_u8(bin_value_n,0)][0]
//                             * plane[vget_lane_u8(bin_value_n,1)][1]
//                             * plane[vget_lane_u8(bin_value_n,2)][2]);


					 float weight = (
                              plane[bin_value[0]][0]
                            * plane[bin_value[1]][1]
                            * plane[bin_value[2]][2]);
					

                    delta_x += static_cast<float>(norm_j * weight);
                    delta_y += static_cast<float>(norm_i * weight);
                    sum_wij += static_cast<float>(weight);
                }
            }
            row_index++;
        }

        next_rect.x += static_cast<int>((delta_x/sum_wij)*centre);
        next_rect.y += static_cast<int>((delta_y/sum_wij)*centre);

        if(abs(next_rect.x-target_Region.x)<1 && abs(next_rect.y-target_Region.y)<1)
        {
            break;
        }
        else
        {
            target_Region.x = next_rect.x;
            target_Region.y = next_rect.y;
        }
    }

    return next_rect;
}
