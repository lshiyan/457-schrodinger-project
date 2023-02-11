#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "derivatives.h"
#include "extremum.h"
#include "solve.h"

typedef double (*FuncPT)(double); 
FuncPT ORIG_FUNC; 
double Extremum_DF(double x);

double Extremum_GetExtremum(FuncPT func, double x_init, double *curvature){
    double tol, ddf;
    int count;
    ORIG_FUNC = func;//Pointer to inputted function.
    tol=1.0e-10;
    double root= Solve_Newton (0.0, Extremum_DF, x_init, tol, &count); //Calculating critical point by finding root of first derivative.
    double secondd= Derivative_SecondD(root, func);//Calculating second derivative at critical point.
    *curvature=secondd;//Setting pointer to value of second derivative at critical point.
    return root;
}

double Extremum_DF(double x){
    double f;
    f=Derivative_FirstD(x, ORIG_FUNC);//Calculating first derivative.
    return f;
}

