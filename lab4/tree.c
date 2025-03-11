#include "tree.ih"

void copyTree(Tree origin, Tree destination)
{
    /* override the destination if origin is a file */
    if (origin->in->type == File)
    {
        free(destination->in->content.file);
        destination->in->content.file = malloc(origin->in->size * sizeof(char));
        strcpy(destination->in->content.file, origin->in->content.file);
        destination->in->size = origin->in->size;
        return;
    }

    /* if origin is a folder, obtain it's child list */
    int size = 0;
    Tree *children = childList(origin->in->content.folder, &size);

    /* copy the children of origin to destination */
    if (children != NULL)
    {
        for(int idx = 0; idx != size; ++idx)
            copyTree(children[idx], createTree(destination,
                                            children[idx]->name,
                                            children[idx]->in->type));
        free(children);
    }
}

Tree createRoot()
{
    Name rootName = "/";
    Tree root = createTree(NULL, rootName, Folder);
    root->parent = root;
    return root;
}

Tree createTree(Tree parent, Name name, InodeType type)
{
    /* create a TreeNode */
    Tree tr = malloc(sizeof(TreeNode));
    tr->parent = parent;
    strcpy(tr->name, name);

    /* create the Inode */
    tr->in = malloc(sizeof(Inode));
    if (type == File)
    {
        tr->in->content.file = malloc(sizeof(char));
        tr->in->content.file[0] = '\0';
        tr->in->size = 1;
    }
    else
    {
        tr->in->content.folder = createTrie();
        tr->in->size = 0;
    }
    tr->in->type = type;
    tr->in->refCount = 1;

    /* if a parent is specified, add tr to the parent's child trie */
    if (parent != NULL)
    {
        insertTrie(parent->in->content.folder, tr);
        ++(parent->in->size);
    }

    /* return the created tree node */
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

    /* search fo the child file */
    Tree child = searchTrie(tr->in->content.folder, nodeName);
    if (child != NULL)
        return child;
    
    /* if the name is not found, tr remains the same */
    return tr;
}

Tree findRoot(Tree tr)
{
    /* case tr is the root */
    if (tr->parent == tr)
        return tr;

    /* case tr is a child */
    return findRoot(tr->parent);
}

void freeTree(Tree tr)
{
    if (tr == NULL)
        return;
    
    /* free the inode */
    freeNode(tr->in);

    /* free the tree */
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
        /* free the content */
        if (in->type == File)
            free(in->content.file);
        else
            freeTrie(in->content.folder);

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