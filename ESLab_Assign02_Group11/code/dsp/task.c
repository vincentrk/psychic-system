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

void track_iter(
	int height, int width,
	int bins, float bin_width,
	float * target_ratio, unsigned char * pixels,
	float * result_y, float * result_x
) {
	float centre;
	float centre_inv;
	int i;
	int n = 0;
	float * target_ratio_a = target_ratio;
	float * target_ratio_b = target_ratio + bins;
	float * target_ratio_c = target_ratio + bins * 2;

	float delta_x = 0.0f;
	float delta_y = 0.0f;
	float sum_wij = 0.0f;

	centre = (height - 1) / 2.0f;
	centre_inv = 1 / centre;
	for (i=0; i<height; i++) {
		float norm_i = (i - centre) * centre_inv;
		float norm_i_sqr = norm_i * norm_i;
		int j;
		for (j=0; j<width; j++) {
			float norm_j = (j - centre) * centre_inv;
			float norm_j_sqr = norm_j * norm_j;
			if (norm_i_sqr + norm_j * norm_j <= 1.0f) {
				float sign_i = (norm_i > 0) - (norm_i < 0);
				float sign_j = (norm_j > 0) - (norm_j < 0);
				unsigned char bina = pixels[n++] * bin_width;
				unsigned char binb = pixels[n++] * bin_width;
				unsigned char binc = pixels[n++] * bin_width;
				float weight = sqrt(
					  target_ratio_a[bina]
					* target_ratio_b[binb]
					* target_ratio_c[binc]);
				delta_x += norm_j * weight;
				delta_y += norm_i * weight;
				sum_wij += weight;
			}
		}
	}
	*result_y = ((delta_y/sum_wij))*centre;
	*result_x = ((delta_x/sum_wij))*centre;
}

Int Task_execute (Task_TransferInfo * info)
{
	int   * bufi;
	float * buff;
	unsigned char * frame;
	float result_y;
	float result_x;

	while (TRUE) {
		//wait for semaphore
		SEM_pend (&(info->notifySemObj), SYS_FOREVER);

		//invalidate cache
		BCACHE_inv ((Ptr)buf, length, TRUE) ;

		//call the functionality to be performed by dsp
		bufi = (int   *) buf;
		buff = (float *) buf;
		frame = (unsigned char *) ( (&bufi[4]) + bufi[2]*3 );
		track_iter(
			bufi[0], bufi[1],
			bufi[2], buff[3],
			&buff[4], frame,
			&result_y, &result_x);
		buff[0] = result_y;
		buff[1] = result_x;

		//write back to main memory
		BCACHE_wb ((Ptr)buf, 128, TRUE) ;

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