//globals
extern double *matrix_flat;
extern double **matrix;
extern double *vector;
extern double *result;
extern long long size;

//generate a matrix and vector of the specified size, and initialize them with some values
void generate_matrix_and_vector();
//free the memory allocated for the matrix and vector
void free_vector_and_matrix();

//print the matrix and vector (for debugging purposes)
//params: matrix, vector, size of both
//returns: void
void printMatrix(double** matrix, int n);

//print the vector 
//params: vector, size of vector
//returns: void
void printVector(double* vector, int n);