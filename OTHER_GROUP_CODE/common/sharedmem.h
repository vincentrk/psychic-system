#ifndef SHAREDMEM_H_
#define SHAREDMEM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define IDX_PIXEL_LENGTH    0
#define IDX_PDF_LENGTH      1
#define IDX_BIT_SHIFT       2
#define IDX_NORM_I          3
#define IDX_CENTRE          4
#define IDX_OFFSET_W_0      5
#define IDX_OFFSET_W_1      6

#define IDX_DELTA_X_RES     7
#define IDX_WEIGHT_I_RES    8

#define IDX_PIXEL_START     9
/* IDX_PDF_START is indicated by the IDX_PIXEL_START + the pixel length */

#ifdef __cplusplus
}
#endif

#endif /* SHAREDMEM_H_ */
