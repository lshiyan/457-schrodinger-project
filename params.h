#ifndef PARAMS_H
#define PARAMS_H
#define hbarc (197.3) 

typedef struct params{
    double mass; 
    double Ea;
    double ka; 
    double r0;
    double x0; 
    int ell;
    char *mass_unit; 
    char *length_unit; 
    double nucA; 
    double nucZ; 
    double Et_min;
    double Et_max;
} Params;

typedef struct dynamic_vars{
    double Eb; 
    double kb; 
    double rc; 
    double Et; 
    double xc; 
    double rf; 
    double xf; 
    double Et_min;
    double Et_max;
} DynamicVars; 

extern Params PARAM_DATA; //Defining some parameters that will be used.

#endif