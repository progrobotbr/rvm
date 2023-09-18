#include "tiposbasicos.h"
#include "loadfile.h"
#include "arrayMalloc.h"

ArrayMalloc *createArrayMalloc(long tamini){
   ArrayMalloc *m =  malloc(sizeof(ArrayMalloc));      
   m->mem = malloc(sizeof(PPMEM)*tamini);
   m->tam = tamini;
   m->index=-1;
   return(m);
}

CBOOL resizeArrayMalloc(ArrayMalloc *self){
   
   long l, lnew, lold;
   PPMEM * mem, *itemold, *itemnew;
   
   lold=lnew=self->tam;
   itemold=self->mem;
   
   lnew = ( lnew * 3 ) / 2;
   
   itemnew = malloc(lnew*sizeof(PPMEM));
   if(itemnew == 0){
     return(CFALSE);
   }
   
   mem = itemnew;
   
   for(l=0;l<lold;l++){
     *itemnew=*itemold;                   
     itemnew++;
     itemold++;                   
   }
   
   free(self->mem);
   self->mem=mem;
   self->tam=lnew;
   
   return(CTRUE);
}

/*CBOOL appendArrayMalloc(ArrayMalloc *self, PPMEM item){*/
void * safeMalloc(ArrayMalloc *self, int ptam){
   long l; 
   PPMEM *mem;
   void *item;
   
   if(ptam <=0){
     return(0);      
   }
   
   /* pega memória */
   item = malloc(ptam);
   if(item == 0){
     return(item);     
   }
           
   l = self->index;
   l++;
   if(l>=self->tam){
     CASSERT(resizeArrayMalloc(self),CFALSE);
   }
   self->index++;
   if(l==7){
     l=7;
   }        
   mem = self->mem;
   mem=mem+l;
   *mem = item;
   return(item);
}

CBOOL appendArrayMalloc(ArrayMalloc *self, void *item){
   long l; 
   PPMEM *mem;
   
   l = self->index;
   l++;
   if(l>=self->tam){
     CASSERT(resizeArrayMalloc(self),CFALSE);
   }
   self->index++;
   if(l==6){
     l=6;
   }        
   mem = self->mem;
   mem=mem+l;
   *mem = item;
   return(CTRUE);
}

void deleteArrayMalloc(ArrayMalloc *self, CBOOL ball){ 
  long i,l;   
  PPMEM *item;
  PPMEM obj;
  char *nome1;
  int j;
  printf("\nApagando:\n");
  if(ball == CTRUE){
    l=self->index;
    item = self->mem;
    for(i=0;i<l;i++){
       j=l;
       printf("\nTeste:");printf("%i",i);   
       obj = *item;  
       nome1 = obj;            
       printf(nome1);printf("\n");              
       free(obj);
       item++;
    }
  }
  
  /*free(self->mem);*/
  /*free(self);*/
  
}
