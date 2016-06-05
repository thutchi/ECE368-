#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "sorting_main.h"
int main(int argc, char**argv)
{
  Node * temp_List = NULL;
  int save_check = 0;
  clock_t load = clock();
  Node * temp = Load_File(argv[1]);
  clock_t load1 = clock();
  
  clock_t sort = clock();
  temp_List = Shell_Sort(temp);
  clock_t sort1 = clock();
  
  clock_t save = clock();
  save_check = Save_File(argv[2], temp_List);
  if(save_check < 0)
    {
      fprintf(stderr, "The save file did not write correctly");
    }
  clock_t save1 = clock();
  
  clock_t total_save = save1 - save;
  clock_t total_load = load1 - load;
  clock_t total_sort = sort1 - sort;
  
  long double in_out = (long double)(total_save + total_load)/(long double)CLOCKS_PER_SEC;
  long double sort_time = (long double)(total_sort)/(long double)CLOCKS_PER_SEC;
  printf("\n");
  printf("I/O time:  %Le\n", in_out);
  printf("Sorting time:  %Le\n",sort_time);
  Node_destroy(temp);
  return 0;
} 
