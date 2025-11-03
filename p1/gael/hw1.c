#include <stdio.h>
#include <stdlib.h>
#define N 5
#define M 6


//Function to print the matrix
void printMatrix(float** matrix, int row, int column){
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            printf("%f", matrix[i][j]);
            printf("\t");
        }
        printf("\n");
    }
}

// Function to free the malloc
void freeMatrix1(float** matrix, int row, int column){
    // Frees each array inside the main array
    for (int i = 0; i < row; i++)
    {
        free(matrix[i]);
    }
    // Lastly free's the main array
    free(matrix);   
}


// Problem 1
void matrixArrayOfArrays(int n, int m){
    // Create initial Array of pointers
    float** arrRow = malloc(m * sizeof(float*));
    // loop through the size of inital array to create an array of size n in each
    for (int i = 0; i < m; i++)
    {
        float* arrCol = malloc(n * sizeof(float));
        arrRow[i] = arrCol;
    }

    // Now add the numbers to the matrix
    int counter = 1;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arrRow[i][j] = counter;
            counter++;
        }
    }

    printMatrix(arrRow, m, n);
    freeMatrix1(arrRow, m, n);
}

void freeMatrix2(float** matrix){
    // Free's longArr
    free(matrix[0]);

    // Free's pointerArr
    free(matrix);
}

// Function to print the transposed matrix
void printTransposedMatrix(float** matrix, int row, int column){
    // Outer loop for columns
    for (int j = 0; j < column; j++) { 
        // Inner loop for rows
        for (int i = 0; i < row; i++) {    
            printf("%f\t", matrix[i][j]);
        }
        printf("\n");
    }
}


// Problem 2:
void matrixOneBigArray(int n, int m){
    float** pointerArr = malloc(m * sizeof(float*));
    float* longArr = malloc(n * m * sizeof(float));

    // connect the pointerArr to the longArr
    for (int i = 0; i < m; i++)
    {
        // Pointer Arithmetic 
        pointerArr[i] = longArr + (n * i);
    }
    
    
    int counter = 1;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            pointerArr[i][j] = counter;
            counter++;
            // pointerArr[i][j] = (j * m) + i + 1;
        }
    }
    
    printTransposedMatrix(pointerArr, m, n);
    freeMatrix2(pointerArr);

}




int main(){
    // printf("Hello World");

    // Problem 1:
    matrixArrayOfArrays(N, M);

    // space inbetween
    // printf("\n");

    // Problem 2:
    matrixOneBigArray(N, M);

    return 0;
}

/*
 Number 5 Part A:

    The pros of the first is very felxable since you can resize each array within the array of pointers.
    Which also means that each array can be different sizes.
    The Cons of the first is that it uses a lot of memory to conatin all of those arrays.
    The more you add, the more memoy you end up eating away.

    The Pros for the second was that it doesn't have to be to complex, by allocating space for each array.
    Since we only needed to allocate two arrays, it makes it easy to free them. (Cause less problems)
    The cons of the second is that it's not as flexable.

 */

/*
Number 5 Part B:
    For the first method I think a good situation would be sorting, since it's so felxable.

    Foer the second method I think a good situation is if you are only focused on speed.
*/