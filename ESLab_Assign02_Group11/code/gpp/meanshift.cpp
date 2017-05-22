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
    kernel.convertTo(kernel, CV_32S);
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
    int offset_y = 0; //std::max(0, target_Region.y - target_Region.height));
    int offset_x = 0; //std::max(0, target_Region.x - target_Region.width));

    int rect_y = target_Region.y - offset_y;
    int rect_x = target_Region.x - offset_x;

    track_inner(
        target_Region.height,
        target_Region.width,
        (unsigned char *) next_frame.ptr<cv::Vec3b>(0),
        next_frame.cols,
        kernel.ptr<int>(0),
        kernel.cols,
        target_model.ptr<int>(0),
        bin_width_pow,
        cfg.num_bins,
        cfg.MaxIter,
        &rect_y,
        &rect_x
    );

    target_Region.y = rect_y + offset_y;
    target_Region.x = rect_x + offset_x;
    return target_Region;
}
