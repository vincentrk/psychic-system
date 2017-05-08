#if !defined (MATRIXMULT_H)
#define MATRIXMULT_H

#define MATRIX_SIZE_DEFAULT 128

#if defined (__cplusplus)
extern "C"
{
#endif /* defined (__cplusplus) */


NORMAL_API Void accelMult(Char8* dspExecutable,int size, int * mat1, int * mat2, int * prod);

NORMAL_API DSP_STATUS accelMult_Create(Char8* dspExecutable, Uint8 processorId);

NORMAL_API DSP_STATUS accelMult_Execute(Uint8 processorId,int size, int * mat1, int * mat2, int * prod);

NORMAL_API Void accelMult_Delete(Uint8 processorId);

#endif /* !defined (MATRIXMULT_H) */


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
