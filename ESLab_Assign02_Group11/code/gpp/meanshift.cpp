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
//    std::cerr << "entering pdf_representation()\n";
    cv::Mat pdf_model(3,cfg.num_bins,CV_32S,cv::Scalar(init));

    int height = rect.height;
    int width = rect.width;

    int kern_h = height / 2;
    int kern_w = width / 2;

    int * plane_a = pdf_model.ptr<int>(0);
    int * plane_b = pdf_model.ptr<int>(1);
    int * plane_c = pdf_model.ptr<int>(2);

    if (!kernel.isContinuous()) {
        std::cerr << "Error: kernel is not continuous\n";
        return pdf_model;
    }
    if (!frame.isContinuous()) {
        std::cerr << "Error: frame is not continuous\n";
        return pdf_model;
    }

    const int * kernel_ptr = kernel.ptr<int>(0);
    int kernel_row_size = kernel.cols;

    pdf_representation_inner(
    height,
    width,
    plane_a,
    plane_b,
    plane_c,
    kernel_ptr,
    kernel_row_size,
    (unsigned char *) (frame.ptr<cv::Vec3b>(rect.y) + rect.x),
    frame.cols,
    bin_width_pow);

//    return pdf_model;

    int row_index = rect.y;
    for(int i=0;i<height;i++)
    {
        int clo_index = rect.x;
        for(int j=0;j<width;j++)
        {
            cv::Vec3b bin_value;
            cv::Vec3b curr_pixel_value = frame.at<cv::Vec3b>(row_index,clo_index);
            bin_value[0] = (curr_pixel_value[0] >> bin_width_pow);
            bin_value[1] = (curr_pixel_value[1] >> bin_width_pow);
            bin_value[2] = (curr_pixel_value[2] >> bin_width_pow);
            int kernel_element = kernel_ptr[abs(i - kern_h) * kernel_row_size + abs(j - kern_w)];
            int val_a = plane_a[bin_value[0]];
            int val_b = plane_b[bin_value[1]];
            int val_c = plane_c[bin_value[2]];
            plane_a[bin_value[0]] = val_a + kernel_element;
            plane_b[bin_value[1]] = val_b + kernel_element;
            plane_c[bin_value[2]] = val_c + kernel_element;
            clo_index++;
        }
        row_index++;
    }
//    std::cerr << "leaving pdf_representation()\n";
    return pdf_model;

}

cv::Rect MeanShift::track(const cv::Mat &next_frame)
{
    int num_bins = cfg.num_bins;

    cv::Mat target_ratio_f(3, num_bins, CV_32F);
    cv::Mat target_ratio(3, num_bins, CV_32S);
    cv::Rect next_rect;

    if (!next_frame.isContinuous()) {
        std::cerr << "Error: frame is not continuous\n";
        return next_rect;
    }

    for(int iter=0;iter<cfg.MaxIter;iter++)
    {
        cv::Mat target_candidate = pdf_representation(next_frame,target_Region, 0);
        float max_ratio[3] = {0.0f};
//        std::cerr << "calculating ratio\n";
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
//        std::cerr << "scaling...\n";

        int height = target_Region.height;
        // Loop is limited to a circle with a diameter of height
        int width = std::min(height, target_Region.width);

        float limit = pow((INT_MAX * 2.0f * 4.0f) / (height * height * height * max_ratio[0] * max_ratio[1] * max_ratio[2]), 1.0f / 3.0f);
        float scale = std::max(limit, 0.0f);
//        std::cerr << "max: " << max_ratio << " scale: " << scale << " limit: " << limit << "\n";
        for (int k=0; k<3; k++)
        {
            for (int b=0; b<num_bins; b++)
            {
//                std::cerr << "ratioF: " << target_ratio_f.at<float>(k, b) << "\n";
                target_ratio.at<int>(k, b) = (target_ratio_f.at<float>(k, b) * scale) + 0.5;
//                std::cerr << "ratioI: " << target_ratio.at<int>(k, b) << "\n";
            }
        }
//        std::cerr << "converted\n";

        int delta_x = 0;
        int sum_wij = 0;
        int delta_y = 0;
        int centre = ((height-1)/2); // Half pixel error

        int * plane_a = target_ratio.ptr<int>(0);
        int * plane_b = target_ratio.ptr<int>(1);
        int * plane_c = target_ratio.ptr<int>(2);

        // Set up data for DSP
/*        unsigned int buf_size = pool_notify_GetSize();
        int   * bufi = pool_notify_GetBuf();
        float * buff = (float *) bufi;

        unsigned int need =
                   sizeof(int)  * 3
                 + sizeof(float)* 1
                 + sizeof(float)* 3 * cfg.num_bins
                 + sizeof(char) * 4 * height * width;
        if (buf_size < need) {
            std::cout << "Error: buffer size too small, need " << need << "\n";
            return next_rect;
        }

        // input: dimensions, bins, bin_width, target_ratio, frame-cutout
        // assume float, int are 32 bits
        int n = 0;
        bufi[n++] = height;
        bufi[n++] = width;
        bufi[n++] = cfg.num_bins;
        buff[n++] = bin_width;
        for (int k=0; k<3; k++) {
            for (int b=0; b<cfg.num_bins; b++) {
                buff[n++] = target_ratio.at<float>(k, b);
            }
        }
        unsigned char * buf_frame = (unsigned char *) &bufi[n];
        int row_index = target_Region.y;
        for (int i=0; i<height; i++) {
            int col_index = target_Region.x;
            for (int j=0; j<width; j++) {
                cv::Vec3b curr_pixel = next_frame.at<cv::Vec3b>(row_index, col_index);
                buf_frame[n++] = curr_pixel[0];
                buf_frame[n++] = curr_pixel[1];
                buf_frame[n++] = curr_pixel[2];
            }
        }

        pool_notify_Execute();
*/
        int row_index = target_Region.y;
        for(int i=0;i<height;i++)
        {
            int norm_i = (i-centre);
            int norm_i_sqr = norm_i*norm_i;
            const cv::Vec3b * pixels = next_frame.ptr<cv::Vec3b>(row_index) + target_Region.x;
            for(int j=0;j<width;j++)
            {
//               std::cerr << "loop\n";
                int norm_j = (j-centre);
                if (norm_i_sqr + norm_j * norm_j <= centre * centre) {
                    // calculate element of weight matrix (CalWeight)
                    cv::Vec3b bin_value;
                    cv::Vec3b curr_pixel = pixels[j];
                    bin_value[0] = curr_pixel[0] >> bin_width_pow;
                    bin_value[1] = curr_pixel[1] >> bin_width_pow;
                    bin_value[2] = curr_pixel[2] >> bin_width_pow;
                    int weight = (
                              plane_a[bin_value[0]]
                            * plane_b[bin_value[1]]
                            * plane_c[bin_value[2]]);
//                    std::cerr << "weight: " << weight << "\n";
//                    if (weight == 0) {
//                        std::cerr << "ZERO: " << i << "," << j << " bin: " << ((int)bin_value[0]) << " " << ((int)bin_value[1]) << " " << ((int)bin_value[2]) << "\n";
//                    }
                    delta_x += (norm_j * weight);
                    delta_y += (norm_i * weight);
//                    if (sum_wij >= INT_MAX - weight) {
//                        std::cerr << "overflow on sum_wij\n";
//                    }
                    sum_wij += (weight);
                }
            }
            row_index++;
        }
//        std::cerr << "sums: " << delta_x << " " << delta_y << " " << sum_wij << "\n";
//        std::cerr << "done\n";

        next_rect.x = target_Region.x;
        next_rect.y = target_Region.y;
        next_rect.width = target_Region.width;
        next_rect.height = target_Region.height;

//        pool_notify_Result();

        //next_rect.x += static_cast<int>((delta_x/sum_wij)*centre);
        //next_rect.y += static_cast<int>((delta_y/sum_wij)*centre);
        //next_rect.x += static_cast<int>(buff[1]);
        //next_rect.y += static_cast<int>(buff[2]);

        if (sum_wij != 0) {
            next_rect.x += ((delta_x/sum_wij));
            next_rect.y += ((delta_y/sum_wij));
        }

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
