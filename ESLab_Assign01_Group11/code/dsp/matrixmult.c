/*  ----------------------------------- DSP/BIOS Headers            */
#include "matrixmulcfg.h"
#include <sys.h>
#include <sem.h>
#include <msgq.h>
#include <pool.h>

/*  ----------------------------------- DSP/BIOS LINK Headers       */
#include <dsplink.h>
#include <failure.h>

/*  ----------------------------------- Sample Headers              */
#include <tskMessage.h>


#include<stdio.h>
//#include "Timer.h"

/* FILEID is used by SET_FAILURE_REASON macro. */
#define FILEID  FID_APP_C


#define SIZE 16
static Int tskMessage();

void matMult(int mat1[SIZE][SIZE], int mat2[SIZE][SIZE], int prod[SIZE][SIZE]);

int main()
{
//    Timer totalTime;
//    initTimer(&totalTime, "Total Time");

        /* Task handler for TSK_create */
        TSK_Handle tskMessageTask;

	int mat1[SIZE][SIZE], mat2[SIZE][SIZE], prod[SIZE][SIZE];
	int i, j;
	
	for (i = 0;i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			mat1[i][j] = i+j*2;
		}
	}
	
	for(i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			mat2[i][j] = i+j*3;
		}
	}

//    startTimer(&totalTime);
	matMult(mat1,mat2,prod);
//    stopTimer(&totalTime);
//    printTimer(&totalTime);	

	for (i = 0;i < SIZE; i++)
	{
		printf("\n");
		for (j = 0; j < SIZE; j++)
		{
			printf("\t%d ", prod[i][j]);
		}
	}
	
	printf("\nDone !!! \n");

        /* Creating task for TSKMESSAGE application */
        tskMessageTask = TSK_create(tskMessage, NULL, 0);
        if (tskMessageTask == NULL)
        {
        SET_FAILURE_REASON(SYS_EALLOC);
        LOG_printf(&trace, "Create TSKMESSAGE: Failed.\n");
	}

	return 0;
}

void matMult(int mat1[SIZE][SIZE], int mat2[SIZE][SIZE], int prod[SIZE][SIZE])
{
	int i, j, k;
	for (i = 0;i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			prod[i][j]=0;
			for(k=0;k<SIZE;k++)
				prod[i][j] = prod[i][j]+mat1[i][k] * mat2[k][j];
		}
	}
}

static Int tskMessage()
{
    Int status = SYS_OK;
    TSKMESSAGE_TransferInfo* info;

    /* Create Phase */
    status = TSKMESSAGE_create(&info);

    /* Execute Phase */
    if (status == SYS_OK)
    {
        /* Start the execution phase. */
        status = TSKMESSAGE_execute(info);
        if (status != SYS_OK)
        {
            SET_FAILURE_REASON(status);
        }
    }

    /* Delete Phase */
    status = TSKMESSAGE_delete(info);
    if (status != SYS_OK)
    {
        SET_FAILURE_REASON(status);
    }
    return status;
}

