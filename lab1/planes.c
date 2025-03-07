#include <stdio.h>

#include "LibStack.h"
#include "LibQueue.h"

#define RUNWAYSIZE 7
#define HANGARSIZE 5

int main()
{
    /* read the number of planes incoming */
    int nPlanes;
    scanf("%d", &nPlanes);

    /* Initialize the necessary data structures */
    /* the queue doubles its memory when full, the stack doesn't */
    Stack hangar = newStack(HANGARSIZE);
    Queue runway = newQueue(RUNWAYSIZE + 1);

    /* loop for each arriving plane */
    int planeId;
    char needsRepair[4];
    for (int i = 0; i != nPlanes; ++i)
    {
        /* scan the plane id and the word for needed repair */ 
        scanf("%d %s", &planeId, needsRepair);

        /* If a plane needs repairs, move it to the hangar */
        if (needsRepair[0] == 'y')
        {
            push(planeId, &hangar);

            /* Check if the hangar is full */
            if (hangar.top == HANGARSIZE)
            {
                /* All planes from the runway depart */
                while (!isEmptyQueue(runway))
                    printf("%d\n", dequeue(&runway));

                /* Move the planes from the hangar to the runway */
                while (!isEmptyStack(hangar))
                    enqueue(pop(&hangar), &runway);
            }
        }

        /* If it doesn't need repairs, move it to the runway */
        else
        {
            enqueue(planeId, &runway);

            /* If the runway is full, all planes depart*/
            if (runway.back == RUNWAYSIZE)
                while (!isEmptyQueue(runway))
                    printf("%d\n", dequeue(&runway));
        }
    }

    /* At the end of the day, clear the runway */
    while (!isEmptyQueue(runway))
        printf("%d\n", dequeue(&runway));

    /* Move the planes from the hangar to the runway */
    while (!isEmptyStack(hangar))
        enqueue(pop(&hangar), &runway);

    /* Clear the runway again */
    while (!isEmptyQueue(runway))
        printf("%d\n", dequeue(&runway));

    /* Free allocated memory and return */
    free(hangar.array);
    free(runway.array);
    return 0;
}
