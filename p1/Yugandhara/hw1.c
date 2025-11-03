#include <stdio.h>
#include <stdlib.h>

void matrixArrayOfArrays(int n, int m);
void matrixOneBigArray(int n,int m); 

#define N 5
#define M 6
         
int main (int argc,char** argv){
matrixArrayOfArrays(N,M);
matrixOneBigArray(N,M);
return 0;
}
void matrixArrayOfArrays(int n, int m){
	float** matrix = (float**)malloc(n*sizeof(float*));
	if(matrix == NULL){
        	printf("Memory allocation failed\n");
        	return;	
    	}
	int value = 1;
	
    	for(int i = 0; i < n; i++){
        	matrix[i] = (float*)malloc(m * sizeof(float));
        	if(matrix[i] == NULL){
            	for(int j = 0; j < i; j++){
                	free(matrix[j]);
            	}	
            	free(matrix);
            	printf("Memory allocation failed\n");
           	 return;
        	}
        for(int j = 0; j < m; j++){
        	matrix[i][j] = (float)value++;
        }
    }
		
   	for (int i = 0; i < n; i++) {
       		for (int j = 0; j < m; j++) {
        	    		printf("%f\t", matrix[i][j]);
		}
		printf("\n");
   	}
	printf("\n");
	for(int j = 0; j<m;j++){
		for(int i=0;i<n;i++){
			printf("%f\t", matrix[i][j]);
		}
		printf("\n");

	}
printf("\n");

	for (int i = 0; i < n; i++) {
  	     	free(matrix[i]);
    	}
		free(matrix);	

}

void matrixOneBigArray(int n, int m){
	float** matrix = (float**)malloc(n*sizeof(float*));
	float* data = (float*)malloc(n*m*sizeof(float));
	if(data ==NULL){
		free(matrix);
		return; 
	}
	for(int i=0; i<n;i++){
		matrix[i] = data +i*m; 
	}

	int value = 1;
	for (int i = 0; i < n; i++) {
        	for (int j = 0; j < m; j++) {
            	matrix[i][j] = (float)value++;
        	}
    	}
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                                printf("%f\t", matrix[i][j]);
                }
                printf("\n");
        }printf("\n");

        for(int j = 0; j<m;j++){
                for(int i=0;i<n;i++){  
                        printf("%f\t", matrix[i][j]);
                }          
                printf("\n");
                
        }printf("\n");
	free(data);
    free(matrix);
}
        
