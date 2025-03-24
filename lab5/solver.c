#include "solver.h"
#include <stdio.h>

Graph readInput()
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

    return G;
}

void calcSolution(Graph G)
{

}

void printSolution(Graph G)
{
    calcSolution(G);

}