#ifndef SOLVER_H
#define SOLVER_H
#include "graph.h"

Graph readInput();
SolGraph calcSolution(Graph G);
void printSolution(Graph G);

#endif