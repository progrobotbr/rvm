
typedef struct {  
  unsigned char tipo;
  char *nome;
}TCON;

typedef struct{
  int           id;
  unsigned char tipo;
  CBOOL         isArray;
  short int     tamArray;
  CBOOL         isParameter;  
  char         *nome;
  char         *nomeobj;
}TVAR;

typedef struct{
  short int qtdVar;
  short int qtdPar;
  short int rettipo;
  CBOOL     retarray;
  short int ntamopcode;
  short int byteop;
  CBOOL     isNative; 
  char     *nome;
  char     *nometipoobj;
  TVAR     *tvar;
  unsigned char *bc;  /*bytecode*/
} TFUC;

typedef struct{
  char *nome;
  int   qconst;
  TCON *cons;
  int   qatrib;
  TVAR *atrib; 
  int   qfunc;
  TFUC *func;
  TREENODE *ffunc;
  TREENODE *fatrib;
} TCLS;

