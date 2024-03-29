#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "meanshift_portable.h"
#ifdef USE_NEON
#include <arm_neon.h>
#endif //USE_NEON

#ifndef DSP_COMPILER
#include <iostream>
#ifdef TIMEDETAIL
    #define HIRESTIMING
#endif
#endif

#ifdef HIRESTIMING
long HiResTime(void);
#endif

#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))


void pdf_representation_inner(
    int height,
    int width,
    PDF_T * RESTRICT pdf_a,
    PDF_T * RESTRICT pdf_b,
    PDF_T * RESTRICT pdf_c,
    const unsigned char * RESTRICT pixels,
    int pixel_stride,
    const PDF_T * RESTRICT kernel,
    int kernel_row_size,
    int bin_width_pow
)
{
    int i, j;
    int pixel_skip = (pixel_stride - width) * CHANNEL_COUNT;
    int kern_h = height / 2;
    int kern_w = width / 2;

#ifdef HIRESTIMING
    long tTemp = HiResTime();
#endif
    for(i=0; i < height; i++) {
        for(j=0; j < width; j++) {
            unsigned char bin_value_a, bin_value_b, bin_value_c;
            PDF_T val_a, val_b, val_c;
            PDF_T kernel_element;
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
#ifdef HIRESTIMING
    std::cout << "pdf_rep: " << (HiResTime()-tTemp) << "\n";
#endif
}

void track_iter_inner(
    const int height,
    int width,
    const PDF_T * RESTRICT ratio_a,
    const PDF_T * RESTRICT ratio_b,
    const PDF_T * RESTRICT ratio_c,
    const unsigned char * RESTRICT pixels,
    const int pixel_stride,
    const int bin_width_pow,
    int * result_y,
    int * result_x
) {
    int i, j;
    int pixel_skip;
    PDF_T delta_x = 0;
    PDF_T delta_y = 0;
    PDF_T sum_wij = 0;
    #ifdef USE_NEON
    int32x4_t preWeights = vsetq_lane_s32(1,preWeights,2);
    int32x4_t newDeltas = vdupq_n_s32(0);
    #endif //USE_NEON
    PDF_T centre = ((height-1)/(PDF_T)2); // Half pixel error

    width = MIN(height, width); // Loop is limited to a circle with a diameter of height
    pixel_skip = (pixel_stride - width) * CHANNEL_COUNT;

#ifdef HIRESTIMING
    long tTemp = HiResTime();
#endif

    for(i=0; i < height; i++) {
        PDF_T norm_i = (i - centre);
        #ifdef USE_NEON
        preWeights = vsetq_lane_s32(norm_i,preWeights,1);
        #endif //USE_NEON
        PDF_T norm_i_sqr = norm_i * norm_i;
        for(j=0; j < width; j++) {
            PDF_T norm_j = (j-centre);
            if (norm_i_sqr + norm_j * norm_j <= centre * centre) {
                // calculate element of weight matrix (CalWeight)
                #ifdef USE_NEON
                preWeights = vsetq_lane_s32(norm_j,preWeights,0);
                #endif //USE_NEON
                unsigned char bin_value_a, bin_value_b, bin_value_c;
                PDF_T weight;
                bin_value_a = (*(pixels + 0)) >> bin_width_pow;
                bin_value_b = (*(pixels + 1)) >> bin_width_pow;
                bin_value_c = (*(pixels + 2)) >> bin_width_pow;
                weight = (
                          ratio_a[bin_value_a]
                        * ratio_b[bin_value_b]
                        * ratio_c[bin_value_c]);


                #ifdef USE_NEON
                newDeltas = vaddq_s32(vmulq_s32(vdupq_n_s32(weight),preWeights),newDeltas);
                #else
                delta_x += norm_j * weight;
                delta_y += norm_i * weight;
                sum_wij += weight;
                #endif //USE_NEON
            }
            pixels += CHANNEL_COUNT;
        }
        pixels += pixel_skip;
    }
#ifdef HIRESTIMING
    std::cout << "iter_in: " << (HiResTime()-tTemp) << "\n";
#endif

    #ifdef USE_NEON
    vst1q_lane_s32(& delta_x,newDeltas,0);
		vst1q_lane_s32(& delta_y,newDeltas,1);
		vst1q_lane_s32(& sum_wij,newDeltas,2);
    #endif //USE_NEON
    *result_y = (delta_y/sum_wij);
    *result_x = (delta_x/sum_wij);
}

void track_inner(
    const int height,
    const int width,
    const unsigned char * RESTRICT pixels,
    const int pixel_stride,
    const PDF_T * RESTRICT kernel,
    const int kernel_row_size,
    const PDF_T * RESTRICT target_model,
    const int bin_width_pow,
    const int bins_num,
    const int iter_max,
    int * rect_y,
    int * rect_x
) {
    const int pdf_size = CHANNEL_COUNT * bins_num * sizeof(PDF_T);
    PDF_T * target_candidate = (PDF_T *) malloc(pdf_size);
    PDF_T * target_ratio = (PDF_T *) malloc(pdf_size);

    int iter;
    for(iter=0; iter < iter_max; iter++) {
        int k;
        int index;
#ifdef FIXEDPOINT
        float max_ratio[CHANNEL_COUNT] = {0.0f};
        float ratio_scale;
#endif

        int delta_y = 0;
        int delta_x = 0;

#ifdef FIXEDPOINT
        memset(target_candidate, 0, pdf_size);
#else
        index = 0;
        for (k=0; k<CHANNEL_COUNT; k++) {
            int b;
            for (b=0; b<bins_num; b++) {
                target_candidate[index] = 1e-10;
                index++;
            }
        }
#endif
        pdf_representation_inner(
            height,
            width,
            target_candidate,
            target_candidate + bins_num,
            target_candidate + bins_num * 2,
            pixels + (pixel_stride * (*rect_y) + (*rect_x)) * CHANNEL_COUNT,
            pixel_stride,
            kernel,
            kernel_row_size,
            bin_width_pow);

        // Calculate the ratios and maximums
        index = 0;
        for (k=0; k<CHANNEL_COUNT; k++) {
            int b;
            for (b=0; b<bins_num; b++) {
#ifdef FIXEDPOINT
                if (target_candidate[index] == 0) {
                    target_ratio[index] = 0;
                } else {
                    ((float *) target_ratio)[index] = sqrt(
                          target_model[index]
                        / target_candidate[index]);
                    max_ratio[k] = MAX(max_ratio[k], ((float *) target_ratio)[index]);
                }
#else
                target_ratio[index] = sqrt(
                          target_model[index]
                        / target_candidate[index]);
#endif
                index++;
            }
        }

#ifdef FIXEDPOINT
        // Scale the ratio array and convert to int
        ratio_scale = pow(
            (INT_MAX * 2.0f * 4.0f) / (height * height * height * max_ratio[0] * max_ratio[1] * max_ratio[2]),
            1.0f / 3.0f);
        index = 0;
        for (k=0; k<CHANNEL_COUNT; k++) {
            int b;
            for (b=0; b<bins_num; b++)
            {
                target_ratio[index] = ((float *)target_ratio)[index] * ratio_scale + 0.5f;
                index++;
            }
        }
#endif

        track_iter_inner(
            height,
            width,
            target_ratio,
            target_ratio + bins_num,
            target_ratio + bins_num * 2,
            pixels + (pixel_stride * (*rect_y) + (*rect_x)) * CHANNEL_COUNT,
            pixel_stride,
            bin_width_pow,
            &delta_y,
            &delta_x
        );

        *rect_y += delta_y;
        *rect_x += delta_x;

        if((delta_y | delta_x) == 0) {
            return;
        }
    }
}
