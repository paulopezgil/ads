#include "main.ih"

/*****************************************************************************\
*  File Organization:                                                         *
*                                                                             *
*  The code is divided into source files, public header files, and internal   *
*  header files. Public headers contain only the declarations and             *
*  preprocessor directives needed by their users (i.e., the source files      *
*  that include them), while internal headers contain the declarations        *
*  and preprocessor directives needed by the source files implementing the    *
*  public header functions. Helper functions (i.e. methods called by the      *
*  functions found in the public header) are declared on the internar header  *
*  if they are only used by the functions found in the public header.         *
*                                                                             *
*  Source file organization:                                                  *
*                                          tree.c ···· trie.c                 *
*                                            ·                                *
*                                            ·                                *
*  main.c ···· console.c ···· commands.c ·····                                *
*                                            ·                                *
*                                            ·                                *
*                                          path.c                             *
*                                                                             *
\*****************************************************************************/

int main()
{
    /* initialize the root directory */
    Tree currentDir = createRoot();

    /* read all the commands until exit is read */
    char name[6];
    int stop = 0;
    while (!stop)
    {
        /* read and execute each command */
        scanf("%s", name);
        stop = executeCommand(name, &currentDir);
    } 
}