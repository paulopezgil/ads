#include "graph.h"
#include <stdlib.h>
#include <limits.h>

void addList(ListPtr *ptr, int node, int weight)
{
    /* traverse the list */
    ListPtr previous = *ptr, next = *ptr;
    while (next != NULL)
    {
        previous = next;
        next = previous->next;
    }

    /* create the next list node */
    next = malloc(sizeof(List));
    next->node = node;
    next->weight = weight;
    next->next = NULL;

    /* add it after the previous list node */
    if (previous != NULL)
        previous->next = next;

    /* if the list is empty set the next node as the first */
    else
        *ptr = next;
}

void addChild(Graph G, int size, int parent, int child, int weight)
{
    /* add child to parent's children list */
    addList(&(G[parent].children), child, weight);

    /* add parent to child's children list in the reversed graph */
    addList(&(G[child + size].children), parent + size, weight);
}

void addReverseButton(Graph G, int size, int node)
{
    /* add a tunnel with weight 0 between the same node in the 2 graphs */
    addList(&(G[node].children), node + size, 0);
    addList(&(G[node + size].children), node, 0);
}

Graph createGraph(int size)
{
    /* added an extra space because the first node is 1 and not 0 */
    /* nodes from 1 to size are the nodes from the normal graph */
    /* The next nodes are from the graph with the paths in reverse order */
    Graph G = calloc(2 * size + 1, sizeof(Node));

    /* initialize all distances to infinity except for node 1 */
    for (int node = 2; node <= 2 * size; ++node)
        G[node].pdistance = INT_MAX;

    return G;
}