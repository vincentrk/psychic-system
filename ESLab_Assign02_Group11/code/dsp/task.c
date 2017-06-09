/*  ----------------------------------- DSP/BIOS Headers            */
#include <std.h>
#include <gbl.h>
#include <log.h>
#include <swi.h>
#include <sys.h>
#include <tsk.h>
#include <pool.h>

/*  ----------------------------------- DSP/BIOS LINK Headers       */
#include <failure.h>
#include <dsplink.h>
#include <platform.h>
#include <notify.h>
#include <bcache.h>
/*  ----------------------------------- Sample Headers              */
#include <pool_notify_config.h>
#include <task.h>

#include <math.h>

#include "meanshift_portable.h"

extern Uint16 MPCSXFER_BufferSize ;


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

struct {
	int height;
	int width;
	int * kernel;
	int kernel_cols;
	int * target_model;
	int bin_width_pow;
	int bins_num;
	int iter_max;
} meanshift_info;

Int Task_execute (Task_TransferInfo * info)
{
	int msg_type;
	int running = 1;
	while (running) {
		//wait for semaphore
		SEM_pend (&(info->notifySemObj), SYS_FOREVER);

		//invalidate cache
		BCACHE_inv ((Ptr)buf, length, TRUE) ;

		//call the functionality to be performed by dsp
		
		msg_type = ((int *) buf)[0];

		if (msg_type == MEANSHIFT_MSG_TRACK) {
			track_inner(
				meanshift_info.height,
				meanshift_info.width,
				((unsigned char *) buf) + 4 * sizeof(int),
				((int *) buf)[3],
				meanshift_info.kernel,
				meanshift_info.kernel_cols,
				meanshift_info.target_model,
				meanshift_info.bin_width_pow,
				meanshift_info.bins_num,
				meanshift_info.iter_max,
				&(((int *)buf)[1]),
				&(((int *)buf)[2])
			);
			((int *) buf)[0] = MEANSHIFT_MSG_SUCCESS;

		} else if (msg_type == MEANSHIFT_MSG_INIT) {
			meanshift_info.height        = ((int *) buf)[1];
			meanshift_info.width         = ((int *) buf)[2];
			meanshift_info.kernel_cols   = ((int *) buf)[3];
			meanshift_info.bin_width_pow = ((int *) buf)[4];
			meanshift_info.bins_num      = ((int *) buf)[5];
			meanshift_info.iter_max      = ((int *) buf)[6];

			meanshift_info.kernel = MEM_calloc (DSPLINK_SEGID,
				meanshift_info.height * meanshift_info.width * sizeof(int),
				128);

			meanshift_info.target_model = MEM_calloc (DSPLINK_SEGID,
				meanshift_info.bins_num * CHANNEL_COUNT * sizeof(int),
				128);
				
            if (meanshift_info.kernel != NULL && meanshift_info.target_model != NULL) {
			    memcpy(
				    meanshift_info.kernel,
				    ((int *) buf) + 7 + meanshift_info.bins_num * CHANNEL_COUNT,
				    meanshift_info.height * meanshift_info.width * sizeof(int));

			    memcpy(
				    meanshift_info.target_model,
				    ((int *) buf) + 7,
				    meanshift_info.bins_num * sizeof(int));

			    ((int *) buf)[0] = MEANSHIFT_MSG_SUCCESS;
		    } else {
		        ((int *) buf)[0] = MEANSHIFT_MSG_FAILURE;
		        ((int *) buf)[1] = MEANSHIFT_E_NOMEM;
	        }

		} else if (msg_type == MEANSHIFT_MSG_STOP) {
            running = 0;
            ((int *) buf)[0] = MEANSHIFT_MSG_SUCCESS;
		}

		//write back to main memory
		BCACHE_wb ((Ptr)buf, 128, TRUE);

		//notify that we are done
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
    }
    if (count==2) {
        length = (int)info;
    }

    SEM_post(&(mpcsInfo->notifySemObj));
}
