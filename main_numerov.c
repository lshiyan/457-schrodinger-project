#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector_mtx.h"
#include "numerov.h"
#include "numerov_params.h"
#include "params.h"

double TestF(double x, DynamicVars *Dyn_Vars);

void ReadInNum_Params(char *input_file_name, NumerovParams *Num_Params);
void PrintParams(NumerovParams Num_Params);
void PrintY(double *y, NumerovParams Num_Params);

int main(int argc, char **argv){
    double *y;
    char *input;
    NumerovParams Num_Params;
    DynamicVars Dyn_Vars;

    input=argv[1];

    ReadInNum_Params(input, &Num_Params);
    PrintParams(Num_Params); //Reading in then printing our parameters.

    y=vector_malloc(Num_Params.nmax+1);
    Num_Params.NumerovFunc_F = TestF; //Test function.

    Numerov_Advance(y, &Num_Params, &Dyn_Vars);
    PrintY(y, Num_Params); //Printing the y-value in our y-list.
    free(y); 
    return 0;
}

double TestF(double x, DynamicVars *Dyn_Vars){
    //return -1.0; //SHO
    return -x; //Test function, solves y''=f(x)y, so Airy equation is y''=-xy.
}

void ReadInNum_Params(char *input_file_name, NumerovParams *Num_Params){
    FILE *input_file;
    double x_i, x_f, y_0, y_1;
    int ix;
    input_file = fopen(input_file_name, "r");

    fscanf(input_file, "%le %le %le %le %d", &x_i, &x_f, &y_0, &y_1, &ix);
    Num_Params->x_i=x_i;
    Num_Params->x_f=x_f;
    Num_Params->y_0=y_0;
    Num_Params->y_1=y_1;
    Num_Params->nmax=ix;
    double final=x_f;
    double initial=x_i;
    double step= (final-initial)/(Num_Params->nmax);
    Num_Params->h=step;
    fclose(input_file); //Reads in params, and assigns them to the appropriate variables.
    return;
}

void PrintParams(NumerovParams Num_Params){
    FILE *output;
    output = fopen("params.dat","w"); // Open a file for writing
    fprintf(output, "x_i = %e\n", Num_Params.x_i);
    fprintf(output, "x_f = %e\n", Num_Params.x_f);
    fprintf(output, "y_0 = %e\n", Num_Params.y_0);
    fprintf(output, "y_1 = %e\n", Num_Params.y_1);
    fprintf(output, "nmax = %d\n", Num_Params.nmax);
    fprintf(output, "h = %e\n", Num_Params.h);
    fclose(output); //Prints out read-in parameters.
    return;
}

void PrintY(double *y, NumerovParams Num_Params){
    FILE *output;
    int n;
    double xn;
    output=fopen("yfile.dat", "w");
    for(n=0; n<=Num_Params.nmax; n++){
        xn = Num_Params.x_i + n*Num_Params.h;
        fprintf(output, "%e %e\n", xn, y[n]);
    }
    fclose(output); //Prints out y-list and corresponding x-value.
    return;
}