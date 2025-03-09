#include "commands.ih"

/******************************************************************************

    DONE: cd, ls, cat, find, touch, echo, mkdir, mv, cp
    UNSTARTED: rm, ln

******************************************************************************/

void cd(Tree *tr, Path pt)
{
    /* if no path is given, return the root */
    if (pt.size == 0)
        *tr = findRoot(*tr);

    /* navigate through the path */
    for (int idx = 0; idx != pt.size; ++idx)
        *tr = findNode(*tr, pt.name[idx]);
}

void ls(Tree tr, Path pt)
{
    /* go to the specified path */
    cd(&tr, pt);

    /* print the name of it's childs */
    for (int idx = 0; idx != tr->in->size; ++idx)
        printf("%s\n", tr->in->content.folder[idx]->name);
}

void cat(Tree tr, Path pt)
{
    /* go to the specified file */
    cd(&tr, pt);

    /* print the content of the file */
    printf("%s\n", tr->in->content.file);
}

/* helper function for find */
void printContent(Tree tr, Path pt)
{
    /* visit all childs of tr */
    for(int chd = 0; chd != tr->in->size; ++chd)
    {
        Tree child = tr->in->content.folder[chd];

        /* create and print the new path for each child of tr */
        Path childPath = createPath(pt.size + 1);
        for(int idx = 0; idx != pt.size; ++idx)
        {
            strcpy(childPath.name[idx], pt.name[idx]);
            printf("%s/", pt.name[idx]);
        }
        strcpy(childPath.name[pt.size], child->name);
        printf("%s\n", child->name);

        /* if the child is a folder, apply recursion */
        if (child->in->type == Folder)
            printContent(child, childPath);

        /* free the child path */
        freePath(childPath);
    }
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
    createFile(tr, pt.name[pt.size - 1], File);
}

void echo(char *str, Tree tr, Path pt, char *(*mode)(char *, char const *))
{
    /* go to the specified file */
    cd(&tr, pt);

    /* if the file does not exist, create it */
    if (tr->name != pt.name[pt.size - 1])
        tr = createFile(tr, pt.name[pt.size - 1], File);

    /* perform the requested operation */
    mode(tr->in->content.file, str);
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
            createTree(tr, pt.name[idx], Folder);

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
        dir2 = createFile(dir2, dir1->name, dir1->in->type);
    
    /* swap the content of the files at dir1 and dir2 */
    swapContent(dir1, dir2);

    /* delete dir1 */
    deleteChild(dir1);
}

void cp(Tree tr, Path pt1, Path pt2)
{
    /* go to the specified addresses */
    Tree dir1 = tr, dir2 = tr;
    cd(&dir1, pt1);
    cd(&dir2, pt2);

    /* if dir1 is a non-directory file, create dir2 if it doesn't exist */
    if (dir1->in->type == File && dir2->in->type == Folder)
        createFile(dir2, dir1->name, dir1->in->type);

    /* call helper function to copy the file */
    copyTree(dir1, createFile(dir2, pt2.name[pt2.size - 1], dir1->in->type));
}

