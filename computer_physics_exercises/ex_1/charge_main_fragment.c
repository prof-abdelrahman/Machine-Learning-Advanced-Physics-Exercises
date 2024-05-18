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



/***************** main program *********************************/
int main(int argc, char **argv)
{
  int num_charges = 2;                               /* number of charges */
  int dim=2;                                  /* dimensionality of system */
  double q[num_charges];                              /* value of charges */
  double pos[num_charges][dim];                    /* position of charges */
  int c;                                                      /* counters */
  double x[dim];                                          /* space vector */
  double potential;                           /* for summing up potential */
  double dr;                       /* difference (in a certain direction) */
  double r, r2;           /* absolute value of difference vector, squared */
  int d;                                             /* dimension counter */



  /** setup charges **/
  q[0] = 1; pos[0][0] = -1.025; pos[0][1] = 0;
  q[1] = -1; pos[1][0] = 1.025; pos[1][1] = 0;

  int no_of_values = 0;
  
  
  x[0] = 1.0; x[1] = -0.5;  /* example for setting position */
  /** iterate over some positions **/
  for (x[0] = -2.0; x[0] <= 2.0; x[0] += 1)
    for (x[1] = -2.0; x[1] <= 2.0; x[1] += 1)
  
  /** COMPLETE THE MAIN PROGRAM HERE:                        **/
  /** ITERATE SUITABLY x[0],x[1] AND OUTPUT EACH TIME x[0] x[1] V(x)   **/
    {
    /** INSIDE OF ITERATION: **/

      potential = 0.0;   /* calculation of potential at position x */
      for (c = 0; c < num_charges; c++)
      {
        dr = 0.0;
        for (d = 0; d < dim; d++)
        {
          dr += (x[d] - pos[c][d]) * (x[d] - pos[c][d]);
        }
        r = dr; 
        r2 = sqrt(r);

      /** COMPLETE THE CODE HERE TO CALCULATE THE COULOMB POTENTIAL **/
        potential += q[c] / r2;
      }
      printf("x:%f y:%f potential:%f\n", x[0], x[1], potential); /* POSSIBLY OUTPUT x[0], x[1] HERE **/
      no_of_values++;
      printf("no_of_values: %d\n", no_of_values);
    }

  return(0);
}

