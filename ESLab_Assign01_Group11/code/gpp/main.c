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
	
	int * matrix1 = malloc(matrix_size * matrix_size * sizeof(int));
	int * matrix2 = malloc(matrix_size * matrix_size * sizeof(int));
	int * matrix_product = malloc(matrix_size * matrix_size * sizeof(int));

	if (matrix1 == NULL || matrix2 == NULL || matrix_product == NULL) {
		fprintf(stderr, "Could not allocate memory\n");
		free(matrix1);
		free(matrix2);
		free(matrix_product);
		return -1;
	}

	int i, j;

	printf("Starting sequential program...\n");

	// SEQUENTIAL VERSION START
	
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
	matMult(matrix_size,mat1,mat2,prod);
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
	if (argc < 2) {
		printf("Usage : %s <absolute path of DSP executable>\n", (int) argv[0]);
	}
	else {
		dspExecutable = argv[1];
		accelMult(dspExecutable,matrix_size, mat1, mat2, prodAccel);
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







void matMult(int size, int * mat1, int * mat2, int * prod)
{
	int i, j, k;
	for (i = 0;i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			prod[i][j]=0;
			for(k=0;k<size;k++)
				prod[i][j] = prod[i][j]+mat1[i][k] * mat2[k][j];
		}
	}
}
