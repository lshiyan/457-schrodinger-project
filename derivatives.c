#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "derivatives.h"

double Derivative_FirstD(double x, double (*func)(double)){
    double h;
    h=pow(10,-5);
    if (x!=0.0){
        h=h*x;
    }
    double df=((*func)(x+h)-(*func)(x-h))/(2*h);
    return df; //Calculating first derivative using finite differences.
}

double Derivative_SecondD(double x, double (*func)(double)){
    double h;
    h=pow(10,-5);
    if (x!=0.0){
        h=h*x;
    }

    double df=((*func)(x+h)+(*func)(x-h)-2*(*func)(x))/(h*h);
    return df; //Calculating seocnd derivative using finite differences.
}