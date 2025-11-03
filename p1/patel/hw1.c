#include <stdio.h>
#include <stdlib.h>

void matrixArrayOfArrays(int n, int m) {
    float **A = (float **)malloc(m * sizeof(float *));
    if (!A) { perror("malloc failed"); exit(1); }

    for (int r = 0; r < m; r++) {
        A[r] = (float *)malloc(n * sizeof(float));
        if (!A[r]) { perror("malloc failed"); exit(1); }
    }

    // Fill array
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            A[r][c] = (float)(r * n + c + 1);
        }
    }

    // Print matrix
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            printf("%8.6f ", A[r][c]);
        }
        printf("\n");
    }

    printf("\n");

    // Print transpose
    for (int c = 0; c < n; c++) {
        for (int r = 0; r < m; r++) {
            printf("%8.6f ", A[r][c]);
        }
        printf("\n");
    }

    printf("\n");

    // Free memory
    for (int r = 0; r < m; r++) {
        free(A[r]);
    }
    free(A);
}

void matrixOneBigArray(int n, int m) {
    float **rows = (float **)malloc(m * sizeof(float *));
    if (!rows) { perror("malloc failed"); exit(1); }

    float *data = (float *)malloc(m * n * sizeof(float));
    if (!data) { perror("malloc failed"); free(rows); exit(1); }

    for (int r = 0; r < m; r++) {
        rows[r] = &data[r * n];
    }

    // Fill array
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            rows[r][c] = (float)(r * n + c + 1);
        }
    }

    // Print matrix
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            printf("%8.6f ", rows[r][c]);
        }
        printf("\n");
    }

    printf("\n");

    // Print transpose
    for (int c = 0; c < n; c++) {
        for (int r = 0; r < m; r++) {
            printf("%8.6f ", rows[r][c]);
        }
        printf("\n");
    }

    printf("\n");

    free(data);
    free(rows);
}

#define N 5
#define M 6

int main(void) {
    matrixArrayOfArrays(N, M);
    matrixOneBigArray(N, M);
    return 0;
}

