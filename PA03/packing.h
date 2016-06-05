typedef struct tree{
  int thisnode;
  int parnode;
  int lcnode;
  int rcnode;
  char cutline;
  double width;
  double height;
  double xcord;
  double ycord;
  struct tree * leftnode;
  struct tree * rightnode;
}Tree;

Tree * Load(char * Filename, Tree ** rootnode, int * blocks);
Tree * Save_Tree(int thisnode, int parnode, int lcnode, int rcnode, char cutline, double width, double height, int nodes, int counter, Tree * array);
void build_tree(Tree * array, Tree * holder);
void post_order_print(Tree * headnode);
void in_order_print(Tree * headnode);
void pre_order_print(Tree * headnode);
void find_dimensions(Tree * headnode);
void find_coordinates(Tree * headnode);
int Save_File(char * Filename, int blocks, Tree * array);
