
#include "var.h"
#include "tipos.h"
/*
** Iniciliza variavel e passa para objeto
*/

void initVar(Var *pv,
             unsigned char tipo,
             unsigned char isArray,
             short int     sizeArray){
                  
    //Var *v1=(Var *)malloc(sizeof(Var));
    
    pv->tipo = tipo-1;
    pv->isArray = isArray;
    pv->sizeArray = sizeArray;
    
    if(isArray){
      switch(tipo){
        case CCHAR:
          pv->ca = malloc(sizeof(char)*sizeArray);
          pv->mem = (U1 *) pv->ca;
          break;
        case CINT:
          pv->ia = malloc(sizeof(short int)*sizeArray);
          pv->mem = (U1 *) pv->ia;
          break;
        case CLONG:
          pv->la = malloc(sizeof(int)*sizeArray);
          pv->mem = (U1 *) pv->la;
          break;
        case CFLOAT:
          pv->fa = malloc(sizeof(double)*sizeArray);
          pv->mem = (U1 *) pv->fa;
          break;
      }
    }
//    return(v1);
}

void deleteVar(Var *self){
  free(self->mem);
  free(self);    
}

Var *createVar(){
  Var *v=(Var*)malloc(sizeof(Var));
  return(v);
}

Var *createVarMany(int i){
  Var *v=(Var*)malloc(sizeof(Var)*i);
  return(v);
}

Var getVarArray(Var *o, int i){
  Var v;
  v.tipo = o->tipo;
  v.isArray=FALSE;
  switch(o->tipo){
    case CCHAR:
      v.c = *(o->ca+i);
      break;
    case CINT:
      v.i= *(o->ia+i);
      break;
    case CLONG:
      v.l = *(o->la+i);
      break;
    case CFLOAT:
      v.f = *(o->fa+i);
      break;
  }
  return(v);                
}

void copyVar(Var *o, Var *d){
     
  d->tipo = o->tipo;
  d->isArray = o->isArray;
  d->sizeArray = o->sizeArray;
    
  if(o->isArray){
                    
    d->mem=o->mem;            
    switch(o->tipo){
      case CCHAR:
        d->ca = o->ca;
        break;
      case CINT:
        d->ia = o->ia;
        break;
      case CLONG:
        d->la = o->la;
        break;
      case CFLOAT:
        d->fa = o->fa;
        break;
    }                     
           
  }else{
           
    switch(o->tipo){
      case CCHAR:
        d->c = o->c;
        break;
      case CINT:
        d->i = o->i;
        break;
      case CLONG:
        d->l = o->l;
        break;
      case CFLOAT:
        d->f = o->f;
        break;
    }
  }                     
}     


void moveVar(Var *o, Var *d){
     
  if(o->isArray){
                    
    free(d->mem);
    d->mem=o->mem;
    d->sizeArray = o->sizeArray;
        
    switch(o->tipo){
      case CCHAR:
        d->ca = o->ca;
        break;
      case CINT:
        d->ia = o->ia;
        break;
      case CLONG:
        d->la = o->la;
        break;
      case CFLOAT:
        d->fa = o->fa;
        break;
      }                     
             
   }else{
           
      switch(o->tipo){
        case CCHAR:
          switch(d->tipo){
            case CCHAR:
              d->c = o->c;   
              break;
            case CINT:
              d->i = o->c;  
              break;   
            case CLONG:
              d->l = o->c;                            
            case CFLOAT:
              d->f = o->c;                   
              break;      
          }
          break;
        case CINT:
          switch(d->tipo){
            case CCHAR:
              d->c = o->i;   
              break;
            case CINT:
              d->i = o->i;  
              break;   
            case CLONG:
              d->l = o->i;                            
            case CFLOAT:
              d->f = o->i;                   
              break;      
          }
          break;
        case CLONG:
          switch(d->tipo){
            case CCHAR:
              d->c = o->l;   
              break;
            case CINT:
              d->i = o->l;  
              break;   
            case CLONG:
              d->l = o->l;                            
            case CFLOAT:
              d->f = o->l;                   
              break;      
          }
          break;
        case CFLOAT:
          switch(d->tipo){
            case CCHAR:
              d->c = o->f;   
              break;
            case CINT:
              d->i = o->f;  
              break;   
            case CLONG:
              d->l = o->f;                            
            case CFLOAT:
              d->f = o->f;                   
              break;      
          }
          break;
     } 
   }                  
}     
