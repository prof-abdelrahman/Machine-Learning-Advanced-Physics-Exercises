/**********************************************************/
/*** Simulation of diluted ferromagnet                  ***/
/***                                                    ***/
/*** Version 0.1.0.0                                    ***/
/***                                                    ***/
/*** A.K. Hartmann May 2005                             ***/
/***                                                    ***/
/**********************************************************/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "percol.h"
#include "diluted.h"

// extern void diluted_PT(int num_T, short int **spin, int num_n, int N, 
// 		       int *next,  short int *e, double *T, 
// 		       int *exch, int *tries);


// Write a function diluted_PT() (e.g. in a new file diluted_PT.c) which takes num_T=
// nT configurations and num_T temperature values as parameters. The functions performs
// for each configuration some sweeps (here, e.g., 1, maybe other values like num_T work
// better, never mind) of the local Monte Carlo (MC), by calling diluted_mc_T(). Af-
// terwards num_T−1 times two neighbouring configurations at Tk, Tk+1 are tried to be
// exchanged (each time k 2 {0, 1, 2, . . . ,num_T−2} is randomly selected). A full such cycle
// is considered as one step of the MC time.
// The Functions receives also arrays exch[] and tries[], by which the number of ac-
// cepted and attempted exchanges are counted, each time at the k-th entry. This is used
// to calculate the acceptance rates (double) exch[k]/tries[k].
// The head of the functions is:
/************************** diluted_PT() ***********************/
/** Does parallel tempering for diluted ferromagnet **/
/** at num_T temperatures T_0<T_1<...T_{num_T-1}. **/
/** NOTE: This implmentation is for maximum simplicity, **/
/** hence, it will perform poorly **/
/** PARAMETERS: (*)= return-paramter **/
/** num_T: number of temperatures **/
/** (*) spin_cfg: num_T spin-configurations **/
/** num_n: number of neighbours in lattice **/
/** N: number of spins **/
/** next: gives neighbours next[0..N][0..2*num_n+1] **/
/** e: sites arre ocupied (e[i]=1),empty (=0 ) **/
/** T: num_T temperatures in units of J **/
/** (*) exch: count accepted swaps T_k <-> T_{k+1} **/
/** (*) tries: count tried swaps T_k <-> T_{k+1} **/
/** RETURNS: **/
/** nothing **/
/***************************************************************/
// void diluted_PT(int num_T, short int **spin_cfg, int num_n, int N,
// int *next, short int *e, double *T,
// int *exch, int *tries)
// Hint 1: Inside diluted_PT()you also have to call diluted_energy().
// Hint 2: Exchange two configurations, by exchanging the corresponding two pointers
// stored in spin_cfg, do NOT exchange all spin values, which would be much slower.
void diluted_PT(int num_T, short int **spin_cfg, int num_n, int N,
                int *next, short int *e, double *T,
                int *exch, int *tries) {
    // int min = 0;
    // Perform local Monte Carlo sweeps for each configuration
    for (int i = 0; i < num_T; i++) {
        diluted_mc_T(spin_cfg[i], num_n, N, next, e, num_T,  T[i]);
    }

    // Perform temperature exchanges
    for (int k = 0; k < num_T - 1; k++) {
        // Randomly select two neighbouring configurations
        int k1 = rand() % (num_T-1);
        int k2 = (k1 + 1);

        // Calculate the energy difference between the two configurations
        double delta_E = diluted_energy(spin_cfg[k1], num_n, N, next, e) -
                         diluted_energy(spin_cfg[k2], num_n, N, next, e);

        // Perform the exchange with a probability based on the energy difference
        // delta_E <= 0 ||
        double metropolis_prob = exp(((1/ T[k1]) - (1/ T[k2])) * delta_E);
        // min = (metropolis_prob <= 1) ? metropolis_prob : 1;
        double random_num = r_0_1();
        if (random_num < metropolis_prob) {
            // Exchange the pointers to the configurations
            short int *temp = spin_cfg[k1];
            spin_cfg[k1] = spin_cfg[k2];
            spin_cfg[k2] = temp;

            // Increment the accepted exchange count
            exch[k]++;
        }

        // Increment the attempted exchange count
        tries[k]++;
    }
}


int main(int argc, char** argv)
{
  int dim;                                          /* dimension of system */
  int num_n;                             /* number of neighbors in lattice */
  int num_T;                                     /* number of temperatures */
  int num_sweeps, sweep;                              /* ... of simulation */
  double *T;                                               /* temperatures */ 
  double p_hole;                                 /* prob. pf having a hole */
  int real_id, real_id0;                     /* ID of realization (= seed) */
  int num_real;                                  /* number of realisations */
  int seed;                       /* seed of generator for simulation part */
  int size;                 /* size of system (if all sides have same size */
  int *l;                                               /* sizes of system */
  short int **spin;                                 /* spin configurations */
  short int *e;                       /* whether a spin is occupied or not */
  double energy, mag, mag2;                             /* ... of spin cfg */

  int do_up;                             /* start with all spins aligned ? */

  int N, N_spins;                                /* number of sites, spins */
  int *next;                                        /* neighbour relations */
  int *cluster;                                 /* cluster id of each spin */
  int num_cluster;                              /* number of spin clusters */
  int size_largest, id_largest;            /* for largest cluster of spins */
  int t, conf;                                             /* loop counter */
  int d;                       /* loop counter over dimensions, directions */
  int argz = 1;                  /* counter for treating arguments/options */
  int do_stdout;                               /* write output to stdout ? */
  FILE *file;
  char filename[1000], appendix[1000];
  int *exch, *tries;


  num_T = 2; T=NULL; p_hole = 0.0; real_id0 = 1000; num_real = 1; dim = 2; 
  do_up = 0;                                             /* default values */
  seed = 10000; strcpy(appendix, ""); do_stdout = 0; 

  while((argz<argc)&&(argv[argz][0] == '-'))              /* treat options */
  {
    if(strcmp(argv[argz], "-p") == 0)
    {
      sscanf(argv[++argz], "%lf", &p_hole);
    }
    else if(strcmp(argv[argz], "-T") == 0)
    {
      sscanf(argv[++argz], "%d", &num_T);
      T = (double *) malloc(num_T*sizeof(double));
      for(t=0; t<num_T; t++)
	sscanf(argv[++argz], "%lf", &T[t]);
    }
    else if(strcmp(argv[argz], "-up") == 0)
    {
      do_up = 1;
    }
    else if(strcmp(argv[argz], "-seed") == 0)
    {
      sscanf(argv[++argz], "%d", &seed);
    }
    else if(strcmp(argv[argz], "-real") == 0)
    {
      sscanf(argv[++argz], "%d", &real_id0);
    }
    else if(strcmp(argv[argz], "-num") == 0)
    {
      sscanf(argv[++argz], "%d", &num_real);
    }
    else if(strcmp(argv[argz], "-stdout") == 0)
    {
      do_stdout = 1;
    }
    else if(strcmp(argv[argz], "-appendix") == 0)
    {
      strcpy(appendix, argv[++argz]);
    }
    else
    {
      fprintf(stderr, "unkown option: %s\n", argv[argz]);
      exit(1);
    }
    argz++;
  }

  if( (argc-argz) < 1)
  {
    fprintf(stderr, "USAGE: %s {<options>} <L> <#sweeps>\n", argv[0]);
    fprintf(stderr, "   OPTIONS:\n");
    fprintf(stderr, "    -T <n> <T1>...<Tn>: set temperatures (d:%d)\n",
	    num_T);
    fprintf(stderr, "       -p <p>: set hole prob. (d:%2.1f)\n", p_hole);
    fprintf(stderr, "          -up: start with all spins up (d:random)\n");
    fprintf(stderr, "    -real <r>: seed for realisation (d:%d)\n", real_id0);
    fprintf(stderr, "    -num <n>: number of realisations (d:%d)\n", num_real);
    fprintf(stderr, "    -seed <s>: seed for MC rng  (d:%d)\n", seed);
    fprintf(stderr, "-appendix <a>: for output filename\n");
    fprintf(stderr, "      -stdout: write output to stdout\n");
    exit(1);
  }
  size = atoi(argv[argz++]);
  num_sweeps = atoi(argv[argz++]);

  l = (int *) malloc(dim*sizeof(int));     /* allocations/ intializations */
  l[0] = size;
  for(d=1; d<dim; d++)
    l[d] = l[0];
  /*mf_init_arr(dim, l, 1, &(n), &N, &(next), &(tfeld), 0);*/
  next = percol_init_next(dim, l, &N);
  num_n = 2*dim;
  exch = (int *) malloc(num_T*sizeof(int));
  tries = (int *) malloc(num_T*sizeof(int));
  spin = (short int **) malloc((num_T)*sizeof(short int*));
  for(t=0; t<num_T; t++)
  {
    spin[t] = (short int *) malloc((N+1)*sizeof(short int));
    exch[t] = 0;
    tries[t] = 0;
  }
  e = (short int *) malloc((N+1)*sizeof(short int));
  cluster = (int *) malloc((N+1)*sizeof(int));

  if(T == NULL)
  {
    T = (double *) malloc(num_T*sizeof(double));
    T[0]=1.0;
    T[1]=3.0;
    /*T[2]=2.0;
      T[3]=2.5;
      T[4]=3.0;*/
  }

  for(real_id = real_id0; real_id < real_id0+num_real; real_id++)
  {                                          /* loop over all realizations*/
    char filename[2000]; // Increase the size of the filename buffer
    sprintf(filename, "dPTL%dp%3.2fID%d%s.out", size, p_hole, 
	    real_id, appendix);
    if(do_stdout)
      file = stdout;
    else
      file = fopen(filename, "w");
    fprintf(file,"# run: ");
    for(t=0; t<argz; t++)
      fprintf(file, "%s ", argv[t]);
    fprintf(file, "\n");

    srand(real_id);
    {
      double r_num;

      N_spins = 0;
      for(t=1; t<=N; t++)                   /* initialize disorder randomly */
      {
	r_num = r_0_1();
	if(r_num<p_hole)
	  e[t] = 0;
	else
	{
	  e[t] = 1;
	  N_spins++;
	}
      }
    }

    num_cluster = percol_cluster(num_n, N, next, e, cluster);
    size_largest = percol_largest(N, num_cluster, cluster, &id_largest);
    

    fprintf(file, "# Info realisation %d:" 
	   "numb. clusters=%d, id_largest=%d, size_largest = %d\n", 
	   real_id, num_cluster, id_largest, size_largest);

    fprintf(file, "# time n x(energy mag mag2)\n");
    srand(seed);
    for(conf=0; conf<num_T;conf++)
      for(t=1; t<=N; t++)              /* initialize spins (randomly) */
	if(do_up || (r_0_1()<0.5))
	  spin[conf][t] = 1;
	else
	  spin[conf][t] = -1;
    
    for(sweep=0; sweep<num_sweeps; sweep++)
    {
      diluted_PT(num_T, spin, num_n, N, next, e, T, exch, tries);
      fprintf(file, "%d ", (sweep+1));
      for(t=0; t<num_T; t++)
      {
	energy = diluted_energy(spin[t], num_n, N, next, e)/N_spins;
	mag = diluted_magnetisation(spin[t], N, e)/N_spins;
	mag2 = diluted_mag_cluster(spin[t], N, e, cluster, id_largest)/
	  size_largest;
	fprintf(file, "%f %f %f  ", energy, fabs(mag), fabs(mag2));
      }
      fprintf(file, "\n");
    }
    /*diluted_print(spin, N, l[0], e);*/
    fclose(file);
  }

  fprintf(stderr, "# statistics of acceptances rates:\n");
  for(t=0; t<num_T-1; t++)
    fprintf(stderr, "#[T_%d,T_%d]=[%f,%f]: %f\n", t, t+1, T[t], T[t+1],
	   (double) exch[t]/tries[t]);


    
  free(l);
  free(next);
  for(t=0; t<num_T; t++)
    free(spin[t]);
  free(spin);
  free(T);
  free(exch); free(tries);
  free(e);
  free(cluster);

  return(0);
}
