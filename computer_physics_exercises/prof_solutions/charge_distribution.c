/*******************************************************************/
/*** Program for calculating the potential for a two-dimensional ***/
/*** charge distribution                                         ***/
/***                                                             ***/
/*** Lecture: Computational Physics                              ***/
/*** A.K. Hartmann 2011                                          ***/
/***                                                             ***/
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/** datastructure for one charge **/
typedef struct 
{
  double    q;      /* charge */
  double *pos;      /* position in d-dimensional space */
} charge_t;


/**************** coulomb_potential() *******************/
/** Calculates Coulomb potential (1/r) at position 'x' **/
/** in a 'dim' dimensional system, where a system of   **/
/** charges is given.                                  **/ 
/** PARAMETERS: (*)= return-paramter                   **/
/**         dim: dimension of system                   **/
/**           x: position where to obtain potential    **/
/** num_charges: number of charges                     **/
/**      charge: system of charges                     **/
/** RETURNS:                                           **/
/**     potential at 'x'                               **/
/********************************************************/
double coulomb_potential(int dim, double *x, int num_charges, charge_t *charge)
{
  double potential = 0.0;                  /* for summing up potential */
  double dr;                    /* difference (in a certain direction) */
  double r, r2;        /* absolute value of difference vector, squared */
  int c;                                             /* charge counter */
  int d;                                          /* dimension counter */
		 
  for(c=0; c<num_charges; c++)
  {
    r2 = 0.0;
    for(d=0; d<dim; d++)
    {
      dr = x[d] - charge[c].pos[d];
      r2 += dr*dr;
    }
    r = sqrt(r2);
    if(r == 0)
      potential += charge[c].q*1e10;
    else
      potential += charge[c].q/r;
  }

  return(potential);
}

/***************** main program *********************************/
int main(int argc, char **argv)
{
  int num_charges;                                   /* number of charges */
  int dim;                                   /* dimensionalyity of system */
  charge_t *charge;                                   /* array of charges */
  int c;                                                      /* counters */
  double *x;                                              /* space vector */

  dim = 2;
  num_charges = 2;

  /** allocate memory for charges etc **/
  x = (double *) malloc(dim*sizeof(double));
  charge = (charge_t *) malloc(num_charges*sizeof(charge_t));
  for(c=0; c<num_charges; c++)
    charge[c].pos = (double *) malloc(dim*sizeof(double));

  /** setup charges **/
  charge[0].q = 1; charge[0].pos[0] = -1.025; charge[0].pos[1] = 0;
  charge[1].q = -1; charge[1].pos[0] = 1.025; charge[1].pos[1] = 0;
  
  /** iterate over some positions **/
  for(x[0] = -2; x[0] <= 2; x[0] += 0.05)
    for(x[1] = -2; x[1] <= 2; x[1] += 0.05)
      printf("%f %f %f\n", x[0], x[1],
	     coulomb_potential(dim, x, num_charges, charge));

  for(c=0; c<num_charges; c++)                             /* free memory */
    free(charge[c].pos);
  free(charge);
  free(x);
  return(0);
}

