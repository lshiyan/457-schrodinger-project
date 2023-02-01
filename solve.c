#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "solve.h"

double Solve_Get_Df (double (*func)(double), double x); //Declaring test function.

double Solve_Bisect (double nu, double (*func)(double), double x_min, double x_max, double tol, int *count){
    double x_mid, f_max, f_min, f_mid, err; //Defining the relevant parameters.
    int count_max; //Maximum number of iterations allowed for the recursions.
    count_max=1000;
    *count+=1; //Every time the function recurses, the value of the int pointed to by the *count pointer increases by one. Manages recursion depth.

    if (*count>count_max){
        fprintf(stderr, "Solve_Bisect: Done %d iterations without convergence.\n", count_max);
        fprintf(stderr, "Exiting \n");
        exit(0); //Exiting if the bisect method iterates too much.
    }

    f_max=(*func)(x_max)-nu;
    f_min=(*func)(x_min)-nu;

    //If either x_max or x_min are the zero, then they are returned.
    if (f_max==0.0){
        return x_max;
    }
    
    if (f_min==0.0){
        return x_min;
    }

    //If the function has the same parity at the two endpoints, then there is not necessarily a solution between the two points.
    if (f_max*f_min > 0.0){
        fprintf(stderr, "Solve_Bisect: No solution with this range.\n");
        fprintf(stderr, "Exiting \n");
        exit(0);
    }

    x_mid=(x_min+x_max)/2.0;
    f_mid=(*func)(x_mid)-nu; //Calculating midpoints.

    //Making sure the midpoints aren't the zeros.
    if (f_mid==0){
        return x_mid; //Returning midpoint if f(x_mid) close enough to nu.
    }

    if(nu != 0.0) {err = fabs(f_mid/nu);}
    else {err = fabs(f_mid);} /*We want f(x_mid) to be small *relative* to our desired value, i.e if the value is 0.01 and f(x_mid) is 0.02, it is
                                    small, but not small relative to 0.01*/


    if (err<tol){return x_mid;}//Returning the midpoint if the error is small enough.

    if (f_mid*f_max<0.0){//Calling the function again using the midpoint as the left point if the parity of the right endpoint and the midpoint don't match.
        return Solve_Bisect(nu, func, x_mid, x_max, tol, count);
    }

    else{//Calling the function again using the midpoint as the right point if the parity of the left endpoint and the midpoint don't match.
        return Solve_Bisect(nu, func, x_min, x_mid, tol, count);
    }
}

double Solve_Get_Df(double (*func)(double), double x_old){
    double h, df;
    if(x_old != 0.0) { h = x_old*1.0E-5; }
    else {h = 1.0E-5; }
    df = (*func)(x_old+h) - (*func)(x_old-h);
    df /= 2.0*h;
    return df; //Calculating first derivative of a function using finite differences.
}

double Solve_Newton
(double nu, double (*func)(double), double x_0, double tol, int *count){
    double x_old, x_new, err, df, h; //Relevant parameters similar to Bisect.
    int count_max;
    count_max = 1000;
    x_old = x_0; //Starting point of iteration.
    do{
        df=Solve_Get_Df(func, x_old);

        if (fabs(df)<tol){
            fprintf(stderr, "Solve_Get_Df: Derivative is 0 \n");
            fprintf(stderr, "Exiting \n");
            exit(0); //Divide by 0 error.
        }

        x_new=x_old + (nu-(*func)(x_old))/df;
        err=fabs((x_new-x_old)/x_old);
        x_old=x_new;
        *count+=1; //Calculating next iteration, and increasing the count value by 1 to manage recursion.

        if (*count==count_max){
            fprintf(stderr, "Solve_Get_Df: Too many iterations \n");
            fprintf(stderr, "Exiting \n");
            exit(0); //Too many iterations, similar error to Bisect.
        }
    }while (err>tol); //Continue doing this while the error is greater than a certain tolerance.

    return x_new; //Return the value once the error gets close enough to 0.
}
