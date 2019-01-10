
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 *calc sqrt(a) + sqrt(b)
**/
 
 static double addsqrt(double a , double b){
	 return sqrt(a)+sqrt(b);
 }
 
 
 int main( int argc, char *argv[]){
	if(argc < 3) {
		printf("Usage: input double a and  double b\n");
		return 1;
	}
 
	double a = atof(argv[1]);
	double b = atof(argv[2]);
	
	double c = addsqrt(a,b);
	
	printf("sqrt(%f) + sqrt(%f) = %f\n", a, b, c);
	return 0;
 }