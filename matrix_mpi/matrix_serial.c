#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


//matrix-vector multiplication
//params: matrix, vector, result vector, size of both
//returns: void (result is stored in the result vector)
//Side effect: modifies the result vector to contain the product of the matrix and vector
void matrix_vector_multiply(double** matrix, double* vector, double* result, int n) {
	for (int i = 0; i < n; i++) {
		result[i] = 0.0;
		for (int j = 0; j < n; j++) {
			result[i] += matrix[i][j] * vector[j];
		}
	}
}

int main() {
	generate_matrix_and_vector();
	printf("Multiplying matrices\n");
	matrix_vector_multiply(matrix, vector, result, size);
	printVector(result, size);
	free_vector_and_matrix();
	return 0;
}