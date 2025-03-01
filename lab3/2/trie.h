#ifndef TRIE_H
#define TRIE_H

#include "lpm.h"

typedef struct TrieNode *Trie;

typedef struct TrieNode {
    int id;
    Trie child[2];
} TrieNode;

Trie createTrie(Subnet *sn, int n);
int matchingId(IpAddress ip, Trie tr);
void freeTrie(Trie root);


#endif