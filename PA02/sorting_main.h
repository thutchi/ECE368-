typedef struct node{
  long value;
  struct node * next;
} Node;


typedef struct list{
  Node * node;
  struct list * next;
  struct list * prev;
}List;

void print(Node * linked_list);
Node * Load_File(char * Filename);
Node * Create(long x);
Node * Insert_ln(Node * temp, long x);
Node * Shell_Sort(Node * list);
void   Insertion(List * Listofpointers);
List * List_Insert(Node * ln, List * List_temp);
List * List_Create(Node * ln);
int Save_File(char * Filename, Node * list);
void Node_destroy(Node * ln);
void List_Destroy(List * listofpointers);
