#include "../../solver.h"
#include <stdio.h>

/* 
    the test was created before readInput was a void function, the main
    functionality is the same.
*/
int main()
{
    /* read the first line and create the graph */
    int nChambers, nTunnels;
    scanf("%d %d", &nChambers, &nTunnels);
    Graph G = createGraph(nChambers);

    /* read the chambers with a reverse button */
    int readNum = 0;
    scanf("%d", &readNum);
    while (readNum != -1)
    {
        addReverseButton(G, nChambers, readNum);
        scanf("%d", &readNum);
    }

    /* read the tunnels */
    int parent, child, weight;
    for (int idx = 0; idx != nTunnels; ++idx)
    {
        scanf("%d %d %d", &parent, &child, &weight);
        addChild(G, nChambers, parent, child, weight);
    }

    /* print the generated graph */
    printf("Normal graph: \n\n");
    for (int idx = 1; idx <= nChambers; ++idx)
    {
        printf("(Child, weight) list of node %d:\n", idx);
        ListPtr ptr = G[idx].children;
        for(int jdx = 0; ptr != NULL; ++jdx)
        {
            printf("(%d, %d)", ptr->node, ptr->weight);
            ptr = ptr->next;
        }
        printf("\n\n");
    }

    /* print the reversed graph */
    printf("Reversed graph: \n\n");
    for (int idx = nChambers + 1; idx <= 2 * nChambers; ++idx)
    {
        printf("(Child, weight) list of node %d:\n", idx % nChambers);
        ListPtr ptr = G[idx].children;
        for(int jdx = 0; ptr != NULL; ++jdx)
        {
            printf("(%d, %d)", ptr->node % nChambers, ptr->weight);
            ptr = ptr->next;
        }
        printf("\n\n");
    }
}