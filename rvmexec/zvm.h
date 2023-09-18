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
#define _END      0     

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
  VAR           *stack;
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
  TFRAME    stackFrameMem[1000];
  TFRAME   *stackFrame;
  TREENODE *memcb;
  ADMem    *memci;
  int       rc;
  char     *firstClass;
} TMEMVM;

TMEMVM gMvm;

VAR (*gAdd[4])(VAR *, VAR *);
VAR (*gSub[4])(VAR *, VAR *);
VAR (*gMul[4])(VAR *, VAR *);
VAR (*gDiv[4])(VAR *, VAR *);
VAR (*gAnd[4])(VAR *, VAR *);
VAR (*gOr[4])(VAR *, VAR *);
VAR (*gEq[4])(VAR *, VAR *);
VAR (*gLt[4])(VAR *, VAR *);
VAR (*gLe[4])(VAR *, VAR *);
VAR (*gGt[4])(VAR *, VAR *);
VAR (*gGe[4])(VAR *, VAR *);

void (*nm[4][4])(VAR *);

TFRAME * op_createStackFrameByIndex(int index, VAR **pstack, CCLS *pci);
TFRAME * popStackFrame(CBOOL ppopret, TFRAME *ptf, VAR *stack);
TFRAME * op_createStackFrameByName(int pidobj, char *pnomefunc, VAR **pstack);
VAR op_loadc(TCLS *ptcls, int i);
void moveVar(VAR *o, VAR *d);

   




        
