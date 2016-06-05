#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "packing.h"

int main(int argc, char **argv)
{
  int blocks;
  Tree * array, *root;
  printf("\n");
  array  = Load(argv[1], &root, &blocks);
  printf("Preorder: ");
  pre_order_print(root);
  printf("\n\n");
  printf("Inorder: ");
  in_order_print(root);
  printf("\n\n");
  printf("Postorder: ");
  post_order_print(root);
  printf("\n\n");

  find_dimensions(root);
  clock_t time1 = clock();
  find_coordinates(root);
  clock_t time2 = clock();
  double total_time = (double)(time2 - time1)/(double)CLOCKS_PER_SEC;
  int check = Save_File(argv[2], blocks, array);
  printf("Width: %e\nHeight: %e\nX-coordinate: %e\nY-coordinate: %e\n\nElapsed Time: %e\n", root -> width, root -> height, array[blocks - 1].xcord, array[blocks - 1].ycord, total_time);
  if(check == 0)
    {
      fprintf(stderr, "Did not save file!!!!!!");
    }
  free(array);
  return 1;
}
// function loads file and makes an array of nodes and builds the tree
Tree * Load(char * Filename, Tree ** rootnode, int * blocks)
{
  char charwidth;
  char charheight;
  //Tree * array;
  int nodes = 0;
  int thisnode;
  int parnode;
  int lcnode;
  int rcnode;
  char cutline;
  double width;
  double height;
  int i = 0;
  int check = 0;
  FILE * fptr = fopen(Filename, "r");
  if(fptr == NULL)
    {
      return NULL;
    }
  check = fscanf(fptr, "%d", blocks);
  if(check == 0)
    {
      return NULL;
    }
  check = fscanf(fptr, "%d", &nodes);
  if(check == 0)
    {
      return NULL;
    }
  Tree * array = malloc(sizeof(Tree) *nodes);
  while(i < nodes)
    { 
      if(i < *blocks)
	{
      check = fscanf(fptr, "%d %d %d %d %c %lf %lf", &thisnode, &parnode, &lcnode, &rcnode, &cutline, &width, &height);
	}
      if(i >= *blocks)
	{
	  check = fscanf(fptr, "%d %d %d %d %c %c %c", &thisnode, &parnode, &lcnode, &rcnode, &cutline, &charwidth, &charheight);
	  width = -1;
	  height = -1;
	}
      if(parnode == -1)
	{
	  *rootnode = &array[thisnode - 1];
	}
      array = Save_Tree(thisnode, parnode, lcnode, rcnode, cutline, width, height, nodes, i, array);
      i++;
    }
  build_tree(array, *rootnode);
  fclose(fptr);
  return array;
}

//builds tree
void  build_tree(Tree * array, Tree * holder)
{
  int left = holder -> lcnode;
  int right = holder -> rcnode;
  if(left != -1)
    {
      holder -> leftnode = &array[left -1];
      build_tree(array, holder -> leftnode);
    }
   if(right != -1)
    {
      holder -> rightnode = &array[right -1];
      build_tree(array, holder -> rightnode);
    }   
   
   return;

}
//builds a node
Tree * Save_Tree(int thisnode, int parnode, int lcnode, int rcnode, char cutline, double width, double height, int nodes, int counter, Tree * array)
{
  Tree * temp = malloc(sizeof(Tree));
  temp -> thisnode = thisnode;
  temp -> parnode = parnode;
  temp -> lcnode = lcnode;
  temp -> rcnode = rcnode;
  temp -> cutline = cutline;
  temp -> width = width;
  temp -> height = height;
  temp -> xcord = 0;
  temp -> ycord = 0;
  temp -> leftnode = NULL;
  temp -> rightnode = NULL;
  array[counter] = *temp;
  free(temp);
  return array;
}

//prints post order traversal 
void post_order_print(Tree * headnode)
{
  if(headnode != NULL)
    {
      post_order_print(headnode -> leftnode);
      post_order_print(headnode -> rightnode);
      printf("%d ", headnode -> thisnode);
    }
}

//prints pre order traversal 
void pre_order_print(Tree * headnode)
{
  if(headnode != NULL)
    {
      printf("%d ", headnode -> thisnode);
      pre_order_print(headnode -> leftnode);
      pre_order_print(headnode -> rightnode);
    }
}

//prints in order traversal
void in_order_print(Tree * headnode)
{
  if(headnode != NULL)
    {
      in_order_print(headnode -> leftnode);
      printf("%d ", headnode -> thisnode);
      in_order_print(headnode ->rightnode);
    }
}

//finds dimensions by traversing the tree in post order
void find_dimensions(Tree * headnode)
{
  if(headnode == NULL)
    {
      return;
    }
  if(headnode -> lcnode != -1)
    {
      find_dimensions(headnode -> leftnode);
    }
  if(headnode -> rcnode !=-1)
    {
      find_dimensions(headnode -> rightnode);
    }
  if(headnode -> cutline == 'H')
    {
      headnode -> height = headnode -> leftnode -> height + headnode ->rightnode -> height;
      if(headnode -> leftnode -> width > headnode -> rightnode -> width)
	{
	  headnode -> width = headnode -> leftnode -> width;
	}
      else 
	{
	  headnode -> width = headnode -> rightnode -> width;
	}
    }
  if(headnode -> cutline == 'V')
    {
      headnode -> width = headnode -> leftnode -> width + headnode -> rightnode -> width;
      if(headnode -> leftnode -> height > headnode -> rightnode -> height)
	{
	  headnode -> height = headnode -> leftnode -> height;
	}
      else
	{
	  headnode -> height = headnode -> rightnode -> height;
	}
    }
}

//finds coordinates by pre order traversal 
void find_coordinates(Tree * headnode)
{
  if(headnode == NULL)
    {
      return;
    }
  if(headnode -> cutline == 'H')
    {
      headnode -> rightnode -> xcord = headnode -> xcord;
      headnode -> rightnode -> ycord = headnode -> ycord;
      headnode -> leftnode -> xcord = headnode -> xcord;
      headnode -> leftnode -> ycord = headnode -> ycord + headnode->rightnode->height;
    }
  if(headnode -> cutline == 'V')
    {
      headnode -> leftnode -> xcord = headnode -> xcord;
      headnode -> leftnode -> ycord = headnode -> ycord;
      headnode -> rightnode -> xcord = headnode -> xcord + headnode->leftnode->width;
      headnode -> rightnode -> ycord = headnode -> ycord;
    }
  find_coordinates(headnode -> leftnode);
  find_coordinates(headnode -> rightnode);
}


//saves the file and prints in the file 
int Save_File(char * Filename, int blocks, Tree * array)
{
  int i = 0;
  FILE * fptr = fopen(Filename, "w");
  if(fptr == NULL)
    {
      return 0;
    }
  fprintf(fptr, "%d\n", blocks);

  for(i = 0; i < blocks; i++)
    {
      fprintf(fptr, "%d %e %e %e %e\n",array[i].thisnode, array[i].width, array[i].height, array[i].xcord, array[i].ycord);
    }
  fclose(fptr);
  return(i);
}
