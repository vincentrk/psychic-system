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
}

void  MeanShift::Init_target_frame(const cv::Mat &frame,const cv::Rect &rect)
{
    target_Region = rect;
    kernel.create(rect.height, rect.width, CV_32F);
    float kernel_sum = Epanechnikov_kernel(kernel);
    kernel /= kernel_sum; // pre-scale kernel
    target_model = pdf_representation(frame,target_Region);
}

float  MeanShift::Epanechnikov_kernel(cv::Mat &kernel)
{
    int h = kernel.rows;
    int w = kernel.cols;

    float epanechnikov_cd = 0.1*PI*h*w;
    float kernel_sum = 0.0;
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            float x = static_cast<float>(i - h/2);
            float  y = static_cast<float> (j - w/2);
            float norm_x = x*x/(h*h/4)+y*y/(w*w/4);
            float result =norm_x<1?(epanechnikov_cd*(1.0-norm_x)):0;
            kernel.at<float>(i,j) = result;
            kernel_sum += result;
        }
    }
    return kernel_sum;
}
cv::Mat MeanShift::pdf_representation(const cv::Mat &frame, const cv::Rect &rect)
{
    cv::Mat pdf_model(8,16,CV_32F,cv::Scalar(1e-10));

    cv::Vec3f curr_pixel_value;
    cv::Vec3f bin_value;

    int row_index = rect.y;
    int clo_index = rect.x;

    for(int i=0;i<rect.height;i++)
    {
        clo_index = rect.x;
        for(int j=0;j<rect.width;j++)
        {
            curr_pixel_value = frame.at<cv::Vec3b>(row_index,clo_index);
            bin_value[0] = (curr_pixel_value[0]/bin_width);
            bin_value[1] = (curr_pixel_value[1]/bin_width);
            bin_value[2] = (curr_pixel_value[2]/bin_width);
            pdf_model.at<float>(0,bin_value[0]) += kernel.at<float>(i,j);
            pdf_model.at<float>(1,bin_value[1]) += kernel.at<float>(i,j);
            pdf_model.at<float>(2,bin_value[2]) += kernel.at<float>(i,j);
            clo_index++;
        }
        row_index++;
    }

    return pdf_model;

}

cv::Rect MeanShift::track(const cv::Mat &next_frame)
{
    cv::Rect next_rect;
    for(int iter=0;iter<cfg.MaxIter;iter++)
    {
        cv::Mat target_candidate = pdf_representation(next_frame,target_Region);

        float delta_x = 0.0;
        float sum_wij = 0.0;
        float delta_y = 0.0;
        float centre = static_cast<float>((target_Region.height-1)/2.0);
//        double mult = 0.0;

        next_rect.x = target_Region.x;
        next_rect.y = target_Region.y;
        next_rect.width = target_Region.width;
        next_rect.height = target_Region.height;

        cv::Vec3f curr_pixel;
        cv::Vec3f bin_value;

        int row_index = target_Region.y;
        for(int i=0;i<target_Region.height;i++)
        {
            float norm_i = static_cast<float>(i-centre)/centre;
            float norm_i_sqr = norm_i*norm_i;
            // since (0 <= i < weight.rows)
            // it follows (-1 <= norm_i <= 1)
            int col_index = target_Region.x;
            for(int j=0;j<target_Region.width;j++)
            {
                float norm_j = static_cast<float>(j-centre)/centre;
//                mult = pow(norm_i,2)+pow(norm_j,2)>1.0?0.0:1.0;
                if (abs(norm_j) <= 1.0 && norm_i_sqr + norm_j * norm_j <= 1.0) {
                    // calculate element of weight matrix (CalWeight)
                    curr_pixel = next_frame.at<cv::Vec3b>(row_index,col_index);
                    bin_value[0] = curr_pixel[0] / bin_width;
                    bin_value[1] = curr_pixel[1] / bin_width;
                    bin_value[2] = curr_pixel[2] / bin_width;
                    float weight = target_model.at<float>(0, bin_value[0])
                             / target_candidate.at<float>(0, bin_value[0]);
                    weight *= target_model.at<float>(1, bin_value[1])
                        / target_candidate.at<float>(1, bin_value[1]);
                    weight = sqrt(
                        weight * target_model.at<float>(2, bin_value[2])
                           / target_candidate.at<float>(2, bin_value[2])
                    );

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
