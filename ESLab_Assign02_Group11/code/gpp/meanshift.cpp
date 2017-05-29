/*
 * Based on paper "Kernel-Based Object Tracking"
 * you can find all the formula in the paper
*/

#include"meanshift.h"
#include "meanshift_portable.h"
#include <limits>
#include <algorithm>
#include <new>
#include <stdexcept>
#include "Timer.h"

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
#ifdef USE_DSP
    // We assume this for communicating with the DSP
    assert(sizeof(int)==4);
    assert(sizeof(int)==sizeof(int *));
#endif
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
        throw std::invalid_argument("Unsupported ratio of piexl_range and num_bins");
    }
}

void  MeanShift::Init_target_frame(const cv::Mat &frame,const cv::Rect &rect)
{
    target_Region = rect;
    float kernel_sum = Epanechnikov_kernel(kernel, rect.height, rect.width);
    kernel *= INT_MAX / kernel_sum; // pre-scale kernel
    kernel.convertTo(kernel, CV_32S);
    target_model = pdf_representation(frame,target_Region,0);

#ifdef USE_DSP
    int * buf = pool_notify_GetBuf();
    unsigned int buf_size = pool_notify_GetSize();

    if ( (unsigned int)
        (7 * sizeof(int)
        + kernel.rows * kernel.cols * sizeof(int)
        + cfg.num_bins * CHANNEL_COUNT * sizeof(int))
        > buf_size
    ) {
        throw std::runtime_error("DSP buffer too small for kernel data");
    }
    buf[0] = MEANSHIFT_MSG_INIT;
    buf[1] = rect.height;
    buf[2] = rect.width;
    buf[3] = kernel.cols;
    buf[4] = bin_width_pow;
    buf[5] = cfg.num_bins;
    buf[6] = cfg.MaxIter;

    memcpy(
        &(buf[7]),
        target_model.ptr<int>(0),
        cfg.num_bins * CHANNEL_COUNT * sizeof(int));

    memcpy(
        &(buf[7 + cfg.num_bins * CHANNEL_COUNT]),
        kernel.ptr<int>(0),
        kernel.rows * kernel.cols * sizeof(int));

    pool_notify_Execute();
    pool_notify_Result();
    if (buf[0] != MEANSHIFT_MSG_SUCCESS) {
        std::cerr << "DSP error code " << buf[1] << "\n";
        throw std::runtime_error("DSP error");
    }

#else
    frame_cut = (unsigned char *) malloc(rect.height * rect.width * 9 * CHANNEL_COUNT);
    if (frame_cut == NULL) {
        std::cerr << "Could not allocate frame_cut buffer\n";
        throw std::bad_alloc();
    }
#endif
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
    cv::Mat pdf_model(CHANNEL_COUNT,cfg.num_bins,CV_32S,cv::Scalar(init));

    if (!kernel.isContinuous()) {
        throw std::runtime_error("Error: kernel is not continuous");
    }
    if (!frame.isContinuous()) {
        throw std::runtime_error("Error: frame is not continuous");
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
    Timer totalTimer("Total Frame");
    Timer acquireTimer("Pool Acquire");
    Timer pFrameTimer("Process Frame");
    int offset_y = std::max(0, target_Region.y - target_Region.height);
    int offset_x = std::max(0, target_Region.x - target_Region.width);
    int size_y = std::min(next_frame.rows - offset_y, target_Region.height * (1+2));
    int size_x = std::min(next_frame.cols - offset_x, target_Region.width * (1+2));

    int rect_y = target_Region.y - offset_y;
    int rect_x = target_Region.x - offset_x;

#ifdef USE_DSP
    totalTimer.Start();
    acquireTimer.Start();
    int * buf = pool_notify_GetBuf();
    unsigned int buf_size = pool_notify_GetSize();

    if ( (unsigned int) (5 * sizeof(int) + size_y * size_x * CHANNEL_COUNT * sizeof(char)) > buf_size) {
        std::cerr << "Need buffer of " << (5 * sizeof(int) + size_y * size_x * CHANNEL_COUNT * sizeof(char)) << "B\n";
        throw std::runtime_error("DSP buffer too small for pixel data");
    }
    buf[0] = MEANSHIFT_MSG_TRACK;
    buf[1] = rect_y;
    buf[2] = rect_x;
    buf[3] = size_x;

    frame_cut = (unsigned char *) (&(buf[4]));
    for (int y=0; y<size_y; y++) {
        memcpy(
            frame_cut + size_x * CHANNEL_COUNT * y,
            next_frame.ptr<cv::Vec3b>(offset_y + y) + offset_x,
            size_x * CHANNEL_COUNT);
    }
    acquireTimer.Stop();
    pFrameTimer.Start();
    pool_notify_Execute();
    pool_notify_Result();
    if (buf[0] != MEANSHIFT_MSG_SUCCESS) {
        std::cerr << "DSP error code " << buf[1] << "\n";
        throw std::runtime_error("DSP error");
    }
    rect_y = buf[1];
    rect_x = buf[2];
    pFrameTimer.Stop();
    totalTimer.Stop();
    totalTimer.Print();
    acquireTimer.Stop();
    pFrameTimer.Stop();
#else
    for (int y=0; y<size_y; y++) {
        memcpy(
            frame_cut + size_x * CHANNEL_COUNT * y,
            next_frame.ptr<cv::Vec3b>(offset_y + y) + offset_x,
            size_x * CHANNEL_COUNT);
    }

    track_inner(
        target_Region.height,
        target_Region.width,
        frame_cut,
        size_x,
        kernel.ptr<int>(0),
        kernel.cols,
        target_model.ptr<int>(0),
        bin_width_pow,
        cfg.num_bins,
        cfg.MaxIter,
        &rect_y,
        &rect_x
    );
#endif

    target_Region.y = rect_y + offset_y;
    target_Region.x = rect_x + offset_x;
    return target_Region;
}
