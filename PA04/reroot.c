#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "reroot.h"

int main(int argc, char **argv)
{
  int size = 0;
  int i = 0;
  double max_width = 0;
  double max_height = 0;
  Tree * array= Load(argv[1], &size);
  int check = 0;
  Stack * myStack = NULL;
  Tree * node = NULL;
  //creates the binary tree
  for(i = 0; i < size; i++)
    {
      if(array[i].cutline == '-')
	{
          Stack_Push(&(array[i]), &(myStack));
	}
      else
	{
	  node = Stack_Pop(&(myStack), &(array[i]));
	}
    }
  printf("Preorder: ");
  pre_order_print(node);
  printf("\n\nInorder: ");
  inorder_print(node);
  printf("\n\nPostorder: ");
  post_order_print(node);
  find_dimensions(node);
  clock_t time1 = clock();
  find_coordinates(node);
  clock_t time2 = clock();
  double total_time = (double)(time2 - time1)/(double)CLOCKS_PER_SEC;
  printf("\n\nWidth: %e\nHeight: %e\n",node -> width, node -> height);
  printf("\nX-coordinate: %e\nY-coordinate: %e\n",array[0].xcoord, array[0].ycoord);
  printf("\nElapsed time: %e\n", total_time);
  max_width = array[size -1].width;
  max_height = array[size -1].height;
  check = Save(argv[2], array, size);
  if(check != size)
    {
      fprintf(stderr, "did not write everything\n");
    } 
  clock_t time3 = clock();
  reroot_right(node, node -> right, &max_width, &max_height);
  reroot_left(node, node -> left, &max_width, &max_height);
  clock_t time4 = clock();
  double total_time2 = (double)(time4 - time3)/(double)CLOCKS_PER_SEC; 
  printf("\nBest width: %e\nBest height: %e\n",max_width, max_height);
  printf("\nElapsed time for re-rooting: %e\n",total_time2);
  free(myStack);
  free(array);
 
  return 1;

}

//loads the file into an array of nodea
Tree * Load(char * Filename, int * size)
{
  double width;
  double height;
  char cutline;
  char comma;
  char parth;
  FILE * fptr = fopen(Filename, "r");
  int check = 0;
  while(!feof(fptr))
    {
      check = fscanf(fptr, "%c", &cutline);
      if(cutline == '(')
	{
	  check = fscanf(fptr, "%le %c %le %c", &width, &comma, &height, &parth);
	  if(check < 0)
	    {
	      fprintf(stderr, "2nothing left to read");
	    }
          
	}     
      if(check != -1)
	{
	  (*size)++;
	} 
    }
  rewind(fptr);
  Tree * array = malloc(sizeof(Tree) * (*size));
  int counter = 0;
  while(counter < *size)
    {
      check = fscanf(fptr, "%c", &cutline);
      if(cutline == '(')
	{
          check = fscanf(fptr, "%le %c %le %c", &width, &comma, &height, &parth);
	  array = Create_Array(array, width, height, '-', counter);
	    
	}
      if(cutline == 'V' || cutline == 'H')
	{
	  check = fscanf(fptr, "%le %c %le %c",&width, &comma, &height, &parth);
	  array = Create_Array(array, 0, 0, cutline, counter);
	    
	}
      counter++;
     
    }
  fclose(fptr);
  return array;
}

//creates the array of the node
Tree * Create_Array(Tree * array, double width, double height, char cutline, int counter)
{
  Tree * temp = malloc(sizeof(Tree));
  temp -> width = width;
  temp -> height = height;
  temp -> cutline = cutline;
  temp -> xcoord = 0;
  temp -> ycoord = 0;
  temp -> left = NULL;
  temp -> right = NULL;
  array[counter] = *temp;
  free(temp);
  return array;
}

//pushes on the stack 
void Stack_Push(Tree * holder, Stack ** myStack)
{
  Stack * temp = malloc(sizeof(Stack));
  temp -> next = *myStack;
  temp -> node = holder;
  *myStack = temp; 
}

//pops the stack 
Tree * Stack_Pop(Stack ** myStack, Tree * holder)
{
  if(myStack == NULL || holder == NULL)
    {
      return NULL;
    }
  
  Tree * myNode = (*myStack) -> node;
  holder -> right = myNode;
  Stack * temp = (*myStack) -> next;
  free(*myStack);
  *myStack = temp;
  Tree * myNode2 = (*myStack) -> node;
  holder -> left = myNode2;
  temp = (*myStack) -> next;
  free(*myStack);
  *myStack = temp;
  Stack_Push(holder, myStack);
  return holder;
}

//post order print 
void post_order_print(Tree * node)
{
  if(node != NULL)
    {
      post_order_print(node -> left);
      post_order_print(node -> right);
      if(node -> cutline == '-')
	{
          printf("(%le,%le)", node -> width, node -> height);
	}
      else
	{
	  printf("%c",node -> cutline);
	}
    }
}

//pre order print 
void pre_order_print(Tree * node)
{
  if(node != NULL)
    {
      if(node -> cutline == '-')
	{
          printf("(%le,%le)", node -> width, node -> height);
	}
      else
	{
	  printf("%c",node -> cutline);
	}
      pre_order_print(node -> left);
      pre_order_print(node -> right);
    }
}    

//in order print 
void inorder_print(Tree * node)
{
if(node != NULL)
    {
      inorder_print(node -> left);
      if(node -> cutline == '-')
	{
          printf("(%le,%le)", node -> width, node -> height);
	}
      else
	{
	  printf("%c",node -> cutline);
	}
      inorder_print(node -> right);
    }
}

//find coordinates
void find_coordinates(Tree * headnode)
{
  if(headnode == NULL)
    {
      return;
    }
  if(headnode -> cutline == 'H')
    {
      headnode -> right -> xcoord = headnode -> xcoord;
      headnode -> right -> ycoord = headnode -> ycoord;
      headnode -> left -> xcoord = headnode -> xcoord;
      headnode -> left -> ycoord = headnode -> ycoord + headnode->right->height;
    }
  if(headnode -> cutline == 'V')
    {
      headnode -> left -> xcoord = headnode -> xcoord;
      headnode -> left -> ycoord = headnode -> ycoord;
      headnode -> right -> xcoord = headnode -> xcoord + headnode->left->width;
      headnode -> right -> ycoord = headnode -> ycoord;
    }
  find_coordinates(headnode -> left);
  find_coordinates(headnode -> right);
}

//finds dimensions 
void find_dimensions(Tree * headnode)
{
  if(headnode == NULL)
    {
      return;
    }
  if(headnode -> left != NULL)
    {
      find_dimensions(headnode -> left);
    }
  if(headnode -> right != NULL)
    {
      find_dimensions(headnode -> right);
    }
  if(headnode -> cutline == 'H')
    {
      headnode -> height = headnode -> left -> height + headnode ->right -> height;
      if(headnode -> left -> width > headnode -> right -> width)
	{
	  headnode -> width = headnode -> left -> width;
	}
      else 
	{
	  headnode -> width = headnode -> right -> width;
	}
    }
  if(headnode -> cutline == 'V')
    {
      headnode -> width = headnode -> left -> width + headnode -> right -> width;
      if(headnode -> left -> height > headnode -> right -> height)
	{
	  headnode -> height = headnode -> left -> height;
	}
      else
	{
	  headnode -> height = headnode -> right -> height;
	}
    }
}

//reroots the right side of the tree
void reroot_right(Tree * A, Tree * B, double * max_width, double * max_height)
{
  //stops recursion if one of the childern is null(because of the strictly binary tree)
  if(B -> left == NULL)
    {
      return;
    }
  //changes pointer of A right and B right
  A-> right = B -> right;
  B -> right = A;
  find_dimensions(B);
  //finds area of rectangle after new dimensions 
  if((B->width * B->height) < ((*max_width) * (*max_height)))
    {
      *max_width = B -> width;
      *max_height = B -> height;
    }
  if((B -> width * B -> height) == ((*max_width) * (*max_height)))
    {
      if(B -> width < *max_width)
	{
	  *max_width = B -> width;
	  *max_height = B -> height;
	}
    }
  //thens go to  the left
  reroot_left(B, B->left, max_width, max_height);
    
  //rewrites the the pointers to its orginal position 
  B ->right = A->right;
  A-> right = B;
    
  //writes A right to B left 
  A->right = B->left;
  B -> left = A;
  find_dimensions(B);
  //Finds area of the new dimensions 
  if((B -> width * B -> height) < ((*max_width) * (*max_height)))
    {
      *max_width = B -> width;
      *max_height = B -> height;
    }
   if((B -> width * B -> height) == ((*max_width) * (*max_height)))
    {
      if(B -> width < *max_width)
	{
	  *max_width = B -> width;
	  *max_height = B -> height;
	}
    }
   //then goes to the right 
  reroot_right(B,B->right, max_width, max_height);
  
  //rewrites the pointers to the orignal position  
  B->left = A->right;
  A->right = B;
    
}

//reroots the left side of the tree
void reroot_left(Tree * A, Tree * B, double * max_width, double * max_height)
{
  //returns if a child is null (because it is a strictly binary tree)
  if(B -> right == NULL)
    {
      return;
    }
  //reroots B left and A left 
  A -> left = B -> left;
  B -> left = A;
  find_dimensions(B);
  //computes the area of the square after finding the dimensions
  if((B -> width * B -> height) < ((*max_width) * (*max_height)))
    {
      *max_width = B -> width;
      *max_height = B -> height;
    }
   if((B -> width * B -> height) == ((*max_width) * (*max_height)))
    {
      if(B -> width < *max_width)
	{
	  *max_width = B -> width;
	  *max_height = B -> height;
	}
    }
   //then goes to the right
  reroot_right(B, B-> right, max_width, max_height);
  //reassigns the tree back to the orginal state  
  B -> left = A -> left;
  A -> left = B;
    
  //reroots A left and B right
  A->left = B -> right;
  B -> right = A;
  find_dimensions(B);
  
  //computes area and changes if it needs to 
  if((B -> width * B -> height) < ((*max_width) * (*max_height)))
    {
      *max_width = B -> width;
      *max_height = B -> height;
    }
   if((B -> width * B -> height) == ((*max_width) * (*max_height)))
    {
      if(B->width < *max_width)
	{
	  *max_width = B->width;
	  *max_height = B->height;
	}
    }
   //then goes to the left 
  reroot_left(B, B-> left, max_width, max_height);

  //reassigns the pointer to the original state
  B -> right = A -> left;
  A -> left = B;
}

//Saves the width, height, xcoord, ycoord of a rectangle to a file 
int Save(char * Filename, Tree * array, int size)
{
  if(array == NULL)
    {
      return 0;
    }
  int i = 0;
  FILE * fptr = fopen(Filename, "w");
  for(i = 0; i < size; i ++)
    {
      if(array[i].cutline == '-')
	{
	  fprintf(fptr, "%e %e %e %e\n",array[i].width, array[i].height, array[i].xcoord, array[i].ycoord);
	}
    } 
  fclose(fptr);
  return i;

}
