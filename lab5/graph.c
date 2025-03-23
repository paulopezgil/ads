#include "graph.h"

EdgeList createEdgeList()
{
    EdgeList list;

    /* set default values */
    list.size = 0;
    list.capacity = 1;
    list.vertex = malloc(sizeof(Edge));

    return list;
}

Graph createGraph(int nChambers)
{
    /* added an extra space because the first node is 1 and not 0 */
    Graph G = malloc((nChambers + 1) * sizeof(Node));

    /* initialize the EdgeLists */
    G->parents = createEdgeList();
    G->children = createEdgeList();
}

void addVertex(EdgeList *list, int id, int weight)
{
    /* double the capacity if necessary */
    if (list->size == list->capacity)
    {
        list->capacity *= 2;
        list->vertex = realloc(list->vertex, list->capacity);
    }

    /* add the vertex to the list */
    list->vertex[list->size].id = id;
    list->vertex[list->size].weight = weight;
    ++(list->size);
}

void addEdge(Graph G, int parent, int child, int weight)
{
    /* add the child to parent's children list */
    addVertex(&(G[parent].children), child, weight);

    /* add parent to child's parent list */
    addVertex(&(G[child].parents), parent, weight);
}