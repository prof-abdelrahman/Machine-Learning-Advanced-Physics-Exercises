/* Integration of function */

#include <stdio.h>
#include <math.h>

/******************** integrate() *********************/
/** Integrates a 1-dim function numerically using **/
/** the rectangular rule **/
/** PARAMETERS: (*)= return-paramter **/
/** from: startpoint of interval **/
/** to: endpoint of interval **/
/** num_steps: number of integration steps **/
/** f: p. to function to be integrated **/
/** RETURNS: **/
/** value of integral **/
/******************************************************/

double integrate(double from, double to, int num_steps, double (* f)(double)) {

  // Calculate the width of each subinterval
  double delta = (to - from) / num_steps;

  // Initialize the sum to zero
  double sum = 0.0;

  // x
  double x = from;
  double f_x = f(x);
  double f_xp1;

  // Loop over the subintervals
  for (int i = 0; i < num_steps; ++i) {
    f_xp1 = f(x + delta);
    sum += f_x + f_xp1;
    x += delta;
    f_x = f_xp1;	
  }

  return (sum * delta / 2.0);
}

int main() {
    int num_steps = 1000;          /* number of integration steps */

    printf("Int(0,PI/2) sin(x) = %f\n", 
        integrate(0, M_PI/2, num_steps, sin));
    printf("Int(0,PI) sin(x) = %f\n", 
        integrate(0, M_PI, num_steps, sin));
    printf("Int(0,1.5*PI) sin(x) = %f\n", 
        integrate(0, 1.5*M_PI, num_steps, sin));
    printf("Int(0,2*PI) sin(x) = %f\n", 
        integrate(0, 2*M_PI, num_steps, sin)); 
    
    return 0;
}