#include<stdio.h>
#include<stdlib.h>
int main()
{
  long y = 10000000;
  char * Filename = "input1.txt";
  FILE * fptr;
  long x;
  fptr = fopen(Filename, "w");
  if(fptr == NULL)
    {
      fclose(fptr);
    }

  int i = 0;
  fprintf(fptr, "%li\n", y);
  for(i = 0; i < 10000000; i++)
    {
      x = random();
      fprintf(fptr,"%li\n", x);
    }
  fclose(fptr);
  return 1;
}


