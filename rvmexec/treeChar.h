 
struct _treenode{
  char c;
  struct _treenode *prior;
  struct _treenode *next;
  struct _treenode *down;
  struct _treenode *up;
  void *val;      
};

typedef struct _treenode TREENODE;

void * initTreeChar();
void * findTreeChar(char *c, TREENODE **self);
CBOOL putTreeChar(char *c, void *val, TREENODE **self);
TREENODE *createTreeNode(char c);

