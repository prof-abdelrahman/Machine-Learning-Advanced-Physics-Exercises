/****************************************************************/
/*** Simulation of layered neural networks (perceptron)       ***/
/*** see: H. Ritter et al, Neuronale Netze, Addison-Wesely    ***/
/*** Chap. 3                                                  ***/
/*** Compile: cc -o feed_forward feed_forward_gragment.c -lm  ***/
/*** A.K. Hartmann January 2011                               ***/
/*** Computerorientierte Physik                               ***/
/*** University of Oldenburg, Germany 2011                    ***/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/********************* output_neuron2() *****************/
/** Calculates output of one McCullo-Pitts Neuron with **/
/** 'Fermi' function' for                              **/
/** given input x and weighte w (threshold 0)          **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of input values               **/
/**            x: input                                **/
/**            w: weight vector                        **/
/** RETURNS:                                           **/
/**     neuron output (in [0,1])                       **/
/********************************************************/
double output_neuron2(int L, double *x, double *w)
{
  double sum = 0.0;
  int t;
  
  for(t=0; t<=L; t++)
    sum += w[t]*x[t];

  return(1.0/(1+exp(-sum)));
}


/********************* output_ff_network() **************/
/** Calculates output of feed-froward network (one     **/
/** hidden layer given input x and weights w,wt        **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of input values               **/
/**            x: input                                **/
/**            M: size of hidden layer                 **/
/**        (*) y: hidden layer neurons                 **/
/**            w: weight matrix input->hidden          **/
/**           wt: weight vector hidden->output         **/
/** RETURNS:                                           **/
/**     network output (in [0,1])                      **/
/********************************************************/
double output_ff_network(int L, double *x, int M, double *y, double **w, double *wt) {
  // Calculate the output of the neural network
  double z = 0.0;
  for (int j = 1; j <= M; j++) {
    y[j] = output_neuron2(L, x, w[j]);
  }
  z = output_neuron2(M, y, wt);
  return z; // Apply the sigmoid function to the output
}

// // This function is not shown in the image, but it is a common activation function in neural networks
// double sigmoid(double x) {
//   return 1.0 / (1.0 + exp(-x));
// }

/******************* random_vector_d() ******************/
/** Generates a random 0/1 vector 'x' of length 'L'    **/
/** for entries (1..L), entry 0 is 1                   **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of values                     **/
/**        (*) x: vector                               **/
/** RETURNS:                                           **/
/**     (nothing)                                      **/
/********************************************************/
void random_vector_d(int L, double *x)
{
  int t;

  x[0] = 1;
  for(t=1; t<=L; t++)
    if(drand48()<0.5)
      x[t] = 0;
    else
      x[t] = 1;
}



/******************* test_majority_d() ******************/
/** Test for 0/1 vector 'x' of length 'L' whether      **/
/** more than half of the bits of 1..L are 1.          **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of values                     **/
/**            x: vector                               **/
/** RETURNS:                                           **/
/**     1 if number of 1bits >= L/2, 0 else            **/
/********************************************************/
int test_majority_d(int L, double *x)
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


/********************* test_parity_d() ******************/
/** Test for 0/1 vector 'x' of length 'L' whether      **/
/** the number of 1 bits of 1..L is odd.               **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of values                     **/
/**            x: vector                               **/
/** RETURNS:                                           **/
/**     1 if number of 1bits  is odd                   **/
/********************************************************/
int test_parity_d(int L, double *x)
{ 
  int t;
  int counter = 0;

  for(t=1; t<=L; t++)
    if(x[t] != 0)
      counter++;

  return(counter %2);

}


/************************* ff_learning() ****************/
/** Peforms 'K' steps of learning algorithm:           **/
/** generate random vector and adjust weights using    **/
/** parameter 'epsilon' to learn function 'f'          **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of (real) values              **/
/**            M: number of hidden neuron              **/
/**        (*) w: weight matrix input ->hidden         **/
/**       (*) wt: weight vector hidden->output         **/
/**      epsilon: learning rate                        **/
/**            f: target function                      **/
/**            K: number of iterations                 **/
/** RETURNS:                                           **/
/**     (nothing)                                      **/
/********************************************************/
// This function is supposed to adjust the weights (wij and ˜wj), by iterating a loop 
// K times. Within the loop, each time
// – random vectors (x1, . . . , xL) € {0, 1}L are generated by calling random_vector_d()
// – the output of the network is calculated by calling output_ff_network()
// – the output of the network is compared to the target function f() by calling f()
// – the weights are adjusted according to the learning rule 
void ff_learning(int L, int M, double **w, double *wt, double epsilon,
			 int (*f)(int, double *), int K )
{
  int step, t ,t2;                                 /* loop counters */
  double *x;                                       /* input vector */
  double *y;                              /* hidden neurons vector */
  double z, z_wanted;                             /* output values */

  /** PLEASE INSERT COUR CODE HERE **/
  x = (double *) malloc( (L+1)*sizeof(double));
  y = (double *) malloc( (M+1)*sizeof(double));
  x[0] = 1;                              /* bit 0 <-> threshold */
  y[0] = 1;
  for(step=0; step<K; step++)             /* main learning loop */
  {
    random_vector_d(L, x);
    z = output_ff_network(L, x, M, y, w, wt);
    z_wanted = f(L, x);
    if(z != z_wanted)
    {
      for(t=0; t<=M; t++)
      {
        wt[t] += epsilon*(z_wanted-z)*y[t];
        // z = output_ff_network(L, x, M, y, w, wt);
        // if (z != z_wanted){
          for(t2=0; t2<=L; t2++)
            w[t][t2] += epsilon*(z_wanted-z)*wt[t]*y[t]*(1-y[t])*x[t2];
            // w[t][t2] += epsilon*(z_wanted-z)*x[t2];
        // }
      }
    }
  }
  free(x);
  free(y);
}

/************************* ff_testing() *****************/
/** Peforms 'K' steps of ff algorithm:                 **/
/** generate random vector and evaluate network and    **/
/** compare with  function 'f'                         **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of (real) values              **/
/**            M: number of hidden neuron              **/
/**        (*) w: weight matrix input ->hidden         **/
/**       (*) wt: weight vector hidden->output         **/
/**      epsilon: learning rate                        **/
/**            f: target function                      **/
/**            K: number of iterations                 **/
/** RETURNS:                                           **/
/**     error rate                                     **/
/********************************************************/
double ff_testing(int L, int M, double **w, double *wt, 
			 int (*f)(int, double *), int K )
{
  int step;                                 /* loop counters */
  double *x;                                       /* input vector */
  double *y;                              /* hidden neurons vector */
  double z, z_wanted;                             /* output values */
  double deviation = 0;

  x = (double *) malloc( (L+1)*sizeof(double));
  y = (double *) malloc( (M+1)*sizeof(double));
  x[0] = 1;                              /* bit 0 <-> threshold */
  y[0] = 1;
  for(step=0; step<K; step++)             /* main learning loop */
  {
    random_vector_d(L, x);
    z = output_ff_network(L, x, M, y, w, wt);
    z_wanted = f(L, x);
    deviation += fabs(z-z_wanted);
  }
  free(x);
  free(y);

  return(deviation/K);
}




int main(int argc, char **argv)
{
  int L;                                         /* number of input bits */
  int M;                                     /* number of hidden neurons */
  double **w;                        /* weight vector input -> first layer */
  double *wt;                       /* weight vector first layer -> output */
  double epsilon;                                         /* learning rate */
  int run, t, t2;                                         /* loop counters */
  int maxrun;
  int argz = 1;                         /* to treat command-line arguments */
  int seed = 1000;
  int (*function)(int, double*);                  /*function to be learned */
  function = test_parity_d;
  // function = test_majority_d;

  L = atoi(argv[argz++]);
  M = atoi(argv[argz++]);
  maxrun = atoi(argv[argz++]);
  if(argz< argc)                                          /* optional seed */
    seed = atoi(argv[argz++]);
  srand48(seed);

  double ref = 0.5;

   w = (double **) malloc((M+1)*sizeof(double *));       /* allocate memory */
  for(t=0; t<=M; t++)
  {
    w[t] = (double *) malloc((L+1)*sizeof(double));
    for(t2=0; t2<=L; t2++){
      if (ref == 0.5){
        w[t][t2] =0;
        ref = -0.5;
      }
      else{
        w[t][t2] =-0.1;
        ref = 0.5;
      }
      // w[t][t2] =1*(drand48()-0.5);
    }
  }
  ref = 0;
  wt = (double *) malloc((M+1)*sizeof(double));
  for(t=0; t<=M; t++)
    wt[t] = (drand48()-0.5);

  // w = (double **) malloc((M+1)*sizeof(double *));       /* allocate memory */
  // for(t=0; t<=M; t++)
  // {
  //   w[t] = (double *) malloc((L+1)*sizeof(double));
  //   for(t2=0; t2<=L; t2++){
  //     // if (ref == 0.5){
  //     //   w[t][t2] = (t2-0.5);
  //     //   ref = -0.5;
  //     // }
  //     // else{
  //     //   w[t][t2] = (t2+0.5);
  //     //   ref = 0.5;
  //     // }
        
  //     // w[t][t2] = ref+t2; /* random initial weights */
  //     w[t][t2] = ref+1;
  //   }
      
  // }
  // wt = (double *) malloc((M+1)*sizeof(double));
  // double wt_ref = 0;
  // for(t=0; t<=M; t++){
  //   // if (ref == 0.5){
  //   //     wt[t] = (t-0.5);
  //   //     ref = -0.5;
  //   //   }
  //   //   else{
  //   //     wt[t] = (t+0.5);
  //   //     ref = 0.5;
  //   //   }
  //     // wt[t] = ref+t; /* random initial weights */
  //   // wt[t] = (drand48()-0.5);
  //   wt[t]= wt_ref+1;
  //   }
    


  epsilon = 1.0;

  for(run=0; run<maxrun; run++)              /* perform iterative learning */
  {
    if(run %100 == 0)
    {
      printf("%d %f\n", run, ff_testing(L, M, w, wt, function, 1000));
    }
    ff_learning(L, M, w, wt, epsilon, function, 1);
  }

  for(t=0; t<=M; t++)                           /* print resulting network */
  {
    printf("# ");
    for(t2=0; t2<=L; t2++)
      printf("w[%d][%d]=%f, ", t, t2, w[t][t2]);
    printf("\n");
  }
  for(t=0; t<=M; t++)
    printf("# wt[%d]=%f, ", t, wt[t]);
  printf("\n");

  for(t=0; t<=M; t++)                        /* give back allocated memory */
    free(w[t]);
  free(w);
  free(wt);
  return(0);
}

