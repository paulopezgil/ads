#include "trie.h"
#include <stdlib.h>

TrieNode *createNode()
{
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));

    /* initialize the Node with default values */
    node->id = -1;
    node->child[0] = NULL;
    node->child[1] = NULL;

    return node;
}

void insertSubnet(Trie node, int ip, int mask, int id)
{
    /* reach the node where id is stored */
    /* bits go from 0 to 31 */
    for (int bit = 31; bit != 31 - mask; --bit)
    {
        /* Obtain the digit at the corresponding bit */
        int digit = (ip >> bit) & 1;

        /* create the child if it doesn't exist */
        if (node->child[digit] == NULL)
            node->child[digit] = createNode();

        /* go to the next node */
        node = node->child[digit];
    }

    /* store the id */
    node->id = id;
}

Trie createTrie(Subnet *sn, int n)
{
    /* the root will be 0.0.0.0/0 (if found) */
    Trie root = createNode();

    /* insert each subnet into the trie */
    for (int pos = 0; pos != n; ++pos)
        insertSubnet(root, transformIp(sn[pos].ip, sn[pos].mask),
                     sn[pos].mask, sn[pos].id);

    /* return the created trie */
    return root;
}

int matchingId(IpAddress ip, Trie tr)
{
    int lpmId = -1;
    int intIp = transformIp(ip, 32);

    /* visit the nodes following the binary representation of intIp */
    for (int bit = 31; tr != NULL; --bit)
    {
        /* if tr.id != -1 then a subnet matches the ip */
        if (tr->id != -1)
            lpmId = tr->id;

        /* visit the next child */
        tr = tr->child[(intIp >> bit) & 1];
    }

    return lpmId;
}

void freeTrie(Trie root)
{
    /* base case: NULL pointer */
    if (root == NULL)
        return;

    /* recursively free the nodes */
    freeTrie(root->child[0]);
    freeTrie(root->child[1]);
    free(root);
}