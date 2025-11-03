#include <stdio.h>
#include <stdlib.h>

#define N 5
#define M 6

/* Function 1: allocate as an array of pointers to separately malloc'd rows */
void matrixArrayOfArrays(int n, int m) {
    float **A = (float **)malloc((size_t)m * sizeof(float *));
    if (!A) {
        fprintf(stderr, "malloc failed for row pointer array\n");
        return;
    }
    for (int i = 0; i < m; ++i) {
        A[i] = (float *)malloc((size_t)n * sizeof(float));
        if (!A[i]) {
            fprintf(stderr, "malloc failed for row %d\n", i);
            for (int k = 0; k < i; ++k) free(A[k]);
            free(A);
            return;
        }
    }

    float val = 1.0f;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = val++;
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%f", A[i][j]);
            if (j < n - 1) printf("\t");
        }
        printf("\n");
    }
    printf("\n");
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < m; ++i) {
            printf("%f", A[i][j]);
            if (i < m - 1) printf("\t");
        }
        printf("\n");
    }

    for (int i = 0; i < m; ++i) {
        free(A[i]);
    }
    free(A);
}

/* Function 2: allocate as an array of pointers + one big contiguous block */
void matrixOneBigArray(int n, int m) {
    float **A = (float **)malloc((size_t)m * sizeof(float *));
    if (!A) {
        fprintf(stderr, "malloc failed for row pointer array\n");
        return;
    }
    float *block = (float *)malloc((size_t)n * (size_t)m * sizeof(float));
    if (!block) {
        fprintf(stderr, "malloc failed for data block\n");
        free(A);
        return;
    }
    for (int i = 0; i < m; ++i) {
        A[i] = block + (size_t)i * (size_t)n;
    }

    float val = 1.0f;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = val++;
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%f", A[i][j]);
            if (j < n - 1) printf("\t");
        }
        printf("\n");
    }
    printf("\n");
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < m; ++i) {
            printf("%f", A[i][j]);
            if (i < m - 1) printf("\t");
        }
        printf("\n");
    }

    free(block);
    free(A);
}

int main(int argc, char **argv) {
    matrixArrayOfArrays(N, M);
    matrixOneBigArray(N, M);
    return 0;
}


