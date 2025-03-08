#include "tree.ih"

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
    /* case / */
    if (strcmp(nodeName, "/") == 0)
        return findRoot(tr);

    /* case . */
    if (strcmp(nodeName, ".") == 0)
        return tr;

    /* case .. */
    if (strcmp(nodeName, "..") == 0)
        return tr->parent;

    /* navigate the files in the tr folder */
    Tree child;
    for (int i = 0; i != tr->size; ++i)
    {
        child = tr->in.folder[i];

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