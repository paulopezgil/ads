#include "solver.h"

int main()
{
    /* read the input according to themis format */
    Graph G;
    int nChambers;
    readInput(&G, &nChambers);

    /* print the shortest path from node 1 to n */
    printSolution(G, nChambers);

    /* free the allocated memory */
    freeGraph(G, nChambers);
}