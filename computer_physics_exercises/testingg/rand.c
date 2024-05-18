#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator using the current time
    srand48(time(NULL));

    // Generate and print 5 random numbers
    printf("Random numbers:\n");
    for (int i = 0; i < 5; ++i) {
        double random_number = drand48(); // Generate a random number
        printf("%f\n", random_number);
    }

    double r = drand48();
    printf("Random number between 0 and 1: %f\n", r);

    return 0;
}
