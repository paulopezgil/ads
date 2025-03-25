#include "heap.h"
#include <stdlib.h>

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
    int posNode = hp->position[node];
    if (posNode != 1)
    {
        /* obtain the parent node and it's position in the heap array */
        int posParent = posNode / 2;
        int parent = hp->array[posParent].id;

        /* compare the node with it's parent */
        if (hp->array[posNode].dist < hp->array[posParent].dist)
        {
            /* swap the nodes at posNode and posParent */
            HeapNode auxNode = hp->array[posNode];
            hp->array[posNode] = hp->array[posParent];
            hp->array[posParent] = auxNode;

            /* swap node's and parent's position index */
            hp->position[node] = posParent;
            hp->position[parent] = posNode;

            /* call upHead recursively */
            upHeap(hp, node);
        }
    }
}

void downHeap(Heap *hp, int node)
{
    int posNode = hp->position[node];
    int posLeftChild = 2 * posNode;
    int posRightChild = 2 * posNode + 1;

    /* find the smallest dist between the node and it's childs */
    int posSmallest = posNode;
    if (posLeftChild < hp->front &&
        hp->array[posLeftChild].dist < hp->array[posSmallest].dist)
        posSmallest = posLeftChild;
    if (posLeftChild < hp->front &&
        hp->array[posRightChild].dist < hp->array[posSmallest].dist)
        posSmallest = posRightChild;
    
    /* update the heap with the found smallest child */
    if (posSmallest != posNode)
    {            
        /* swap the nodes at posSmallest and posNode */
        HeapNode auxNode = hp->array[posNode];
        hp->array[posNode] = hp->array[posSmallest];
        hp->array[posSmallest] = auxNode;

        /* swap node's and smallest's child position index */
        hp->position[hp->array[posNode].id] = posSmallest;
        hp->position[hp->array[posSmallest].id] = posNode;

        /* recursively update the node's position */
        downHeap(hp, node);
    }
}

void freeHeap(Heap hp)
{
    free(hp.array);
    free(hp.position);
}