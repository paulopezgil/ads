#include "console.ih"

void executeCommand(char *name, Tree *dir)
{
    execute[getCommandId(name)](dir);
}

/**********************************************************************\
*   The following functions parse the input from stdin, and call the   *
*   appropiate methods with the scanned arguments                      *
\**********************************************************************/

int getCommandId(char *command)
{
    if (strcmp(command, "exit") == 0)
        return EXIT;
    if (strcmp(command, "cd") == 0)
        return CD;
    if (strcmp(command, "ls") == 0)
        return LS;
    if (strcmp(command, "cat") == 0)
        return CAT;
    if (strcmp(command, "find") == 0)
        return FIND;
    if (strcmp(command, "touch") == 0)
        return TOUCH;
    if (strcmp(command, "echo") == 0)
        return ECHO;
    if (strcmp(command, "mkdir") == 0)
        return MKDIR;
    if (strcmp(command, "cp") == 0)
        return CP;
    if (strcmp(command, "rm") == 0)
        return RM;
    if (strcmp(command, "ln") == 0)
        return LN;
    return -1;
}

void callExit(Tree *dir)
{
    freeTree(findRoot(*dir));
    exit(1);
}

void callCd(Tree *dir)
{
    Path *pt = NULL;
    readPath(pt);
    cd(dir, *pt);
}

void callLs(Tree *dir)
{
    Path *pt = NULL;
    readPath(pt);
    ls(*dir, *pt);
}

void callCat(Tree *dir)
{
    Path *pt = NULL;
    readPath(pt);
    cat(*dir, *pt);
}

void callFind(Tree *dir)
{
    find(*dir);
}

void callTouch(Tree *dir)
{
    /* read the paths until '\n' is read */
    Path pt;
    while (readPath(&pt))
    {
        readPath(&pt);
        touch(*dir, pt);
    }
}

void callEcho(Tree *dir)
{
    //scanf(" \"%s\" > ");
}

/* we assume that the -p flag is always given*/
void callMkdir(Tree *dir)
{
    Path *pt = NULL;
    readPath(pt);
    mkdir(*dir, *pt);
}

void callMv(Tree *dir)
{
    Path *pt1 = NULL, *pt2 = NULL;
    readPath(pt1);
    readPath(pt2);
    mv(*dir, *pt1, *pt2);
}

void callCp(Tree *dir)
{

}

void callRm(Tree *dir)
{

}

void callLn(Tree *dir)
{

}