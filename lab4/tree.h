#ifndef FILE_H
#define FILE_H
#define MAX_SIZE 61


#ifndef NAME
#define NAME
typedef char Name[MAX_SIZE];
#endif

typedef struct TreeNode *Tree;

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

Tree createFile(Tree tr, Name filename, InodeType type);
Tree createTree(Tree parent, Name name, InodeType inT);
Tree findNode(Tree tr, Name nodeName);
Tree findRoot(Tree tr);
void freeTree(Tree root);


#endif