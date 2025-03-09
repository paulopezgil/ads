#include "commands.ih"

/******************************************************************************

    DONE: cd, ls, cat, find, touch, echo, mkdir, mv
    UNSTARTED: cp, rm, ln

******************************************************************************/

void cd(Tree *tr, Path pt)
{
    /* if no path is given, return the root */
    if (pt.size == 0)
        *tr = findRoot(*tr);

    /* navigate through the path */
    for (int i = 0; i != pt.size; ++i)
        *tr = findNode(*tr, pt.name[i]);
}

void ls(Tree tr, Path pt)
{
    /* go to the specified path */
    cd(&tr, pt);

    /* print the name of it's childs */
    for (int i = 0; i != tr->size; ++i)
        printf("%s\n", tr->in.folder[i]->name);
}

void cat(Tree tr, Path pt)
{
    /* go to the specified file */
    cd(&tr, pt);

    /* print the content of the file */
    printf("%s\n", tr->in.file);
}

/* helper function for find */
void printContent(Tree tr, Path pt)
{
    /* visit all childs of tr */
    for(int i = 0; i != tr->size; ++i)
    {
        Tree child = tr->in.folder[i];

        /* create and print the new path for each child of tr */
        Path childPath = createPath(pt.size + 1);
        for(int j = 0; j != pt.size; ++j)
        {
            strcpy(childPath.name[j], pt.name[j]);
            printf("%s/", pt.name[j]);
        }
        strcpy(childPath.name[pt.size], child->name);
        printf("%s\n", child->name);

        /* if the child is a folder, apply recursion */
        if (child->inT == Folder)
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
    mode(tr->in.file, str);
}

void mkdir(Tree tr, Path pt)
{
    /* loop through all elements of the path */
    Tree auxTr;
    for (int i = 0; i != pt.size; ++i)
    {
        auxTr = findNode(tr, pt.name[i]);

        /* case where the folder doesn't exist*/
        if (auxTr == tr)
            createTree(tr, pt.name[i], Folder);

        tr = auxTr;
    }
}

void mv(Tree tr, Path pt1, Path pt2)
{
    Tree dir1 = tr, dir2 = tr;

    /* go to the specified addresses */
    cd(&dir1, pt1);
    cd(&dir2, pt2);
    Tree parent1 = dir1->parent;

    /* find the index of the file at pt1 in it's parent's child array */
    int idx;
    for (idx = 0; idx != parent1->size; ++idx)
        if (parent1->in.folder[idx] == dir1)
            break;

    /* if the file with pt1 already exists at pt2, override it */
    if (dir2->inT == File && strcmp(dir1->name, dir2->name) == 0)
    {
        strcpy(dir2->in.file, dir1->in.file);
        freeTree(dir1);
    }

    /* otherwise, change the path of the file at pt1 to pt2 */
    else
    {
        ++(dir2->size);
        dir2->in.folder = realloc(dir2->in.folder, dir2->size * sizeof(TreeNode));
        dir2->in.folder[dir2->size - 1] = dir1;
        dir1->parent = dir2;
    }

    /* remove the file from the parent's child array */
    --(parent1->size);
    for (int chd = idx; chd != parent1->size; ++chd)
        parent1->in.folder[chd] = parent1->in.folder[chd + 1];
}