#include "solver.h"

int main()
{
    /* read the input according to themis format */
    Graph G = readInput();

    /* print the shortest path from node 1 to n */
    printSolution(G);
}