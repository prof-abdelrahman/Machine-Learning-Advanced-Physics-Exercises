// Matrix permutation

#include <stdio.h>

int main() {

    /* contain the denition of three matrices, one is a nn permutation matrix
    (n is an even number) perm and two (test, result) are nm matrices*/
    int n=6,                    /* permutation matrix has size n x n */
    m=5;
    double perm[n][n], test[n][m], result[n][m];

    /*initialize perm such that neighboring rows are exchanged*/
    int temp;
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            if( j == (i+ 1-2*(i%2)) )  
	            perm[i][j] = 1.0;
	        else
	            perm[i][j] = 0.0;
        }
    }

    /*initialize test in an arbitrary way such that different rows can be distinguished*/
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            test[i][j] = (double)i;
        }
    }
    // sizeof(test)/sizeof(test[0]) = n
    // sizeof(test[0])/sizeof(int) = m

    /*calculate the matrix product result = perm X test*/
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            result[i][j] = 0;
            for (int k = 0; k<n; k++) {
                result[i][j] += perm[i][k]*test[k][j];
            }
        }
    }

    /*print the matrix result row by row*/
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            printf("%f ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
