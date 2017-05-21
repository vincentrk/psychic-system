
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
);

