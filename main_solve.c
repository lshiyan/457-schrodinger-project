#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "solve.h"

double f_solve(double x){
    return sin(x);
}

double f_solve(double x); //Declaring the function that is to be solved.

int main(void){
    double x_max, x_min, x, tol;
    int count;
    fprintf(stdout, "Solve_Bisect\n");
    count = 0;
    tol = 1.0e-10; //Defining error tolerance, and setting a count int to be passed as reference.
    x = Solve_Bisect(0.0, f_solve, 0.1, 4.0, tol, &count);
    fprintf(stdout, "count = %d\n", count);
    fprintf(stdout, "x = %e\n", x);
    fprintf(stdout, "Solve_Newton\n");
    x = Solve_Newton(0.0, f_solve, 4.0, tol, &count);
    fprintf(stdout, "count = %d\n", count);
    fprintf(stdout, "x = %e\n", x);
    return 1; //Test cases, outputs count number, numerical solution, and method of solution, (Newton or Bisect).
}

