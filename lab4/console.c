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

/* read a string of arbitrary length until the delimiter is found */
char *readString(char delimiter)
{
    int capacity = 1, size = 0, foundDelimiter = 0;
    char *str = malloc(sizeof(char));

    while (!foundDelimiter)
    {
        str[size] = getchar();

        /* stop if the delimiter is found */
        if (str[size] == delimiter)
            break;

        /* otherwise, continue and double the capacity if necessary */
        ++size;
        if (size == capacity)
        {
            capacity *= 2;
            str = realloc(str, capacity * sizeof(char));
        }
    }

    /* turn the delimiter into a null terminator and return */
    str[size] = '\0';
    return str;
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
    Path *pt = NULL;
    while (readPath(pt))
        touch(*dir, *pt);
}

void callEcho(Tree *dir)
{
    getchar();   /* skip the initial " */

    /* read the content of the string */
    char *content = readString('"');

    getchar();   /* skip ' ' */
    getchar();   /* skip '>' */

    /* deduce the mode of execution */
    char *(*mode)(char *, char const *) = strcpy;
    if (getchar() == '>')
    {
        getchar();       /* skip ' ' */
        mode = strcat;   /* append instead of overriding */
    }

    /* read the path */
    Path *pt = NULL;
    readPath(pt);

    /* call the appropiate version of echo */
    echo(content, *dir, *pt, mode);
}

/* we assume that the -p flag is always given*/
void callMkdir(Tree *dir)
{   
    /* skip "-p "*/
    getchar();
    getchar();
    getchar();

    /* read the paths until '\n' is read */
    Path *pt = NULL;
    while (readPath(pt))
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