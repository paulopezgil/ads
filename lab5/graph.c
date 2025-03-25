#include "graph.h"
#include <stdlib.h>
#include <limits.h>

ListPtr createList(int node, int weight)
{
    ListPtr ptr = malloc(sizeof(List));
    ptr->node = node;
    ptr->weight = weight;
    ptr->next = NULL;
    return ptr;
}

void addChild(Graph G, int size, int parent, int child, int weight)
{
    /* create the first child if it doesn't exist */
    if (G[parent].children == NULL)
    {
        G[parent].children = createList(child, weight);
        G[parent].lastChild = G[parent].children;
    }
    else    /* add child to parent's children list */
    {
        G[parent].lastChild->next = createList(child, weight);
        G[parent].lastChild = G[parent].lastChild->next;
    }

    /* create the first child in the reversed graph if it doesn't exist */
    if (G[child + size].children == NULL)
    {
        G[child + size].children = createList(parent + size, weight);
        G[child + size].lastChild = G[child + size].children;
    }
    else    /* add child to parent's children list */
    {
        G[child + size].lastChild->next = createList(parent + size, weight);
        G[child + size].lastChild = G[child + size].lastChild->next;
    }
}

void addReverseButton(Graph G, int size, int node)
{
    /* add an edge with weight 0 between node and node + size (in the reversed graph) */
    G[node].children = createList(node + size, 0);
    G[node].lastChild = G[node].children;

    /* add an edge with weight 0 between node + size (in the reversed graph) and node */
    G[node + size].children = createList(node, 0);
    G[node + size].lastChild = G[node + size].children;
}

Graph createGraph(int size)
{
    /* added an extra space because the first node is 1 and not 0 */
    /* nodes from 1 to size are the nodes from the normal graph */
    /* The ptr nodes are from the graph with the paths in reverse order */
    return calloc(2 * size + 1, sizeof(Node));
}

void freeList(ListPtr ptr)
{
    if (ptr == NULL)
        return;

    freeList(ptr->next);
    free(ptr);
}

void freeGraph(Graph G, int size)
{
    /* first free the children lists */
    for (int node = 0; node != 2 * size + 1; ++node)
        freeList(G[node].children);

    /* then free the graph */
    free(G);
}