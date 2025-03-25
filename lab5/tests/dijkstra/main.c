#include "../../solver.h"
#include "../../graph.h"
#include "../../heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

void printHeap(Heap hp)
{
    printf("Heap size: %d\n", hp.size);
    printf("Heap front: %d\n", hp.front);
    printf("Position array: ");
    for (int idx = 0; idx != hp.size; ++idx)
        printf("%d ", hp.position[idx]);
    printf("\nHeap array: ");
    for(int idx = 1; idx != hp.front; ++idx)
        printf("(%d %d) ", hp.array[idx].id, hp.array[idx].dist);
    printf("\n");
}

void readInput(Graph *G, int *nChambers)
{
    /* read the first line and create the graph */
    int nTunnels;
    scanf("%d %d", nChambers, &nTunnels);
    *G = createGraph(*nChambers);

    /* read the chambers with a reverse button */
    int readNum = 0;
    scanf("%d", &readNum);
    while (readNum != -1)
    {
        addReverseButton(*G, *nChambers, readNum);
        scanf("%d", &readNum);
    }

    /* read the tunnels */
    int parent, child, weight;
    for (int idx = 0; idx != nTunnels; ++idx)
    {
        scanf("%d %d %d", &parent, &child, &weight);
        addChild(*G, *nChambers, parent, child, weight);
    }
}

void dijkstra(Graph G, int nChambers)
{
    Heap hp = createHeap(2 * nChambers);

    /* initialize the distances to infinity (except for node 1)*/
    G[1].dist = 0;
    addHeap(&hp, 1, 0);
    for (int idx = 2; idx <= 2 * nChambers; ++idx)
    {
        G[idx].dist = INT_MAX;
        addHeap(&hp, idx, INT_MAX);
    }

    printf("Initial Heap:\n");
    printHeap(hp);
    printf("\n");

    while (!isEmptyHeap(hp))
    {
        /* remove the node with the minimum distance in the heap*/
        HeapNode min = removeMin(&hp);
        printf("\n\n\n\n\nLooking at node %d:\n", min.id);

        /* recompute the distances of the children of min */
        for (ListPtr ptr = G[min.id].children; ptr != NULL; ptr = ptr->next)
        {
            printf("Looking at child %d:\n", ptr->node);
            /* compute the new distance and compare it to the previous one */
            int newDist = min.dist + ptr->weight;
            int oldDist = G[ptr->node].dist;
            int posNode = hp.position[ptr->node];
            printf("newDist = %d, posNode = %d, oldDist = %d\n", newDist, posNode, oldDist);
            if (newDist < oldDist)
            {
                printf("Updating old distance\n");
                /* update the graph node */
                G[ptr->node].parent = min.id;
                G[ptr->node].dist = newDist;

                /* update the heap */
                hp.array[posNode].dist = newDist;
                upHeap(&hp, ptr->node);
            }
            printf("\nHeap:\n");
            printHeap(hp);
        }
    }

    freeHeap(hp);
}



int main()
{
    Graph G;
    int nChambers;
    readInput(&G, &nChambers);

    dijkstra(G, nChambers);
    
    return 0;
}
