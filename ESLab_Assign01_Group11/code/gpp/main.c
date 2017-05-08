/*  ----------------------------------- OS Specific Headers           */
#include <stdio.h>
#include <stdlib.h>

/*  ----------------------------------- DSP/BIOS Link                 */
#include <gpptypes.h>
#include <dsplink.h>
#include <errbase.h>

/*  ----------------------------------- Application Header            */
#include <system_os.h>
#include <matrixmult.h>

/*  ----------------------------------- Custom Headers                */
#include "Timer.h"

void matMult(int mat1[SIZE][SIZE], int mat2[SIZE][SIZE], int prod[SIZE][SIZE]);

int main(int argc, char** argv)
{
    Timer totalTime;
    initTimer(&totalTime, "Total Time Sequential");

    // prodAccel will hold the result from the accelerated algorithm
	int mat1[SIZE][SIZE], mat2[SIZE][SIZE], prod[SIZE][SIZE], prodAccel[SIZE][SIZE];
	int i, j;

	printf("Starting sequential program...\n");

	// SEQUENTIAL VERSION START

	int matrix_size = argv[2];
	
	for (i = 0;i < matrix_size; i++)
	{
		for (j = 0; j < matrix_size; j++)
		{
			mat1[i][j] = i+j*2;
		}
	}
	
	for(i = 0; i < matrix_size; i++)
	{
		for (j = 0; j < matrix_size; j++)
		{
			mat2[i][j] = i+j*3;
		}
	}

    startTimer(&totalTime);
	matMult(mat1,mat2,prod);
    stopTimer(&totalTime);
    printTimer(&totalTime);	

	for (i = 0;i < matrix_size; i++)
	{
		printf("\n");
		for (j = 0; j < matrix_size; j++)
		{
			printf("\t%d ", prod[i][j]);
		}
	}
	
	printf("\nSequential done! \n \nStarting accelerated program...\n");


	// DSP VERSION START

	Char8* dspExecutable = NULL;
	Timer dspTime;
	initTimer(&dspTime, "Total time accelerated");

	// Check for executable path
	if (argc != 3) {
		printf("Usage : %s <absolute path of DSP executable>\n", (int) argv[0]);
	}
	else {
		dspExecutable = argv[1];
		accelMult(dspExecutable,argv[2], mat1, mat2, prodAccel);
		printf("\nAccelerated done!\n");
	}
	// print accel results
	for (i = 0;i < matrix_size; i++)
	{
		printf("\n");
		for (j = 0; j < matrix_size; j++)
		{
			printf("\t%d ", prodAccel[i][j]);
		}
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
