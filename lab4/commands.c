#include "commands.ih"

/******************************************************************************

    DONE: cd, ls, cat, find, touch, echo, mkdir, mv, cp
    UNSTARTED: rm, ln

******************************************************************************/

void cd(Tree *tr, Path pt)
{
    /* if an empty path is given, go to the root */
    if (pt.size == 0)
        *tr = findRoot(*tr);

    /* navigate through the path */
    for (int idx = 0; idx != pt.size; ++idx)
        *tr = findNode(*tr, pt.name[idx]);
}

void ls(Tree tr, Path pt)
{
    /* go to the specified path */
    if (pt.size != 0)
        cd(&tr, pt);

    /* Obtain tr's child list */
    int size = 0;
    Tree *children = childList(tr->in->content.folder, &size);

    /* print the name of it's childs */
    for (int idx = 0; idx != size; ++idx)
        printf("%s\n", children[idx]->name);

    /* free allocated memory */
    free(children);
}

void cat(Tree tr, Path pt)
{
    /* go to the specified file */
    cd(&tr, pt);

    /* print the content of the file */
    if (tr->in->size != 1)
        printf("%s\n", tr->in->content.file);
}

/* helper function for find */
void printContent(Tree tr, Path pt)
{
    /* Obtain tr's child list */
    int size = 0;
    Tree *children = childList(tr->in->content.folder, &size);

    /* visit all childs of tr */
    for(int chd = 0; chd != size; ++chd)
    {
        /* create and print the new path for each child of tr */
        Path childPath = createPath(pt.size + 1);
        for(int idx = 0; idx != pt.size; ++idx)
        {
            strcpy(childPath.name[idx], pt.name[idx]);
            printf("%s/", pt.name[idx]);
        }
        strcpy(childPath.name[pt.size], children[chd]->name);
        printf("%s\n", children[chd]->name);

        /* if the child is a folder, apply recursion */
        if (children[chd]->in->type == Folder)
            printContent(children[chd], childPath);

        /* free the child path */
        freePath(childPath);
    }

    /* free allocated memory */
    free(children);
}

void find(Tree tr)
{
    /* print initial dot */
    printf(".\n");

    /* create the initial path */
    Path pt = createPath(1);
    strcpy(pt.name[0], ".");

    /* call the helper function */
    printContent(tr, pt);

    /* free the initial path */
    freePath(pt);
}

void touch(Tree tr, Path pt)
{
    /* go to the specified directory */
    cd(&tr, pt);

    /* create the file using helper function */
    createTree(tr, pt.name[pt.size - 1], File);
}

/* overwrite the contents of the file with str */
void echo(char *str, int size, Tree tr, Path pt, int override)
{
    /* go to the specified file */
    cd(&tr, pt);

    /* if the file does not exist, create it */
    if (tr->in->type != File)
        tr = createTree(tr, pt.name[pt.size - 1], File);

    /* perform the requested operation */
    if (override)
    {
        /* overwrite the file */
        free(tr->in->content.file);
        tr->in->content.file = malloc(size * sizeof(char));
        strcpy(tr->in->content.file, str);

        /* update the size of the file */
        tr->in->size = size;
    }
    else
    {
        /* append the content of str to the file */
        tr->in->content.file = realloc(tr->in->content.file,
                                       (tr->in->size + size) * sizeof(char));
        strcat(tr->in->content.file, str);
        tr->in->size += size;
    }
}

void mkdir(Tree tr, Path pt)
{
    /* loop through all elements of the path */
    Tree auxTr;
    for (int idx = 0; idx != pt.size; ++idx)
    {
        auxTr = findNode(tr, pt.name[idx]);

        /* case where the folder doesn't exist*/
        if (auxTr == tr)
            auxTr = createTree(tr, pt.name[idx], Folder);

        tr = auxTr;
    }
}

void mv(Tree tr, Path pt1, Path pt2)
{
    /* go to the specified addresses */
    Tree dir1 = tr, dir2 = tr;
    cd(&dir1, pt1);
    cd(&dir2, pt2);
    
    /* if the file at pt2 doesn't exist, create it */
    if (strcmp(dir1->name, dir2->name) != 0)
        dir2 = createTree(dir2, pt2.name[pt2.size - 1], dir1->in->type);
    /* swap the content of the files at dir1 and dir2 */
    swapContent(dir1, dir2);

    /* delete dir1 */
    freeTree(dir1);
}

void cp(Tree tr, Path pt1, Path pt2)
{
    /* go to the specified addresses */
    Tree dir1 = tr, dir2 = tr;
    cd(&dir1, pt1);
    cd(&dir2, pt2);

    /* create dir2 except when overriding an existing non-directory file */
    if (!(dir1->in->type == File && dir2->in->type == File))
        createTree(dir2, dir1->name, dir1->in->type);

    /* call helper function to copy the file */
    copyTree(dir1, dir2);
}

