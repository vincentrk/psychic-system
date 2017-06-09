#define MEANSHIFT_MSG_INIT 1
#define MEANSHIFT_MSG_TRACK 2
#define MEANSHIFT_MSG_STOP 4
#define MEANSHIFT_MSG_SUCCESS 16
#define MEANSHIFT_MSG_FAILURE 32
#define MEANSHIFT_E_NOMEM 128

#define CHANNEL_COUNT 3

#ifdef DSP_COMPILER
    #define RESTRICT restrict
#else
    #define RESTRICT __restrict
#endif

#ifdef FIXEDPOINT
    #define PDF_T int
#else
    #define PDF_T float
#endif

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
);

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
);

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
);

