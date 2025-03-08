#ifndef PATH_H
#define PATH_H
#define MAX_SIZE 61

#ifndef NAME
#define NAME
typedef char Name[MAX_SIZE];
#endif

typedef struct Path {
    Name *name;
    int size;
    int capacity;
} Path;

void appendName(Path *pt, Name name);
Path createPath(int capacity);
Path readPath();
void freePath(Path pt);


#endif