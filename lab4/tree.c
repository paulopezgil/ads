#include "tree.ih"

/* create a copy of a Tree at a given Tree of the same type */
void copyTree(Tree origin, Tree destination)
{
    /* override destination if origin is a file */
    if (origin->in->type == File)
    {
        strcpy(destination->in->content.file, origin->in->content.file);
        return;
    }

    /* if origin is a folder, copy it's contents to destination */
    Tree newDest;
    for(int idx = 0; idx != origin->in->size; ++idx)
    {
        newDest = createFile(destination,
                             origin->in->content.folder[idx]->name,
                             origin->in->content.folder[idx]->in->type);
        copyTree(origin->in->content.folder[idx], newDest);
    }
}

/* create a node on a given folder */
Tree createFile(Tree tr, Name name, InodeType type)
{
    /* allocate space for 1 more node */
    tr->in->content.folder = realloc(tr->in->content.folder, tr->in->size + 1);
    
    /* create the node */
    tr->in->content.folder[tr->in->size] = createTree(tr, name, type);

    /* update the size of the folder*/
    ++(tr->in->size);

    /* return the tree node */
    return tr->in->content.folder[tr->in->size - 1];
}

/* create a tree */
Tree createTree(Tree parent, Name name, InodeType type)
{
    /* create the TreeNode */
    Tree tr = malloc(sizeof(TreeNode));
    tr->parent = parent;
    strcpy(tr->name, name);
    
    /* create the Inode */
    tr->in = malloc(sizeof(Inode));
    tr->in->type = type;
    tr->in->size = 0;
    tr->in->refCount = 1;

    return tr;
}

void deleteChild(Tree tr)
{
    Tree parent = tr->parent;

    /* case where tr is the root */
    if (parent == tr)
    {
        freeTree(tr);
        return;
    }

    /* find the index of tr in it's parent's child array */
    int idx;
    for (idx = 0; idx != parent->in->size; ++idx)
        if (parent->in->content.folder[idx] == tr)
            break;

    /* remove tr from the parent's child array */
    --(parent->in->size);
    for (int chd = idx; chd != parent->in->size; ++chd)
        parent->in->content.folder[chd] = parent->in->content.folder[chd + 1];

    /* free tr */
    freeTree(tr);
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

    /* navigate the nodes in tr folder */
    Tree child;
    for (int i = 0; i != tr->in->size; ++i)
    {
        child = tr->in->content.folder[i];

        /* compare the found and original name */
        if (strcmp(child->name, nodeName) == 0)
            return child;
    }

    /* if the name is not found, tr remains the same */
    return tr;
}

/* find the root of a tree */
Tree findRoot(Tree tr)
{
    /* case tr is the root */
    if (tr->parent == tr)
        return tr;

    /* case tr is a child */
    return findRoot(tr->parent);
}

/* free a tree */
void freeTree(Tree tr)
{
    if (tr == NULL)
        return;
    
    /* free the inode */
    freeNode(tr->in);

    /* free the tree node */
    free(tr);
}

void freeNode(Inode *in)
{
    if (in == NULL)
        return;

    /* decrease the reference count */
    --(in->refCount);

    /* free the node only if the reference count has reached 0 */
    if (in->refCount == 0)
    {
        /* free a file */
        if (in->type == File)
            free(in->content.file);

        /* recursively free a folder */
        else
        {
            for (int i = 0; i != in->size; ++i)
                freeTree(in->content.folder[i]);
            free(in->content.folder);
        }

        /* free the inode */
        free(in);
    }
}

void swapContent(Tree tr1, Tree tr2)
{
    Inode *aux = tr1->in;
    tr1->in = tr2->in;
    tr2->in = aux;
}