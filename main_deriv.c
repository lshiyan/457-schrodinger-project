#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "derivatives.h"

double test_func(double x);

int main(){
    int i, imax;
    double x, dx, x_min, x_max, f, df, ddf;
    FILE *output; 
    x_min = 0.0;
    x_max = 15.0;
    imax = 1000;//Setting x-range and smallness of x step.
    dx = (x_max - x_min)/((double) imax);//Setting small x step, will iterate our derivative methods through each step.
    output = fopen("derivative_test.dat","w");
    for (i=0; i<=imax; i++){
        x = x_min + dx*i;
        f= test_func(x);//Inputting test function.
        df=Derivative_FirstD(x, test_func);//Calculating first derivative at given point.   
        ddf=Derivative_SecondD(x, test_func);//Calculating second derivative at given point.
        fprintf(output, "%e %e %e %e\n", x, f, df, ddf);//Printing values to a text file.
    }
    fclose(output); 
    return 0;
}
double test_func(double x){
    return x; //Test function.
}