#include <stdio.h>
#include <stdlib.h>
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
	unsigned long long  traps=getNumTraps(argc,argv);
	double h=(b-a)/traps;
	double approx=Trap(a,b,traps,h);
	printf("The ln(3) is approximately %.20f with %llu trapezoids\n",approx,traps);
}
