#include <stdlib.h>

void pdf_representation_inner(
    int height,
    int width,
    int * __restrict__ pdf_a,
    int * __restrict__ pdf_b,
    int * __restrict__ pdf_c,
    const int * __restrict__ kernel,
    int kernel_row_size,
    const unsigned char * __restrict__ pixels,
    int pixel_stride,
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

