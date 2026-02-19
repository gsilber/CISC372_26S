#include <stdio.h>
#include <stdlib.h>

//globals
double *matrix_flat;
double **matrix;
double *vector;
double *result;
long long size;

//generate a matrix and vector of the specified size, and initialize them with some values
void generate_matrix_and_vector() {
	printf("Enter the size for our matrix and vector (assume matrix is square)\n");
	long long n;
	scanf("%lld", &n);
	size=n;
	printf("Generating a %lld x %lld matrix and a vector of size %lld\n", n, n, n);
	matrix_flat = malloc(n * n * sizeof(double));
	matrix = malloc(n * sizeof(double*));
	for (int i = 0; i < n; i++) {
		matrix[i] = &matrix_flat[i * n];
	}
	vector = malloc(n * sizeof(double));
	result = malloc(n * sizeof(double));
	for (int i = 0; i < n; i++) {
		vector[i] = (double)(i + 1);
		result[i] = 0.0;
		for (int j = 0; j < n; j++) {
			matrix[i][j] = (double)(i * n + j + 1);
		}
	}
}

//free the memory allocated for the matrix and vector
void free_vector_and_matrix() {
	free(matrix_flat);
	free(matrix);
	free(vector);
	free(result);
}	

//print the matrix and vector (for debugging purposes)
//params: matrix, vector, size of both
//returns: void
void printMatrix(double** matrix, int n) {
	printf("Matrix:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%6.2f ", matrix[i][j]);
		}
		printf("\n");
	}
}

//print the vector 
//params: vector, size of vector
//returns: void
void printVector(double* vector, int n) {
	printf("Vector:\n");
	for (int i = 0; i < n; i++) {
		printf("%6.2f\n", vector[i]);
	}
}
