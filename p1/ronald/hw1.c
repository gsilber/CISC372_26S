#include <stdio.h>
#include <stdlib.h>
#define N 5
#define M 6

void matrixArrayofArrays(int n, int m);
void matrixFlat(int n, int m);
void matrixOneBigArray(int n, int m);

int main(int argc,char** argv) {
    matrixArrayofArrays(N, M);
    matrixOneBigArray(N, M);
    return 0;
}

void matrixArrayofArrays(int n, int m) {
    if (n <= 0 || m <= 0) {
    printf ("void.\n");
    return;
    }

    float **rows = malloc(n * sizeof(float*));
    if (!rows) {
        perror("allocation failed");
        return;
    }

    for (int i = 0; i < n; i++) {
        rows[i] = malloc(m * sizeof(float));
        if (!rows[i]) {
            perror("allocation failed");
            for (int k = 0; k < i; k++)
            free(rows[k]);
            free(rows);
            return;
        }  
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            rows[i][j] = (float)(i * m + j + 1);
        }
    }

    for (int i = 0 ; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%6.6f\t", rows[i][j]);
        }
        printf("\n");
    }
    
    printf(" \n");

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            printf("%6.6f\t", rows[i][j]);
        }
        printf("\n");
    }
    
    printf(" \n");
    
    for (int i = 0; i < n; i++) {
        free (rows[i]);
    }
    free(rows);

    matrixFlat(n, m);
}

void matrixFlat(int n, int m) {
     if (n <= 0 || m <= 0) {
    printf ("void.\n");
    return;
    }

    float *a = malloc(n * m * sizeof(float));
    if (!a) {
        perror("void.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i * m + j] = (float)(i * m + j + 1);
        }
    }

    for (int i = 0 ; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%6.6f\t", a[i * m + j]);
        }
        printf("\n");
    }
    
    printf(" \n");

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            printf("%6.6f\t", a[i * m + j]);
        }
        printf("\n");
    }
    printf(" \n");
    free(a);
}


void matrixOneBigArray(int n, int m) {
    if (n <= 0 || m <= 0) {
    printf ("void.\n");
    return;
    }

    float **rows = malloc(n * sizeof(*rows));
    if (!rows) {
        perror("allocation failed");
        return;
    }

    float *block = malloc(n * m * sizeof(*block));
    if (!block) {
       perror("allocation failed");
       free(rows);
       return; 
    }
    for (int i = 0; i < n; ++i)
        rows[i] = block + (size_t)i * m;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            rows[i][j] = (float)(i * m + j + 1);

    for (int i = 0 ; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%6.6f\t", rows[i][j]);
        }
        printf("\n");
    }
    
    printf(" \n");

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            printf("%6.6f\t", rows[i][j]);
        }
        printf("\n");
    }
    
    printf(" \n");
    
    free(block);
    free(rows);
}

// 5. a. What are the pros and cons of each method of allocation?
// Pros: flexible, resource optimization, adaptibility
// Cons: Memory leaks, slower perfomance, complexity

// 5. b. Can you think of a situation where one of these would be better than the other?
// Stack: small & fast, auto-frees; limited size/lifetime.
// Heap: large/dynamic; manual free, slower, leak risks.
// small/temporary → stack; big/dynamic/shared → heap