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
    return tr->in.folder[tr->size - 1];
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
void freeTree(Tree tr)
{
    if (tr == NULL)
        return;

    // free a file
    if (tr->inT == File)
        free(tr);

    // recursively free a folder
    for (int i = 0; i != tr->size; ++i)
        freeTree(tr->in.folder[i]);
    free(tr);
}

void deleteNode(Tree tr)
{
    Tree parent = tr->parent;

    /* case where tr is the root */
    if (parent == tr)
    {
        freeTree(tr);
        return;
    }

    /* find the index tr in it's parent's child array */
    int idx;
    for (idx = 0; idx != parent->size; ++idx)
        if (parent->in.folder[idx] == tr)
            break;

    /* remove tr from the parent's child array */
    --(parent->size);
    for (int chd = idx; chd != parent->size; ++chd)
        parent->in.folder[chd] = parent->in.folder[chd + 1];

    /* free tr */
    freeTree(tr);
}

void swapContent(Tree tr1, Tree tr2)
{
    Tree aux = tr1;

    /* swap the Inode Type */
    tr1->inT = tr2->inT;
    tr2->inT = aux->inT;

    /* swap the content */
    tr1->in = tr2->in;
    tr2->in = aux->in;

    /* swap the sizes */
    tr1->size = tr2->size;
    tr2->size = aux->size;
}