//functions - save file, load file, print, shell-sort insertion, shell-sort selection

#include <stdio.h> 
#include <stdlib.h>
#include "sorting_main.h"
#include <time.h>

void Shell_Insertion_Sort(long * Array, int Size, double * N_Comp, double * N_Move)
{
  int i = 0;
  int j = 0;
  int k = 1;
  int p = 0;
  int gap;
  int seq_count;
  long temp;
  while(k < Size)
    {
      k = k * 3;
      p = p + 1;
    }
  k = k / 3;
  p = p - 1;
  while(p >= 0)
    {
      gap = k;
      seq_count = p;
      do
	{
	  for(j = gap; j < Size; j++)
	    {
	      temp = Array[j];
	      (*N_Move)++;
              i = j;
	      while(i >= gap && Array[i - gap] > temp)
		{
                  (*N_Comp)++;
		  Array[i] = Array[i - gap];
		  (*N_Move)++;
		  i = i - gap;
		}
	      Array[i] = temp;
	      (*N_Move)++;
	    }
	  gap = (gap / 3) * 2;
	  seq_count = seq_count - 1;
	}while(seq_count >=0);
      k = k / 3;
      p = p - 1;
    }

  return;
}


void Shell_Selection_Sort(long * Array, int Size, double * N_Comp, double * N_Move)
{ 
  int i;
  int j;
  int k = 1;
  int p = 0;
  int gap;
  int seq_count;
  long  temp;
  int iMin;
  while(k < Size)
    {
      k = k * 3;
      p = p + 1;
    }
  k = k / 3;
  p = p - 1;
  while(p >= 0)
    {
      gap = k;
      seq_count = p;
      do
	{
	  for(j = 0; j < Size; j++) 
	    {
              iMin = j;
	      temp = Array[j];
	      (*N_Move)++;
	      for(i = j + gap; i < Size; i += gap)
		{
		  (*N_Comp)++;
		  if(Array[i] < Array[iMin])
		    {
		      iMin = i;
		    }
		}     
              if(iMin != j)
		{
		  Array[j] = Array[iMin];
                  Array[iMin] = temp;
                  (*N_Move)+=2;
		} 
	    }
	  gap = (gap / 3) * 2;
	  seq_count = seq_count - 1;
	}while(seq_count >=0);
      k = k / 3;
      p = p - 1;
    }
}

long * Load_File(char * Filename, int * Size)
{
  int open = 0;
  FILE * fptr;
  int i = 0;
  fptr = fopen(Filename, "r");
  while(fptr == NULL)
    {
      return 0;
    }
  
  if(i == 0)
    {
      open = fscanf(fptr, "%d", Size);
      if(open == 0)
	{
	  fclose(fptr);
	}
    }
  
  long * temp = malloc(*Size * sizeof(long));
  if(temp == NULL)
    {
      free(temp);
    }
  while(!feof(fptr) && open == 1)
    {
      open = fscanf(fptr, "%li", &temp[i]);
      i++;
    }
  fclose(fptr);
  return(temp);
}

int Save_File(char * Filename, long * Array, int Size)
{
  int num = 0;
  FILE * fptr;
  int i = 0;
  int close = 0;
  fptr = fopen(Filename, "w");
  if(fptr == NULL)
    {
      return 0;
    }
  close = fprintf(fptr, "%d\n", Size);
  if(close > -1)
    {
      num++;
    }
  for(i = 0; i < Size; i++)
    {
      close = fprintf(fptr, "%li\n", Array[i]);
      if(close > -1)
	{
          num++;
	}
    }
  fclose(fptr); 
  return num;
}

int Print_Seq(char * Filename, int Size)
{ 
  int num = 0;
  int close = 0;
  int print_1 = 1;
  FILE * fptr;
  int gap = 0;
  int q = 0;
  int e = 0;
  int x = 0;
  fptr = fopen(Filename, "w");
  int k = 1;
  int p = 0;
  int r = 0;
    while(k < Size)
      {
	k = k * 3;
	p = p + 1;
      }

    k = k/3;
    p = p - 1;
    int new_size = (p + 1) * (p +2) / 2;
    close = fprintf(fptr, "%d\n", new_size);
    if(close > -1)
      {
        num++;
      }
    
    close = fprintf(fptr,"%d\n", print_1);
    if(close > -1)
      {
        num++;
      }
    gap = 1;
    for(e = 0; e < p; e++)
      {
	q++;
	gap = gap * 2;
	r = gap;
	close = fprintf(fptr, "%d\n", gap);
	if(close > -1)
	  {
 	    num++;
	  }
	for(x = 1; x < q + 1; x++)
	  {
	    r =(r * 3)/2;
	    close = fprintf(fptr, "%d\n", r);
	    if(close > -1)
	      {
	        num++;
	      }
              
	  }
      }
  fclose(fptr);
  return num;
	    
}
