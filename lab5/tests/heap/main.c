#include "../../heap.h"
#include <stdio.h>

void printHeap(Heap hp)
{
    printf("Heap size: %d\n", hp.size);
    printf("Heap front: %d\n", hp.front);
    printf("Position array: ");
    for (int idx = 0; idx != hp.size; ++idx)
        printf("%d ", hp.position[idx]);
    printf("\nHeap array: ");
    for(int idx = 1; idx != hp.front; ++idx)
        printf("(%d %d) ", hp.array[idx].id, hp.array[idx].dist);
    printf("\n");
}


int main()
{
    /* test createHeap */
    printf("Testing createHeap:\n");
    Heap hp = createHeap(3);
    printf("\n");

    /* test isEmptyHeap */
    printf("Testing isEmptyHeap:\n");
    if (isEmptyHeap(hp))
        printf("The heap is empty\n");
    printf("\n");
    
    /* test addHeap */
    printf("Testing addHeap:\n");
    addHeap(&hp, 1, 10);
    addHeap(&hp, 2, 20);
    addHeap(&hp, 3, 30);
    addHeap(&hp, 4, 40);
    printHeap(hp);
    printf("\n");

    /* test removeMin */
    printf("Testing removeMin:\n");
    HeapNode min = removeMin(&hp);
    printf("Removed (%d %d) from the heap\n", min.id, min.dist);
    printHeap(hp);
    printf("\n");

    /* test upHeap - simulating decreaseKey */
    printf("Testing upHeap (decreaseKey):\n");
    addHeap(&hp, 1, 10);
    printHeap(hp);
    
    // Update node 3's distance to be smaller (simulate decreaseKey)
    int nodeToUpdate = 3;
    int newDist = 5;
    int pos = hp.position[nodeToUpdate];
    hp.array[pos].dist = newDist;
    printf("Changed node %d's distance to %d\n", nodeToUpdate, newDist);
    
    // Call upHeap to restore heap property
    upHeap(&hp, nodeToUpdate);
    printf("After upHeap:\n");
    printHeap(hp);
    printf("\n");

    /* test downHeap more thoroughly */
    printf("Testing downHeap more thoroughly:\n");
    // First, create a new heap with a specific structure
    freeHeap(hp);
    hp = createHeap(10);
    
    // Add elements in a specific order
    addHeap(&hp, 1, 100); // Root element
    addHeap(&hp, 2, 20);
    addHeap(&hp, 3, 30);
    addHeap(&hp, 4, 40);
    addHeap(&hp, 5, 50);
    printf("Initial heap:\n");
    printHeap(hp);
    
    // Manually modify the root to have a large value (to force downHeap)
    hp.array[1].dist = 500;
    printf("After modifying root value to 500:\n");
    printHeap(hp);
    
    // Call downHeap on the root
    downHeap(&hp, hp.array[1].id);
    printf("After downHeap:\n");
    printHeap(hp);
    printf("\n");

    /* test removing multiple elements */
    printf("Testing multiple removeMin operations:\n");
    min = removeMin(&hp);
    printf("Removed (%d %d) from the heap\n", min.id, min.dist);
    printHeap(hp);
    
    min = removeMin(&hp);
    printf("Removed (%d %d) from the heap\n", min.id, min.dist);
    printHeap(hp);
    
    min = removeMin(&hp);
    printf("Removed (%d %d) from the heap\n", min.id, min.dist);
    printHeap(hp);
    printf("\n");

    /* test freeHeap */
    printf("Testing freeHeap:\n");
    freeHeap(hp);
    printf("Heap memory freed\n");
    printf("\n");

    return 0;
}