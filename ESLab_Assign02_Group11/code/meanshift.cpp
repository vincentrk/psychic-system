/*
 * Based on paper "Kernel-Based Object Tracking"
 * you can find all the formula in the paper
*/

#include"meanshift.h"

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
    bin_width= 1/ bin_width;
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
cv::Mat MeanShift::pdf_representation(const cv::Mat &frame, const cv::Rect &rect)
{
    cv::Mat pdf_model(3,cfg.num_bins,CV_32F,cv::Scalar(1e-10));

    int height = rect.height;
    int width = rect.width;

    int kern_h = height / 2;
    int kern_w = width / 2;

    float * plane_a = pdf_model.ptr<float>(0);
    float * plane_b = pdf_model.ptr<float>(1);
    float * plane_c = pdf_model.ptr<float>(2);

    int row_index = rect.y;
    for(int i=0;i<height;i++)
    {
        int clo_index = rect.x;
        for(int j=0;j<width;j++)
        {
            cv::Vec3b bin_value;
            cv::Vec3b curr_pixel_value = frame.at<cv::Vec3b>(row_index,clo_index);
            bin_value[0] = (curr_pixel_value[0]*bin_width);
            bin_value[1] = (curr_pixel_value[1]*bin_width);
            bin_value[2] = (curr_pixel_value[2]*bin_width);
            float kernel_element = kernel.at<float>(abs(i - kern_h), abs(j - kern_w));
            plane_a[bin_value[0]] += kernel_element;
            plane_b[bin_value[1]] += kernel_element;
            plane_c[bin_value[2]] += kernel_element;
            clo_index++;
        }
        row_index++;
    }

    return pdf_model;

}

cv::Rect MeanShift::track(const cv::Mat &next_frame)
{
    cv::Mat target_ratio(3, cfg.num_bins, CV_32F);
    cv::Rect next_rect;

    for(int iter=0;iter<cfg.MaxIter;iter++)
    {
        cv::Mat target_candidate = pdf_representation(next_frame,target_Region);
        for (int k=0; k<3; k++)
        {
            for (int b=0; b<cfg.num_bins; b++)
            {
                target_ratio.at<float>(k, b) = target_model.at<float>(k, b)
                                         / target_candidate.at<float>(k, b);
            }
        }

        float delta_x = 0.0;
        float sum_wij = 0.0;
        float delta_y = 0.0;
        float centre = static_cast<float>((target_Region.height-1)/2.0);
//        double mult = 0.0;

        next_rect.x = target_Region.x;
        next_rect.y = target_Region.y;
        next_rect.width = target_Region.width;
        next_rect.height = target_Region.height;

        int height = target_Region.height;
        int width = target_Region.width;

        float * plane_a = target_ratio.ptr<float>(0);
        float * plane_b = target_ratio.ptr<float>(1);
        float * plane_c = target_ratio.ptr<float>(2);

        int row_index = target_Region.y;
        for(int i=0;i<height;i++)
        {
            float norm_i = static_cast<float>(i-centre)/centre;
            float norm_i_sqr = norm_i*norm_i;
            // since (0 <= i < weight.rows)
            // it follows (-1 <= norm_i <= 1)
            int col_index = target_Region.x;
            for(int j=0;j<width;j++)
            {
                float norm_j = static_cast<float>(j-centre)/centre;
//                mult = pow(norm_i,2)+pow(norm_j,2)>1.0?0.0:1.0;
                if (norm_j > 1.0) {
                    // norm_j grows lineairly with j, so it will be "too big" for the rest of the loop
                    break;
                }
                if (norm_i_sqr + norm_j * norm_j <= 1.0) {
                    // calculate element of weight matrix (CalWeight)
                    cv::Vec3b bin_value;
                    // uint8x16_t bin_value, curr_pixel;
                    // vld1q_u8(next_frame.ptr);
                    cv::Vec3b curr_pixel = next_frame.at<cv::Vec3b>(row_index,col_index);
                    bin_value[0] = curr_pixel[0] * bin_width;
                    bin_value[1] = curr_pixel[1] * bin_width;
                    bin_value[2] = curr_pixel[2] * bin_width;
                    float weight = sqrt(
                              plane_a[bin_value[0]]
                            * plane_b[bin_value[1]]
                            * plane_c[bin_value[2]]);

                    delta_x += static_cast<float>(norm_j * weight);
                    delta_y += static_cast<float>(norm_i * weight);
                    sum_wij += static_cast<float>(weight);
                }
                col_index++;
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
