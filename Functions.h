#ifndef FUNCTIONS_H
#define FUNCTIONS_H


typedef struct Node
{
    int Val;
    int ConNum;
    struct Node **Cons;
} Node;

typedef struct Graph
{
    int NodeNum;
    Node **Nodes;
} Graph;

Graph* CreateGraph();
void CreateNode(Graph *MyGraph, int NUM);
int IsCon(Graph *MyGraph, int src, int dest);
void AddCon(Graph *MyGraph, int src, int dest);
void ExportToDot(Graph *MyGraph, const char *filename);
void RemoveCon(Graph *MyGraph, int src, int dest);
void RemoveNode(Graph *MyGraph, int Rem);
void DeallocateGraph(Graph *MyGraph);










#endif