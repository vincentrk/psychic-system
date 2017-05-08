
/*  ----------------------------------- DSP/BIOS Link                   */
#include <dsplink.h>

/*  ----------------------------------- DSP/BIOS LINK API               */
#include <proc.h>
#include <msgq.h>
#include <pool.h>

/*  ----------------------------------- Application Header              */
#include <matrixmult.h>
#include <system_os.h>

#include <stdio.h>

#include "Timer.h"

#if defined (__cplusplus)
extern "C"
{
#endif /* defined (__cplusplus) */






    /* Number of arguments specified to the DSP application. */
#define NUM_ARGS 1

    /* Argument size passed to the control message queue */
#define ARG_SIZE 256

    /* ID of the POOL used by helloDSP. */
#define SAMPLE_POOL_ID  0

    /*  Number of BUF pools in the entire memory pool */
#define NUMMSGPOOLS     4

    /* Number of messages in each BUF pool. */
#define NUMMSGINPOOL0   1
#define NUMMSGINPOOL1   2
#define NUMMSGINPOOL2   2
#define NUMMSGINPOOL3   4

    /* Control message data structure. */
    /* Must contain a reserved space for the header */
    typedef struct ControlMsg
    {
        MSGQ_MsgHeader header;
        Uint16 command;
        Uint32 arg1[SIZE];		// used to be Char8 arg1[256] = 2048 bits
        Uint32 arg2[SIZE];      	// now, 2 x 32 x 16 = 1024
    } ControlMsg;

    /* Messaging buffer used by the application.
     * Note: This buffer must be aligned according to the alignment expected
     * by the device/platform. */
#define APP_BUFFER_SIZE DSPLINK_ALIGN (sizeof (ControlMsg), DSPLINK_BUF_ALIGN)

    /* Definitions required for the sample Message queue.
     * Using a Zero-copy based transport on the shared memory physical link. */
#if defined ZCPY_LINK
#define SAMPLEMQT_CTRLMSG_SIZE  ZCPYMQT_CTRLMSG_SIZE
    STATIC ZCPYMQT_Attrs mqtAttrs;
#endif

    /* Message sizes managed by the pool */
    STATIC Uint32 SampleBufSizes[NUMMSGPOOLS] =
    {
        APP_BUFFER_SIZE,
        SAMPLEMQT_CTRLMSG_SIZE,
        DSPLINK_ALIGN (sizeof(MSGQ_AsyncLocateMsg), DSPLINK_BUF_ALIGN),
        DSPLINK_ALIGN (sizeof(MSGQ_AsyncErrorMsg), DSPLINK_BUF_ALIGN)
    };

    /* Number of messages in each pool */
    STATIC Uint32 SampleNumBuffers[NUMMSGPOOLS] =
    {
        NUMMSGINPOOL0,
        NUMMSGINPOOL1,
        NUMMSGINPOOL2,
        NUMMSGINPOOL3
    };

    /* Definition of attributes for the pool based on physical link used by the transport */
#if defined ZCPY_LINK
    STATIC SMAPOOL_Attrs SamplePoolAttrs =
    {
        NUMMSGPOOLS,
        SampleBufSizes,
        SampleNumBuffers,
        TRUE   /* If allocating a buffer smaller than the POOL size, set this to FALSE */
    };
#endif

    /* Name of the first MSGQ on the GPP and on the DSP. */
    STATIC Char8 SampleGppMsgqName[DSP_MAX_STRLEN] = "GPPMSGQ1";
    STATIC Char8 SampleDspMsgqName[DSP_MAX_STRLEN] = "DSPMSGQ";

    /* Local GPP's and DSP's MSGQ Objects. */
    STATIC MSGQ_Queue SampleGppMsgq = (Uint32) MSGQ_INVALIDMSGQ;
    STATIC MSGQ_Queue SampleDspMsgq = (Uint32) MSGQ_INVALIDMSGQ;

    /* Place holder for the MSGQ name created on DSP */
    Char8 dspMsgqName[DSP_MAX_STRLEN];

    /* Extern declaration to the default DSP/BIOS LINK configuration structure. */
    extern LINKCFG_Object LINKCFG_config;







NORMAL_API Void accelMult(Char8* dspExecutable,Char8* matrix_size, int mat1[SIZE][SIZE], int mat2[SIZE][SIZE], int prod[SIZE][SIZE]){
	DSP_STATUS status = DSP_SOK;
	Uint8 processorId = 0;

	SYSTEM_0Print ("========== Application: Matrix Multiplication ==========\n");
    if ((dspExecutable != NULL) && (mat1 != NULL) && (mat2 != NULL))
    {
        if (processorId >= MAX_DSPS)
        {
            SYSTEM_1Print("== Error: Invalid processor id %d specified ==\n", processorId);
            status = DSP_EFAIL;
        }
        /* Specify the dsp executable file name for message creation phase. */
        if (DSP_SUCCEEDED(status))
        {
            status = accelMult_Create(dspExecutable,matrix_size, processorId);

            /* Execute the message execute phase. */
            if (DSP_SUCCEEDED(status))
            {
                status = accelMult_Execute(processorId,matrix_size, mat1, mat2, prod);
            }

            /* Perform cleanup operation. */
            accelMult_Delete(processorId);
        }
    }
    else
    {
        status = DSP_EINVALIDARG;
        SYSTEM_0Print("ERROR! Invalid pointers to mat1 or mat2\n");
    }
    SYSTEM_0Print ("========================================================\n");
}

//   ----------------------------------------------------------------------------
//   Create
//   ----------------------------------------------------------------------------
NORMAL_API DSP_STATUS accelMult_Create(Char8* dspExecutable,Char8* matrix_size, Uint8 processorId) {
	DSP_STATUS status = DSP_SOK;
    Uint32 numArgs = NUM_ARGS;
    MSGQ_LocateAttrs syncLocateAttrs;
    Char8* args[NUM_ARGS];

    SYSTEM_0Print("Entered accelMult_Create()\n");
    /* Create and initialize the proc object. */
    status = PROC_setup(NULL);
    /* Attach the Dsp with which the transfers have to be done. */
    if (DSP_SUCCEEDED(status))
    {
        status = PROC_attach(processorId, NULL);
        if (DSP_FAILED(status))
        {
            SYSTEM_1Print("PROC_attach () failed. Status = [0x%x]\n", status);
        }
    }
    /* Open the pool. */
    if (DSP_SUCCEEDED(status))
    {
        status = POOL_open(POOL_makePoolId(processorId, SAMPLE_POOL_ID), &SamplePoolAttrs);
        if (DSP_FAILED(status))
        {
            SYSTEM_1Print("POOL_open () failed. Status = [0x%x]\n", status);
        }
    }
    else
    {
        SYSTEM_1Print("PROC_setup () failed. Status = [0x%x]\n", status);
    }
    SYSTEM_0Print("Pool opened\n");
    /* Open the GPP's message queue */
    if (DSP_SUCCEEDED(status))
    {
        status = MSGQ_open(SampleGppMsgqName, &SampleGppMsgq, NULL);
        if (DSP_FAILED(status))
        {
            SYSTEM_1Print("MSGQ_open () failed. Status = [0x%x]\n", status);
        }
    }
    /* Set the message queue that will receive any async. errors */
    if (DSP_SUCCEEDED(status))
    {
        status = MSGQ_setErrorHandler(SampleGppMsgq, POOL_makePoolId(processorId, SAMPLE_POOL_ID));
        if (DSP_FAILED(status))
        {
            SYSTEM_1Print("MSGQ_setErrorHandler () failed. Status = [0x%x]\n", status);
        }
    }
    SYSTEM_0Print("Message queue created\n");

    /* Load the executable on the DSP. */
    if (DSP_SUCCEEDED(status))
    {
        args [0] = matrix_size;
        {
            status = PROC_load(processorId, dspExecutable, numArgs, args);
        }
        if (DSP_FAILED(status))
        {
            SYSTEM_1Print("PROC_load () failed. Status = [0x%x]\n", status);
        }
    }
    SYSTEM_0Print("Executable loaded on DSP\n");

    /* Start execution on DSP. */
    if (DSP_SUCCEEDED(status))
    {
        status = PROC_start(processorId);
        if (DSP_FAILED(status))
        {
            SYSTEM_1Print("PROC_start () failed. Status = [0x%x]\n", status);
        }
    }
    SYSTEM_0Print("DSP started executing\n");

    /* Open the remote transport. */
    if (DSP_SUCCEEDED(status))
    {
        mqtAttrs.poolId = POOL_makePoolId(processorId, SAMPLE_POOL_ID);
        status = MSGQ_transportOpen(processorId, &mqtAttrs);
        if (DSP_FAILED(status))
        {
            SYSTEM_1Print("MSGQ_transportOpen () failed. Status = [0x%x]\n", status);
        }
    }

    /* Locate the DSP's message queue */
    /* At this point the DSP must open a message queue named "DSPMSGQ" */
    if (DSP_SUCCEEDED(status))
    {
        syncLocateAttrs.timeout = WAIT_FOREVER;
        status = DSP_ENOTFOUND;
        SYSTEM_2Sprint(dspMsgqName, "%s%d", (Uint32) SampleDspMsgqName, processorId);
        while ((status == DSP_ENOTFOUND) || (status == DSP_ENOTREADY))
        {
            status = MSGQ_locate(dspMsgqName, &SampleDspMsgq, &syncLocateAttrs);
            if ((status == DSP_ENOTFOUND) || (status == DSP_ENOTREADY))
            {
                SYSTEM_Sleep(100000);
            }
            else if (DSP_FAILED(status))
            {
                SYSTEM_1Print("MSGQ_locate () failed. Status = [0x%x]\n", status);
            }
        }
    }

    SYSTEM_0Print("Leaving accelMult_Create()\n");
    return status;
}

//   ----------------------------------------------------------------------------
//   Execute
//   ----------------------------------------------------------------------------
NORMAL_API DSP_STATUS accelMult_Execute(Uint8 processorId,Char8* matrix_size, int mat1[SIZE][SIZE], int mat2[SIZE][SIZE], int prod[SIZE][SIZE]) {
	DSP_STATUS  status = DSP_SOK;
    Uint16 sequenceNumber = 0;
    Uint16 msgId = 0;
    int i;
    ControlMsg *msg;
    Uint32 result = 0;
    Timer timerDSP;
    initTimer(&timerDSP,"DSP Time");

    int matrix_size_int = atoi(matrix_size);
    SYSTEM_0Print("Entered accelMult_Execute()\n");

#if defined (PROFILE)
    SYSTEM_GetStartTime();
#endif

    // this
    // guarantees that we will at least wait for one message
    // In total we expect a total of SIZE * SIZE messages plus the first one from DSP
    for (i = -1 ; (i < (matrix_size_int * matrix_size_int)) && (DSP_SUCCEEDED (status)); i++)
    {
        /* Receive the message. */
        status = MSGQ_get(SampleGppMsgq, WAIT_FOREVER, (MsgqMsg *) &msg);
        if (DSP_FAILED(status))
        {
            SYSTEM_1Print("MSGQ_get () failed. Status = [0x%x]\n", status);
        }
#if defined (VERIFY_DATA)
        /* Verify correctness of data received. */
        if (DSP_SUCCEEDED(status))
        {
            status = matrixMult_VerifyData(msg, sequenceNumber);
            if (DSP_FAILED(status))
            {
                MSGQ_free((MsgqMsg) msg);
            }
        }
#endif

        if (msg->command == 0x01) {

            // SYSTEM_0Print("Message command 0x01 received\n");
            startTimer(&timerDSP);
        } else if (msg->command == 0x02) {
            // SYSTEM_0Print("Message command 0x02 received\n");
        	// Extract the result vector and put into output
        	// So far this is sequential. It should only do additions while the pool is full and
        	// it's waiting for the DSP to send something...
            result = 0;
            int p = 0;
            for(p = 0; p < matrix_size_int; p++){
                // SYSTEM_1Print("%d ", msg->arg1[p]);
            	result += msg->arg1[p];
            }
            // SYSTEM_0Print("\n");
            // Safe because first message (i.e. i=-1) is 0x01
        	prod[i%matrix_size_int][i/matrix_size_int] = result;
        }

        /* If the message received is the final one, free it. */
        if (i == matrix_size_int * matrix_size_int - 1)
        {
          stopTimer(&timerDSP);
          printTimer(&timerDSP);
        	SYSTEM_0Print("Last message received.\n");
            MSGQ_free((MsgqMsg) msg);
        }
        else
        {
            // /* Send the same message received in earlier MSGQ_get () call. */
            // if (DSP_SUCCEEDED(status))
            // {
            //     msgId = MSGQ_getMsgId(msg);
            //     MSGQ_setMsgId(msg, msgId);
            //     status = MSGQ_put(SampleDspMsgq, (MsgqMsg) msg);
            //     if (DSP_FAILED(status))
            //     {
            //         MSGQ_free((MsgqMsg) msg);
            //         SYSTEM_1Print("MSGQ_put () failed. Status = [0x%x]\n", status);
            //     }
            // }
            /* Send the two vectors to be multiplied. */
            if (DSP_SUCCEEDED(status))
            {
                msgId = MSGQ_getMsgId(msg);
                MSGQ_setMsgId(msg, msgId);
                // Put the vectors in the message
                // x = (i) % SIZE
                // y = (i) / SIZE
                int p = 0;
                for (p = 0; p < matrix_size_int; p++) {
                	msg->arg1[p] = mat1[(i+1) % matrix_size_int][p];
                	msg->arg2[p] = mat2[p][(i+1) / matrix_size_int];
                }

                // Print what we are sending
                // SYSTEM_0Print("Sending:\n");
                for(p = 0; p < matrix_size_int; p++){
                    // SYSTEM_1Print("%d ", msg->arg1[p]);
                    result += msg->arg1[p];
                }
                // SYSTEM_0Print("\n");
                // for(p = 0; p < matrix_size_int; p++){
                    // SYSTEM_1Print("%d ", msg->arg2[p]);
                // }
                // SYSTEM_0Print("\nExpecting: \n");
                // for(p = 0; p < matrix_size_int; p++){
                    // SYSTEM_1Print("%d ", msg->arg1[p] * msg->arg2[p]);
                // }
                // SYSTEM_0Print("\n");
                // Send the message
                status = MSGQ_put(SampleDspMsgq, (MsgqMsg) msg);
                if (DSP_FAILED(status))
                {
                    MSGQ_free((MsgqMsg) msg);
                    SYSTEM_1Print("MSGQ_put () failed. Status = [0x%x]\n", status);
                }
            }

            sequenceNumber++;
            /* Make sure that the sequenceNumber stays within the permitted
             * range for applications. */
            if (sequenceNumber == MSGQ_INTERNALIDSSTART)
            {
                sequenceNumber = 0;
            }

#if !defined (PROFILE)
            if (DSP_SUCCEEDED(status) && ((i % 100) == 0))
            {
                SYSTEM_1Print("Transferred %ld messages\n", i);
            }
#endif
        }
    }

#if defined (PROFILE)
    if (DSP_SUCCEEDED(status))
    {
            SYSTEM_GetEndTime();
            //SYSTEM_GetProfileInfo(numIterations);
    }
#endif

    SYSTEM_0Print("Leaving helloDSP_Execute ()\n");

    return status;

}

//   ----------------------------------------------------------------------------
//   Delete
//   ----------------------------------------------------------------------------
NORMAL_API Void accelMult_Delete(Uint8 processorId) {
    DSP_STATUS status = DSP_SOK;
    DSP_STATUS tmpStatus = DSP_SOK;

    SYSTEM_0Print("Entered helloDSP_Delete ()\n");

    /* Release the remote message queue */
    status = MSGQ_release(SampleDspMsgq);
    if (DSP_FAILED(status))
    {
        SYSTEM_1Print("MSGQ_release () failed. Status = [0x%x]\n", status);
    }

    /* Close the remote transport */
    tmpStatus = MSGQ_transportClose(processorId);
    if (DSP_SUCCEEDED(status) && DSP_FAILED(tmpStatus))
    {
        status = tmpStatus;
        SYSTEM_1Print("MSGQ_transportClose () failed. Status = [0x%x]\n", status);
    }

    /* Stop execution on DSP. */
    tmpStatus = PROC_stop(processorId);
    if (DSP_SUCCEEDED(status) && DSP_FAILED(tmpStatus))
    {
        status = tmpStatus;
        SYSTEM_1Print("PROC_stop () failed. Status = [0x%x]\n", status);
    }

    /* Reset the error handler before deleting the MSGQ that receives */
    /* the error messages.                                            */
    tmpStatus = MSGQ_setErrorHandler(MSGQ_INVALIDMSGQ, MSGQ_INVALIDMSGQ);

    if (DSP_SUCCEEDED(status) && DSP_FAILED(tmpStatus))
    {
        status = tmpStatus;
        SYSTEM_1Print("MSGQ_setErrorHandler () failed. Status = [0x%x]\n", status);
    }

    /* Close the GPP's message queue */
    tmpStatus = MSGQ_close(SampleGppMsgq);
    if (DSP_SUCCEEDED(status) && DSP_FAILED(tmpStatus))
    {
        status = tmpStatus;
        SYSTEM_1Print("MSGQ_close () failed. Status = [0x%x]\n", status);
    }

    /* Close the pool */
    tmpStatus = POOL_close(POOL_makePoolId(processorId, SAMPLE_POOL_ID));
    if (DSP_SUCCEEDED(status) && DSP_FAILED(tmpStatus))
    {
        status = tmpStatus;
        SYSTEM_1Print("POOL_close () failed. Status = [0x%x]\n", status);
    }

    /* Detach from the processor */
    tmpStatus = PROC_detach(processorId);
    if (DSP_SUCCEEDED(status) && DSP_FAILED(tmpStatus))
    {
        status = tmpStatus;
        SYSTEM_1Print("PROC_detach () failed. Status = [0x%x]\n", status);
    }

    /* Destroy the PROC object. */
    tmpStatus = PROC_destroy();
    if (DSP_SUCCEEDED(status) && DSP_FAILED(tmpStatus))
    {
        status = tmpStatus;
        SYSTEM_1Print("PROC_destroy () failed. Status = [0x%x]\n", status);
    }

    SYSTEM_0Print("Leaving helloDSP_Delete ()\n");
}


#if defined (VERIFY_DATA)
    /** ============================================================================
     *  @func   helloDSP_VerifyData
     *
     *  @desc   This function verifies the data-integrity of given buffer.
     *
     *  @modif  None
     *  ============================================================================
     */
    STATIC NORMAL_API DSP_STATUS matrixMult_VerifyData(IN MSGQ_Msg msg, IN Uint16 sequenceNumber)
    {
        DSP_STATUS status = DSP_SOK;
        Uint16 msgId;

        /* Verify the message */
        msgId = MSGQ_getMsgId(msg.header);
        if (msgId != sequenceNumber)
        {
            status = DSP_EFAIL;
            SYSTEM_0Print("ERROR! Data integrity check failed\n");
        }

        return status;
    }
#endif /* if defined (VERIFY_DATA) */

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
