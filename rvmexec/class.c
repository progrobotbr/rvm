#include "zzdata.h"
#include "zzfuncdecl.h"

CCLS * createInstance(char *pnome, TREENODE *pclassbase, ADMem *pdamem){
    int i,t;
    TCLS *cb;
    CCLS *ci;
    TVAR *tv;
    VAR *v;
    cb = findTreeChar(pnome, &pclassbase);
    CASSERT(cb!=0, 0);
    
    //debug
    //if(strcmp(pnome,"PRINT")==0){
    //  ccbb = cb;                           
    //}

    //ci = appendADMItem(pdamem);
    ci = zmalloc(sizeof(clazz));
    gMvm.GCMem->mark2(ci,GCNORELEASE);
    
    /* Tratamento de atributos */
    t  = cb->qatrib;
    ci->qatrib = 0;
    tv = cb->atrib;
    if(t>0){
      ci->atrib = zmalloc(sizeof(VAR)*t);
      gMvm.GCMem->mark2(ci->atrib,GCNORELEASE);
      ci->qatrib = t;
      CASSERT(ci->atrib!=0, 0);
      v = ci->atrib; 
      for(i=0;i<t;i++){
        v->tipo=0;
        v++;
      }
      v = ci->atrib;   
    }
    for(i=0;i<t;i++){
       createVARfromTVAR(v, tv);
       v++; tv++;              
    }
    
    ci->cb = cb;
    gMvm.GCMem->mark2(ci,GCRELEASE);
    if(ci->qatrib>0){
      gMvm.GCMem->mark2(ci->atrib,GCRELEASE);
    }
    return(ci);
}

void assignInstanceVar(VAR *pvar, CCLS * pci){
   pvar->tipo = COBJ;
   pvar->isArray = CFALSE;
   pvar->tamArray = 0;
   //pvar->o = pci->id;
   pvar->o = (clazzptr) pci;
}

int assignInstanceVarArray(VAR *pvar, CCLS * pci, int pidxarray){
   CASSERT(pidxarray>= pvar->tamArray, 1); 
   pvar->oa[pidxarray] = pci;
   return(0);
}

int op_CreateInstance(char *pnome, VAR *pv){
  int rc;
  TCLS *cb;
  CCLS *ci;
  
  cb =  findTreeChar(pnome, &gMvm.memcb);
  if(cb==0){
    //printf(pnome);
    //printf("\n");
    rc = loadClass(pnome, &cb);
    //printf("-fdf");
  
    CASSERT(rc==0, 1);            
    rc = putTreeChar(pnome, cb, &gMvm.memcb);
    CASSERT(rc==CTRUE, 2);
  }
  ci = createInstance(pnome, gMvm.memcb, gMvm.memci);
  CASSERT(ci!=0, 3);     
  
  assignInstanceVar(pv, ci);
  return(0);
}

int createVARfromTVAR(VAR *v, TVAR *tv){
  int i,t,y;
  char      *ca;
  int       *ia;
  long      *la;
  double    *fa;
  void      **oa;
  VAR *px1, rs, v1;
          
  //t = v->tipo = tv->tipo;
  t = tv->tipo;
  v->isArray  = tv->isArray;
  y = v->tamArray = tv->tamArray;
  v->nomeobj  = tv->nomeobj;
  
  if(tv->isArray == CTRUE){
    v->oa = '\0';             
    switch(t){
        case CRCHAR:
          ca = v->ca = zmalloc(sizeof(char)*y);
          for(i=0;i<y;i++){
            *ca = ' ';
            ca++;               
          }                 
          break;
        case CINTEGER:
          ia = v->ia = zmalloc(sizeof(int)*y);
          for(i=0;i<y;i++){
            *ia = 0;
            ia++;               
          }                 
         break;
        case CLONG:
          la = v->la = zmalloc(sizeof(long)*y);
          for(i=0;i<y;i++){
            *la = 0;
            la++;               
          }                 
          break;
        case CFLOAT:
          fa = v->fa = zmalloc(sizeof(double)*y);
          for(i=0;i<y;i++){
            *fa = 0;
            fa++;               
          }                 
          break;
        case COBJ:
          //oa = v->oa = zmalloc(sizeof(long)*y);
          oa = v->oa = zmalloc(sizeof(clazzptr)*y);
          for(i=0;i<y;i++){
            *oa = '\0';
            oa++;               
          }                 
          break;  
    }
  }else{
     switch(t){
       case CRCHAR:
          v->c=' ';
          break;
        case CINTEGER:
          v->i=0;
          break;
        case CLONG:
          v->l=0;
          break;
        case CFLOAT:
          v->f=0;
          break;
        case COBJ:
          v->o=0;
          break;
        case CTBTABLE:
          
          i = op_CreateInstance("BSTABLE", &rs);
          v->o = rs.o;
          v->tipo = COBJ;
          px1 = getAttribClass("BSTABLE.SELF", rs.o);
          if(px1==0){
            //ERR_RAISE(grc);     
          }else{
            v1.t=(void *)createTbObj();
            v1.tipo = CTBTABLE;
            moveVar(&v1, px1);
          } 
          return; 
          break;      
     }   
  }
  v->tipo = t;      
} 

void initVarOBJ(VAR *v, clazzptr l){
  v->tipo = COBJ;
  v->isArray = CFALSE;
  v->tamArray = 0;
  v->o = l;     
}

TFUC * getFuncClassByIndex(TCLS *pcb, int index){
   CASSERT(index<=pcb->qfunc, 0);
   //printf("clxbyidx0\n");
   return(pcb->func+index);
}
   
TFUC * getFuncClassByName(TCLS *pcb, char *pnome){
  TFUC *tf;
  tf = findTreeChar(pnome, &pcb->ffunc);
  return(tf);
}

VAR * getAttribClass(char *pnome, clazzptr pindex){
  char *c;
  VAR *v;
  TCON *cn;
  CCLS *ci;
  TCLS *cb;
  TVAR *tv;
 
  grc = 0; 
  /* ajusta nome => header.idade, muda para idade*/
  c=pnome;
  c=strchr(c,'.');
  c++;
  /*
  while(*c!='\0'){
    if(*c=='.'){
      c++;
      break;
    }
    c++;          
  }
  */
  ci = 0;
  //ci = findADMItemByKey(gMvm.memci, pindex);
  ci=pindex;
  if(ci==0){
    grc=41;        
    return(0);        
  }
  cb=ci->cb;
  tv = findTreeChar(c, &cb->fatrib);
  if(tv==0){
    grc=42;        
    return(0);        
  }
  
  v=0;          
  v = ci->atrib+tv->id;
  if(v==0){
    grc=43;       
  }         
  return(v);
}

/**** CONSTANTES ****/
char * getConstante(TCLS *cb, int pindex){
  TCON *tcon;
  tcon = cb->cons+pindex;
  //ipause++;
  //if(strcmp("PRINT",cb->nome)==0){
    //printf("xxxx %s\n",cb->nome);
  //}
  //if(ipause==651139){
    //ipause=651139;
    //return("");
  //}
  return(tcon->nome);
} 

/*** malloc ***/
/*
void * zmalloc(unsigned long l){
  void * ll;
  LM+=l;
  ll = MHEAPPOINT;
  MHEAPPOINT+=l+1;
  //printf("\nv%i\n",LM);
  //if(LM==107366){
  //  LM=107366;
  //}
  if(LM>1000000000){
    printf("\nv%i\n",LM);
    system("PAUSE");                  
  }
  //return(ymalloc(l));
  return(ll);
}

void * zrealloc(void *p, unsigned long l){
  void * ll;
  LM+=l;
  ll = MHEAPPOINT;
  MHEAPPOINT+=l+1;
  //printf("v%i\n",LM);
  if(LM==107366){
    LM=107366;
  }
  //return(ymalloc(l));
  return(ll);
}

void zfree(void *p){
}
*/               
