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

void pdf_representation_inner(
    int height,
    int width,
    int * RESTRICT pdf_a,
    int * RESTRICT pdf_b,
    int * RESTRICT pdf_c,
    const unsigned char * RESTRICT pixels,
    int pixel_stride,
    const int * RESTRICT kernel,
    int kernel_row_size,
    int bin_width_pow
);

void track_iter_inner(
    const int height,
    int width,
    const int * RESTRICT ratio_a,
    const int * RESTRICT ratio_b,
    const int * RESTRICT ratio_c,
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
    const int * RESTRICT kernel,
    const int kernel_row_size,
    const int * RESTRICT target_model,
    const int bin_width_pow,
    const int bins_num,
    const int iter_max,
    int * rect_y,
    int * rect_x
);

