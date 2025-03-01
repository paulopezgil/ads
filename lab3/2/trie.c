#include "trie.h"
#include <stdlib.h>

TrieNode *createNode()
{
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));

    /* initialize the Node with the default */
    node->id = -1;
    node->child[0] = NULL;
    node->child[1] = NULL;

    return node;
}

void insertSubnet(Trie node, int ip, int mask, int id)
{
    /* insert the ip into the trie */
    if (mask == 0)
        node->id = id;
    else
    {
        /* Extract the bit at position mask */
        int bit = (ip >> mask) & 1;

        /* create the child if it doesn't exist */
        if (node->child[bit] == NULL)
            node->child[bit] = createNode();

        /* go to the next node */
        insertSubnet(node->child[bit], ip, mask - 1, id);
    }
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
