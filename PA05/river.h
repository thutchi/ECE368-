typedef struct graph{
  int xcoordinate; 
  int ycoordinate;
  int weight;
  int label;
  struct graph * next;
}Graph;

Graph *Load(char * Filename, int * size, int * counter);
void Create_Graph(Graph * arrayofnodes, int counter);
void Bellman_Ford(Graph * arrayofnodes, int counter);
void Graph_Destroy(Graph * temp);
