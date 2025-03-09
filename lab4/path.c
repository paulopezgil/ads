#include "path.ih"

/* add a name to the path */
void appendName(Path *pt, Name name)
{
    /* if the path is full, double it's capacity */
    if (pt->size == pt->capacity)
    {
        pt->capacity *= 2;
        pt->name = realloc(pt->name, pt->capacity * sizeof(Name));
    }

    /* add the new name */
    strcpy(pt->name[pt->size], name);
    pt->size += 1;
}

/* create a new path with given capacity */
Path createPath(int capacity)
{
    Path pt;
    pt.name = malloc(capacity * sizeof(Name));
    pt.size = 0;
    pt.capacity = capacity;
    return pt;
}

/* read a path from stdin */
int readPath(Path *pt)
{
    /* reinitialize pt in case it was already initialized */
    if (pt != NULL)
        freePath(*pt);
    *pt = createPath(1);
    Name name;

    /* check if it's an absolute path */
    name[0] = getchar();
    if (name[0] == '/')
    {
        name[1] = '\0';
        appendName(pt, name);
    }
    else
        ungetc(name[0], stdin);

    /* read each name until a slash, space or line break is found */
    char separator = 'a';
    while (separator != ' ' && separator != '\n')
    {
        scanf("%[^/ \n]", name);
        appendName(pt, name);
        separator = getchar();
    }

    /* return 1 if the separator is ' ' and 0 if it's '\n' */
    return separator == ' ';
}

/* free a path */
void freePath(Path pt)
{
    free(pt.name);
}