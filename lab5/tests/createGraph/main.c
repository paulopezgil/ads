#include "../../graph.h"
#include <stdio.h>

int main()
{
    /* test createGraph */
    Graph G = createGraph(3);
    for(int idx = 1; idx <= 6; ++idx)
    {
        printf("Node %d:\n", idx);
        printf("ListPtr = %p ", (void *)G[idx].children);
        printf("nChilds = %d ", G[idx].nChilds);
        printf("parent = %d ", G[idx].parent);
        printf("pdistance = %d\n", G[idx].pdistance);
    }
}