#ifndef MEANSHIFT_H
#define MEANSHIFT_H
#include <iostream>
#include <math.h>
#include <arm_neon.h>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#define PI 3.1415926

typedef struct myModelStruct
{
	float32x4_t at[4][3];
}myModel;
	
class MeanShift
{
 private:
    int bin_width;
    int bin_width_pow;
    int8x8_t bin_width_pow_neon;
    myModel target_model;
    cv::Rect target_Region;
    cv::Mat kernel;

    struct config{
        int num_bins;
        int piexl_range;
        int MaxIter;
    }cfg;

public:
    MeanShift();
    void Init_target_frame(const cv::Mat &frame,const cv::Rect &rect);
    float & kernel_elem(int row, int col, int height, int width);
    float Epanechnikov_kernel(cv::Mat &kernel, int h, int w);
    myModel  pdf_representation(const cv::Mat &frame,const cv::Rect &rect);
    cv::Mat CalWeight(const cv::Mat &frame, float32x4_t &target_model, cv::Mat &target_candidate, cv::Rect &rec);
    cv::Mat CalWeight_opt(const cv::Mat &frame, float32x4_t &target_model, cv::Mat &target_candidate, cv::Rect &rec);
    cv::Rect track(const cv::Mat &next_frame);
};

#endif // MEANSHIFT_H
