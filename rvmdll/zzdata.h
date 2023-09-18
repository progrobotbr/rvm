
#define CCHAR    1
#define CINTEGER 2
#define CLONG    3 
#define CFLOAT   4
#define COBJ     5

#define CTRUE  1
#define CFALSE 0
#define CNULL -1

typedef int CBOOL;

typedef unsigned char          U1;
typedef short int              S1;
typedef unsigned short int     S2;
typedef long int               L1;
typedef float                  F1;

/***************************************
**** loadclass.h
****************************************/

#define CL1 1
#define CTQ 2
#define CT1 3
#define FD1 4
#define FVQ 5
#define FVL 6
#define BC1 7

#define CASSERTCL(x,y) if(x==CFALSE) { deleteArrayMalloc(mem, CTRUE);*pcls = cls;close(fp);return(y); }
#define CASSERT(x,y) if(x==CFALSE) { return(y); }

typedef struct {
  short int iqtdcons;
  short int iqtdfunc;
  short int iqtdvglo;
} TCL1;

        
typedef struct {
  short int qtditem;
} TQT1;

typedef struct {  
  short int id;
  short int tipo;
  short int tam;
}TCT1;

typedef struct {
  short int id;
  unsigned char tipo;
  unsigned char isArray;
  short int tamArray;
  unsigned char isParameter;
} TLV1;

typedef struct {
  short int id;
  short int qtdVar;
  short int qtdPar;
  short int rettipo;
  short int retarray;
  short int ntamopcode;
  short int ntamstack;
  short int byteop;
  short int isNative; 

  /*
     nome
     nometipoobj
  */
} TFD1;

typedef struct {
  short int tamnome1;
  char *nome1;
  short int tamnome2;
  char *nome2;
} TNM;



/****************************************
*** treechar.h
*****************************************/
struct _treenode{
  char c;
  struct _treenode *prior;
  struct _treenode *next;
  struct _treenode *down;
  struct _treenode *up;
  void *val;      
};

typedef struct _treenode TREENODE;


/****************************************
* metaclass.h
*****************************************/
typedef struct {  
  int id;      
  unsigned char tipo;
  int tam;
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
  short int ntamstack;
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

/**********************************
***** class.h
***********************************/

/* Tipo Básico */
typedef struct {
   unsigned char tipo;  
   unsigned char isArray;
   short int     tamArray;
   char         *nomeobj;
   union {   
     char       c;      
     short int  i;
     long int   l;  
     double     f;
     long       o;
     char      *ca;
     short int *ia;
     long int  *la;
     double    *fa;
     long      *oa;
  };
} VAR;

/* Classe */
typedef struct {
  int           id;
  unsigned char mark;
  unsigned char isActive;
  TCLS         *cb;     /* metadado da classe */
  int           qatrib;
  VAR          *atrib;         
} CCLS;        


/**************************************
** arrayMalloc
***************************************/

typedef char * PPMEM;

typedef struct _arrayitem ArrayItem;

struct _arrayMalloc {
  PPMEM *mem;
  long tam;     
  long index;
};       

typedef struct _arrayMalloc ArrayMalloc;

/**************************************
** arrayDynamic.h
***************************************/

struct _admem {
  CCLS *mem;
  long tam;     
  long index;
  int tamitem;
};       

typedef struct _admem ADMem;


/**************************************
** zvm.h
***************************************/
/**** DEFINICAO DE BYTECODES ****/

/****** Dicionário ********************************
_ADD      soma dois operandos
_SUBR     subtração de dois operandos
_MUL      multiplicação de dois operandos
_DIV      divisao dedois ops
_IFFALSE  #n   muda para instrução #n se falso
_EQ       igualdade entre dois ops
_GT       greater than entre dois ops (edp)
_GTE      greater than and equal edp
_LT       lower than edp
_LTE      lower than and equal edp
_AND      and edp
_OR       or  edp
_GOTO     #n  vai para o operando #n
_CALLF    #c  carrega uma funcao #c no frame
_CALLNATV #c,#p chama função nativa #c com qtd de parametros #p
_RET      retorna para função chamadora, retornando para frame anterior a variavel atual da pilha 
_RETNULL  retorna para função chamadora sem retornar parametro
_NEW      cria nova instancia de classe
_LOADC    #n carrega constante de id #n
_LOADV    #n carrega variável #n 
_STORV    #n armazena variável #n
_LOADVY
_STORVY
_GLOADV
_GSTORV
_GLOADVY  
_GSTORVY  
_OCALLF   
_OLOADV   
_OSTORV   
_OLOADVY  
_OSTORVY  
_NEWY          
**************************************************/

#define _ADD      50
#define _SUBR     51
#define _MUL      52
#define _DIV      53
#define _IFFALSE  60
#define _EQ       61
#define _GT       62
#define _GTE      63
#define _LT       64
#define _LTE      65
#define _AND      66
#define _OR       67
#define _GOTO     70
#define _CALLF    71      
#define _CALLNATV 72  
#define _RET      73       
#define _RETNULL  74   
#define _NEW      75       
#define _LOADC    80     
#define _LOADV    81     
#define _STORV    82
#define _LOADVY   83
#define _STORVY   84
#define _GLOADV   85
#define _GSTORV   86
#define _GLOADVY  87
#define _GSTORVY  88
#define _OCALLF   89
#define _OLOADV   90
#define _OSTORV   91
#define _OLOADVY  92
#define _OSTORVY  93
#define _NEWY     94
#define _END      95     

/*
    t  -> Tipo da variável de retorno
    p1 -> Primeira variável
    p2 -> Segunda variável
*/

#define NORMALIZE(t,p1,p2)  if(p1.tipo==p2.tipo) \
                              t=p1.tipo; \
                            else \
                              if(p1.tipo>p2.tipo){ \
                                t=p1.tipo; \
                                nm[p2.tipo][p1.tipo](&p2); \
                              }else{ \
                                t=p2.tipo; \
                                nm[p1.tipo][p2.tipo](&p1); \
                              }



/**** FRAME ****/
typedef struct {

  unsigned char  isNative;        
  VAR           *stack; /*aponta para a base do stack*/
  VAR           *stackpt; /*aponta para algum ponto do stack */ 
  unsigned char *bc; /* bytecodes - aponta para a base dos bytes codes na definicao da funcao */
  int   qtdVar;
  int   qtdPar;
  VAR  *var;
  CCLS *ci;
  TCLS *cb;
  TFUC *tfuc;
  TVAR *tvar;
  char *nomeclass;
  char *nomefunc;
  int   rc;

} TFRAME;

/**** DADOS GLOBAIS DA VM ****/
typedef struct {
  TFRAME    stackFrameMem[100];
  TFRAME   *stackFrame;
  TREENODE *memcb;
  ADMem    *memci;
  int       rc;
  char     *firstClass;
} TMEMVM;

TMEMVM gMvm;

void (*gAdd[5])(VAR *, VAR *);
void (*gSub[5])(VAR *, VAR *);
void (*gMul[5])(VAR *, VAR *);
void (*gDiv[5])(VAR *, VAR *);
void (*gAnd[5])(VAR *, VAR *);
void (*gOr[5])(VAR *, VAR *);
void (*gEq[5])(VAR *, VAR *);
void (*gLt[5])(VAR *, VAR *);
void (*gLe[5])(VAR *, VAR *);
void (*gGt[5])(VAR *, VAR *);
void (*gGe[5])(VAR *, VAR *);

void (*nm[5][5])(VAR *);

        


