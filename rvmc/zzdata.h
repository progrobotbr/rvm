#define BOOL int
#define TRUE 1
#define FALSE 0

//Symbols
#define CNOME 1
#define CNUMFILHOS 2
#define CVARIABLE 1
#define CFUNCAO 2
#define CCONST 3
#define CTIPOPARIN 1
#define CTIPOPAROUT 2
#define CTIPOVAR 3
#define GLOBALS 0
#define CQTDCOMAND 100
#define CMAQCOMMANDS 36
//Symbols

#define SS(x)   newString(x)
#define SP(x,y) x->mv(x,y)
#define SG(x)   x->c
#define SC(x,y) x->concat(x,y)
#define SC3(x1,x2,x3) SC(SC(x1,x2),x3)
#define SC4(x1,x2,x3,x4) SC(SC(SC(x1,x2),x3),x4)
#define SC5(x1,x2,x3,x4,x5) SC(SC(SC(SC(x1,x2),x3),x4),x5)
#define SC6(x1,x2,x3,x4,x5,x6) SC(SC(SC(SC(SC(x1,x2),x3),x4),x5),x6)
#define SC7(x1,x2,x3,x4,x5,x6,x7) SC(SC(SC(SC(SC(SC(x1,x2),x3),x4),x5),x6),x7)
#define SC8(x1,x2,x3,x4,x5,x6,x7,x8) SC(SC(SC(SC(SC(SC(SC(x1,x2),x3),x4),x5),x6),x7),x8)
#define SC9(x1,x2,x3,x4,x5,x6,x7,x8,x9) SC(SC(SC(SC(SC(SC(SC(SC(x1,x2),x3),x4),x5),x6),x7),x8),z9)
#define SL(x,y) x->cmp(x,y)
#define SI(x)   x->size(x)
#define SV(x,y) x=newString(y)
#define Mid(x,y,z) x->mid(x,y,z)
#define Trim(x) x->trim(x)
#define Len(x)  x->size(x)
#define Not !
#define UCase(x) x->ucase(x)
#define LCase(x) x->lcase(x)
#define Asc(x) x->asc(x)
#define isNumeric(x) x->isnum(x)
#define vbCrLf newString("\n")
#define CInt(x) string_str_int(x)
#define Str(x) string_int_str(x)
#define Replace(x,y,z) string_replace(x,y,z)
#define NIL 0
#define Err_Raise(x) rquit(0,x)

#define CHALT() if(gErrNum != 0){ if(!gErrQtMsg) printf(gErrMsg->c);return(NIL);}
#define assert(x,y)  { if(x==0){ Err_Raise(y); CHALT(); }}


//dict
#define Tag_CBEG 44
#define Tag_CEND 45
#define Tag_CIF 3
#define Tag_CELSE 33
#define Tag_CWHILE 5
#define Tag_CCVAR 6
#define Tag_CPAROPEN 7
#define Tag_CPARCLOS 8
#define Tag_CFUNC 9
#define Tag_CASSIGN 10
#define Tag_CINTEGER 2
#define Tag_CFLOAT 4
#define Tag_CLONG 3   //bug 3
#define Tag_COBJ 39
#define Tag_CVAROBJ 86
#define Tag_CCARESP 13
#define Tag_CARRAY 14
#define Tag_CENDPROGRAM 15
#define Tag_CCALC 16
#define Tag_CCARGS 17
#define Tag_CNULL 18
#define Tag_CREL 19
#define Tag_CEQ 20 //Equal
#define Tag_CGE 21 //Greater Equal
#define Tag_CLE 22 //Lower Equal
#define Tag_CGT 23 //Greater Than
#define Tag_CLT 24 //Lower Than
#define Tag_CAND 25
#define Tag_COR 26
#define Tag_CDEF 27
#define Tag_CSEQ 28
#define Tag_CCOMMAND  29
#define Tag_CCOMMANDS  30
#define Tag_CCBOOL  31
#define Tag_CRETURN  32
//#define Tag_CCVARMOV  33
#define Tag_CCBREAK  34
#define Tag_CCDECLINT  35
#define Tag_CCDECLCHAR  36
#define Tag_CCDECLFLOAT  37
#define Tag_CCDECLOBJ  38
#define Tag_CCDECLLONG 87
#define Tag_CCHAR1  1
#define Tag_CCLASS  40
#define Tag_CENDCLASS  41
#define Tag_CCLASSBODY  42
#define Tag_CDECLVAR  43
#define Tag_CNEW  46
#define Tag_CLASSATTRIB  47
#define Tag_CLASSMETHOD  48
#define Tag_CALLFUNC  49
#define Tag_CNEWCLASS  50
#define Tag_CNEWARRAY  51
#define Tag_CNEWTOOBJ  52
#define Tag_CASSIGNLOC  53
#define Tag_CASSIGNATR  54
#define Tag_CLASSATTRIBARRAY  55
#define Tag_CCVARARRAY  56
#define Tag_CENDDEF  58
#define Tag_CENDIF  59
#define Tag_CENDWHILE  60
#define Tag_CDEFNATIVE  61
#define Tag_CSTRING  62
#define Tag_CTBAPPEND  63
#define Tag_CTBINSERT  64
#define Tag_CTBMODIFY  65
#define Tag_CTBREAD  66
#define Tag_CTBLOOP  67
#define Tag_CTBDELETE  68
#define Tag_CTBDECLWA  69
#define Tag_CTBDECLTB  70
#define Tag_CTBTABLE  71
#define Tag_CTBWA  72
#define Tag_CTO  73
#define Tag_CFROM  74
#define Tag_CIN  75
#define Tag_CLOOP  76
#define Tag_CAPPEND  77
#define Tag_CINSERT  78
#define Tag_CREAD  79
#define Tag_CMODIFY  80
#define Tag_CDELETE  81
#define Tag_CINDEX  82
#define Tag_CINTO  83
#define Tag_CNE 84
#define Tag_CENDLOOP 85

#define tag2_OADD  1
#define tag2_OSUBR  2
#define tag2_OMUL  3
#define tag2_ODIV  4
#define tag2_OIFFALSE  5
#define tag2_OEQ  6
#define tag2_OGT  7
#define tag2_OGTE  8
#define tag2_OLT  9
#define tag2_OLTE  10
#define tag2_OAND  11
#define tag2_OOR  12
#define tag2_OGOTO  13
#define tag2_OCALLF  14
#define tag2_OCALLNATV  15
#define tag2_ORET  16
#define tag2_ORETNULL  17
#define tag2_ONEW  18
#define tag2_OLOADC  19
#define tag2_OLOADV  20
#define tag2_OSTORV  21
#define tag2_OLOADVY  22
#define tag2_OSTORVY  23
#define tag2_OGLOADV  24
#define tag2_OGSTORV  25
#define tag2_OGLOADVY  26
#define tag2_OGSTORVY  27
#define tag2_OOCALLF  28
#define tag2_OOLOADV  29
#define tag2_OOSTORV  30
#define tag2_OOLOADVY  31   //Objeto - mo
#define tag2_OOSTORVY  32   //Objeto - move pilha para array
#define tag2_ONEWY  33      //New array
#define tag2_OEND  34       //Final de programa na função
#define tag2_CCOMMAND 29
#define tag2_CCOMMANDS 30
#define tag2_CCBOOL 31
#define tag2_CRETURN 32
//#define tag2_CCVARMOV 33
#define tag2_CCBREAK 34
#define tag2_CCDECLINT 35
#define tag2_CCDECLCHAR 36
#define tag2_CCDECLFLOAT 37
#define tag2_CCDECLOBJ 38
#define tag2_CCHAR1 1
#define tag2_CCLASS 40
#define tag2_CENDCLASS 41
#define tag2_CCLASSBODY 42
#define tag2_CDECLVAR 43
#define tag2_CNEW 46
#define tag2_CLASSATTRIB 47
#define tag2_CLASSMETHOD 48
#define tag2_CALLFUNC 49
#define tag2_CNEWCLASS 50
#define tag2_CNEWARRAY 51
#define tag2_CNEWTOOBJ 52
#define tag2_CASSIGNLOC 53
#define tag2_CASSIGNATR 54
#define tag2_CLASSATTRIBARRAY 55
#define tag2_CCVARARRAY 56
#define tag2_CENDDEF 58
#define tag2_CENDIF 59
#define tag2_CENDWHILE 60
#define tag2_CDEFNATIVE 61
#define tag2_CSTRING 62
#define tag2_CTBAPPEND 63
#define tag2_CTBINSERT 64
#define tag2_CTBMODIFY 65
#define tag2_CTBREAD 66
#define tag2_CTBLOOP 67
#define tag2_CTBDELETE 68
#define tag2_CTBDECLWA 69
#define tag2_CTBDECLTB 70
#define tag2_CTBTABLE 71
#define tag2_CTBWA 72
#define tag2_CTO 73
#define tag2_CFROM 74
#define tag2_CIN 75
#define tag2_CLOOP 76
#define tag2_CAPPEND 77
#define tag2_CINSERT 78
#define tag2_CREAD 79
#define tag2_CMODIFY 80
#define tag2_CDELETE 81
#define tag2_CINDEX 82
#define tag2_CINTO 83

//Arquivo
#define DOTBIC ".bic"
#define DOTRVM ".rvm"
//fim dict

//tipos básicos
typedef unsigned char          U1;

// string 
struct _string {
  char *c;
  int tam;
  void (*mv)( struct _string *self, char * );
  int (*size)( struct _string *self);
  BOOL (*isNull)( struct _string *self);
  BOOL (*cmp)( struct _string *self, struct _string *other);
  struct _string *(*concat)( struct _string *self, struct _string *other);
  struct _string *(*mid)(struct _string *self, int ini, int len);
  struct _string *(*trim)(struct _string *self);
  int (*asc)(struct _string *self);
  struct _string *(*ucase)(struct _string *self);
  struct _string *(*lcase)(struct _string *self);
  BOOL (*isnum)(struct _string *self);
};
 
typedef struct _string * string ;

string newString(char *c);
int string_size(string self);
BOOL string_isnull(string self);
BOOL string_cmp(string self, string other);
string string_concat(string self, string other);
void string_mv(string self, char *);
string string_mid(string self, int ini, int len);
string string_trim( string self );
int string_asc(string self);
string string_ucase(string self);
BOOL string_isnum(string self);
string string_int_str(int i); 
string Replace(string s, string f, string v);
string string_lcase(string self);
int string_str_int(string s);
string string_replace(string s, string f, string v);

//node
struct _node {
    struct _node **mFilhos;
    int id;
    int idClass;
    int tipo;
    string valor;
    int linha; 
    int idConst; 
    int validtipo; 
    string validnomeobj;
    BOOL isAttribute;
    BOOL isArrayCall;
    BOOL isArray;
    int idxArray;
    BOOL isNative;
    int qtdFilhos; 
    void (*initFilhos)(struct _node *self, int p1);
    void (*putFilho)(struct _node *self, int p1, struct _node *p2);
    struct _node * (*getFilho)(struct _node *self, int p1);
};

typedef struct _node * node;

void node_initFilhos(node self, int p1);
void node_putFilho(node self, int p1, node p2);
node node_getFilho(node self, int p1);
BOOL isNothing( node n );
node newNode();

// Fim node

// Início Token

struct _token{
      string valor;
      int tipo;
      string erro;
      int linha;
};

typedef struct _token * token;

token newToken();

// Fim token 

//// Parse
//símbolos
struct _mc {
  string s;
  int i;
};

typedef struct _mc mc;

//*
struct _ElemAssign{
  string ldEsq1;
  int    ldEsq1Tipo;
  string ldEsq1Cls;
  BOOL   ldEsq1Gbl;
  int    ldEsq1Id;
  string ldEsq2;
  int    ldEsq2Tipo;
  string ldEsq2Cls;
  string atribConst;
  string funcObj;
  int    funcObjTipo;
  string funcObjCls;
  BOOL   isArray;
  node   oIdxArray;
};

typedef struct _ElemAssign * ElemAssign;

//*
//Parsef

void initParse(string p1, BOOL bMoveTok);
string Parse();
node createNode(token p1); 
node createNode1(int p1); 
token getToken(); 
BOOL isNumber(string c); 
BOOL isNumberFloat(string c, int *p1); 
BOOL isLetter(string c); 
int isCommand(string p1); 
void moveToken();  
string tg(int p1);  
BOOL matchToken(string p1); 
BOOL matchTokenMsg(string sp1, string pErr); 
BOOL matchTokenWMoveMsg(string p1, string pErr); 
BOOL matchTokenType(int p1); 
BOOL matchTokenTypeMsg(int p1, string pErr); 
BOOL matchTokenTypeWMoveMsg(int p1, string pErr); 
node Class(); 
node ClassBody(); 
node Def(BOOL pbIsNative);
node Decl();
node Stmts();
node Seq(node p1, node p2);
node wordIf(int p0, node p1, node p2);
node wordElse(int p0, node p1, node p2, node p3);
node wordWhile(int p0, node p1, node p2);
node wordFunc(int p0, string p1, node p2);
node wordDef(int p0, string p1, node p2, node p3)  ;
node wordBreak(int p0);
node wordDecl(int p0);
node tbAppend();
node tbInsert();
node tbDelete();
node tbModify();
node tbRead();
node tbLoop();
ElemAssign assignGetLdEsq();
node assignNewArray(ElemAssign pAgn);
node callFunctionObj(string pParte1, string pParte2);
node callFunction(string pTokenValor, int pTokenTipo);
node assignVar(ElemAssign pAgn);
node Bool( BOOL pCalledByFunc  );
node RelOr(BOOL pCalledByFunc);
node RelCmpEq(BOOL pCalledByFunc);
node RelEq(BOOL pCalledByFunc);
node CalcMais(BOOL pCalledByFunc);
node CalcVezes(BOOL pCalledByFunc);
node CalcFator(BOOL pCalledByFunc);
node getTerm(BOOL pCalledByFunc);
node pegaArgs(BOOL pFirst);
node pegaParDef(BOOL pFirst);
node list2Lang(node p1);
string emit2Lang2(node p1);
string putC(string p1, BOOL bEnter);
string calcSimbol(string p1);
int getIdS(string p0, int ptipo);
void bufferBytes(unsigned char b);
void initBufferBytes();
void validVarAssignMsg(int pidFunc, string pNomeVar, string pNomeClass);
void validVarAssignObjMsg(int pidFunc, string pNomeVarE, string pNomeVarD);
int getId(string p0, int pObjTipo);
int getIDF(string p0);
node Stmt();
void validVarMsg(string pvar, string pmsg);
int getIdVarFunc(int pidFunc, string pNome);;

//Array

struct _array{
       int len;
       int size_tipo;
       unsigned char * obj;
};
typedef struct _array * array;
unsigned char * redim( array ar, int tamarray, BOOL preserve);
array newarray(int size_tipo);

//Symbols
//;
// Estrutura de linhas do arquivo de class;
//;
// CTQ - quantidade de constantes;
// CT1 - dados a ser gravado;
// FQT - quantidade de funções;
// VGQ - quantidade de variáveis globais;
// FD1 - dados da função;
//  LV1 - variáveis da função;
//  BCI - binário;
//;
//;


//;
// Armazena id e variaveis de funcoes;
//;
////#define CNOME = 1;
//#define CVARIABLE 1
//#define CFUNCAO 2
//#define CCONST 3
//#define CTIPOPARIN 1
//#define CTIPOPAROUT 2
//#define CTIPOVAR 3

//;
//;
//#define CINTEGER 11
//#define CFLOAT 12
//#define CCHAR1 38
//;
//#define GLOBALS 1
//;
//;

struct _Variable{
  string  nome;
  int     tipo;
  int     isArray;
  int     arrayTam;
  BOOL    isParameter;
  string  nomeobj;
  BOOL    isnewok;//indica se já foi instanciada;
};

typedef struct _Variable Variable;

struct _Funcao{
  int       id;
  string    nome;
  int       qtdVar;
  int       parQtdVar;
  Variable *varLocal;
  array     array_varLocal;
  int       rettipo;
  string    retnomeobj;
  BOOL      retarray;
  node      retbool;
  int       ntamopcode;
  string    prgAssembly;
  BOOL      isNative;
  BOOL      isReturnOk; //indica que foi utilizado o campo RETURN;
};

typedef struct _Funcao Funcao;

struct _Elem{
  int       id;
  string    nome;
  int       objtp;
  Variable  var;
  Funcao    Funcao;
  int       tipoData; //usado para constantes;
  BOOL      bngrava; //não grava;
};

typedef struct _Elem Elem;

//-------------------------------------------;
//;
//           Gravação de Arquivos;
//;
//-------------------------------------------;

struct _tFilePrgTxt{ //utilizado para gravar arquivo texto;
  string  s1;
};

struct _QT{ //Constagem de itens;
  short int  qtdItem;
};
typedef struct _QT QT;
  
struct _CT1{  //Constantes;
  short int  id;
  short int  tipoData;
  short int  tam;
  string     nome;
};
typedef struct _CT1 CT1;

struct _CL1{
  short int    iqtdcons;
  short int    iQtdFunc;
  short int    iqtdvglo;
  string       sNome;
};
typedef struct _CL1 CL1;

struct _FD1{ //Definição de Funções;
  short int    id;
  short int    qtdVar;
  short int    parQtdVar;
  short int    rettipo;
  short int    retarray; //byte;
  short int    ntamopcode;
  short int    ntamstack;
  short int    byteop; //tamanho do stack;
  short int    isNative; //byte;
  string nome; //Grava sempre 2 bytes com o tamanho da string;
  string retnomeobj;
};
typedef struct _FD1 FD1;

struct _LV1{ //Variáveis;
  short int     id;
  unsigned char tipo;
  unsigned char isArray;
  short int     tamArray;
  unsigned char isParameter;
  string        nomeobj; //2bytes com o tamanho da string;
  string        nome;    //2bytes com o tamanho da string;
};
typedef struct _LV1 LV1;

node wordReturn(int p0, node p1);
node assignGetLdDir(ElemAssign pAgn);
node assignNewObj(ElemAssign pAgn);
node RelCmp(BOOL pCalledByFunc);
string putC(string p1, BOOL bEnter);
unsigned char getOpCod(int p1);
string getOpNome(int p1);
unsigned char getOpCodByName(string p1);
void validFuncMsg(string pNomeFunc, string pmsg);
void validFuncMsg2(string pNomeFunc, string pmsg);
void validFuncChamadaMsg(string pReplace, string pNomeFunc, node b);
string validFuncLocalParBase(int pCtxFuncId, string pNomeFunc, string pReplace, node pNoPar);
void validVarAssignObjNewMsg(int pidFunc, string pNomeVarE, string pNomeVarEClass, string pNomeClass);
void validAssignTipoCalcMsg(int pTipoE, int pTipoD);
void validObjIsInstanceadMsg(int pidFunc, string pNomeVarE);
void validFuncReturnOk(int pCtxFuncId, string pnomef, BOOL pcheckret, int ptipo, string pclass, BOOL parray);
int pegaTipoVar(int pidFunc, string pNomeVar, string pNomeClass, string *pclass, int *pId, BOOL *pbGlobal, BOOL *pisArray);
BOOL pegaVarFuncClass(int pidFunc, string pNomeVar, string pNomeClass, Variable *pvar, BOOL pNewOk, int * pId, BOOL * pbGlobal, BOOL * pisArray);
int getStackCodByName(string p1);
BOOL validIsWorkArea(string s1, int pi);
BOOL validIsTable(string s1, int pi);
int rput(FILE *pfp, unsigned char *pv ,string pid);
int read(FILE *pfp, unsigned char *pv ,string pid);
int read2(FILE *pfp,unsigned char * pdata,string pid, int tam);
void rquit(int pErr, string s);
BOOL pegaRetFunc(string pNomeFunc, int * ptipo, BOOL * pisArray, string pclass, BOOL * pIsNative);
BOOL ReadClass(string pNome);
BOOL validFuncBase(string pNomeFunc);
BOOL validVarBase(int pFuncId, string pvar);
int getIdElem(string p0, int pObjTipo);
void putReturnOk(int pCtxFuncId , node pbool);
int pegaIdFunc(string pNomeFunc);
int pegaIdFunc2(string pNomeFunc);
int putConst(string pNome, int ptipo);
int putFunc(string pNome, int ptipo, string pNomeObj, BOOL pisArray, BOOL pbIsNative);
int putVar(string pNome, int ptipo, BOOL pisArray, int pArrayTam, string pNomeClass);
int putVarFunc(int pId, int pTipoLoc, string pNomeVar, int pTipoVar, BOOL pisArray, int pArrayTam, string pNomeClass);
int validFuncReturnOkBase(int pCtxFuncId,BOOL pcheckret, int ptipo, string pclass, BOOL parray);
int validObjIsInstanceadBase(int pidFunc, string pNomeVarE);
int validVarAssignObjBase(int pidFunc, string pNomeVarE, string pNomeVarD);
int validVarAssignObjNewBase(int pidFunc, string pNomeVarE, string pNomeVarEClass, string pNomeClass);
string getAssembly();
void mv_pt_arr_3(char *o, char *d);
void putNomeClass(string pNome);
void putFuncClass(string pNomeClass, Funcao tfunc);
string readall();
void initFuncao(Funcao *f);
void initElem(Elem *e);
void initVar(Variable *v);
void initParseToken(string p1);
void initEnvironment();
void lg1(string s);
void lg2(string s);
//void CHALT();
void debug(node n);
void imprimeByteCode();

//////
/// Variaveis
//////
unsigned char *mBuffer;
array         array_mbuffer;
int           gQtdBuffer;

// Simbolos;
array  marray_sym;
Elem  *mSymbols;
int    gQtdSymbols;

//Arquivos
FILE  *gGravaFp;
FILE  *gReadFp;

//
mc mCommand[CQTDCOMAND][2];
mc mMaqCommands[CMAQCOMMANDS][3];

//
int     gQtdVar;
int     gQtdFunc;     //válido para qualquer função que entrar na tabela;
int     gQtdFuncId;   //válido para funções que são consideradas no array de localizacao da classe;
int     gQtdFuncClass;
int     gQtdConst;
string  gNomeClass_;

//
string  mTexto;
int     mIdx;
int     mTam;
token   gToken;
node    gProg;
int     mLinha;
int     gFuncId;
string  g2Lang;
int     g2Line;
BOOL    g2NumeraLinha;

//
int    gidebug;
int    gdebuglg2;
int    gdebugnode;
string gPath;
string gExtSource;
string gExtComp;
string gFileSource;

//Err
int    gErrNum;
int    gErrQtMsg;
string gErrMsg;



