#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "extremum.h"

double test_func(double x);

int main(void){
    double x_init = 1.0;//Initial point to start the Newton Method from, make sure it's not singular.
    double *curvature;
    double extremum=Extremum_GetExtremum(test_func, x_init, curvature);
    double curve=*curvature;
    FILE *output;
    output = fopen("extremum_test.dat","w");//Opening file.
    fprintf(output, "%e %e %e \n", extremum, test_func(extremum), curve);//Writing relevant parameters to file.
    fclose(output);
    return 0;
}
double test_func(double x){
    double f;
    f = x*x - 2.0*x + 1;
    // Test Case 2:
    // f = 1.0/x/x - 2.0/x;
    // Test Case 3:
    // f = 1.0/x/x - 1.0/(1.0 + exp(x - 5.0));
    return f; //Returning test function.
}