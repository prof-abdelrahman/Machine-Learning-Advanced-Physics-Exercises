/****************************************************************/
/*** Simulates d-dim percolation                              ***/
/*** A.K. Hartmann June 2004                                  ***/
/*** Rechnergest�tztes Wissenschaftliches Rechnen             ***/
/*** University of Goettingen, Germany 2004                   ***/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_FILENAME_LENGTH 50

#include "stacks.h"
#include "percol.h"

/******************* percol_spanning() *******************/
/** Determines whether cluster ’cluster_ID’ occupies **/
/** for each x ordinate at least one site. **/
/** For each site, in ’cluster[i]’ the ID of the **/
/** cluster (starting at 0) is stored **/
/** PARAMETERS: (*)= return-paramter **/
/** N: number of sites **/
/** cluster: ID of clusters sites are contained in **/
/** cluster_ID: ID of the cluster which is tested **/
/** x_length: length of system in x direction **/
/** RETURNS: **/
/** 1 if all x values are occpied (<->spanning) **/
/********************************************************/
// int percol_spanning(int N, int *cluster, int cluster_ID, int x_length)
// {
//   int i, spanning;
//   spanning = 0;
//   for(i=1; i<=N; i++)
//     if(cluster[i] == cluster_ID)
//       if( (i-1)%x_length == 0 )
//       {
//   spanning = 1;
//   break;
//       }
//   return(spanning);
// }

int percol_spanning(int N, int *cluster, int cluster_ID, int x_length)
{
  int i, spanning, k, counter;
  spanning = 0;
  counter = 0;
  for(i=0; i<x_length; i++)
  {
    k = 0;
    for (int j = 0; j < x_length; j++) {
      if(cluster[i+k] == cluster_ID) {
        counter++;
      }
      k += x_length;
    }
    if (counter == 0) {
      return(0);
    }
    counter = 0;
  }
  return(1);
}

/* main to test percol_spanning function */
// int main() {
//   int N = 100; // number of sites
//   int *cluster; // ID of clusters sites are contained in
//   int cluster_ID = 1; // ID of the cluster which is tested
//   int x_length = 10; // length of system in x direction

//   // Allocate memory for the cluster array
//   cluster = (int *) malloc((N+1)*sizeof(int));

//   // Initialize the cluster array with some values
//   for (int i = 1; i <= N; i++) {
//     cluster[i] = cluster_ID;
//   }

//   // Print the cluster array
//   printf("Cluster array:\n");
//   for (int i = 1; i <= N; i++) {
//     printf("%d ", cluster[i]);
//     if (i % x_length == 0) {
//       printf("\n");
//     }
//   }
//   // Call the percol_spanning function
//   int spanning = percol_spanning(N, cluster, cluster_ID, x_length);

//   // Print the result
//   printf("Spanning: %d\n", spanning);
//   printf("\n");

//   // Free the memory
//   free(cluster);

//   /* Another cluster array of 4*4 size test
//   0 0 0 0
//   1 0 0 0
//   1 0 0 0
//   0 0 0 1 */
//   N = 16; // number of sites
//   cluster_ID = 1; // ID of the cluster which is tested
//   x_length = 4; // length of system in x direction

//   // Array of cluster2
//   int cluster2[4][4] = {
//     {0, 0, 0, 0},
//     {1, 0, 0, 0},
//     {1, 0, 0, 0},
//     {0, 0, 0, 1}
//   };

//   // Print the cluster array
//   printf("Cluster array 2:\n");
//   for (int i = 0; i < 4; i++) {
//     for (int j = 0; j < 4; j++) {
//       printf("%d ", cluster2[i][j]);
//     }
//     printf("\n");
//   }

//   // Call the percol_spanning function
//   int spanning2 = percol_spanning(N, (int *)cluster2, cluster_ID, x_length);

//   // Print the result
//   printf("Spanning: %d\n", spanning2);
//   printf("\n");

//   /* Another cluster array of 4*4 size test
//   1 0 0 0
//   0 0 1 0
//   0 1 0 0
//   0 0 0 1 */
//   N = 16; // number of sites
//   cluster_ID = 1; // ID of the cluster which is tested
//   x_length = 4; // length of system in x direction

//   // Array of cluster3
//   int cluster3[4][4] = {
//     {1, 0, 0, 0},
//     {0, 0, 1, 0},
//     {0, 1, 0, 0},
//     {0, 0, 0, 0}
//   };

//   // Print the cluster array
//   printf("Cluster array 3:\n");
//   for (int i = 0; i < 4; i++) {
//     for (int j = 0; j < 4; j++) {
//       printf("%d ", cluster3[i][j]);
//     }
//     printf("\n");
//   }

//   // Call the percol_spanning function
//   int spanning3 = percol_spanning(N, (int *)cluster3, cluster_ID, x_length);

//   // Print the result
//   printf("Spanning: %d\n", spanning3);
//   printf("\n");

//   /* Another cluster array of 4*4 size test
//   1 1 0 0
//   0 0 1 0
//   0 0 0 0
//   1 0 0 1 */
//   N = 16; // number of sites
//   cluster_ID = 1; // ID of the cluster which is tested
//   x_length = 4; // length of system in x direction

//   // Array of cluster4
//   int cluster4[4][4] = {
//     {1, 1, 0, 0},
//     {0, 0, 1, 0},
//     {0, 0, 0, 0},
//     {1, 0, 0, 1}
//   };

//   // Print the cluster array
//   printf("Cluster array 4:\n");
//   for (int i = 0; i < 4; i++) {
//     for (int j = 0; j < 4; j++) {
//       printf("%d ", cluster4[i][j]);
//     }
//     printf("\n");
//   }

//   // Call the percol_spanning function
//   int spanning4 = percol_spanning(N, (int *)cluster4, cluster_ID, x_length);

//   // Print the result
//   printf("Spanning: %d\n", spanning4);
//   printf("\n");

//   /* Another cluster array of 6*6
//   0 1 0 0 0 0
//   1 0 0 0 0 0
//   0 0 1 1 1 0
//   0 0 0 0 0 0
//   0 0 0 0 0 0
//   0 0 0 0 0 0 */
//   N = 36; // number of sites
//   cluster_ID = 1; // ID of the cluster which is tested
//   x_length = 6; // length of system in x direction

//   // Array of cluster5
//   int cluster5[6][6] = {
//     {0, 1, 0, 0, 0, 0},
//     {1, 0, 0, 0, 0, 0},
//     {0, 0, 1, 1, 1, 0},
//     {0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0}
//   };

//   // Print the cluster array
//   printf("Cluster array 5:\n");
//   for (int i = 0; i < 6; i++) {
//     for (int j = 0; j < 6; j++) {
//       printf("%d ", cluster5[i][j]);
//     }
//     printf("\n");
//   }

//   // Call the percol_spanning function
//   int spanning5 = percol_spanning(N, (int *)cluster5, cluster_ID, x_length);

//   // Print the result
//   printf("Spanning: %d\n", spanning5);
//   printf("\n");

//   /* Another cluster array of 6*6
//   0 1 0 0 0 0
//   1 0 0 0 0 0
//   0 0 1 1 1 0
//   0 0 0 0 0 0
//   0 0 0 0 0 0
//   0 0 0 0 0 1 */
//   N = 36; // number of sites
//   cluster_ID = 1; // ID of the cluster which is tested
//   x_length = 6; // length of system in x direction

//   // Array of cluster6
//   int cluster6[6][6] = {
//     {0, 1, 0, 0, 0, 0},
//     {1, 0, 0, 0, 0, 0},
//     {0, 0, 1, 1, 1, 0},
//     {0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 1}
//   };

//   // Print the cluster array
//   printf("Cluster array 6:\n");
//   for (int i = 0; i < 6; i++) {
//     for (int j = 0; j < 6; j++) {
//       printf("%d ", cluster6[i][j]);
//     }
//     printf("\n");
//   }

//   // Call the percol_spanning function
//   int spanning6 = percol_spanning(N, (int *)cluster6, cluster_ID, x_length);

//   // Print the result
//   printf("Spanning: %d\n", spanning6);
//   printf("\n");

//   return 0;
// }



int main(int argc, char *argv[])
{
  int dim;                    /* dimension of system */
  int num_n;    /* number of neighbours of each site */
  int *l;                         /* sizes of system */
  int *next;           /* stores neighbours of sites */
  int t, r;                         /* loop counters */
  int N;                          /* number of sites */
  double prob;           /* probability of occ. site */
  short int *site;     /* site is occupied or empty? */
  int *cluster;           /* cluster id of each site */
  int num_clusters;             /* numb. of clusters */
  double *value;                   /* stores results */
  double mean;                       /* final result */
  int run, num_runs; /* cur., max no. of indep. runs */
  int id_largest;           /* id of largest cluster */

  dim = 2;            /* initialization + parameters */
  num_n = 2*dim;                   /* simple lattice */
  l = (int *) malloc(dim*sizeof(int));

  if(argc<4)
  {
    printf("USAGE %s <L> <p> <num_runs>\n", argv[0]);
    printf("   (prints cluster if <num_runs>=1)\n");
    exit(1);
  }
  l[0] = atoi(argv[1]);
  for(r=1; r<dim; r++)
    l[r] = l[0];
  next = percol_init_next(dim, l, &N);

  /*for(t=1; t<=N; t++)
    for(r=0; r<2*dim; r++)
    printf("NEXT(%d,%d)=%d\n",t, r, NEXT(t,r));
  exit(1);*/
  site = (short int *) malloc((N+1)*sizeof(short int));
  cluster = (int *) malloc((N+1)*sizeof(int));
  sscanf(argv[2], "%lf", &prob); 
  num_runs = atoi(argv[3]);
  value = (double *) malloc(num_runs*sizeof(double));

  for(run=0; run<num_runs; run++)
  {
    for(t=1; t<=N; t++)
      if(drand48() < prob)
	site[t] = 1;
      else
	site[t] = 0;

    num_clusters = percol_cluster(num_n, N, next, site, cluster);
    value[run] = (double )percol_largest(N, num_clusters, cluster, 
      &id_largest)/N;
    /* UNCOMMENT NEXT LINE FOR SPANNING PROBABILITY EXERCISE */
    value[run] = (double) percol_spanning(N, cluster, id_largest, l[0]);

    /* UNCOMMENT NEXT LINE FOR SURFACE SIZE EXERCISE */
    // value[run] = (double) percol_surface(num_n, N, next, num_clusters,
    //   cluster, id_largest);

    if(num_runs == 1)
      for(t=1; t<=N; t++)          
      {
	if(site[t] == 1)
	  printf("%3d", cluster[t]);
	else
	  printf("   ");
	if( ((t-1)%l[0]) == (l[0]-1) ) 
	  printf("\n");
      }

  }
  // Open file for writing
  char filename[MAX_FILENAME_LENGTH];
  sprintf(filename, "%d.out", l[0]);
  FILE *output_file = fopen(filename, "a");
  if (output_file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

  mean = percol_analysis(num_runs, value);
  printf("%f %f %d \n", prob, mean, l[0]);
  fprintf(output_file, "%f %f %d \n", prob, mean, l[0]);
  

  free(value);
  free(cluster);
  free(site);
  free(next);
  free(l);
  return(0);
}
