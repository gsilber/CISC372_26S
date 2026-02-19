#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "function.h"

#define DEFAULT_NUM_TRAPS 20

//getNumTraps: gets the number of trapezoids to use from the command line, or returns a default value if none is given
//Params: argc - the number of command line arguments, argv - the array of command line
//Returns: the number of trapezoids to use
unsigned long long getNumTraps(int argc,char** argv){
	if (argc==1) return DEFAULT_NUM_TRAPS;
	return atol(argv[1]);
}

//Trap: estimates the integral of func from start to end using the trapezoidal rule with trap_count trapezoids and base length base_len
//Params: start - the start of the interval, end - the end of the interval,
//trap_count - the number of trapezoids to use, base_len - the length of the base of each trapezoid
//Returns: the estimated integral of func from start to end
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
	unsigned long long  traps=getNumTraps(argc,argv);
	double h=(b-a)/traps;
	clock_t startclock=clock();
	double approx=Trap(a,b,traps,h);
	clock_t endclock=clock();
	double time_spent = (double)(endclock - startclock) / CLOCKS_PER_SEC;
	printf("The ln(3) is approximately %.20f with %llu trapezoids in %lf seconds\n",approx,traps,time_spent);
}
