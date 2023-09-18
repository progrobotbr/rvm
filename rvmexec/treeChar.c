#include "zzdata.h"
#include "zzfuncdecl.h"

void * initTreeChar(){
  return(0);    
}  
  
void * findTreeChar(char *c, TREENODE **self){
  CBOOL bok;
  TREENODE *lmm, *lma;
  /*printf("\ntree");*/
  
  lmm = *self;
  
  if(*self==0){
    return(0);  /*a árvore não foi criada */
  }
                     
  while(*c!='\0'){
    /*printf("\ntree");*/
    bok=CFALSE; 
    if(lmm->up != 0){
      //lmm=lmm->next;
    }                       
    while(lmm != 0){
      if(*c == lmm->c){
        lma=lmm;    
        lmm=lmm->down;
        bok=CTRUE;
        break;            
      }else{
        lmm = lmm->next;
      }      
    }
    if(bok==CFALSE){
       return(0);             
    }
    c++;                                                      
  }
  if(bok==CTRUE){
    if(lma->val != 0){             
      return(lma->val);
    }else{
      return(0);    
    }  
  }else{
    return(0);
  }                   
}
  
CBOOL putTreeChar(char *c, void *data, TREENODE **self){
  CBOOL bok; 
  CBOOL bfirst; 
  CBOOL bdesc;
  TREENODE *lmm, *lma, *lmt;
  /*self = pself;*/
  lmm = *self;
  lma = *self;
  bfirst = CTRUE;
  /*bdesc = CFALSE;*/
  /*printf("putree");*/
  while(*c!='\0'){
    bok = CFALSE; 
    
    if(lmm==0){
      bfirst=CFALSE;
      lmm = createTreeNode(' '); 
      *self = lmm;
      lmm->next = createTreeNode(*c);
      lma=lmm;
      lmm = lmm->next;
      //lmm->prior = '\0';
      lmm->prior = lma;
      lmm->down = createTreeNode(' '); 
      lmt=lmm->down;
      lmt->up = lmm;
      lmm = lmt;
      c++;
      bok = CTRUE;
      continue;
    }else{
      //if(lmm->up != 0 && lmm->next != 0){  //bug 8 comentei 
        //lmm=lmm->next; //bug 8 comentei 
      //} //bug 8 comentei 
    }               
   
    while(1){
      if(*c==lmm->c){   /* igual */  /*r = r*/
        lma = lmm;
        lmm = lmm->down; 
        bok = CTRUE;
        break;             
      }else if(*c<lmm->c){ /* menor */ /* r < s*/
        lma = lmm->prior;
        if(bfirst == CTRUE){
          lmt = createTreeNode(*c);
          lmt->down = createTreeNode(' ');
          lmt->next = lmm; //
          lmm->prior = lmt;
          
          lma->next = lmt;
          lmt->prior = lma;
          
          lmm = lmt->down;
          lmm->up = lmt;  
         
          //bug 8
          //lmt->next = (*self)->next;
          //lma = *self;
          //lma->next = lmt;
          //lmt->prior = lma;
          //lma = lmt;
          //bug 8
          
          bok = CTRUE; 
          break;
        }else if(lmm->up==0){
          lmt = createTreeNode(*c);
          lma = lmm->prior;
          lma->next = lmt;
          lmt->prior = lma;
          lmt->next = lmm;
          lmm->prior = lmt;
          lmt->down = createTreeNode(' ');
          lmm = lmt->down;
          lmm->up = lmt;
          lma = lmt;
          bok = CTRUE;  
          break;         
        }else{       
          lmm = lmm->next;
        }      
      }else{
         if(lmm->next!=0){
           lmm = lmm->next;
         }else{                   
           lmt = createTreeNode(*c);
           lma = lmt;
           lmt->down = createTreeNode(' ');
           lmm->next = lmt;
           lmt->prior = lmm;
           lmm = lmt->down;
           lmm->up = lmt;
           //lmm = lmt->down; bug 8
           bok = CTRUE;
           break;  
         }
       }
    }  
    c++; 
    bfirst=CFALSE;                              
  }   

  if(bok==CTRUE){
    lma->val = data;
  }else{
    return(CFALSE);    
  }       
  return(CTRUE);           
} 

TREENODE *createTreeNode(char c){
  TREENODE *tn = ymalloc(sizeof(TREENODE));
  tn->c = c;
  tn->next = 0;
  tn->down = 0;
  tn->up=0;
  tn->prior=0;
  tn->val=0;
  return(tn);       
} 
