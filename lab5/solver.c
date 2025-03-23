Graph readInput()
{
    int nChambers, nTunnels;

    /* read the first line and create the graph */
    scanf("%d %d", &nChambers, &nTunnels);
    Graph G = createGraph(nChambers);

    /* read the chambers with a reverse button */
    int readNum = 1;
    while (readNum != -1)
    {
        scanf("%d", &readNum);
        G[readNum].reversible = 1;
    }

    /* read the tunnels */
    int parent, child, weight;
    for (int idx = 0; idx != nTunnels; ++idx)
    {
        scanf("%d %d %d", &parent, &child, &weight);
        addEdge(G, parent, child, weight);
    }

    return G;
}

SolGraph calcSolution(Graph G)
{

}

void printSolution(SolGraph G)
{


}