/****************************************************************/
/*** Simulation of totally assymetric exclusion process       ***/
/*** A.K. Hartmann December 2014                              ***/
/*** Computeroriented Physics                                ***/
/*** University of Oldenburg, Germany 2014                    ***/
/****************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
  double alpha;   /* probability of inserting a particle */
  double beta;    /* probability of exiting a particle */
  int L;          /* number of sites */
  int *site;      /* array of sites */
} tasep_sys_t;




/******************* tasep_sweep() *******************/
/** Performs one sweep:                             **/
/** 1. possibly empties last site (prob. sys->beta) **/
/** 2. advances particles inside system (prob. 0.5) **/
/** 3. possibly occupies 1st site (prob. sys->alpha)**/
/** PARAMETERS: (*)= return-paramter                **/
/**      (*) sys: ptr to system                     **/
/** RETURNS:                                        **/
/**   current                                       **/
/*****************************************************/
double tasep_sweep(tasep_sys_t *sys)
{
  int num_hops;
  int t;      /* loop counter */

  num_hops = 0;
  /* if last site is occupied: empty with probability sys->beta: */
  if( (sys->site[sys->L-1] == 1) && (drand48() < sys->beta))
  {
    sys->site[sys->L-1] = 0;
    num_hops++;
  }

  /* advance particles with prob. 0.5 if successor is empty */
  for(t=sys->L-2; t>=0; t--)
    if( (sys->site[t] == 1)&&(sys->site[t+1] == 0)&&(drand48() < 0.5))
    {
      sys->site[t] = 0;
      sys->site[t+1] = 1;
      num_hops++;
    }

  /* if first site is empty, occupy with prob. sys->alpha: */
  if( (sys->site[0] == 0) && (drand48() < sys->alpha) )
    sys->site[0] = 1;

  return((double) num_hops/sys->L);
}


/***************** tasep_density() *******************/
/** Calculates density in system.                   **/
/** PARAMETERS: (*)= return-paramter                **/
/**      (*) sys: ptr to system                     **/
/** RETURNS:                                        **/
/**   density                                       **/
/*****************************************************/
double tasep_density(tasep_sys_t *sys)
{
  double density = 0.0;
  int t;  /* loop counter */

  for(t=0; t<sys->L; t++)
    density += sys->site[t];

  return(density/sys->L);
}


int main(int argc, char **argv)
{
  int seed;                               /* of random number generator */
  int sweep, num_sweeps;   /* current/total number of simulation sweeps */
  tasep_sys_t sys;                                     /* actual system */
  int argz = 1;              /* counter to treat command-line arguments */
  int t;                                                /* loop counter */
  double current, sum_current;             /* current of partciles, sum */
  double density, sum_density;                 /* particle density, sum */

  // test 
  // num_sweeps = 10;
  // sweep = 0;
  // int sys_L = 100;
  // double sys_alpha = 0.2;
  // double sys_beta = 0.1;
  // int sys_site[sys_L];
  // for (int i = 0; i < sys_L; i++) {
  //   sys_site[i] = 0;
  // }
  // sys.L = sys_L;
  // sys.alpha = sys_alpha;
  // sys.beta = sys_beta;
  // sys.site = sys_site;
  // printf("sys.L: %d\n", sys.L);
  // printf("sys.alpha: %f\n", sys.alpha);
  // printf("sys.beta: %f\n", sys.beta);
  // printf("sys.site: ");
  // for (int i = 0; i < sys.L; i++) {
  //   printf("%d ", sys.site[i]);
  // }
  // printf("\n");
  // end test

  seed = 1000;

  if(argc - argz < 4)
  {
    printf("USAG:E %s <L> <alpha> <beta> <#sweeps>\n", argv[0]);
    exit(1);
  }
  sys.L = atoi(argv[argz++]);
  sscanf(argv[argz++], "%lf", &sys.alpha);
  sscanf(argv[argz++], "%lf", &sys.beta);
  num_sweeps = atoi(argv[argz++]);

  sys.site = (int *) malloc(sys.L * sizeof(int));         /* initialize */
  for(t=0; t<sys.L; t++)
    sys.site[t] = 0;


  /** main simulation loop */
  sum_current = 0;
  sum_density = 0;
  for(sweep=0; sweep<num_sweeps; sweep++)
  {
    current = tasep_sweep(&sys);
    density = tasep_density(&sys);
    sum_current += current; sum_density += density;
    /*for(t=0; t<sys.L; t++)
      printf("%1d", sys.site[t]);
      printf("\n");*/
    printf("%d %f %f %f %f\n", sweep, current, (double) sum_current/(sweep+1), 
	   density, sum_density/(sweep+1));
  }

  free(sys.site);                                        /* free memory */
  return(0);
}
