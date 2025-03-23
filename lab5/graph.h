#ifndef GRAPH_H
#define GRAPH_H

typedef struct Node *Graph;

typedef struct Edge
{
    int id;
    int weight;
};

typedef struct EdgeList
{
    Edge *vertex;
    int size;
    int capacity;
}

typedef struct Node {
    EdgeList parents;
    EdgeList children;
    int reversible;
} Node;

typedef struct SolNode *SolGraph;

typedef struct SolNode {
    int dist;
    SolGraph parent;
    int reversed;
};

Graph createGraph(int nChambers);
void addEdge(Graph G, int parent, int child, int weight);

#endif