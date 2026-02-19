#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "function.h"

#define DEFAULT_NUM_TRAPS 20

unsigned long long getNumTraps(int argc,char** argv){
	if (argc==1) return DEFAULT_NUM_TRAPS;
	return atol(argv[1]);
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
	unsigned long long  traps=getNumTraps(argc,argv);
	double h=(b-a)/traps;

	//here is where the parallel stuff comes in.
	unsigned long long local_traps=traps/com_sz;
	double start=a+my_rank*local_traps*h;
	double end=start+local_traps*h;
	double local_approx=Trap(start,end,local_traps,h);
	if (my_rank==0){
		double approx=local_approx;
		for (int source=1;source<com_sz;source++){
			MPI_Recv(&local_approx,1,MPI_DOUBLE,source,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			approx+=local_approx;
		}
		printf("The ln(3) is approximately %.20f with %llu trapezoids\n",approx,traps);
	}else{
		MPI_Send(&local_approx,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
	}

	MPI_Finalize();
}
