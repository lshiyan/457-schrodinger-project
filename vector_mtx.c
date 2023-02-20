#include <stdio.h>
#include <stdlib.h>
#include "vector_mtx.h"

double *vector_malloc(int nmax){
    double *pt;
    int n;
    pt = (double *)malloc(sizeof(double)*nmax);
    for(n=0; n<nmax; n++) pt[n] = 0.0;
    return pt; //Makes a 1-D list, returns a pointer to the first reference in the list.
}
double **mtx_malloc(int mmax, int nmax){
    double **pt;
    int m, n;
    pt = (double **)malloc(sizeof(double *)*mmax);
    for(m=0; m<mmax; m++){
        pt[m] = (double *)malloc(sizeof(double)*nmax);
    }
    for(m=0; m<mmax; m++){
        for(n=0; n<nmax; n++) {pt[m][n] = 0.0;}
    }
    return pt; //Makes a 2-D list, returns a pointer to the first reference in the first list.
}
void mtx_free(double **mtx, int mmax){
    int m;
    for(m=0; m<mmax; m++) { free(mtx[m]); }
    free(mtx);
    return;
}