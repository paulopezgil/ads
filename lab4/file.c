#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/******************************************************************************

    DONE: cd, ls, cat, find
    UNFINISHED: findNode (needs to handle .. and . and other cases)
    UNSTARTED: touch, echo, mkdir, mv, cp, rm, ln
    TODO: the program is leaking, free the created Paths

******************************************************************************/


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

    return tr;
}

Tree cd(Tree tr, Path pt)
{
    /* navigate through the path */
    for (int i = 0; i != pt.length; ++i)
        tr = findNode(tr, pt.component[i]);

    return tr;
}

void ls(Tree tr, Path pt)
{
    /* go to the specified path */
    tr = cd(tr, pt);

    /* print the name of it's childs */
    for (int i = 0; i != tr->size; ++i)
        printf("%s\n", tr->in.folder[i]->name);
}

void cat(Tree tr, Path pt, Name filename)
{
    /* go to the specified location */
    tr = cd(tr, pt);

    /* find the specified file */
    tr = findNode(tr, filename);

    /* print the content of the file */
    printf("%s\n", tr->in.file);
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
    }
}

void find(Tree tr)
{
    /* print initial dot */
    printf(".\n");

    /* create the initial path */
    Path pt = createPath(1);
    strcpy(pt.component[0], ".");

    /* call the helper function */
    printContent(tr, pt);
}