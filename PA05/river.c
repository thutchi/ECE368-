#include "river.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  int counter = 0;
  int size = 0;
  Graph * arrayofnodes = Load(argv[1], &size, &counter);
  Create_Graph(arrayofnodes, counter);
  Bellman_Ford(arrayofnodes, counter);
  int i;
  for(i = 0; i < counter; i++)
    {
       Graph_Destroy(arrayofnodes[i].next);
    }
  free(arrayofnodes);
  return 0;
}
Graph * Load(char * Filename, int * size, int * counter)
{
  FILE* fptr = fopen(Filename, "r");
  int check = 0;
  int n = 0;
  int i = 0;
  check = fscanf(fptr, "%d", size);
  if(check != 1)
    {
      fprintf(stderr, "fail\n");
    }
  int x = *size;
  n = (*size *(*size)) - (*size); 
  int ind = 0;
  int j = 0;
  int * array = malloc(sizeof(int) * n);
  Graph * array_nodes = malloc(sizeof(Graph) *(n+2));
  array_nodes[*counter].xcoordinate = -1;
  array_nodes[*counter].ycoordinate = 0;
  array_nodes[*counter].next = NULL;
  array_nodes[*counter].label = *counter;
  *counter = *counter + 1;

  for(i = 0; i < n; i++)
    {
      check = fscanf(fptr, "%1d",&(array[i]));
      //printf(" value = %d, index = %d\n", array[i], i);
      if(check != 1)
	{
	  fprintf(stderr, "error");
	}   
    }
  ind = 0;
  for(i = 0; i < x-1; i++)
    {
      for(j = 0; j < x; j++)
	{
	  if(array[ind] == 1)
	    {
              
              array_nodes[*counter].xcoordinate = j;
              array_nodes[*counter].ycoordinate = i;
              array_nodes[*counter].label = *counter;
              array_nodes[*counter].next = NULL;
	      *counter= *counter + 1;
	    }
          ind++;
	}
    }
  array_nodes[*counter].xcoordinate = x;
  array_nodes[*counter].ycoordinate = 0;
  array_nodes[*counter].next = NULL;
  array_nodes[*counter].label = *counter;
  *counter = *counter + 1;
  for(i = 0; i < *counter; i++)
    {
      array_nodes[i].weight = *size * 2;
    }
  fclose(fptr);
  free(array);
  return array_nodes;
}

void Create_Graph(Graph * arrayofnodes, int counter)
{
  int i = 0;
  Graph * newnode = NULL;
  for(i = 0; i < counter; i++)
    {
      if(i == 0)
	{
	  int x = 0;
	  while(x + 1 < counter)
	    {
              newnode = malloc(sizeof(Graph));
	
      *newnode = arrayofnodes[x+1];
              newnode->next = arrayofnodes[i].next;
              arrayofnodes[i].next = newnode;
	      newnode->weight = arrayofnodes[x+1].xcoordinate * 2;
	      x++;
	    }
	}
      else if (i == counter - 1)
        {
	  int j;
	        for(j = 1; j < counter -1; j++)
		 {
		   newnode = malloc(sizeof(Graph));
		  *newnode = arrayofnodes[i];
		  newnode -> next = arrayofnodes[j].next;
		  arrayofnodes[j].next = newnode;
		  newnode -> weight = ((arrayofnodes[i].xcoordinate - arrayofnodes[j].xcoordinate) * 2) - 1;
		 }
        }
      else
	    {
              int j;
	      int left;
	      int right;
	      int weight;
	      for(j = i + 1; j < counter - 1; j++)
		{
		 newnode = malloc(sizeof(Graph));
		 *newnode = arrayofnodes[j];
		 newnode -> next = arrayofnodes[i].next;
		 arrayofnodes[i].next = newnode;
                 if(arrayofnodes[j].xcoordinate < arrayofnodes[i].xcoordinate)
		   {
		     left = j;
		     right = i;
		   }
		 else
		   {
		     left = i;
		     right = j;
		   }
		 if(arrayofnodes[right].ycoordinate >= arrayofnodes[left].ycoordinate -(arrayofnodes[right].xcoordinate - arrayofnodes[left].xcoordinate) && arrayofnodes[right].ycoordinate <= arrayofnodes[left].ycoordinate + (arrayofnodes[right].xcoordinate - arrayofnodes[left].xcoordinate))
		   {
		     weight = ((arrayofnodes[right].xcoordinate - arrayofnodes[left].xcoordinate)*2) - 1;
		   }
		 else
		   {
		     if(arrayofnodes[right].ycoordinate > arrayofnodes[left].ycoordinate)
		       {
		         weight =  ((arrayofnodes[right].ycoordinate - arrayofnodes[left].ycoordinate)*2) - 2;
		       }
		     else
		       {
                         weight =  ((arrayofnodes[left].ycoordinate - arrayofnodes[right].ycoordinate)*2) - 2;

		       }
		   }
		 newnode -> weight = weight;
		 newnode = malloc(sizeof(Graph));
		 *newnode = arrayofnodes[i];
		 newnode -> next = arrayofnodes[j].next;
		 arrayofnodes[j].next = newnode;
		 newnode -> weight = weight;
		 
		}

	    } 
    }
}


void Bellman_Ford(Graph * arrayofnodes, int counter)
{
  int i;
  int j;
  arrayofnodes[0].weight = 0;
  Graph * temp = NULL;
  for(i = 0; i<= counter - 1; i++)
    {
      for(j = 0; j < counter - 1; j++)
	{
	  temp = arrayofnodes[j].next;
	  while(temp != NULL)
	    {              
	      if(arrayofnodes[temp->label].weight > arrayofnodes[j].weight + temp -> weight)
		{
		  arrayofnodes[temp->label].weight =  arrayofnodes[j].weight + temp -> weight;
		}
	      temp = temp -> next;
	    }
	}

    } 
  printf("%d\n", arrayofnodes[counter -1].weight);
 
}



void Graph_Destroy(Graph * temp)
{
  while(temp != NULL)
    {
      Graph *ntemp = temp->next;
      free(temp);
      temp = ntemp;
    }
}
