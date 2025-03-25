#include "solver.h"
#include <stdio.h>

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

    while (!isEmptyHeap(hp))
    {
        /* remove the node with the minimum distance in the heap*/
        HeapNode min = removeMin(&hp);

        /* recompute the distances of the children of min */
        for (ListPtr ptr = G[min.id].children; ptr != NULL; ptr = ptr->next)
        {
            /* compute the new distance and compare it to the previous one */
            int newDist = min.dist + ptr->weight;
            int posNode = hp.position[ptr->node];
            if (newDist < hp.array[posNode].dist)
            {
                /* update the graph node */
                G[ptr->node].parent = min.id;
                G[ptr->node].dist = newDist;

                /* update the heap */
                hp.array[posNode].dist = newDist;
                upHeap(&hp, ptr->node);
            }
        }
    }

    freeHeap(hp);
}

void printSolution(Graph G, int nChambers)
{
    dijkstra(G, nChambers);

}