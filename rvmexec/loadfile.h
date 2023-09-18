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
  S1 id;
  U1 tipo;
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
