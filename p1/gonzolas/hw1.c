#include <stdio.h>
#include <stdlib.h>
#define N 5
#define M 6

void matrixArrayOfArrays(int n, int m);
void matrixOneBigArray(int n, int m);
int main(void) {
    matrixArrayOfArrays(N, M);
    matrixOneBigArray(N, M);
    return 0;
}

void matrixArrayOfArrays(int n, int m) {
    float **matrix = (float **)malloc(m * sizeof(float *));
    if (!matrix) return;
    for (int i = 0; i < m; i++) {
        matrix[i] = (float *)malloc(n * sizeof(float));
        if (!matrix[i]) { 
            for (int k = 0; k < i; k++) free(matrix[k]);
            free(matrix);
            return;
        }
    }
    int value = 1;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = (float)value++;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f", matrix[i][j]);
            if (j < n - 1) printf("\t");
        }
        printf("\n");
    }
    printf("\n");
    //transpose
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            printf("%f", matrix[i][j]);
            if (i < m - 1) printf("\t");
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < m; i++) free(matrix[i]);
    free(matrix);
}

//second function
void matrixOneBigArray(int n, int m) {
    float **matrix = (float **)malloc(m * sizeof(float *));
    if (!matrix) return;
    float *data = (float *)malloc((size_t)m * (size_t)n * sizeof(float));
    if (!data) { free(matrix); return; }
    for (int i = 0; i < m; i++) matrix[i] = &data[i * n];
    int value = 1;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = (float)value++;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f", matrix[i][j]);
            if (j < n - 1) printf("\t");
        }
        printf("\n");
    }
    printf("\n");
    //transpose
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            printf("%f", matrix[i][j]);
            if (i < m - 1) printf("\t");
        }
        printf("\n");
    }
    free(data);
    free(matrix);
} 
// 5a. What are the pros and cons of each method of allocation?
// The pros: -each row is allocated on its own, allowing different row 
// lengths
//-the indexing with [row][col] matches the way we usually think about matrices
//-works well when rows do not all contain the same number of elements
//
//The cons:
//-Rows are scattered in memory, which can lead to fragmentation
//-Cache performance suffers since elements are not stored in one block
//-Requires a malloc for each row, increasing overhead
//-every row must be freed before freeing the pointer array itself
//
//------method two-------
//Pros: -Data is stored in one continuous chunk,helping performance
//-fewer malloc calls mean less extra memory used
//-just two free() calls to release everything
//The cons:
//-All rows must be the same length
//-it is not ideal for sparse or uneven matrices since space can be wasted
//
// 5b. Can you think of a situation where one of these would be better than the other?
// for array of arrays:
// -Choose this method when handling sparse data where some rows contain much less information
// -also when you expect to add or remove entire rows often
//
// for one big array:
// -Choose this when the data structure requires all rows to be the same length
// -when you are dealing with large matrices where speed is crucial
//
