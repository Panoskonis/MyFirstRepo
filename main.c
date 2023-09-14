#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"

int main(void)
{
    Graph *Graph_1 = CreateGraph();
    CreateNode(Graph_1, 1);
    CreateNode(Graph_1, 2);
    CreateNode(Graph_1, 3);
    CreateNode(Graph_1, 4);
    CreateNode(Graph_1, 5);
    AddCon(Graph_1, 1, 2);
    AddCon(Graph_1, 1, 3);
    AddCon(Graph_1, 1, 4);
    AddCon(Graph_1, 1, 5);
    AddCon(Graph_1, 2, 3);
    AddCon(Graph_1, 2, 4);
    AddCon(Graph_1, 2, 5);
    AddCon(Graph_1, 3, 4);
    AddCon(Graph_1, 3, 5);
    AddCon(Graph_1, 4, 5);
    ExportToDot(Graph_1, "Test.dot");
    // RemoveCon(Graph_1, 3, 1);
    // RemoveCon(Graph_1, 3, 2);
    // RemoveCon(Graph_1, 3, 5);
    // RemoveCon(Graph_1, 3, 4);
    RemoveNode(Graph_1, 3);
    ExportToDot(Graph_1, "Test1.dot");
    DeallocateGraph(Graph_1);

    return 0;
}
