#include <stdio.h>
#include <stdlib.h>

#define N 5
#define M 6

// Function 1: array of arrays
void matrixArrayOfArrays(int n, int m) {
    float **matrix = (float **)malloc(n * sizeof(float *));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed for matrix rows.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        matrix[i] = (float *)malloc(m * sizeof(float));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for row %d.\n", i);
            exit(1);
        }
    }

    // Fill with values 1..n*m
    int val = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = (float)val++;
        }
    }

    // Print original matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%f", matrix[i][j]);
            if (j < m - 1) printf("\t");
        }
        printf("\n");
    }

    // Print transpose
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            printf("%f", matrix[i][j]);
            if (i < n - 1) printf("\t");
        }
        printf("\n");
    }

    // Free memory
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function 2: one big array
void matrixOneBigArray(int n, int m) {
    float **matrix = (float **)malloc(n * sizeof(float *));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed for matrix rows.\n");
        exit(1);
    }

    float *data = (float *)malloc(n * m * sizeof(float));
    if (data == NULL) {
        fprintf(stderr, "Memory allocation failed for matrix data.\n");
        exit(1);
    }

    // Set row pointers
    for (int i = 0; i < n; i++) {
        matrix[i] = &data[i * m];
    }

    // Fill with values 1..n*m
    int val = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = (float)val++;
        }
    }

    // Print original matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%f", matrix[i][j]);
            if (j < m - 1) printf("\t");
        }
        printf("\n");
    }

    // Print transpose
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            printf("%f", matrix[i][j]);
            if (i < n - 1) printf("\t");
        }
        printf("\n");
    }

    // Free memory
    free(data);
    free(matrix);
}

int main(int argc, char **argv) {
    matrixArrayOfArrays(N, M);
    matrixOneBigArray(N, M);
    return 0;
}

//**
// QUESTIONS
// 
// The array of arrays method is flexible because each row is a separate allocation, allowing rows to be resized or swapped independently and making it possible to create jagged arrays where rows have different lengths. However, it has poorer performance for most numerical tasks because the data is not stored contiguously, which leads to worse cache locality, more pointer chasing, and slightly more complex memory management since you must allocate and free many small blocks.
//
//The one big block method stores all elements in a single contiguous memory region, which improves cache performance, allows fast sequential access. Its main drawback is inflexibility: all rows must have the same length, and resizing or removing a row requires moving data or reallocating the entire block. If this is the case, then it is best to use arrays
// */