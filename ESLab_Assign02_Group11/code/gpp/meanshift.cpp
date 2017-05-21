/*
 * Based on paper "Kernel-Based Object Tracking"
 * you can find all the formula in the paper
*/

#include"meanshift.h"
#include "meanshift_portable.h"
#include <limits>
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
void print_mat_int(cv::Mat &mat)
{
    int h = mat.rows;
    int w = mat.cols;
    for (int y=0; y<h; y++) {
        for(int x=0; x<w; x++) {
            std::cout << mat.at<int>(y, x) << " ";
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
}

void  MeanShift::Init_target_frame(const cv::Mat &frame,const cv::Rect &rect)
{
    target_Region = rect;
    float kernel_sum = Epanechnikov_kernel(kernel, rect.height, rect.width);
    kernel *= INT_MAX / kernel_sum; // pre-scale kernel
//    print_mat(kernel);
    kernel.convertTo(kernel, CV_32S);
//    std::cerr << INT_MAX << " max\n";
//    print_mat_int(kernel);
    target_model = pdf_representation(frame,target_Region,0);
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
//    std::cout << "kernel size: " << h << ";" << w << "\n";

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

cv::Mat MeanShift::pdf_representation(const cv::Mat &frame, const cv::Rect &rect, const float init)
{
    cv::Mat pdf_model(3,cfg.num_bins,CV_32S,cv::Scalar(init));

    if (!kernel.isContinuous()) {
        std::cerr << "Error: kernel is not continuous\n";
        return pdf_model;
    }
    if (!frame.isContinuous()) {
        std::cerr << "Error: frame is not continuous\n";
        return pdf_model;
    }

    pdf_representation_inner(
        rect.height,
        rect.width,
        pdf_model.ptr<int>(0),
        pdf_model.ptr<int>(1),
        pdf_model.ptr<int>(2),
        (unsigned char *) (frame.ptr<cv::Vec3b>(rect.y) + rect.x),
        frame.cols,
        kernel.ptr<int>(0),
        kernel.cols,
        bin_width_pow);

    return pdf_model;
}

cv::Rect MeanShift::track(const cv::Mat &next_frame)
{
    int num_bins = cfg.num_bins;

    cv::Mat target_ratio_f(3, num_bins, CV_32F);
    cv::Mat target_ratio(3, num_bins, CV_32S);

    if (!next_frame.isContinuous()) {
        std::cerr << "Error: frame is not continuous\n";
        return target_Region;
    }

    for(int iter=0;iter<cfg.MaxIter;iter++)
    {
        cv::Mat target_candidate = pdf_representation(next_frame,target_Region, 0);
        float max_ratio[3] = {0.0f};
        for (int k=0; k<3; k++)
        {
            for (int b=0; b<num_bins; b++)
            {
                if (target_candidate.at<int>(k, b) == 0) {
                    target_ratio_f.at<float>(k, b) = 0;
                } else {
                    target_ratio_f.at<float>(k, b) = sqrt(target_model.at<int>(k, b)
                                             / target_candidate.at<int>(k, b));
                    max_ratio[k] = std::max(max_ratio[k], target_ratio_f.at<float>(k, b));
                }
            }
        }

        int height = target_Region.height;
        // Loop is limited to a circle with a diameter of height
        int width = std::min(height, target_Region.width);

        float limit = pow((INT_MAX * 2.0f * 4.0f) / (height * height * height * max_ratio[0] * max_ratio[1] * max_ratio[2]), 1.0f / 3.0f);
        float scale = std::max(limit, 0.0f);
        for (int k=0; k<3; k++)
        {
            for (int b=0; b<num_bins; b++)
            {
                target_ratio.at<int>(k, b) = (target_ratio_f.at<float>(k, b) * scale) + 0.5;
            }
        }

        int delta_x = 0;
        int delta_y = 0;

        track_iter_inner(
            height,
            width,
            target_ratio.ptr<int>(0),
            target_ratio.ptr<int>(1),
            target_ratio.ptr<int>(2),
            (unsigned char *) (next_frame.ptr<cv::Vec3b>(target_Region.y) + target_Region.x),
            next_frame.cols,
            bin_width_pow,
            &delta_y,
            &delta_x
        );

        target_Region.y += delta_y;
        target_Region.x += delta_x;

        if((delta_y | delta_x) == 0) {
            break;
        }
    }

    return target_Region;
}
