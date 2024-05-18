/*******************************************************************/
/*** Calculates all permutations of a given array of numbers     ***/
/*** using a recursive approach                                  ***/
/*** Makes a simple statistics of the permutations               ***/
/***                                                             ***/
/*** Based on sample programs from the book:                     ***/
/*** A.K. Hartmann                                               ***/
/*** Big practical guide to computer simulation                  ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Algorithms and data structures                     ***/
/*** Section: Iteration and recursion                            ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>


/********************** count_up() *************************/
/** Counts how often an array element is followed by a     **/
/** larger element.                                       **/
/**                                                       **/
/** Parameters: (*) = return parameter                    **/
/**        n_max: size of array                           **/
/**            a: array                                   **/
/** Returns:                                              **/
/**        number of 'up' pairs                           **/
/***********************************************************/
int count_up(int n_max, int *a)
{
  int t;
  int count = 0;

  /*** ADD CODE HERE ***/
  /* Design, implement and test a sequential function, which counts for an array a[] the
  number of neighboring pairs a[t],a[t+1] for which the first element is smaller, i.e., the
  array runs locally “up”. */
  for (t = 0; t < n_max - 1; t++)
  {
    if (a[t] < a[t + 1])
    {
      count++;
    }
  }
  
  return(count);
}


/******************* permutation() *************************/
/** Obtains all permutations of positions 0..n-1 of a     **/
/** given array 'a' of numbers and prints them if n==1,   **/
/** including the higher index entries (from 0..n_max-1). **/
/** Also a statistics on the permutations regarding       **/
/** 'up_count()' is performed                             **/
/**                                                       **/
/** Parameters: (*) = return parameter                    **/
/**            n: current range                           **/
/**        n_max: size of array                           **/
/**            a: array                                   **/
/**      (*)  up: pointer to total number of 'up' pairs   **/
/**      (*) num: pointer to number of permutations       **/
/** Returns:                                              **/
/**        (nothing)                                      **/
/***********************************************************/
void permutation(int n, int n_max, int *a, double *up, double *num)
{
  int t;
  int exch;

  if(n==1)                                       /* print solution */
  {

    /*** ADD CODE HERE ***/
    /* Design, implement and test a recursive function, which generates all permutations of
    the numbers 1,2,...,n. The function should print the permutations for n=1 and count the
    number of “up” pairs for each permutation. */
    for (t = 0; t < n_max; t++)
    {
      printf("%d ", a[t]);
    }
    printf("\n");
    /****/
    
    *up += count_up(n_max, a);
    *num += 1;
  }
  else
  {
    /*** ADD CODE HERE ***/
    /* Design, implement and test a recursive function, which generates all permutations of
    the numbers 1,2,...,n. The function should print the permutations for n=1 and count the
    number of “up” pairs for each permutation. */
    for (t = 0; t <= n - 1; t++)
    {
      exch = a[t];
      a[t] = a[n - 1];
      a[n - 1] = exch;
      permutation(n - 1, n_max, a, up, num);
      exch = a[t];
      a[t] = a[n - 1];
      a[n - 1] = exch;
    }
    // permutation(n - 1, n_max, a, up, num);
    /****/
  }

}

/*******************************************************************/
/**                m a i n    p r o g r a m                       **/
/*******************************************************************/
// int main(int argc, char **argv)
// {
//   int n;            /* number of which factorial is to be computed */    
//   int *a;                                     /* array for numbers */
//   int t;                                           /* loop counter */
//   double up;    /* number of 'up' pairs, summed over all sequences */
//   double num;                            /* number of permutations */
//   n = atoi(argv[1]);             /* n= first command line argument */
//   a = malloc(n*sizeof(int));
//   for(t=0; t<n; t++)
//     a[t]=t+1;
//   up = 0.0; num = 0.0;
//   permutation(n, n, a, &up, &num);

//   printf("n=%d, %f sequences <up>=%f\n", n, num, up/num);
//   free(a);
//   return(0);
// }

int main()
{
  /* test count up function*/
  int n = count_up(5, (int[]){1, 2, 3, 4, 5});
  printf("%d\n", n);
  int n1 = count_up(5, (int[]){5, 4, 3, 2, 1});
  printf("%d\n", n1);
  int n2 = count_up(5, (int[]){1, 2, 3, 5, 4});
  printf("%d\n", n2);

  printf("\n");

  /* test permutation function of array containing {1,2,3} */
  int *a1 = malloc(3 * sizeof(int));
  for (int t = 0; t < 3; t++)
  {
    a1[t] = t + 1;
  }
  double up1 = 0.0;
  double num1 = 0.0;
  permutation(3, 3, a1, &up1, &num1);
  printf("n=%d, permutation=%f, sequences <up>=%f\n", 3, num1, up1 / num1);
  free(a1);

  printf("\n");


  /* test permutation function */
  int *a = malloc(5 * sizeof(int));
  for (int t = 0; t < 5; t++)
  {
    a[t] = t + 1;
  }
  double up = 0.0;
  double num = 0.0;
  permutation(5, 5, a, &up, &num);
  printf("n=%d, permutation=%f, sequences <up>=%f\n", 5, num, up / num);
  free(a);

  /* Execute the program for n = 2, 3, . . . , 10. How does the number of permutationen
  behave? What do you get for the average number of “up” pairs. Can you explain it? (2
  P) */
  printf("\n");

  /* Execute the program for n = 2, 3, . . . , 10. How does the number of permutationen
  behave? What do you get for the average number of “up” pairs. Can you explain it? (2
  P)  */
  // for (int n = 2; n <= 10; n++)
  // {
  //   int *a = malloc(n * sizeof(int));
  //   for (int t = 0; t < n; t++)
  //   {
  //     a[t] = t + 1;
  //   }
  //   double up = 0.0;
  //   double num = 0.0;
  //   permutation(n, n, a, &up, &num);
  //   printf("n=%d, permutation=%f, sequences <up>=%f\n", n, num, up / num);
  //   /* export the results to txt file */
  //   FILE *f = fopen("permutation.txt", "a");
  //   if (f == NULL)
  //   {
  //     printf("Error opening file!\n");
  //     exit(1);
  //   }
  //   fprintf(f, "n=%d, permutation=%f, sequences <up>=%f\n", n, num, up / num);
  //   fclose(f);
  //   free(a);
  //   printf("\n");
  // }

  return 0;
}
