#include "console.ih"

void callCd(Tree *dir)
{
    Path pt = readPath();
    *dir = cd(*dir, pt);
}


int getCommand(char *command)
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

int readInput()
{
    /* initialize the file system */
    Name firstName = "/";
    Tree rootDir = createTree(NULL, firstName, Folder);
    Tree currentDir = rootDir;

    /* read all commands */
    char name[6];
    while (1)
    {
        /* get the command name */
        scanf("%s", name);
        int command = getCommand(name);

        /* call the corresponding command */
        execute[command](&currentDir);
    }
}