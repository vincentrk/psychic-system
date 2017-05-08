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

void matMult(int size, int * mat1, int * mat2, int * prod);

int main(int argc, char** argv)
{
    Timer totalTime;
    initTimer(&totalTime, "Total Time Sequential");

	int matrix_size = MATRIX_SIZE_DEFAULT;
	if (argc > 2) {
		matrix_size = atoi(argv[3]);
	}

    // prodAccel will hold the result from the accelerated algorithm
	
	int * mat1 = malloc(matrix_size * matrix_size * sizeof(int));
	int * mat2 = malloc(matrix_size * matrix_size * sizeof(int));
	int * prod = malloc(matrix_size * matrix_size * sizeof(int));

	if (mat1 == NULL || mat2 == NULL || prod == NULL) {
		fprintf(stderr, "Could not allocate memory\n");
		free(mat1);
		free(mat2);
		free(prod);
		return -1;
	}

	int i, j;

	printf("Starting sequential program...\n");

	// SEQUENTIAL VERSION START
	
	for (i = 0;i < matrix_size; i++)
	{
		for (j = 0; j < matrix_size; j++)
		{
			mat1[i*matrix_size+j] = i+j*2;			
		}
	}
	
	for(i = 0; i < matrix_size; i++)
	{
		for (j = 0; j < matrix_size; j++)
		{
			mat2[i*matrix_size+j] = i+j*3;
		}
	}

    startTimer(&totalTime);
	matMult(matrix_size,mat1,mat2,prod);
    stopTimer(&totalTime);
    printTimer(&totalTime);	

	for (i = 0;i < matrix_size; i++)
	{
		printf("\n");
		for (j = 0; j < matrix_size; j++)
		{
			printf("\t%d ", prod[i*matrix_size+j]);
		}
	}
	
	printf("\nSequential done! \n \nStarting accelerated program...\n");


	// DSP VERSION START

	Char8* dspExecutable = NULL;
	Timer dspTime;
	initTimer(&dspTime, "Total time accelerated");

	// Check for executable path
	if (argc < 2) {
		printf("Usage : %s <absolute path of DSP executable>\n", argv[0]);
	}
	else {
		dspExecutable = argv[1];
		accelMult(dspExecutable,matrix_size, mat1, mat2, prod);
		printf("\nAccelerated done!\n");
	}
	// print accel results
	for (i = 0;i < matrix_size; i++)
	{
		printf("\n");
		for (j = 0; j < matrix_size; j++)
		{
			printf("\t%d ", prod[i*matrix_size+j]);
		}
	}

	return 0;
}







void matMult(int size, int * mat1, int * mat2, int * prod)
{
	int i, j, k;
	for (i = 0;i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			prod[i*size+j]=0;
			for(k=0;k<size;k++)
				prod[i*size+j] = prod[i*size+j]+mat1[i*size+k] * mat2[k*size+j];
		}
	}
}
