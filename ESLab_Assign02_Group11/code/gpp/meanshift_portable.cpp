#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "meanshift_portable.h"

#ifndef DSP_COMPILER
#include <iostream>
#endif


#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

void pdf_representation_inner(
    int height,
    int width,
#ifdef DSP_COMPILER
    int * restrict pdf_a,
    int * restrict pdf_b,
    int * restrict pdf_c,
    const unsigned char * restrict pixels,
    int pixel_stride,
    const int * restrict kernel,
#else
    int * __restrict__ pdf_a,
    int * __restrict__ pdf_b,
    int * __restrict__ pdf_c,
    const unsigned char * __restrict__ pixels,
    int pixel_stride,
    const int * __restrict__ kernel,
#endif
    int kernel_row_size,
    int bin_width_pow
)
{
    int i, j;
    int pixel_skip = (pixel_stride - width) * 3;
    int kern_h = height / 2;
    int kern_w = width / 2;

#ifndef DSP_COMPILER
/*    std::cerr << "pdf_rep: "
        << height << "\n"
        << width << "\n"
        << pdf_a << "\n"
        << pdf_b << "\n"
        << pdf_c << "\n"
        << (const int *)pixels << "\n"
        << pixel_stride << "\n"
        << kernel << "\n"
        << kernel_row_size << "\n"
        << bin_width_pow << "\n"
        << "===\n";*/
#endif

    for(i=0; i < height; i++) {
        for(j=0; j < width; j++) {
            unsigned char bin_value_a, bin_value_b, bin_value_c;
            int val_a, val_b, val_c;
            int kernel_element;
            bin_value_a = (*pixels++) >> bin_width_pow;
            bin_value_b = (*pixels++) >> bin_width_pow;
            bin_value_c = (*pixels++) >> bin_width_pow;
            kernel_element = kernel[abs(i - kern_h) * kernel_row_size + abs(j - kern_w)];
            val_a = pdf_a[bin_value_a];
            val_b = pdf_b[bin_value_b];
            val_c = pdf_c[bin_value_c];
            pdf_a[bin_value_a] = val_a + kernel_element;
            pdf_b[bin_value_b] = val_b + kernel_element;
            pdf_c[bin_value_c] = val_c + kernel_element;
        }
        pixels += pixel_skip;
    }
}

void track_iter_inner(
    const int height,
    int width,
#ifdef DSP_COMPILER
    const int * restrict ratio_a,
    const int * restrict ratio_b,
    const int * restrict ratio_c,
    const unsigned char * restrict pixels,
#else
    const int * __restrict__ ratio_a,
    const int * __restrict__ ratio_b,
    const int * __restrict__ ratio_c,
    const unsigned char * __restrict__ pixels,
#endif
    const int pixel_stride,
    const int bin_width_pow,
    int * result_y,
    int * result_x
) {
    int i, j;
    int pixel_skip;
    int delta_x = 0;
    int delta_y = 0;
    int sum_wij = 0;
    int centre = ((height-1)/2); // Half pixel error

    width = MIN(height, width); // Loop is limited to a circle with a diameter of height
    pixel_skip = (pixel_stride - width) * 3;

#ifndef DSP_COMPILER
/*    std::cerr << "track_iter: "
        << height << "\n"
        << width << "\n"
        << ratio_a << "\n"
        << ratio_b << "\n"
        << ratio_c << "\n"
        << (const int *) pixels << "\n"
        << pixel_stride << "\n"
        << bin_width_pow << "\n"
        << "===\n";

    std::cerr << "ratios:\n";
    for (i=0; i < 16; i++) {
        std::cerr << ratio_a[i] << " ";
        std::cerr << ratio_b[i] << " ";
        std::cerr << ratio_c[i] << "\n";
    }*/
#endif

    for(i=0; i < height; i++) {
        int norm_i = (i - centre);
        int norm_i_sqr = norm_i * norm_i;
        for(j=0; j < width; j++) {
            int norm_j = (j-centre);
#ifndef DSP_COMPILER
//            std::cerr << "coord: (" << i << "," << j << ") (" << norm_i << "," << norm_j << ")\n";
//            std::cerr << "pixel: " << (const int *) pixels << " : " << (const int) (*pixels) << "\n";
#endif
            if (norm_i_sqr + norm_j * norm_j <= centre * centre) {
                // calculate element of weight matrix (CalWeight)
                unsigned char bin_value_a, bin_value_b, bin_value_c;
                int weight;
                bin_value_a = (*(pixels + 0)) >> bin_width_pow;
                bin_value_b = (*(pixels + 1)) >> bin_width_pow;
                bin_value_c = (*(pixels + 2)) >> bin_width_pow;
                weight = (
                          ratio_a[bin_value_a]
                        * ratio_b[bin_value_b]
                        * ratio_c[bin_value_c]);
#ifndef DSP_COMPILER
//                std::cerr << "weight: (" << weight << ", " << (int) bin_value_a << ", " << ratio_a[bin_value_a] << ", " << norm_j << ")\n";
#endif
                delta_x += norm_j * weight;
                delta_y += norm_i * weight;
                sum_wij += weight;
            } else {
#ifndef DSP_COMPILER
//                std::cerr << "else\n";
#endif
            }
            pixels += 3;
        }
        pixels += pixel_skip;
    }
    *result_y = (delta_y/sum_wij);
    *result_x = (delta_x/sum_wij);
#ifndef DSP_COMPILER
//    std::cerr << "sums: (" << delta_y << ", " << delta_x << ", " << sum_wij << ")\n";
//    std::cerr << "result: (" << *result_y << "," << *result_x << ")\n";
#endif
}

void track_inner(
    const int height,
    const int width,
#ifdef DSP_COMPILER
    const unsigned char * restrict pixels,
    const int pixel_stride,
    const int * restrict kernel,
    const int kernel_row_size,
    const int * restrict target_model,
#else
    const unsigned char * __restrict__ pixels,
    const int pixel_stride,
    const int * __restrict__ kernel,
    const int kernel_row_size,
    const int * __restrict__ target_model,
#endif
    const int bin_width_pow,
    const int bins_num,
    const int iter_max,
    int * rect_y,
    int * rect_x
) {
    const int pdf_size = 3 * bins_num * sizeof(int);
    int * target_candidate = (int *) malloc(pdf_size);
    int * target_ratio = (int *) malloc(pdf_size);

    int iter;
    for(iter=0; iter < iter_max; iter++) {
#ifndef DSP_COMPILER
//        std::cerr << iter << "iteration\n";
#endif
        int k;
        int index;
        float max_ratio[3] = {0.0f};
        float ratio_scale;

        int delta_y = 0;
        int delta_x = 0;

        memset(target_candidate, 0, pdf_size);
        pdf_representation_inner(
            height,
            width,
            target_candidate,
            target_candidate + bins_num,
            target_candidate + bins_num * 2,
            pixels + (pixel_stride * (*rect_y) + (*rect_x)) * 3,
            pixel_stride,
            kernel,
            kernel_row_size,
            bin_width_pow);

        index = 0;
        for (k=0; k<3; k++) {
            int b;
            for (b=0; b<bins_num; b++) {
                if (target_candidate[index] == 0) {
                    target_ratio[index] = 0;
                } else {
                    ((float *) target_ratio)[index] = sqrt(
                          target_model[index]
                        / target_candidate[index]);
                    max_ratio[k] = MAX(max_ratio[k], ((float *) target_ratio)[index]);
                }
                index++;
            }
        }

        ratio_scale = pow(
            (INT_MAX * 2.0f * 4.0f) / (height * height * height * max_ratio[0] * max_ratio[1] * max_ratio[2]),
            1.0f / 3.0f);
        index = 0;
        for (k=0; k<3; k++) {
            int b;
            for (b=0; b<bins_num; b++)
            {
                target_ratio[index] = ((float *)target_ratio)[index] * ratio_scale + 0.5f;
#ifndef DSP_COMPILER
//                std::cerr << "target_ratio_DSP: " << target_ratio[index] << "\n";
#endif
                index++;
            }
        }

        track_iter_inner(
            height,
            width,
            target_ratio,
            target_ratio + bins_num,
            target_ratio + bins_num * 2,
            pixels + (pixel_stride * (*rect_y) + (*rect_x)) * 3,
            pixel_stride,
            bin_width_pow,
            &delta_y,
            &delta_x
        );

        *rect_y += delta_y;
        *rect_x += delta_x;

#ifndef DSP_COMPILER
//        std::cerr << "newrect: (" << *rect_y << "," << *rect_x << ")\n";
//        std::cerr << "delta: (" << delta_y << "," << delta_x << ")\n";
#endif

        if((delta_y | delta_x) == 0) {
            return;
        }
    }
}

