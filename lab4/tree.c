#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* create a file on a given folder */
Tree createFile(Tree tr, Name filename, InodeType type)
{
    /* allocate space for 1 more file */
    tr->in.folder = realloc(tr->in.folder, tr->size + 1);

    /* create the file */
    tr->in.folder[tr->size] = createTree(tr, filename, type);

    /* update the size of the folder*/
    ++(tr->size);

    /* return the file */
    return tr->in.folder[tr->size];
}

// create a new path with length components
Path createPath(int length)
{
    Path pt;
    pt.component = malloc(length * sizeof(Name));
    pt.length = length;
    return pt;
}

/* create a tree */
Tree createTree(Tree parent, Name name, InodeType inT)
{
    Tree tr = malloc(sizeof(TreeNode));

    tr->parent = parent;
    strcpy(tr->name, name);
    tr->inT = inT;
    tr->size = 0;

    return tr;
}

Tree findNode(Tree tr, Name nodeName)
{
    /* navigate the files in the tr folder */
    for (int i = 0; i != tr->size; ++i)
    {
        Tree child = tr->in.folder[i];

        /* compare the found and original name */
        if (child->inT == File && strcmp(child->name, nodeName) == 0)
            return child;
    }

    /* if the name is not found, tr remains the same */
    return tr;
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

// free a path
void freePath(Path pt)
{
    free(pt.component);
}

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

void printContent(Tree tr, Path pt)
{
    /* visit all childs of tr */
    for(int i = 0; i != tr->size; ++i)
    {
        Tree child = tr->in.folder[i];

        /* create and print the new path for each child of tr */
        Path childPath = createPath(pt.length + 1);
        for(int j = 0; j != pt.length; ++j)
        {
            strcpy(childPath.component[j], pt.component[j]);
            printf("%s/", pt.component[j]);
        }
        strcpy(childPath.component[pt.length], child->name);
        printf("%s\n", child->name);

        /* if the child is a folder, apply recursion */
        if (child->inT == Folder)
            printContent(child, childPath);

        /* free the child path */
        freePath(childPath);
    }
}