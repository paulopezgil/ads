#include <stdio.h>
#include <stdlib.h>

#include "lpm.h"

void readInput(int *n, int *m, Subnet **sn, IpAddress **ip)
{
    /* read the number of lines and reserve memory for the subnets */
    scanf("%d", n);
    *sn = (Subnet *)calloc(*n, sizeof(Subnet));

    /* read each ip, mask and id */
    for (int line = 0; line != *n; ++line)
        scanf("%d.%d.%d.%d/%d %d", (*sn + line)->ip, (*sn + line)->ip + 1, 
                                   (*sn + line)->ip + 2, (*sn + line)->ip + 3, 
                                   &((*sn + line)->mask), &((*sn + line)->id));

    /* read the 2nd number of lines and reserve memory for the ips */
    scanf("%d", m);
    *ip = (IpAddress *)calloc(*m, sizeof(IpAddress));

    /* read each ip */
    for (int line = 0; line != *m; ++line)
        scanf("%d.%d.%d.%d", (*ip)[line], (*ip)[line] + 1,
                             (*ip)[line] + 2, (*ip)[line] + 3);
}

int transformIp(IpAddress ip, int mask)
{
    int result = 0;

    if (mask == 0)
        return 0;

    /* transform the IpAdress into an int */
    result |= (ip[0] << 24);
    result |= (ip[1] << 16);
    result |= (ip[2] << 8);
    result |= ip[3];

    /* All the bits smaller than mask are 0 */
    return result & (0xFFFFFFFF << (32 - mask));
}