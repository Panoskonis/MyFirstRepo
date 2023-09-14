#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"
// Creates Empty Graph
Graph *CreateGraph()
{
    Graph *NewGraph = (Graph *)malloc(sizeof(Graph));
    if (NewGraph == NULL)
    {
        printf("ERROR: New Graph Creation Failed\n");
        exit(1);
    }
    NewGraph->NodeNum = 0;
    NewGraph->Nodes = NULL;
    return NewGraph;
}

// Adds a node to an existing graph
void CreateNode(Graph *MyGraph, int NUM)
{
    if (NUM < MyGraph->NodeNum && MyGraph->Nodes[NUM - 1] == NULL)
    {
        MyGraph->Nodes[NUM - 1] = (Node *)malloc(sizeof(Node));
        if (MyGraph->Nodes[NUM - 1] == NULL)
        {
            printf("ERROR: Allocation of memory for node creation failed!\n");
            exit(1);
        }
        MyGraph->Nodes[NUM - 1]->Val = NUM;
        MyGraph->Nodes[NUM - 1]->ConNum = 0;
        MyGraph->Nodes[NUM - 1]->Cons = NULL;
        return;
    }
    if (NUM < MyGraph->NodeNum && MyGraph->Nodes[NUM - 1] != NULL)
    {
        printf("Node Already exists! Please select a larger node number!\n");
        return;
    }

    MyGraph->NodeNum++;
    MyGraph->Nodes = realloc(MyGraph->Nodes, MyGraph->NodeNum * sizeof(Node *));
    if (MyGraph->Nodes == NULL)
    {
        printf("ERROR: Reallocation of memory for node creation failed!\n");
        exit(1);
    }
    MyGraph->Nodes[MyGraph->NodeNum - 1] = (Node *)malloc(sizeof(Node));
    if (MyGraph->Nodes[MyGraph->NodeNum - 1] == NULL)
    {
        printf("ERROR: Allocation of memory for node creation failed!\n");
        exit(1);
    }
    MyGraph->Nodes[MyGraph->NodeNum - 1]->Val = MyGraph->NodeNum;
    MyGraph->Nodes[MyGraph->NodeNum - 1]->ConNum = 0;
    MyGraph->Nodes[MyGraph->NodeNum - 1]->Cons = NULL;
}

// Return 1 if two nodes are already connected
int IsCon(Graph *MyGraph, int src, int dest)
{
    for (int i = 0; i < MyGraph->Nodes[src - 1]->ConNum; i++)
    {
        if (MyGraph->Nodes[src - 1]->Cons[i] == MyGraph->Nodes[dest - 1])
        {
            printf("Nodes %d and %d already connected\n", MyGraph->Nodes[src - 1]->Val, MyGraph->Nodes[dest - 1]->Val);
            return 1;
        }
    }
    return 0;
}

void AddCon(Graph *MyGraph, int src, int dest)
{
    if (MyGraph->Nodes[src - 1] == NULL || MyGraph->Nodes[dest - 1] == NULL)
    {
        printf("Nodes Must exist or not be reomoved to connect them\n");
        return;
    }
    if (src == dest)
    {
        printf("Can't connect Node with it's self!\n");
        return;
    }
    if (IsCon(MyGraph, src, dest) != 1)
    {
        MyGraph->Nodes[src - 1]->ConNum++;
        MyGraph->Nodes[dest - 1]->ConNum++;
        MyGraph->Nodes[src - 1]->Cons = realloc(MyGraph->Nodes[src - 1]->Cons, (MyGraph->Nodes[src - 1]->ConNum) * sizeof(Node *));
        if (MyGraph->Nodes[src - 1]->Cons == NULL)
        {
            printf("ERROR: Memory allocation with realloc FAILED for src->Cons!\n");
            exit(1);
        }
        MyGraph->Nodes[src - 1]->Cons[MyGraph->Nodes[src - 1]->ConNum - 1] = MyGraph->Nodes[dest - 1];
        MyGraph->Nodes[dest - 1]->Cons = realloc(MyGraph->Nodes[dest - 1]->Cons, (MyGraph->Nodes[dest - 1]->ConNum) * sizeof(Node *));
        if (MyGraph->Nodes[dest - 1]->Cons == NULL)
        {
            printf("ERROR: Memory allocation with realloc FAILED for dest->Cons!\n");
            exit(1);
        }
        MyGraph->Nodes[dest - 1]->Cons[MyGraph->Nodes[dest - 1]->ConNum - 1] = MyGraph->Nodes[src - 1];
    }
}

void ExportToDot(Graph *MyGraph, const char *filename)
{
    FILE *dotFile = fopen(filename, "w");
    if (dotFile == NULL)
    {
        printf("ERROR: Unable to open DOT file for writing.\n");
        return;
    }

    // Write DOT file header
    fprintf(dotFile, "graph G {\n");

    // Write nodes
    for (int i = 0; i < MyGraph->NodeNum; i++)
    {
        if (MyGraph->Nodes[i] != NULL)
        {
            fprintf(dotFile, "  %d;\n", MyGraph->Nodes[i]->Val);
        }
    }

    // Write edges
    for (int i = 0; i < MyGraph->NodeNum; i++)
    {
        if (MyGraph->Nodes[i] != NULL)
        {
            for (int j = 0; j < MyGraph->Nodes[i]->ConNum; j++)
            {
                fprintf(dotFile, "  %d -- %d;\n", MyGraph->Nodes[i]->Val, MyGraph->Nodes[i]->Cons[j]->Val);
            }
        }
    }

    // Close the DOT file
    fprintf(dotFile, "}\n");
    fclose(dotFile);
}

void RemoveCon(Graph *MyGraph, int src, int dest)
{
    Node *SRC = MyGraph->Nodes[src - 1];
    Node *DEST = MyGraph->Nodes[dest - 1];
    for (int i = 0; i < SRC->ConNum; i++)
    {
        if (SRC->Cons[i] == DEST)
        {
            SRC->Cons[i] = NULL;
            SRC->Cons[i] = SRC->Cons[SRC->ConNum - 1];
            SRC->ConNum--;
            SRC->Cons = realloc(SRC->Cons, SRC->ConNum * sizeof(Node *));
            break;
        }
    }
    for (int i = 0; i < DEST->ConNum; i++)
    {
        if (DEST->Cons[i] == SRC)
        {
            DEST->Cons[i] = NULL;
            DEST->Cons[i] = DEST->Cons[DEST->ConNum - 1];
            DEST->ConNum--;
            DEST->Cons = realloc(DEST->Cons, DEST->ConNum * sizeof(Node *));
            break;
        }
    }
}

void RemoveNode(Graph *MyGraph, int Rem)
{
    if (Rem > MyGraph->NodeNum || Rem < 1 || MyGraph->Nodes[Rem - 1] == NULL)
    {
        printf("The Node You Want To Remove Does Not Exist!\n");
        return;
    }
    Node *REM = MyGraph->Nodes[Rem - 1];
    int MAX = REM->ConNum;
    for (int i = 0; i < MAX; i++)
    {
        printf("%d",REM->Cons[i]->Val);
        RemoveCon(MyGraph, Rem, REM->Cons[i]->Val);
    }
    free(REM->Cons);
    MyGraph->Nodes[Rem - 1] = NULL;

    free(REM);
}

void DeallocateGraph(Graph *MyGraph)
{
    for (int i = 0; i < MyGraph->NodeNum; i++)
    {
        if (MyGraph->Nodes[i] != NULL)
        {
            Node *cur = MyGraph->Nodes[i];
            free(cur->Cons);
            free(cur);
        }
    }
    free(MyGraph->Nodes);
    free(MyGraph);
}
