// Pointer juggling

# include <stdio.h>

int main() {
    double value = 3.14;
    double *ptr = &value;
    double **ptr_ptr = &ptr;
    printf("value = %f\n", value);
    printf("*ptr = %f\n", *ptr);
    printf("**ptr_ptr = %f\n", **ptr_ptr);
    printf("%p\n", ptr);
    printf("%p\n", ptr_ptr);
    return 0;
}