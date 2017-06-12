/*  ----------------------------------- DSP/BIOS Headers            */
#include <std.h>
#include <gbl.h>
#include <log.h>
#include <swi.h>
#include <sys.h>
#include <tsk.h>
#include <pool.h>

#include <stdlib.h>
#include <string.h>

/*  ----------------------------------- DSP/BIOS LINK Headers       */
#include <failure.h>
#include <dsplink.h>
#include <platform.h>
#include <notify.h>
#include <bcache.h>
/*  ----------------------------------- Sample Headers              */
#include <pool_notify_config.h>
#include <task.h>

#include "sharedmem.h"

/* ======================================================================== */
/*  Prototypes for timing functions.                                        */
/* ======================================================================== */
#ifdef DSP_TIMER
#include "tsc.h"
typedef unsigned int clock_t;

static inline void clock_enable()
{
    TSC_enable();
}
static inline clock_t clock()
{
    return(TSC_read());
}
#endif


extern Uint16 MPCSXFER_BufferSize ;

static volatile Int32 DoneFlag = 0;


static Void Task_notify (Uint32 eventNo, Ptr arg, Ptr info) ;

Int Task_create (Task_TransferInfo ** infoPtr)
{
    Int status    = SYS_OK ;
    Task_TransferInfo * info = NULL ;

    /* Allocate Task_TransferInfo structure that will be initialized
     * and passed to other phases of the application */
    if (status == SYS_OK)
    {
        *infoPtr = MEM_calloc (DSPLINK_SEGID,
                sizeof (Task_TransferInfo),
                0) ; /* No alignment restriction */
        if (*infoPtr == NULL)
        {
            status = SYS_EALLOC ;
        }
        else
        {
            info = *infoPtr ;
        }
    }

    /* Fill up the transfer info structure */
    if (status == SYS_OK)
    {
        info->dataBuf       = NULL ; /* Set through notification callback. */
        info->bufferSize    = MPCSXFER_BufferSize ;
        SEM_new (&(info->notifySemObj), 0) ;
    }

    /*
     *  Register notification for the event callback to get control and data
     *  buffer pointers from the GPP-side.
     */
    if (status == SYS_OK)
    {
        status = NOTIFY_register (ID_GPP,
                MPCSXFER_IPS_ID,
                MPCSXFER_IPS_EVENTNO,
                (FnNotifyCbck) Task_notify,
                info) ;
        if (status != SYS_OK)
        {
            return status;
        }
    }

    /*
     *  Send notification to the GPP-side that the application has completed its
     *  setup and is ready for further execution.
     */
    if (status == SYS_OK)
    {
        status = NOTIFY_notify (ID_GPP,
                MPCSXFER_IPS_ID,
                MPCSXFER_IPS_EVENTNO,
                (Uint32) 0) ; /* No payload to be sent. */
        if (status != SYS_OK)
        {
            return status;
        }
    }

    /*
     *  Wait for the event callback from the GPP-side to post the semaphore
     *  indicating receipt of the data buffer pointer and image width and height.
     */
    SEM_pend (&(info->notifySemObj), SYS_FOREVER) ;
    SEM_pend (&(info->notifySemObj), SYS_FOREVER) ;

    return status ;
}

unsigned char* buf;
int length;

Int Task_execute (Task_TransferInfo * info)
{
    unsigned char *bufp;
    Int32 *bufp32;
    Int32 *weights;

    Int32 length_pixel;
    Int32 length_pdf;
    Int32 bit_shift;
    Int32 norm_i, norm_i_sq;
    Int32 centre;
    Uint32 offset_w[2];
    Int32 check;

    Int32 delta_x;

    Int32 *delta_x_result;
    Int32 *weight_tmp_i_result;


    while(SEM_pend (&(info->notifySemObj), SYS_FOREVER))
    {
        Int32 weight_tmp_i = 0;

        int i;

        if (DoneFlag == 1)
            return SYS_OK;

        /* Invalidate the fist 4 btes of the shared memory to the the length */
        BCACHE_inv ((Ptr)buf, sizeof(Int32)*IDX_PIXEL_START, TRUE);
        //BCACHE_inv ((Ptr)buf, length, TRUE);
        bufp32 = (Int32 *)buf;

        /* Read the length */
        length_pixel    = bufp32[IDX_PIXEL_LENGTH];
        length_pdf      = bufp32[IDX_PDF_LENGTH];

        /* The start of the data */
        bufp = (unsigned char *)&bufp32[IDX_PIXEL_START];

        /* The start of the PDF */
        weights = &bufp32[IDX_PIXEL_START + ((length_pixel+4)/sizeof(Int32))];

        /* Invalidate the rest of the data */
        BCACHE_inv ((Ptr)bufp, length_pixel+4 + (length_pdf * sizeof(Int32)), FALSE);

        /* Read the other variables */
        bit_shift       = bufp32[IDX_BIT_SHIFT];
        norm_i          = bufp32[IDX_NORM_I];
        centre          = bufp32[IDX_CENTRE];
        offset_w[0]     = (Uint32)bufp32[IDX_OFFSET_W_0];
        offset_w[1]     = (Uint32)bufp32[IDX_OFFSET_W_1];

        /* Read other metadata */
        delta_x_result = &bufp32[IDX_DELTA_X_RES];
        weight_tmp_i_result = &bufp32[IDX_WEIGHT_I_RES];

        /* Set the start value of delta_x */
        delta_x = *delta_x_result;

        /* The start of the PDF */
        weights = &bufp32[IDX_PIXEL_START + ((length_pixel+4)/sizeof(Int32))];

        /* Compute check */
        check = centre * centre;

        /* Compute norm_i squared */
        norm_i_sq = norm_i * norm_i;

        /* Wait untill the invallidation of the cache is done */
        BCACHE_wait();

        /* Do the computations */
        //#pragma UNROLL(5)
        //#pragma MUST_ITERATE(2,,2)
        for (i=0; i<(length_pixel/3); i++)
        {
            // Set x-position with respect to centre (x2)
            Int32 norm_j = (i<<1) - centre;

            // Check if current position is within circle that fits in target box
            if(norm_i_sq + (norm_j*norm_j) < check)
            {
                Int32 weight_tmp_j;
                Uint32 bin_value[3];

                /* Start the calculations */
                // Convert piweight_tmp_ixel value to bin number
                bin_value[0] = bufp[0]>>bit_shift;
                bin_value[1] = bufp[1]>>bit_shift;
                bin_value[2] = bufp[2]>>bit_shift;

                // Sum weights at current pixel location
                weight_tmp_j = weights[bin_value[0]] +
                    weights[offset_w[0]+bin_value[1]] +
                    weights[offset_w[1]+bin_value[2]];

                // Calculate shift in x-direction
                delta_x += norm_j*weight_tmp_j;
                // Accumulate weights
                weight_tmp_i += weight_tmp_j;
            }
            bufp += 3;
        }

        /* Fill in the results */
        *delta_x_result = delta_x;
        *weight_tmp_i_result = weight_tmp_i;

        /* Write the cache for the results */
        BCACHE_wb ((Ptr)buf, sizeof(Int32)*IDX_PIXEL_START, TRUE);
        //BCACHE_wb ((Ptr)buf, length, TRUE);

        /* Notify that we are done */
        NOTIFY_notify(ID_GPP,MPCSXFER_IPS_ID,MPCSXFER_IPS_EVENTNO,(Uint32)0);
    }

    return SYS_OK;
}

Int Task_delete (Task_TransferInfo * info)
{
    Int    status     = SYS_OK ;
    /*
     *  Unregister notification for the event callback used to get control and
     *  data buffer pointers from the GPP-side.
     */
    status = NOTIFY_unregister (ID_GPP,
            MPCSXFER_IPS_ID,
            MPCSXFER_IPS_EVENTNO,
            (FnNotifyCbck) Task_notify,
            info) ;

    /* Free the info structure */
    MEM_free (DSPLINK_SEGID,
            info,
            sizeof (Task_TransferInfo)) ;
    info = NULL ;

    return status ;
}


static Void Task_notify (Uint32 eventNo, Ptr arg, Ptr info)
{
    static int count = 0;
    Task_TransferInfo * mpcsInfo = (Task_TransferInfo *) arg ;

    (Void) eventNo ; /* To avoid compiler warning. */

    count++;
    if (count==1) {
        buf =(unsigned char*)info ;
    } else if (count==2) {
        length = (int)info;
    } else {
        /* Signal we are done */
        DoneFlag = (int)info;
    }

    SEM_post(&(mpcsInfo->notifySemObj));
}
