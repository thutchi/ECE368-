//defines the tree structure

typedef struct tree{
  double width;
  double height;
  double xcoord;
  double ycoord;
  char cutline;
  struct tree * left;
  struct tree * right;
}Tree;

//defines the stack structure

typedef struct stack{
  Tree * node;
  struct stack * next;
}Stack;

Tree * Create_Array(Tree * array, double width, double height, char cutline, int counter);
Tree * Load(char * Filename, int * size);
//Stack * Create_Stack();
void Stack_Push(Tree * holder, Stack ** myStack);
Tree * Stack_Pop(Stack ** myStack, Tree * holder);
void post_order_print(Tree * node);
void Tree_destroy(Tree * node);
void find_dimensions(Tree * headnode);
void find_coordinates(Tree * headnode);
void reroot_right(Tree * A, Tree * B, double * max_width, double * max_height);
void reroot_left(Tree * A, Tree * B, double * max_width, double * max_height);
void pre_order_print(Tree * node);
void inorder_print(Tree * node);
int Save(char * Filename, Tree * array, int size);
