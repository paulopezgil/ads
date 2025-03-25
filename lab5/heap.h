#ifndef HEAP_H
#define HEAP_H
#include "graph.h"

typedef struct HeapNode {
    int id;
    int dist;
} HeapNode;


typedef struct Heap {
    HeapNode *array;
    int *position;     /* positions of the node Ids in the HeapNode array */
    int front;
    int size;
} Heap;

void addHeap(Heap *hp, int node, int dist);
Heap createHeap(int size);
int isEmptyHeap(Heap hp);
HeapNode removeMin(Heap *hp);
void downHeap(Heap *hp, int node);
void upHeap(Heap *hp, int node);
void freeHeap(Heap hp);

#endif