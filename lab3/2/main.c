#include "trie.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m;       /* the number of subnets and ips */
    Subnet *sn;     /* an array of subnets */
    IpAddress *ip;  /* an array of ips */

    /* Read from the standard input*/
    readInput(&n, &m, &sn, &ip);

    /* Create a search trie from the subnet array */
    Trie tr = createTrie(sn, n);

    /* For each requested IP adress, print its longest prefix matching id */
    for (int pos = 0; pos != m; ++pos)
        printf("%d\n", matchingId(ip[pos], tr));

    /* free the arrays */
    free(sn);
    free(ip);
}