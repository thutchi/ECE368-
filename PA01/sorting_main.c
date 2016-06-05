#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sorting_main.h"

int main(int argc, char ** argv)
{
  int close_seq;
  int close_file;
  clock_t clock4 = 0;
  clock_t clock3 = 0;
  long double sorting_time = 0;
  double  N_Comp = 0;
  double  N_Move = 0;
  int Size = 0;
  clock_t clock1 = clock();
  long * Array = Load_File(argv[2], &Size);
  clock_t clock2 = clock();
  if(*(argv[1]) == 'i')
    {
      clock3 = clock();
      Shell_Insertion_Sort(Array, Size, &N_Comp, &N_Move);
      clock4 = clock();
    }
  else
    {
      clock3 = clock();
      Shell_Selection_Sort(Array, Size, &N_Comp, &N_Move);
      clock4 = clock();
    }
  clock_t clock5 = clock();
  close_file = Save_File(argv[4], Array, Size);
  clock_t clock6 = clock();
  if(close_file < 0)
    {
      fprintf(stderr, "Save_file is not working properly");
    }
  clock_t in = clock2 - clock1;
  clock_t out = clock6 - clock5;
  clock_t clock7 = clock();
  close_seq = Print_Seq(argv[3], Size);
  clock_t clock8 = clock();
  clock_t seq = clock8 - clock7;
  if(close_seq < 0)
    {
      fprintf(stderr, "Sequence did not write properly!");
    }
  long double in_out_time = (long double)(in + out + seq)/(long double)CLOCKS_PER_SEC;
 
  sorting_time = (long double)(clock4 - clock3)/(long double)CLOCKS_PER_SEC;
  
  printf("Number of comparisons:  %Le\n", (long double)N_Comp);  
  printf("Number of moves:  %Le\n", (long double)N_Move); 
  printf("I/0 time:  %Le\n", in_out_time);
  printf("Sorting time:  %Le\n", sorting_time);
  free(Array);
  return 1;
}
