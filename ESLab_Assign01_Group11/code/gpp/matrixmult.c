#include <stdio.h>
#include "Timer.h"

#define MATRIX_SIZE_DEFAULT 128

void matMult(int size, int * mat1, int * mat2, int * product);
void matTranspose(int size, int * mat, int * trans);

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
		fprintf(stderr, "Could not allocate memory for matrix\n");
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

	int * matrix2_trans = malloc(matrix_size * matrix_size * sizeof(int));
	if (matrix2_trans == NULL) {
		fprintf(stderr, "Could not allocate memory for transpose matrix\n");
		matrix2_trans = matrix2;
	}
	matTranspose(matrix_size, matrix2, matrix2_trans);
	matMult(matrix_size, matrix1, matrix2_trans, matrix_product);
	if (matrix2_trans != matrix2) {
		free(matrix2_trans);
	}

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

void matTranspose(int size, int * mat, int * trans)
{
	int i, j;

	if (trans == mat) {
		// transpose in-place
		for (i = 0; i < size; i++) {
			for (j = i+1; j < size; j++) {
				int tmp = mat[i * size + j];
				mat[i * size + j] = mat[j * size + i];
				mat[j * size + i] = tmp;
			}
		}
	} else {
		// transpose copy
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				trans[i * size + j] = mat[j * size + i];
			}
		}
	}
}

// mat2 must be transposed
void matMult(int size, int * mat1, int * mat2, int * prod)
{
	if (size < 1) {
		return;
	}

	int i, j, k;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			int sum = 0;
			//prod[i * size + j] = 0;
			for(k = 0; k < size; k++) {
				sum += mat1[i * size + k] * mat2[j * size + k];
			}
			prod[i * size + j] = sum;
		}
	}
}
