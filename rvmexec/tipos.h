

/
//Constantes
typedef struct {
  int id;
  unsigned char tipo;
  int tamnome;
  char *nome;     
} ConstantVal;

//Tipo Básico
/*
typedef struct {
   unsigned char tipo;  
   unsigned char isArray;
   short int sizeArray;
   union {   
     char c;      
     short int i;
     long int l;  
     double f;
     char *ca;
     short int *ia;
     long int *la;
     double *fa;
  };
} Var;
*/
//Operadores Nodes
typedef struct {
  unsigned char Op;
  int qtdeparametros;
  S1 *parametros;
} NodesOp;

//Funcao
typedef struct Funcao{
  int id;
  char *nome;
  int qtdparametros;
  int qtdvar;
  int qtdbinary;
  int qtdnodeop;
  NodesOp *nodeop;
  int qtdlv1;
  TLV1 *vardecl;
} Funcao;

//Programa
typedef struct Prg{
  int id;
  char *nome;
  int qtdconst;
  int qtdvar;
  int qtdfunc;
  ConstantVal *constants;
  Var *variaveis;
  Funcao *funcao;
  struct Prg *next;
} Prg;

typedef struct {
  Prg *PrgAtual;
  Prg *PrgFirst;
  Prg *PrgLast;
  int size;
} PrgPool;

//Heap
typedef struct {
  int QtdVar;
  Var *Var;
} HeapVarLocals;

//Pilha
typedef struct { 
  Var Var;
} PilhaObjeto;

typedef struct {
  int Ponteiro;
  PilhaObjeto Objeto[];       
} PilhaProcesso;        

//Stack Memory
typedef struct {
  void *StackIni;
  void *StackEnd;      
} StackMem;

//Frame
typedef struct {
  int idFuncao;
  int idPrograma;      
  Funcao *Funcao;
  char *NomeFuncao;
  Prg *Prg;
  char *NomePrograma;
  int QtdParametros;
  int QtdOperadores;
  NodesOp *FuncaoOpAtivo; //Ponteiro
  PilhaObjeto *Pilha;
  HeapVarLocals HeapLocal;
} FrameSet;

typedef struct {
  FrameSet *Frame;
  FrameSet *FirstFrame;
  FrameSet *LastFrame;
} PilhaFrameSet;
        
/*
//----- Variáveis Globais
*/

//PilhaFrameSet gFrameFrameSet;
FrameSet *gFrame;
PrgPool gPrgPool;
Prg *gPrg;
Funcao *gFuncao;
PilhaObjeto *gPilha;
StackMem gStackMem;

