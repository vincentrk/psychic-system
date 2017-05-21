
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
);

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
);

