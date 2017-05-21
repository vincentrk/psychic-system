#include <stdlib.h>

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
    const int width,
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
    int pixel_skip = (pixel_stride - width) * 3;
    int delta_x = 0;
    int delta_y = 0;
    int sum_wij = 0;
    int centre = ((height-1)/2); // Half pixel error

    for(i=0; i < height; i++) {
        int norm_i = (i - centre);
        int norm_i_sqr = norm_i * norm_i;
        for(j=0; j < width; j++) {
            int norm_j = (j-centre);
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
                delta_x += norm_j * weight;
                delta_y += norm_i * weight;
                sum_wij += weight;
            }
            pixels += 3;
        }
        pixels += pixel_skip;
    }
    *result_y = (delta_y/sum_wij);
    *result_x = (delta_x/sum_wij);
}
