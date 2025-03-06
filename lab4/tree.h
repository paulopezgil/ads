#ifndef FILE_HH
#define FILE_HH
#define MAX_LENGTH 61



typedef struct TreeNode *Tree;
typedef char Name[MAX_LENGTH];

typedef enum InodeType {
    Folder,
    File
} InodeType;

typedef union Inode {
    Tree *folder;   /* an array of child nodes */
    char *file;     /* an array of characters */
} Inode;

typedef struct TreeNode {
    Tree parent;
    Name name;
    InodeType inT;
    Inode in;
    int size;
} TreeNode;

typedef struct Path {
    Name *component;
    int length;
} Path;


Tree createTree();
Tree findRoot(Tree tr);
void freeTree(Tree root);

Path createPath(int length);
void freePath(Path pt);


#endif