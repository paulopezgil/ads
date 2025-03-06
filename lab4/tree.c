#include "tree.h"
#include <stdlib.h>

// create a tree
Tree createTree();

// free a tree
void freeTree(Tree root)
{
    if (root == NULL)
        return;

    // free a file
    if (root->inT == File)
        free(root);

    // recursively free a folder
    for (int i = 0; i != root->size; ++i)
        freeTree(root->in.folder[i]);
    free(root);
}

// find the root of a tree
Tree findRoot(Tree tr)
{
    // case tr is the root
    if (tr->parent == NULL)
        return tr;

    // case tr is a child
    return findRoot(tr->parent);
}

// create a new path with length components
Path createPath(int length)
{
    Path pt;
    pt.component = malloc(length * sizeof(Name));
    pt.length = length;
    return pt;
}

// free a path
void freePath(Path pt)
{
    free(pt.component);
}