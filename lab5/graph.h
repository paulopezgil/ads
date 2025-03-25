#ifndef GRAPH_H
#define GRAPH_H

typedef struct List *ListPtr;
typedef struct List {
    int node;
    int weight;
    ListPtr next;
} List;

typedef struct Node *Graph;
typedef struct Node {
    ListPtr children;
    int parent;
    int dist;
} Node;

Graph createGraph(int nChambers);
void addChild(Graph G, int size, int parent, int child, int weight);
void addReverseButton(Graph G, int size, int node);

#endif