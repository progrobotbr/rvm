

//Tipo Básico
typedef struct {
        
   unsigned char tipo;  
   unsigned char isArray;
   short int     sizeArray;
   unsigned char *mem;
   
   union {   
     char c;      
     short int i;
     long int l;  
     double f;
     long int obj;
     char *ca;
     short int *ia;
     long int *la;
     double *fa;
     long int *obja;
  };
  
} Var;

void initVar(Var *pv, unsigned char tipo, unsigned char isArray, short int sizeArray);
void copyVar(Var *o, Var *d);
void moveVar(Var *o, Var *d);
void deleteVar(Var *self);
Var *createVar();

