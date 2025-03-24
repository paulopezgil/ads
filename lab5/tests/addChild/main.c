#include "../../graph.h"
#include <stdio.h>

int main()
{
    /* test addChild */
    Graph G = createGraph(3);
    addChild(G, 3, 1, 2, 10);
    addChild(G, 3, 1, 3, 11);
    for(int idx = 1; idx != 4; ++idx)
    {
        printf("Node %d:\n", idx);
        if (G[idx].children == NULL)
            printf("ListPtr = NULL ");
        else
        {
            printf("Children of node %d:\n", idx);
            ListPtr ptr = G[idx].children;
            for (int jdx = 0; ptr != NULL; ++jdx)
            {
                printf("Child %d: node = %d, weight = %d\n", jdx, ptr->node, ptr->weight);
                ptr = ptr->next;
            }
        }
        printf("nChilds = %d\n", G[idx].nChilds);
        printf("parent = %d\n", G[idx].parent);
        printf("pdistance = %d\n", G[idx].pdistance);
    }

    /* print the reversed graph */
    for(int idx = 4; idx != 7; ++idx)
    {
        printf("Node %d (R):\n", idx - 3);
        if (G[idx].children == NULL)
            printf("ListPtr = NULL ");
        else
        {
            printf("Children of node %d (R):\n", idx - 3);
            ListPtr ptr = G[idx].children;
            for (int jdx = 0; ptr != NULL; ++jdx)
            {
                printf("Child %d: node = %d (R), weight = %d\n", jdx, ptr->node - 3, ptr->weight);
                ptr = ptr->next;
            }
        }
        printf("nChilds = %d\n", G[idx].nChilds);
        printf("parent = %d\n", G[idx].parent);
        printf("pdistance = %d\n", G[idx].pdistance);
    }
}