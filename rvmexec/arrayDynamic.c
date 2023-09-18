#include "zzdata.h"
#include "zzfuncdecl.h"

ADMem *createADMem(long tamini){
   ADMem *m =  zmalloc(sizeof(ADMem));      
   m->mem = zmalloc(sizeof(CCLS)*tamini);
   m->tam = tamini;
   m->index = -1;
   return(m);
}

CCLS *createADMItem(ADMem self){
   CCLS *m =  zmalloc(sizeof(CCLS)); 
   return(m);
}

int resizeADMem(ADMem *self){
   
   long l, lnew, lold;
   CCLS *mem, *itemold, *itemnew;
   
   lold=lnew=self->tam;
   itemold=self->mem;
   
   lnew = ( lnew * 3 ) / 2;
   itemnew = zmalloc(lnew*sizeof(CCLS));
   if(itemnew == 0){
     return(0);
   }
   
   mem = itemnew;
   
   for(l=0;l<lold;l++){

     if(itemold->isActive==1){
        *itemnew=*itemold;    
        //printf("mem %i\n", itemnew->id);               
        itemnew++;
     }
     itemold++;                   
   }
   
   self->tam = lnew;
   zfree(self->mem);
   self->mem=mem;
}

CCLS *appendADMItem(ADMem *self){
   long l; 
   CCLS * item;
   
   l = self->index;
   l++;
   if(l>=self->tam){
     if(resizeADMem(self)==0){
       return(0);                 
     }
   }
   
   self->index=l;
   item=self->mem+l;
   item->id=l+1; //o id sempre começará do 1 
   item->isActive=1;
   
   return(item);
}
    
CCLS *findADMItemByKey(ADMem *self, long pid){
   long l,lini,lfim,ltam;
   CCLS *item, *itemini, *itemfim;
   
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
     //item=self->mem+l;
     item = itemini+l;
     if(pid > item->id){
       itemini += l;
       lini += l;
     }else{
       itemfim -= l;    
       lfim -= l;
     }
                       
   }                
   return(0);
}

void deleteADMem(ADMem *self){
   zfree(self->mem);
   zfree(self);
}

/*Deleta somente virtual*/
void deleteADMItem(ADMem *self, long pindex){ 
  CCLS *item;
   
  if(pindex>self->tam){
    return;              
  }
  
  item = self->mem+pindex;    
  item->isActive = 0;
  
}

