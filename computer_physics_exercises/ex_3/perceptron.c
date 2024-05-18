/****************************************************************/
/*** Simulation of layered neural networks (perceptron)       ***/
/*** see: H. Ritter et al, Neuronale Netze, Addison-Wesely    ***/
/*** Chap. 3                                                  ***/
/*** Compile: cc -o perceptron perceptron.c                   ***/
/*** A.K. Hartmann January 2011                               ***/
/*** Computerorientierte Physik                               ***/
/*** University of Oldenburg, Germany 2011                    ***/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/********************* output_neuron() ******************/
/** Calculates output of one McCullo-Pitts Neuron for  **/
/** given input x and weighte w (threshold 0)          **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of input values               **/
/**            x: input                                **/
/**            w: weight vector                        **/
/** RETURNS:                                           **/
/**     neuron output (0/1)                            **/
/********************************************************/
int output_neuron(int L, int *x, double *w)
{
  double sum = 0.0;
  int t;
  
  for(t=0; t<=L; t++)
    sum += w[t]*x[t];

  if(sum>=0)
    return(1);
  else
    return(0);
}



/********************* random_vector() ******************/
/** Generates a random 0/1 vector 'x' of length 'L'    **/
/** for entries (1..L)                                 **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of values                     **/
/**        (*) x: vector                               **/
/** RETURNS:                                           **/
/**     (nothing)                                      **/
/********************************************************/
void random_vector(int L, int *x)
{
  int t;

  for(t=1; t<=L; t++)
    if(drand48()<0.5)
      x[t] = 0;
    else
      x[t] = 1;
}



/********************* test_majority() ******************/
/** Test for 0/1 vector 'x' of length 'L' whether      **/
/** more than half of the bits of 1..L are 1.          **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of values                     **/
/**            x: vector                               **/
/** RETURNS:                                           **/
/**     1 if number of 1bits >= L/2, 0 else            **/
/********************************************************/
int test_majority(int L, int *x)
{ 
  int t;
  int counter = 0;

  for(t=1; t<=L; t++)
    if(x[t] != 0)
      counter++;

  if(counter > L/2)
    return(1);
  else
    return(0);

}


/*********************** test_parity() ******************/
/** Test for 0/1 vector 'x' of length 'L' whether      **/
/** the number of 1 bits of 1..L is odd.               **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of values                     **/
/**            x: vector                               **/
/** RETURNS:                                           **/
/**     1 if number of 1bits >= L/2, 0 else            **/
/********************************************************/
int test_parity(int L, int *x)
{ 
  int t;
  int counter = 0;

  for(t=1; t<=L; t++)
    if(x[t] != 0)
      counter++;

  return(counter %2);

}


/***************** perceptron_learning() ****************/
/** Peforms 'K' steps of learning algorithm:           **/
/** generate random vector and adjust weights using    **/
/** parameter 'epsilon' to learn function 'f'          **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of (real) values              **/
/**        (*) w: weight vector                        **/
/**      epsilon: learning rate                        **/
/**            f: target function                      **/
/**            K: number of iterations                 **/
/** RETURNS:                                           **/
/**     (nothing)                                      **/
/********************************************************/
void perceptron_learning(int L, double *w, double epsilon,
			 int (*f)(int, int *), int K )
{
  int step, t;                                 /* loop counters */
  int *x;                                       /* input vector */
  int y, y_wanted;                             /* output values */
  

  x = (int *) malloc( (L+1)*sizeof(int));
  x[0] = 1;                              /* bit 0 <-> threshold */
  for(step=0; step<K; step++)             /* main learning loop */
  {
    random_vector(L, x);
    y = output_neuron(L, x, w);
    y_wanted = f(L, x);
    if(y != y_wanted)
      for(t=0; t<=L; t++)                     /* adjust weights */
	w[t] += epsilon*(y_wanted- y)*x[t];
  }
  free(x);
}


/***************** perceptron_testing() *****************/
/** Peforms 'K' steps of perceptron algorithm:         **/
/** generate random vector and test wether function 'f'**/
/*+ is reproduced                                      **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of (real) values              **/
/**        (*) w: weight vector                        **/
/**            K: number of iterations                 **/
/**            f: target function                      **/
/** RETURNS:                                           **/
/**     success rate                                      **/
/********************************************************/
double perceptron_testing(int L, double *w,
			 int (*f)(int, int *), int K)
{
  int step;                                     /* loop counter */
  int *x;                                       /* input vector */
  int y, y_wanted;                             /* output values */
  int num_successful=0;                           /* statistics */

  x = (int *) malloc( (L+1)*sizeof(int));
  x[0] = 1;
  for(step=0; step<K; step++)
  {
    random_vector(L, x);
    y = output_neuron(L, x, w);
    y_wanted = f(L, x);
    if(y == y_wanted)
      num_successful++;
  }
  free(x);

  return((double) num_successful/K);
}


int main(int argc, char **argv)
{
  int L=2;                                     /* number of input bits */
  double *w;                                           /* weight vector */
  double epsilon;                                      /* learning rate */
  int *x;                                                      /* input */
  int run, t;                                          /* loop counters */
  int (*function)(int, int*);
  /*function = test_majority;*/ 
  function = test_parity;


  w = (double *) malloc((L+1)*sizeof(double));
  x = (int *) malloc((L+1)*sizeof(int));
  
  for(t=0; t<=L; t++)
    w[t] = 1.0;
  srand48(1000);
  epsilon = 1.0/(2*L);

  for(run=0; run<1000; run++)
  {
    if(run%100)
      printf("%d %f\n", run, 1-perceptron_testing(L, w, function, 1000));
    perceptron_learning(L, w, epsilon, function, 1);
  }
  for(t=0; t<=L; t++)
    printf("# w[%d] = %f\n", t, w[t]);

  free(w);
  free(x);
  return(0);
}

