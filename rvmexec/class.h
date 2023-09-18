

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

CCLS * createInstance(char *pnome, TREENODE *pclassbase, ADMem *pdamem);
TFUC * getFuncClassByIndex(TCLS *pcb, int index);
TFUC * getFuncClassByName(TCLS *pcb, char *pnome);
VAR * getAttribClass(char *pnome, long pindex);
char * getConstante(TCLS *cb, int pindex);

