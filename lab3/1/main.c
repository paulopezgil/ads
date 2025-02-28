#include "lpm.h"

int main()
{
    int n, m;       /* the number of subnets and ips*/
    Subnet *sn;     /* an array of subnets */
    IpAddress *ip;  /* an array of ips*/

    /* Read from the standard input*/
    readInput(&n, &m, &sn, &ip);

    /* For each requested IP adress, print its longest prefix matching id */
    for (int pos = 0; pos != m; ++pos)
        printf("%d\n", matchingId(ip[pos]), sn, n);

    /* free the arrays of subnets and ips */
    free(sn);
    free(ip);
}