#include "../../solver.h"
#include "../../graph.h"
#include <stdio.h>
#include <limits.h>

void printGraph(Graph G, int nChambers) {
    printf("\n=== NORMAL GRAPH ===\n");
    
    // Print headers with proper alignment
    printf("%-8s %-12s %-8s\n", "Node", "Distance", "Parent");
    printf("------------------------\n");
    
    // Print regular nodes data in rows
    for (int i = 1; i <= nChambers; i++) {
        printf("%-8d ", i);
        
        // Print distance
        if (G[i].dist == INT_MAX) {
            printf("%-12s ", "∞");
        } else {
            printf("%-12d ", G[i].dist);
        }
        
        // Print parent
        if (G[i].parent == 0) {
            printf("%-8s", "-");
        } else {
            printf("%-8d", G[i].parent);
        }
        printf("\n");
    }
    
    printf("\n=== REVERSE NODES ===\n");
    printf("%-8s %-12s %-8s\n", "Node", "Distance", "Parent");
    printf("------------------------\n");
    
    // Print reverse nodes data in rows
    for (int i = 1; i <= nChambers; i++) {
        int reverseNode = i + nChambers;
        printf("%-8d ", reverseNode);
        
        // Print distance
        if (G[reverseNode].dist == INT_MAX) {
            printf("%-12s ", "∞");
        } else {
            printf("%-12d ", G[reverseNode].dist);
        }
        
        // Print parent
        if (G[reverseNode].parent == 0) {
            printf("%-12s", "-");
        } else {
            printf("%-12d", G[reverseNode].parent);
        }
        printf("\n");
    }
}

void dijkstra(Graph G, int nChambers);

int main()
{
    Graph G;
    int nChambers;
    readInput(&G, &nChambers);

    dijkstra(G, nChambers);

    printGraph(G, nChambers);
}