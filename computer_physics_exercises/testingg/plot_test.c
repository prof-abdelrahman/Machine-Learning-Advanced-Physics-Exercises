#include <stdio.h>

/* make x and y array and export it to txt */
int main()
{
  FILE *f = fopen("data.txt", "w");
  if (f == NULL)
  {
    printf("Error opening file!\n");
    return 1;
  }
  int i;
  for (i = 0; i < 10; i++)
  {
    fprintf(f, "%d %d\n", i, i * i);
  }
  fclose(f);
  return 0;
}