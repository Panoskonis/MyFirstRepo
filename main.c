#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"
void ShowInstructions()
{
    printf("Use: node 'num' to create a node\n");
    printf("Use con 'num1' 'num2' to connect two existing nodes\n");
    printf("Use remnode 'num' to remove a node\n");
    printf("Use remcon 'num1' 'num2' to remove a connection");
    printf("Use show to print the graph in a png picture!\n");
    printf("Use help to show instructions again\n");
}
int main(void)
{
    Graph *Graph_1 = CreateGraph();
    ShowInstructions();
    while (1)
    {
        char buffer[20];
        char com[10];
        int node_1;
        int node_2;
        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            if (sscanf(buffer, "%10s %d %d", com, &node_1, &node_2) == 1)
            {
                if (strcmp(com, "help") == 0)
                {
                    ShowInstructions();
                }
                else if (strcmp(com, "show") == 0)
                {
                    ExportToDot(Graph_1, "Test.dot");
                    system("dot -Tpng Test.dot -o output.png");
                }
                else if (strcmp(com, "exit") == 0)
                {
                    exit(0);
                }
                else
                {
                    printf("Invalid command!\n");
                }
            }
            else if (sscanf(buffer, "%10s %d %d", com, &node_1, &node_2) == 2)
            {
                if (strcmp(com, "node") == 0)
                {
                    if (node_1 > 0 && (node_1 == Graph_1->NodeNum + 1 || Graph_1->Nodes[node_1 - 1] == NULL))
                    {
                        CreateNode(Graph_1, node_1);
                    }
                    else
                    {
                        printf("Invalid Node number. Please select a number that is larger than the max current node or has been deleted!\n");
                    }
                }
                else if (strcmp(com, "remnode") == 0 )
                {
                    if (node_1 > 0 && node_1 < Graph_1->NodeNum + 1 && Graph_1->Nodes[node_1 - 1] != NULL)
                    {

                        RemoveNode(Graph_1, node_1);
                    }
                    else
                    {
                        printf("Invalid Node to remove\n");
                    }
                }
                else
                {
                    printf("Invalid command!\n");
                }
            }
            else if (sscanf(buffer, "%10s %d %d", com, &node_1, &node_2) == 3)
            {
                if (strcmp(com, "con") == 0)
                {
                    if (node_1 > 0 && node_1 < Graph_1->NodeNum + 1 && Graph_1->Nodes[node_1 - 1] != NULL && node_2 > 0 && node_2 < Graph_1->NodeNum + 1 && Graph_1->Nodes[node_2 - 1] != NULL)
                    {
                        AddCon(Graph_1, node_1, node_2);
                    }
                    else
                    {
                        printf("Please select valid node indexes to connect!\n");
                    }
                }
                else if (strcmp(com, "remcon") == 0)
                {
                    if (node_1 > 0 && node_1 < Graph_1->NodeNum + 1 && Graph_1->Nodes[node_1 - 1] != NULL && node_2 > 0 && node_2 < Graph_1->NodeNum + 1 && Graph_1->Nodes[node_2 - 1] != NULL)
                    {
                        RemoveCon(Graph_1, node_1, node_2);
                    }
                    else
                    {
                        printf("Please select valid nodes!\n");
                    }
                }
                else
                {
                    printf("Invalid Command!\n");
                }
            }
            else
            {
                printf("Invalid Command!\n");
            }
        }
    }
    DeallocateGraph(Graph_1);
    return 0;
}
