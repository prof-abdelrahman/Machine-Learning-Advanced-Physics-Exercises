/****************************************************************/
/*** Generator for exponentially distributed numbers          ***/
/*** Rechnergest�tztes Wissenschaftliches Rechnen             ***/
/*** University of Goettingen, Germany 2004                   ***/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_BINS 100
#define MAX_FILENAME_LENGTH 50
#define NUM_ITERATIONS 100000 // Number of iterations for good statistics


/*********************  rand_U() *****************/
/** Generates random number, which is          **/
/** uniformly distrbuted in [0,\lambda)        **/
/** PARAMETERS: (*)= return-paramter           **/
/**     lambda: parameter of distribution      **/
/** RETURNS:                                   **/
/**      random number                         **/
/************************************************/
// double rand_U(double lambda)
// {
//   double value;
//   do
//     value = ((double)rand())/(RAND_MAX);
//   while(value == 1.0);
//   return(value*lambda);

//   /* Change the rogramm such that in each iteration instead of one single now N expo-
// nentially distributed numbers are drawn and from these N numbers the maximum is
// obtained. The histogram of these maxima z shall be redirected from standard output
// into a file max_<N>.out (replace <N> by the current number N) */

// }


// int main(int argc, char *argv[])
// {
//   int histo[NUM_BINS];                                    /* histogram */
//   int bin;
//   double start_histo, end_histo;                 /* range of histogram */
//   double delta;                                        /* width of bin */
//   int t;                                               /* loop counter */
//   int num_runs;                  /* number of generated random numbers */     
//   double lambda;                          /* parameter of distribution */
//   double number;                                   /* generated number */

//   num_runs = atoi(argv[1]);                         /* read parameters */
//   sscanf(argv[2], "%lf", &lambda);

//   for(t=0; t<NUM_BINS; t++)                    /* initialise histogram */
//       histo[t] = 0;        
//   start_histo = 0.0; end_histo = 10.0/lambda;
//   delta = (end_histo - start_histo)/NUM_BINS; 
  
//   for(t=0; t<num_runs; t++)                               /* main loop */
//   {
//     number = -log(rand_U(1.0))/lambda;   /* generate exp-distr. number */
//     bin = (int) floor((number-start_histo)/delta);
//     if( (bin >= 0)&&(bin < NUM_BINS))                /* inside range ? */
//        histo[bin]++;                                    /* count event */
//   }

//   for(t=0; t<NUM_BINS; t++)              /* print normalized histogram */
//       printf("%f %f\n", start_histo + (t+0.5)*delta,
// 	     histo[t]/(delta*num_runs));

//   return(0);
// }

/* Change the rogramm such that in each iteration instead of one single now N expo-
  nentially distributed numbers are drawn and from these N numbers the maximum is
  obtained. The histogram of these maxima z shall be redirected from standard output
  into a file max_<N>.out (replace <N> by the current number N) */

// Function to generate N exponentially distributed numbers and return the maximum
double max_exponential(int N, double lambda) {
    double max = 0.0; // Initialize max to zero
    for (int i = 0; i < N; i++) { // Generate N exponentially distributed numbers
        double value; // Random number
        do { // Generate random number
            value = ((double)rand())/(RAND_MAX); // Uniformly distributed random number
        } while (value == 1.0); // Avoiding division by zero
        double exponential_value = -log(1 - value) / lambda; // Generating exponentially distributed number
        if (exponential_value > max) { // Check if the current value is greater than max
            max = exponential_value; // Updating max if necessary
        }
    }
    return max; // Return the maximum value
}

// Function to calculate the Gumbel distribution density function
double gumbel_density(double z, double lambda_val, double z0) {
    return exp(-exp(-lambda_val*(z-z0)));
}
int main(int argc, char *argv[])
{
  int histo[NUM_BINS];                                    /* histogram */
  int bin;
  double start_histo, end_histo;                 /* range of histogram */
  double delta;                                        /* width of bin */
  int t;                                               /* loop counter */
  int num_runs = 100000;                  /* number of generated random numbers */     
  double lambda;                          /* parameter of distribution */
  double number;                                   /* generated number */
  int N;

//   num_runs = atoi(argv[1]);                         /* read parameters */
//   sscanf(argv[2], "%lf", &lambda);

// Open file for writing
    char filename[MAX_FILENAME_LENGTH];

    printf("Enter the value of lambda: ");
    scanf("%lf", &lambda);

    printf("Enter the value of N: ");
    scanf("%d", &N);

  for(t=0; t<NUM_BINS; t++)                    /* initialise histogram */
      histo[t] = 0;        
  start_histo = 0.0; end_histo = 10.0/lambda;
  delta = (end_histo - start_histo)/NUM_BINS; 
  
  for(t=0; t<num_runs; t++)                               /* main loop */
  {
    // number = -log(max_exponential(1.0))/lambda;   /* generate exp-distr. number */
    number = max_exponential(N,lambda);   /* generate exp-distr. number */
    bin = (int) floor((number-start_histo)/delta); // Calculate bin index
    if( (bin >= 0)&&(bin < NUM_BINS))                /* inside range ? */
       histo[bin]++;                                    /* count event */
  }

// Write histogram to file
    sprintf(filename, "max_%d.out", N);
    FILE *output_file = fopen(filename, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

  for(t=0; t<NUM_BINS; t++){              /* print normalized histogram */
      printf("%f %f\n", start_histo + (t+0.5)*delta,
	     histo[t]/(delta*num_runs));
        fprintf(output_file, "%f %f\n", start_histo + (t+0.5)*delta,
            histo[t]/(delta*num_runs));
  }

    fclose(output_file);

//   /* Calculation of the exact denisty according to the function G(z) = exp(-exp(-lambda*(z-z0))) */
//     double lambda_val = 1.0; // Lambda value for the Gumbel distribution
//     double z0 = 0.0; // z0 value for the Gumbel distribution

//     // Open file for writing
//     char filename[MAX_FILENAME_LENGTH];
//     sprintf(filename, "gumbel_density.dat");
//     FILE *output_file = fopen(filename, "w");
//     if (output_file == NULL) {
//         fprintf(stderr, "Error opening file.\n");
//         return 1;
//     }

//     // Generate values for z and calculate the corresponding density values
//     for (double z = -10.0; z <= 10.0; z += 0.01) {
//         double density = gumbel_density(z, lambda_val, z0);
//         fprintf(output_file, "%lf %lf\n", z, density);
//     }

//     // Close the file
//     fclose(output_file);

//     printf("Gumbel distribution density function written to %s\n", filename);

  return(0);
}