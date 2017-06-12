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
    int old_pos[2];
    int* target_model;
    int* kernel;

    struct config{
        unsigned int num_bins;
        int piexl_range;
        int MaxIter;
    }cfg;

public:
    int target_Region[4];
    MeanShift();
    void Init_target_frame(const cv::Mat &frame);
    void Epanechnikov_kernel();
    void pdf_representation(const cv::Mat &frame, int* pdf);
    void CalWeight(int* target_model, int* target_candidate,int* weights);
    void CalShift(const cv::Mat &frame,int* index,int* weights);
    cv::Rect track(const cv::Mat &next_frame);
};

#endif // MEANSHIFT_H
