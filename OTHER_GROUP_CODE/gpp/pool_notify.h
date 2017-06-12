#if !defined (pool_notify_H)
#define pool_notify_H

/*  ----------------------------------- DSP/BIOS Link                 */
//#include <dsplink.h>


/** ============================================================================
 *  @const  ID_PROCESSOR
 *
 *  @desc   The processor id of the processor being used.
 *  ============================================================================
 */
#define ID_PROCESSOR       0


/** ============================================================================
 *  @func   pool_notify_Create
 *
 *  @desc   This function allocates and initializes resources used by
 *          this application.
 *
 *  @arg    dspExecutable
 *              DSP executable name.
 *  @arg    strBufferSize
 *              String representation of buffer size to be used
 *              for data transfer.
 *  @arg    strNumIterations
 *              Number of iterations a data buffer is transferred between
 *              GPP and DSP in string format.
 *  @arg    processorId
 *             Id of the DSP Processor.
 *
 *  @ret    DSP_SOK
 *              Operation successfully completed.
 *          DSP_EFAIL
 *              Resource allocation failed.
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    pool_notify_Delete
 *  ============================================================================
 */
NORMAL_API
DSP_STATUS
pool_notify_Create (IN Char8 * dspExecutable,
        IN Char8 * strBufferSize,
        IN Uint8   processorId) ;


/** ============================================================================
 *  @func   pool_notify_Delete
 *
 *  @desc   This function releases resources allocated earlier by call to
 *          pool_notify_Create ().
 *          During cleanup, the allocated resources are being freed
 *          unconditionally. Actual applications may require stricter check
 *          against return values for robustness.
 *
 *  @arg    processorId
 *             Id of the DSP Processor.
 *
 *  @ret    DSP_SOK
 *              Operation successfully completed.
 *          DSP_EFAIL
 *              Resource deallocation failed.
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    pool_notify_Create
 *  ============================================================================
 */
NORMAL_API
Void
pool_notify_Delete (IN Uint8 processorId) ;


/** ============================================================================
 *  @func   pool_notify_Main
 *
 *  @desc   The OS independent driver function for the MESSAGE sample
 *          application.
 *
 *  @arg    dspExecutable
 *              Name of the DSP executable file.
 *  @arg    strBufferSize
 *              Buffer size to be used for data-transfer in string format.
 *  @arg    strNumIterations
 *              Number of iterations a data buffer is transferred between
 *              GPP and DSP in string format.
 *  @arg    strProcessorId
 *             ID of the DSP Processor in string format.
 *
 *  @ret    None
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    pool_notify_Create, pool_notify_Execute, pool_notify_Delete
 *  ============================================================================
 */
NORMAL_API
DSP_STATUS
pool_notify_Init (IN Char8 * dspExecutable,
        IN Char8 * strBufferSize) ;


/** ============================================================================
 *  @func   pool_notify_GetSharedMem
 *
 *  @desc   The OS independent driver function to get the shared memory
 *
 *  @arg    None
 *
 *  @ret    Pointer to the shared memory
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  ============================================================================
 */
NORMAL_API char *const pool_notify_GetSharedMem(void);

/** ============================================================================
 *  @func   pool_notify_NotifySharedMem
 *
 *  @desc   Notify the DSP with the new shared memory and that it can continue
 *          its execution
 *
 *  @arg    Size
 *              The size of the memory that has been updates (so must be invalidated)
 *              when size is -1 all of the shared memory is invalidated
 *
 *  @ret    None
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  ============================================================================
 */
NORMAL_API void pool_notify_NotifySharedMem(long int size);

/** ============================================================================
 *  @func   pool_notify_WaitDSP
 *
 *  @desc   Wait for the DSP to be done with the shared memory
 *
 *  @arg    None
 *
 *  @ret    None
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  ============================================================================
 */
NORMAL_API void pool_notify_WaitDSP(void);

/** ============================================================================
 *  @func   pool_notify_Done
 *
 *  @desc   Notify the DSP that it can stop its execution
 *
 *  @arg    None
 *
 *  @ret    Pointer to the shared memory
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  ============================================================================
 */
NORMAL_API void pool_notify_Done(void);

#endif /* !defined (pool_notify_H) */
