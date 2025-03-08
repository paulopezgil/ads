#include "main.ih"

/*******************************************************************************
*    File organization:                                                        *
*                                                                              *
*  The code is divided into source files, public header files and internal     *
*  header files. Public headers contain only the declarations needed by their  *
*  users (i.e. the source files that include them), whereas internal headers   *
*  contain the declarations needed by the internal methods of the header       *
*  (i.e. the methods used by the methods declared on the public header).       *
*                                                                              *
********************************************************************************/

int main()
{
    /* initialize the root directory */
    Name firstName = "/";
    Tree currentDir = createTree(NULL, firstName, Folder);
    currentDir->parent = currentDir;

    /* read all the commands until exit is read */
    char name[6];
    while (1)
    {
        /* read and execute each command */
        scanf("%s", name);
        executeCommand(name, &currentDir);
    } 
}