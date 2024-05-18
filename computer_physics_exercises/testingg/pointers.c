# include <stdio.h>

int main() {
  int a = 5;
  int *p = &a;
  *p = 6;
  int **pp = &p;
  printf("a = %d\n", a);
  printf("p = %p\n", p);
  printf("*p = %d\n", *p);
    printf("pp = %p\n", pp);
    printf("*pp = %p\n", *pp);
    printf("**pp = %d\n", **pp);
  return 0;
}