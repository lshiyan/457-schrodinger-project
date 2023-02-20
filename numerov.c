#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "numerov.h"
#include "numerov_params.h"
#include "vector_mtx.h"

void Numerov_Make_Fn (double *numerov_F, NumerovParams *Num_Params, DynamicVars *Dyn_Vars);
void Numerov_Advance_A_Step (double *y, int n, double *numerov_F, NumerovParams *Num_Params, DynamicVars *Dyn_Vars);

void Numerov_Advance (double *y, NumerovParams *Num_Params, DynamicVars *Dyn_Vars){
    double *numerov_F;
    int n;
    int nmax;
    nmax = Num_Params->nmax;
    
    numerov_F = vector_malloc(nmax+1); //Creating a list of length nmax+1.
    Numerov_Make_Fn(numerov_F, Num_Params, Dyn_Vars); //Creating a list to store all the y-values. Discretizes x-space.

    y[0] = Num_Params->y_0;
    y[1] = Num_Params->y_1; //Setting two known points to the first two values of the list.

    for(n=2; n<=nmax; n++){
        Numerov_Advance_A_Step(y, n, numerov_F, Num_Params, Dyn_Vars); //Advancing x-step and storing the value in numerov_F.
    }
    return;
}
void Numerov_Make_Fn(double *numerov_F, NumerovParams *Num_Params, DynamicVars *Dyn_Vars){
    int n;
    double x_n;
    for(n=0; n<=Num_Params->nmax; n++){
        double x_i=Num_Params->x_i;
        double h=Num_Params->h;
        x_n = x_i + h*n;
        numerov_F[n]=(Num_Params->NumerovFunc_F)(x_n, Dyn_Vars);//Makes the list that stores the y-values.
    }
    return;
}
void Numerov_Advance_A_Step (double *y, int n, double *numerov_F, NumerovParams *Num_Params, DynamicVars *Dyn_Vars){

    double h;
    double h2_over_12;
    h=Num_Params->h;
    h2_over_12=(h*h)/12;
    y[n]=0.0;
    if(y[n-1] != 0.0){
        y[n] += 2.0*(1 + 5.0*h2_over_12*numerov_F[n-1])*y[n-1];
    }
    if (y[n-2] != 0.0){
        y[n]-=(1-h2_over_12*numerov_F[n-2])*y[n-2];
    }
    y[n]/=(1-h2_over_12*numerov_F[n]); //Advances x-step and calculates the corresponding y-value. 
    return;
}

