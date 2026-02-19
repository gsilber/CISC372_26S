#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "function.h"

#define DEFAULT_NUM_TRAPS 20

void getNumTraps(int my_rank,int com_sz, unsigned long long* n_p){
	if (my_rank==0){
		printf("Enter the number of trapezoids \n");
		scanf( "%llu",n_p);
	}
	MPI_Bcast(n_p,1,MPI_LONG_LONG,0,MPI_COMM_WORLD);
}

double Trap(double start, double end, unsigned long long trap_count,double base_len){
	double approx=(func(start)+func(end))/2;
	for (double i=1;i<trap_count;i++){
		double x=start+i*base_len;
		approx+=func(x);
	}
	approx=base_len*approx;
	return approx;
}
int main(int argc,char** argv){
	int my_rank,com_sz;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &com_sz);
	unsigned long long  traps;
	getNumTraps(my_rank,com_sz,&traps);
	double h=(b-a)/traps;

	//here is where the parallel stuff comes in.
	unsigned long long local_traps=traps/com_sz;
	double start=a+my_rank*local_traps*h;
	double end=start+local_traps*h;
	double local_approx=Trap(start,end,local_traps,h);
	double approx=0;
	MPI_Reduce(&local_approx,&approx,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	if (my_rank==0){
		printf("The ln(3) is approximately %.20f with %llu trapezoids\n",approx,traps);
	}

	MPI_Finalize();
}
