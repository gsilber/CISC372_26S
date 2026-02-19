#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "function.h"

#define DEFAULT_NUM_TRAPS 20

//getNumTraps: gets the number of trapezoids by requsting input on process 0 and broadcasting it to the other processes
//Params: my_rank - the rank of the process, com_sz - the total number of processes, 
// n_p - a pointer to store the number of trapezoids
//Returns: void
//NOTE: This function is different from the previous version because we are now using MPI to get the number of trapezoids from the user and broadcast it to all processes
void getNumTraps(int my_rank,int com_sz, unsigned long long* n_p){
	if (my_rank==0){
		printf("Enter the number of trapezoids \n");
		scanf( "%llu",n_p);
	}
	MPI_Bcast(n_p,1,MPI_LONG_LONG,0,MPI_COMM_WORLD);
}

//Trap: estimates the integral of func from start to end using the trapezoidal rule with trap_count trapezoids and base length base_len
//Params: start - the start of the interval, end - the end of the interval,
//trap_count - the number of trapezoids to use, base_len - the length of the base of each trapezoid
//Returns: the estimated integral of func from start to end
//NOTE: This function is unchanged from the serial version, we are just passing smaller intervals based on the rank of the process
double Trap(double start, double end, unsigned long long trap_count,double base_len){
	double approx=(func(start)+func(end))/2;
	for (double i=1;i<trap_count;i++){
		double x=start+i*base_len;
		approx+=func(x);
	}
	approx=base_len*approx;
	return approx;
}

//Note: We are using MPI_Reduce to sum up the local approximations from each process instead of sending them to process 0 and summing them there. This is more efficient because it reduces the amount of communication between processes.
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
	MPI_Barrier(MPI_COMM_WORLD); //Make sure all processes have finished getting the number of trapezoids before we start the timer
	double mytime = MPI_Wtime();
	double local_approx=Trap(start,end,local_traps,h);
	double approx=0;
	//Do a tree reduction to sum up the local approximations from each process and store the result in approx on process 0
	MPI_Reduce(
	 &local_approx,  	//This is what we want to sum from each process.
	 &approx,  		//This is the variable to store the result in.  The result will only be valid in process 0
	 1, 				//Number of elements to send (in this case it is jsut a single double),
	 MPI_DOUBLE,  	//The type of the data
	 MPI_SUM,     	//The type of reduction we want
	 0, 				//The process rank where approx will be populated by the reduction operation
	 MPI_COMM_WORLD); //Same as always
	if (my_rank==0){
		mytime = MPI_Wtime()-mytime;
		printf("The ln(3) is approximately %.20f with %llu trapezoids in %lf seconds\n",approx,traps,mytime);
	}

	MPI_Finalize();
}
