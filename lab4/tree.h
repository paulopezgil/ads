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

typedef union InodeContent {
    Tree *folder;   /* an array of child nodes */
    char *file;     /* an array of characters */
} InodeContent;

typedef struct Inode {
    InodeType type;
    InodeContent content;
    int size;
    int refCount;
} Inode;

typedef struct TreeNode {
    Tree parent;
    Name name;
    Inode *in;    
} TreeNode;

void copyTree(Tree origin, Tree destination);
Tree createRoot();
Tree createTree(Tree parent, Name name, InodeType type);
void deleteChild(Tree tr);
Tree findNode(Tree tr, Name nodeName);
Tree findRoot(Tree tr);
void freeTree(Tree root);
void freeNode(Inode *in);
void swapContent(Tree tr1, Tree tr2);

#endif