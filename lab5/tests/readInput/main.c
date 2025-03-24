#include <stdio.h>

void readInput()
{
    /* read the first line and create the graph */
    int nChambers, nTunnels;
    scanf("%d %d", &nChambers, &nTunnels);
    /* Graph G = createGraph(nChambers); */
    printf("Created Graph with %d chambers\n", nChambers);

    /* read the chambers with a reverse button */
    int readNum = 0;
    scanf("%d", &readNum);
    while (readNum != -1)
    {
        printf("Chamber %d is reversible\n", readNum);
        scanf("%d", &readNum);
    }

    /* read the tunnels */
    int parent, child, weight;
    for (int idx = 0; idx != nTunnels; ++idx)
    {
        scanf("%d %d %d", &parent, &child, &weight);
        printf("Adding edge from %d to %d with weight %d\n", parent, child, weight);
    }
}

int main()
{
    readInput();
}