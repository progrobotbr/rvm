#ifndef _DLL_H_
#define _DLL_H_

#if BUILDING_DLL
# define DLLIMPORT __declspec (dllexport)
#else /* Not BUILDING_DLL */
# define DLLIMPORT __declspec (dllimport)
#endif /* Not BUILDING_DLL */

#define PMALLOC void *(*pmalloc)(unsigned long l)
#define NULL 0

typedef long VARTB;
typedef void * clazzptr;

//
// Tabela
//

struct _node {
  long sum;
  long tam;
  struct _node *pointer;
  int leaf;
  struct _node *child;
  struct _node *nextnode;
  struct _node *parent;
  long parentidx;
  VARTB value;
};

typedef struct _node node;

struct _node_search{
  node *node;
  long pos;     
};

typedef struct _node_search node_search;

struct _table {
  node *root;
  long size;
  long count;
};

typedef struct _table table;
typedef int CBOOL;
#define CTRUE 1
#define CFALSE 0
//#define CTBNULL '\0'

/****************************
** table.h
*****************************/
table *tbCreate();
node_search tbSearchRoot(table *tb, long pindex);
node  *tbGetNodeByIndex(table *tb, long pindex);
CBOOL  tbInsertRoot(table *tb, VARTB v, long pindex);
CBOOL  tbDeleteRoot(table *tb, long k);
CBOOL  tbUpdateRoot(table *tb, VARTB v,long pindex);

node_search tbSearch(node *x, long pindex, long ipsum);
node *tbSeek(node_search ns);
CBOOL tbInsert(table *tb, VARTB v, long posinnode, node *n1, node *n2, CBOOL pquebra);
CBOOL tbDeleteAdjust(table *tb, node *n);
CBOOL tbDeleteJoinE(node *np, node *ne, node *n);
CBOOL tbDeleteJoinD(node *np, node *nd, node *n);
CBOOL tbDeleteNorm(node *np, node *ne, node *n);
node *tbDeleteGetLast(node *n);
CBOOL tbDeleteNodeElem(table *tb, node *n, long pos);
CBOOL tbNodePutValue(table *tb, node *n, VARTB v, long pos);
CBOOL tbNodePut(node *n1, node *n2, long pos);
node *tbQuebra(node *n);

node *tbCreateNode();
long  tbGetSize();

struct _tableobj{
  node  *(*getItem)(table *tb, long pindex);
  CBOOL  (*Insert) (table *tb, VARTB v, long pindex);
  CBOOL  (*Delete) (table *tb, long k);
  CBOOL  (*Update) (table *tb, VARTB v,long pindex);
  table *tb;         
};

typedef struct _tableobj tableobj;      

/*objetos*/
tableobj *createTbObj();
void freeTbObj(tableobj *tb);


/* Tipo Básico */
typedef struct {
   unsigned char tipo;  
   unsigned char isArray;
   short int     tamArray;
   char         *nomeobj;
   union {   
     char       c;      
     int        i;
     long       l;  
     double     f;
     long       o;
     void  *t;
     char      *ca;
     int       *ia;
     long      *la;
     double    *fa;
     void      *oa;
  };
} VAR;

DLLIMPORT VAR CALC5(int pqtdpar, VAR *pstack, PMALLOC);      //funcao teste
DLLIMPORT VAR __CONCATI(int pqtdpar, VAR *pstack, PMALLOC);  //concatena um int
DLLIMPORT VAR __CONCATC(int pqtdpar, VAR *pstack, PMALLOC);  //concatena um char
DLLIMPORT VAR __CONCATCA(int pqtdpar, VAR *pstack, PMALLOC); //concatena 2 arrays
DLLIMPORT VAR __PRINT(int pqtdpar, VAR *pstack, PMALLOC);    //imprime array de char
DLLIMPORT VAR __PRINTENT(int pqtdpar, VAR *pstack, PMALLOC); //imprime enter
DLLIMPORT VAR __PRINTN(int pqtdpar, VAR *pstack, PMALLOC);   //imprime int
DLLIMPORT VAR __PRINTF(int pqtdpar, VAR *pstack, PMALLOC);   //imprime float
DLLIMPORT VAR __TRUNC(int pqtdpar, VAR *pstack,PMALLOC);    //trunca casas decimais

//Tabela
DLLIMPORT VAR __TBAPPEND(int pqtdpar, VAR *pstack, PMALLOC);
DLLIMPORT VAR __TBINSERT(int pqtdpar, VAR *pstack, PMALLOC);
DLLIMPORT VAR __TBMODIFY(int pqtdpar, VAR *pstack, PMALLOC);
DLLIMPORT VAR __TBREAD(int pqtdpar, VAR *pstack, PMALLOC);

//Funcoes auxliares
VAR CONCATC(int pqtdpar, VAR *pstack, PMALLOC);
VAR CONCATCA(int pqtdpar, VAR *pstack, PMALLOC);
VAR CONCATI(int pqtdpar, VAR *pstack, PMALLOC);
VAR CONCATI(int pqtdpar, VAR *pstack, PMALLOC);
VAR CONCATC(int pqtdpar, VAR *pstack, PMALLOC);
double _btrunc(double f, int qtd);

//String
DLLIMPORT VAR __STRINGLEN(int pqtdpar, VAR *pstack, PMALLOC);

unsigned long lm;

//void * zmalloc(unsigned long l);
#endif /* _DLL_H_ */
