#include "path.ih"

/* add a name to the path */
void appendName(Path *pt, Name name)
{
    /* if the path is full, double it's capacity */
    if (pt->size == pt->capacity)
    {
        pt->name = realloc(pt->name, 2 * pt->size * sizeof(Name));
        pt->capacity *= 2;
    }

    /* add the new name */
    strcpy(pt->name[pt->size], name);
    pt->size += 1;
}

// create a new path with given capacity
Path createPath(int capacity)
{
    Path pt;
    pt.name = malloc(capacity * sizeof(Name));
    pt.size = 0;
    pt.capacity = capacity;
    return pt;
}

/* read a path from stdin */
Path readPath()
{
    Path pt = createPath(1);
    Name readName;

    /* check if it's an absolute path */
    readName[0] = getchar();
    if (readName[0] == '/')
    {
        readName[1] = '\0';
        appendName(&pt, readName);
    }
    else
        ungetc(readName[0], stdin);
}

// free a path
void freePath(Path pt)
{
    free(pt.name);
}