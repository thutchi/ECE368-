#include "sorting_main.h"
#include<stdio.h>
#include<stdlib.h>



/* This function creates space for a doubly linked list that points to the nodes that are gap sizes away*/

List * List_Create(Node * ln)
{
  List * temp = malloc(sizeof(List));
  temp -> node = ln;
  temp -> next = NULL;
  temp -> prev = NULL;
  return temp;
}

/*This function inserts the nodes that are gap length away into a linked list */

/////////////////////////////////////////////////////
List * List_Insert(Node * ln, List * List_temp)
{
  List * new_list = List_Create(ln);
  if(List_temp == NULL)
    {
      return new_list;
    }
  List_temp -> prev = new_list;
  new_list -> next = List_temp;
  List_temp = new_list;
  return new_list;
}

/* This function Creates size for the value read in from the input file */


////////////////////////////////////////////
Node * Create(long x)
{
  Node * temp = malloc(sizeof(Node));
  temp -> value = x;
  temp -> next = NULL;
  return temp;
}

/* This function inserts values into a linked list from the input file  */

/////////////////////////////////////////////
Node * Insert_ln(Node * temp, long x)
{
  Node * y = Create(x);
  y -> next = temp ;
  return y;
}

/*This function reads value from the input file and stores it into a linked list*/

/////////////////////////////////////////////
Node * Load_File(char * Filename)
{
  Node * temp = NULL;
  long value = 0;
  FILE * fptr;
  fptr = fopen(Filename, "r");
  while(fscanf(fptr, "%li", &value) != -1)
    {
      temp = Insert_ln(temp, value);
    }
  fclose(fptr);  
  return(temp);
}

/*This function perfoms insertion on the doubly linked list of linked lists*/

///////////////////////////////////////////////
void Insertion(List * Listofpointers)
{
  List * temp = Listofpointers;
  if(temp -> node == NULL)
    {
      while(temp -> node == NULL)
	{ 
          temp -> node = temp -> next -> node;
	}
    }

  while(temp!= NULL)
    {
      List * temp1 = temp;
	if(temp1 -> prev == NULL && temp1 -> next != NULL)
	  {
	    if(temp1->node->value < temp1->next->node->value)
	      {
		long temp_value = temp1->node->value;
		temp1->node->value = temp1->next->node->value;
		temp1->next->node->value = temp_value;
	      }
	  }

	else if(temp1->prev!=NULL && temp1->next!=NULL)
	  {
	    if(temp1->node->value < temp1->next->node->value)
	      {
		while((temp1->node->value < temp1->next->node->value) && temp1->prev!=NULL && temp1->next!=NULL && temp1!=NULL)
		  {
		    long temp_value = temp1->node->value;
		    temp1->node->value = temp1->next->node->value;
		    temp1->next->node->value = temp_value;
		    temp1 = temp1->prev;
		  }
	      }
	  }
	else if(temp1->next == NULL)
	  {
	    return;
	  }
	temp = temp->next;
    }
  return;
}

/*This function performs shell sort on a linked list by insertion sort. It also helps set nodes to the linked list of linked lists */

//////////////////////////////////////////////
Node * Shell_Sort(Node * list)
{ 
  int gap = 0;
  int count = 0;
  int x = 0;
  int k = 1;
  int p = 0;
  int size = 0;
  Node * temp_size = list;
  while(temp_size -> next != NULL)
    {
      temp_size = temp_size -> next;
      size++; 
    }
  size = size;
  while(k < size)
    {
      k = k * 3;
      p = p + 1;
    }
  p = p - 1;
  k = k/3;
  
  while(p >= 0)
    {
      gap = k;
      count = p;
      do{
	Node * temp = list;
	List * new_list = NULL;
	for(x = 0; x < gap; x++)
	  {
	    int n = 0;
	    if(x == 0)
	      {
		while(temp != NULL)
		  {
		    if(n % gap == 0)
		      {
			new_list = List_Insert(temp, new_list);
		      }
		    n++;
		    temp = temp -> next;
		  }
	      }
	     List * temp_list = new_list;
	     Insertion(new_list);
	     temp_list = new_list;
             while(temp_list != NULL)
	      {
		if(temp_list -> node != NULL)
		  {
		    temp_list -> node = temp_list -> node -> next;
                  }
		temp_list = temp_list -> next;
	      }
	  }
        List_Destroy(new_list);
	gap = gap/3 * 2;
	count = count - 1;
      }while(count>= 0);
      k = k/3;
      p = p-1;
    }
  return(list);
}

/*This function takes a sorted linked list and saves it to the output file*/

////////////////////////////////////////////////////
int Save_File(char * Filename, Node * list)
{
  FILE * fptr;
  int size = 0;
  Node * temp = list;
  fptr = fopen(Filename, "w");
  int check = 0;
    while(temp != NULL)
      {   
	check = fprintf(fptr, "%li\n", temp-> value);
	if(check < 0)
	  {
	   return size;
	  }
	size++;
	temp = temp -> next;
      } 
  size += 1;
  fclose(fptr);
  return size;
}

/*This function frees all the memory allocated to the orginal linked list*/

/////////////////////////////////////////////////////////////
void Node_destroy(Node * ln)
{
  while(ln != NULL)
    {
      Node * head = ln -> next;
      free(ln);
      ln = head;
    }
}

/*This function frees all the memory allocated to the linked list of linked lists*/

///////////////////////////////////////////////////////////////
void List_Destroy(List * listofpointers)
{
  while(listofpointers != NULL)
    {
      List * list_temp = listofpointers -> next;
      free(listofpointers);
      listofpointers = list_temp;
    }
}
