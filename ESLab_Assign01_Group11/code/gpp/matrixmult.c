#include <stdio.h>
#include "Timer.h"

#define MATRIX_SIZE_DEFAULT 128

void matMult(int size, int * mat1, int * mat2, int * product);

int main(int argc, char * argv[])
{
	Timer totalTime;
	initTimer(&totalTime, "Total Time");

	int matrix_size = MATRIX_SIZE_DEFAULT;
	if (argc > 1) {
		matrix_size = atoi(argv[1]);
	}

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

	for (i = 0; i < matrix_size; i++) {
		for (j = 0; j < matrix_size; j++) {
			matrix1[i * matrix_size + j] = i + j * 2;
		}
	}

	for(i = 0; i < matrix_size; i++) {
		for (j = 0; j < matrix_size; j++) {
			matrix2[i * matrix_size + j] = i + j * 3;
		}
	}

	startTimer(&totalTime);
	matMult(matrix_size, matrix1, matrix2, matrix_product);
	stopTimer(&totalTime);
	printTimer(&totalTime);	

	for (i = 0; i < matrix_size; i++) {
//		printf("\n");
		for (j = 0; j < matrix_size; j++) {
//			printf("\t%d ", matrix_product[i * matrix_size + j]);
		}
	}

	printf("\nDone !!! \n");
	free(matrix1);
	free(matrix2);
	free(matrix_product);
	return 0;
}

void matMult(int size, int * mat1, int * mat2, int * prod)
{
	int i, j, k;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			prod[i * size + j] = 0;
			for(k = 0; k < size; k++) {
				prod[i * size + j] += mat1[i * size + k] * mat2[k * size + j];
			}
		}
	}
}
