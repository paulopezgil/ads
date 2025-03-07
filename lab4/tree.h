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


Tree createFile(Tree tr, Name filename, InodeType type);
Path createPath(int length);
Tree createTree(Tree parent, Name name, InodeType inT);
Tree findNode(Tree tr, Name nodeName);
Tree findRoot(Tree tr);
void freePath(Path pt);
void freeTree(Tree root);
void printContent(Tree tr, Path pt);


#endif