#include "solver.h"

int main()
{
    /* read the input according to themis format */
    Graph G = readInput();

    /* Compute the shortest path from node 1 to n */
    SolGraph sol = calcSolution(G);

    /* print the path */
    printSolution(sol);
}