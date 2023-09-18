#include "arraymem.h"

ArrayMem *createArrayMem(long tamini){
   ArrayMem *m =  malloc(sizeof(ArrayMem));      
   m->mem = malloc(sizeof(ArrayItem)*tamini);
   return(m);
}


ArrayItem *createArrayItem(){
   ArrayItem *m =  malloc(sizeof(ArrayItem));      
   return(m);
}

int resizeArray(ArrayMem *self){
   
   long l, lnew, lold;
   ArrayItem *mem, *itemold, *itemnew;
   
   lold=lnew=self->tam;
   itemold=self->mem;
   
   lnew = ( lnew * 3 ) / 2;
   
   itemnew = malloc(lnew*sizeof(ArrayItem));
   if(itemnew == 0){
     return(0);
   }
   
   mem = itemnew;
   
   for(l=0;l<lold;l++){

     if(itemold->isActive==1){
        *itemnew=*itemold;                   
        itemnew++;
     }
     itemold++;                   
   }
   
   free(self->mem);
   self->mem=mem;
}

ArrayItem *appendArrayItem(ArrayMem *self){
   long l; 
   ArrayItem * item;
   
   l = self->index;
   l++;
   if(l>=self->tam){
     return(0);                 
   }
   
   self->index=l;
   item=self->mem+l;
   item->id=l; 
   item->isActive=1;
   
   return(item);
}
    
ArrayItem *findItemArrayByKey(ArrayMem *self, long pid){
   long l,lini,lfim,ltam;
   ArrayItem *item, *itemini, *itemfim;
   
   if(self->tam==0){
      return(0);              
   }
                    
   ltam=self->tam;
   lini=0;lfim=self->index;
   itemini = self->mem+lini;
   itemfim = self->mem+lfim;
   
   while(1){
     if(itemini->id == pid){ 
       if(itemini->isActive == 1)
         return(itemini);
       else
         return(0);
     }else if(itemfim->id == pid){ 
       if(itemfim->isActive == 1)
         return(itemfim);
       else
         return(0);
     }
     /*divide*/
     l=lfim-lini;
     l=l/2;
     if(l==0){
       break;       
     }         
     item=self->mem+l;
     if(pid > item->id){
       lini = lini+l;          
     }else{
       lfim = lfim-l;    
     }
                       
   }                
   return(0);
}

void deleteArray(ArrayMem *self){
   free(self->mem);
   free(self);
}

/*Deleta somente virtual*/
void deleteArrayItem(ArrayMem *self, long pindex){ 
  ArrayItem *item;
   
  if(pindex>self->tam){
    return;              
  }
  
  item = self->mem+pindex;    
  item->isActive = 0;
  
}
