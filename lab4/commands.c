#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/******************************************************************************

    DONE: cd, ls, cat, find, touch, echo, mkdir
    UNSTARTED: mv, cp, rm, ln
    TODO: findNode needs to handle .. and . and other cases

******************************************************************************/

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

void cat(Tree tr, Path pt)
{
    /* go to the specified file */
    tr = cd(tr, pt);

    /* print the content of the file */
    printf("%s\n", tr->in.file);
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

    /* free the initial path */
    freePath(pt);
}

void touch(Tree tr, Path pt)
{
    /* go to the specified directory */
    tr = cd(tr, pt);

    /* create the file using helper function */
    createFile(tr, pt.component[pt.length - 1], File);
}

void echo(char *str, Tree tr, Path pt, char *(*mode)(char *, char const *))
{
    /* go to the specified file */
    tr = cd(tr, pt);

    /* if the file does not exist, create it */
    if (tr->name != pt.component[pt.length - 1])
        tr = createFile(tr, pt.component[pt.length - 1], File);

    /* perform the requested operation */
    mode(tr->in.file, str);
}

void mkdir (Tree tr, Path pt)
{
    /* loop through all elements of the path */
    Tree auxTr;
    for (int i = 0; i != pt.length; ++i)
    {
        auxTr = findNode(tr, pt.component[i]);

        /* case where the folder doesn't exist*/
        if (auxTr == tr)
            createTree(tr, pt.component[i], Folder);

        tr = auxTr;
    }
}