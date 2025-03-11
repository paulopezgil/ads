#include "tree.ih"

Trie createTrie()
{
    /* allocate memory */
    Trie tr = malloc(sizeof(TrieNode));

    /* set default values */
    tr->file = NULL;
    for (int pos = 0; pos != MAX_SIZE; ++pos)
        tr->child[pos] = NULL;

    /* return the trie */
    return tr;
}

void insertTrie(Trie tr, Tree file)
{
    for (int pos = 0; pos != MAX_SIZE; ++pos)
    {
        /* if null-terminator was read, we arrived to the correct node */
        if (file->name[pos] == '\0')
        {
            tr->file = file;
            return;
        }

        /* create the child if it doesn't exist */
        if (tr->child[(int)file->name[pos]] == NULL)
            tr->child[(int)file->name[pos]] = createTrie();

        /* go to the next letter */
        tr = tr->child[(int)file->name[pos]];
    }
}

Tree searchTrie(Trie tr, Name name)
{
    /* search the name in the trie */
    for (int pos = 0; pos != MAX_SIZE; ++pos)
    {
        /* if tr is NULL, there is no child called name */
        if (tr == NULL)
            return NULL;

        /* if null-terminator is read, the name was found */
        if (name[pos] == '\0')
            return tr->file;

        /* go to the next letter */
        tr = tr->child[(int)name[pos]];
    }

    /* at this point, the name wasn't found */
    return NULL;
}

void freeTrie(Trie root)
{
    /* base case: NULL pointer */
    if (root == NULL)
        return;

    /* recursively free the nodes */
    for (int ch = 0; ch != MAX_CHAR; ++ch)
        freeTrie(root->child[(int)ch]);
    free(root);
}