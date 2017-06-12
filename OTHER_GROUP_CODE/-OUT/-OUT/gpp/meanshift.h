#ifndef MEANSHIFT_H
#define MEANSHIFT_H
#include <iostream>
#include <math.h>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#define PI 3.1415926
class MeanShift
{
 private:
    int bin_width;
    int bit_shift;
    cv::Rect target_Region;
    int old_pos[2];
    int* target_model;
    int* target_candidate;
    int* kernel;
    int* weights;

    struct config{
        unsigned int num_bins;
        int piexl_range;
        int MaxIter;
    }cfg;

public:
    MeanShift();
    void Init_target_frame(const cv::Mat &frame,const cv::Rect &rect);
    void Epanechnikov_kernel(int* kernel);
    void pdf_representation(const cv::Mat &frame,const cv::Rect &rect, int* pdf);
    void CalWeight(int* target_model, int* target_candidate);
    void CalShift(const cv::Mat &frame,int* index);
    cv::Rect track(const cv::Mat &next_frame);
};

#endif // MEANSHIFT_H
