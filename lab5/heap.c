#include "heap.h"
#include <limits.h>

void addHeap(Heap *hp, int node, int dist)
{
    /* double the size if needed */
    if (hp->front == hp->size)
    {
        hp->size *= 2;
        hp->array = realloc(hp->array, hp->size * sizeof(HeapNode));
        hp->position = realloc(hp->position, hp->size * sizeof(int));
    }

    /* add the node to the front of the heap */
    hp->array[hp->front].id = node;
    hp->array[hp->front].dist = dist;
    hp->position[node] = hp->front;
    ++(hp->front);

    /* move it to the right position */
    upHeap(hp, node);
}

Heap createHeap(int size)
{
    Heap hp;
    hp.array = malloc((1 + size) * sizeof(HeapNode));
    hp.position = malloc((1 + size) * sizeof(int));
    hp.front = 1;
    hp.size  = 1 + size;
    return hp;
}

int isEmptyHeap(Heap hp)
{
    return (hp.front == 1);
}

/* should only be called when the heap is not empty */
HeapNode removeMin(Heap *hp)
{
    /* store the node with minimum distance */
    HeapNode min = hp->array[1];

    /* move the last node to the root */
    --(hp->front);
    hp->array[1] = hp->array[hp->front];
    hp->position[hp->array[1].id] = 1;

    /* restore the order of the heap if it's not empty */
    if (!isEmptyHeap(*hp))
        downHeap(hp, 1);

    return min;
}

void upHeap(Heap *hp, int node)
{
    /* check if node is the root */
    int positionNode = hp->position[node];
    if (positionNode != 1)
    {
        /* obtain the parent node and it's position in the heap array */
        int positionParent = positionNode / 2;
        int parent = hp->array[positionParent].id;

        /* compare the node with it's parent */
        if (hp->array[positionNode].dist < hp->array[positionParent].dist)
        {
            /* swap the nodes at positionNode and positionParent */
            HeapNode auxNode = hp->array[positionNode];
            hp->array[positionNode] = hp->array[positionParent];
            hp->array[positionParent] = auxNode;

            /* swap node's and parent's position index */
            hp->position[node] = positionParent;
            hp->position[parent] = positionNode;

            /* call upHead recursively */
            upHeap(hp, node);
        }
    }
}

void downHeap(Heap *hp, int node)
{
    
}