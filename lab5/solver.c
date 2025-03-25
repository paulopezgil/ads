#include "solver.h"
#include "heap.h"
#include <stdio.h>
#include <limits.h>

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

        /* if min.dist == INT_MAX, the remaining nodes are not reachable */
        if (min.dist == INT_MAX)
            break;

        /* recompute the distances of the children of min */
        for (ListPtr ptr = G[min.id].children; ptr != NULL; ptr = ptr->next)
        {
            /* compute the new distance and compare it to the previous one */
            int newDist = min.dist + ptr->weight;
            int oldDist = G[ptr->node].dist;
            int posNode = hp.position[ptr->node];
            if (newDist < oldDist)
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

void printParents(Graph G, int currentNode, int nChambers)
{
    int parent = G[currentNode].parent;
    int pressedReverse = parent % nChambers == currentNode % nChambers;

    /* if the parent is the same node, then a reverse button was pressed */
    if (pressedReverse)
        parent = G[parent].parent;

    /* first print the grandparents */
    if (currentNode % nChambers != 1)
        printParents(G, parent, nChambers);

    /* Then print the parent */
    printf("%d", currentNode % nChambers);

    /* if the reverse button was pressed, print a 'R' */
    if (pressedReverse)
        printf(" R");
    
    printf("\n");
}

void printSolution(Graph G, int nChambers)
{
    /* run dijkstra to find the shortest path from node 1 to the others */
    dijkstra(G, nChambers);

    /* first, we handle the case where the distance is equal between node n and 2n */
    int lastNode;
    if (G[nChambers].dist == G[2 * nChambers].dist)
    {
        /* If both distances are infinity, no path was found from node 1 to n */
        if (G[nChambers].dist == INT_MAX)
        {
            printf("IMPOSSIBLE");
            return;
        }

        /* Otherwise, node n has a reverse button. */
        /* We need to find the graph in which it was found (the normal or the reversed). */
        if (G[nChambers].parent == 2 * nChambers)
            lastNode = 2 * nChambers;
        else
            lastNode = nChambers;
    }
    else
    {
        /* Otherwise, check if it's better to go from 1 to n or to 2n */
        if (G[nChambers].dist < G[2 * nChambers].dist)
            lastNode = nChambers;
        else
            lastNode = 2 * nChambers;
    }

    /* print the distance from node 1 to n */
    printf("%d\n", G[lastNode].dist);

    /* print the path */
    printParents(G, G[lastNode].parent, nChambers);
    printf("%d", lastNode);
}