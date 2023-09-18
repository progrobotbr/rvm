#include "zzdata.h"
#include "zzfuncdecl.h"
/*
*  Garbage Collector
*    consiste de uma lista que contem as solicitações de memória
*
*
*/

//Adiciona elemento na lista
int GCCreateNodeMem(GCObj *self, void *pmem, unsigned long size){
  self->mempointer->next = ymalloc(sizeof(memnode));
  if(self->mempointer->next==GCNULL){
    return(GCFALSE);
  }
  self->mempointer = self->mempointer->next;
  self->mempointer->next = GCNULL;
  self->mempointer->mem = pmem;
  self->mempointer->usedmem = size+(sizeof(memnode));
  //debug
  //if(self->mempointer->usedmem==64013){
  //  printf("");                 
  //}
  return(GCTRUE);
}
//
void GCZmarkObj(GCObj *self, void *v){
  v--;
  //if( *((char *)v)==GCRELEASE ){
  //  *((char *)v) = GCREADY;  
  if( *((char *)v)==GCREADY ){
    *((char *)v) = GCRELEASE;  
  }
}

//Marca objeto para liberar memória
#define GCZmark(v)    v--;\
                      if( *((char *)v)==GCRELEASE ){\
                        *((char *)v) = GCREADY;\
                      }

//Libera a memória
void GCZfree(GCObj *self){
   int i=0;
   char *c;
   unsigned long lused=0, lfreed=0;
   memnode *pt, *pta;
   self->objQtd = 0;
   pta = self->memini;
   pt  = self->memini->next;
   /*
   for(long zzz=0; zzz<100000000; zzz++){
           printf("\nGC HERE\n");
   }
   */
   //printf("\nE1-");
   //self->print(self);
   //printf("--- free ---\n");
   while(pt!=GCNULL){
     c = (char *) pt->mem;
     if(*c==GCREADY){
       lfreed+=pt->usedmem;
       free(pt->mem);
       pta->next = pt->next;
       free(pt);
       i++;
     }else{
       pta = pt;
       lused+=pt->usedmem;
       self->objQtd++;   
     }
     pt = pta->next;
   }
   self->mempointer = pta;
   
   //printf("\nE2-");
   //self->print(self);
   //printf("free: %i  qtdobj: %i freed: %i used: %i usedreal: %i usedreal2: %i\n",i,self->objQtd, lfreed, lused, USEDMEM,USEDMEM2);
   //system("PAUSE");
} 

//Imprime a lista 
void GCPrintMem(GCObj *self){
  int i=1;
  char *c;
  memnode *pt, *pta;
  //printf("\nprint mem\n");
  pta = self->memini;
  pt  = self->memini;
  while(pt->next!=GCNULL){
    pt=pt->next;                     
    c = (char *) pt->mem;
    //if(pt->usedmem==1409){
    //  pt->usedmem=1409;                    
    //}
    printf("%i(%i)[%i]-",*c,pt->usedmem,i++);
  }
  printf("\n");
}   

//Aloca memória   
void *GCZmalloc(GCObj *self, unsigned long size, char ptipo){
  long l;
  char *c;
  void *v;
  
  //calcula o momento para o executar o garbage collector
  //printf("tracegc001\n");
  if(self->objQtd > GCQTDOBJINI){
    l = self->objQtd * GCPERINC;
    if(l > self->objLim){
      //printf("tracegc002\n");
      gMvm.garbage(&gMvm);
      l =  self->objQtd * GCPERINCMAX;
      self->objLim=l;
    }else{
      l = self->objQtd * GCPERINCMAX;
      if(self->objLim > l){
        self->objLim = l;
      }
    }
  }
  
  //inicia o processo de pegar memória
  self->objQtd++;
  //debug
  //if(self->objQtd==117){
  //  self->objQtd=117;                    
  //}
  
  USEDMEM2 += size+1+sizeof(memnode);
  v = ymalloc(size+1);
  if(v==GCNULL){
    //tenta limpar a gc para pegar memória
    //printf("tracegc001\n");
    gMvm.garbage(&gMvm);
    v = ymalloc(size+1);
    if(v==GCNULL){
      return(GCNULL);
    }
    l =  self->objQtd * GCPERINCMAX;
    self->objLim=l;
  }
  c  = (char *) v;
  *c = ptipo;
  if(self->createNode(self,v,size+1)==GCFALSE){
    return(GCNULL);
  }
  v++;
  return(v);
}

/*////////////////
**Funções base malloc
*/
void * zmalloc(unsigned long l){
  //if(gMvm.GCMem->objQtd > 9){
   //printf("tracegc\n");
  //}
  return( gMvm.GCMem->malloc(gMvm.GCMem,l,GCRELEASE) );  
}

void * zrealloc(void *p, unsigned long l){
  //if(gMvm.GCMem->objQtd > 9){
  //  printf("trace\n");
  //}
  return( gMvm.GCMem->malloc(gMvm.GCMem,l,GCRELEASE) );   
}

void zfree(void *p){
}

//Fase 1, coloca todos os objetos da lista em disponibilidade
//  depois com a função mark, os objetos serão salvos
//  free libera os objetos
//
//  fases:
//    fase1: dispose: marca todos como disponíveis
//    fase2: mark: marca individualmente os objetos que serão salvos
//    fase3: free: libera todos os objetos e ajusta a lista
//
void GCPutReadyAll(GCObj *self){
  char *c;
  memnode *pt;
  pt = self->memini;
  //printf("\nN1-");
  //self->print(self); 
  while(pt->next!=GCNULL){
    pt=pt->next;   
    c = (char *) pt->mem;
    if( *c==GCRELEASE ){
      *c=GCREADY;
    }
  }
}

CBOOL GCIsMarked(GCObj *self, void *v){
   --v;
   if( *((char *)v) == GCRELEASE){
     return(CTRUE);  
   }else{
     return(CFALSE);    
   }   
}

void GCMark2(void *v, int pFlag){
   --v;
   *((char *)v) = pFlag;
}

//int parada;
void GCGarbage(TMEMVM *pm){
  //parada++;
  //if(parada==4){
    //printf("aa");
    //return;          
  //}   
  GCPutReadyAll(pm->GCMem);
  GCTraverseFrame(pm->GCMem, pm->stackFrameMem, pm->stackFrame);
  GCZfree(pm->GCMem);

}

/*
** Inicia a memoria da VM
**
**  a treechar e stack frame não usam memória da garbage collector,
**    chamam malloc direto
**/
int initMEMVM(char *nameclass){
  //parada = 0;
  gMvm.GCMem = createGCObj();
  if(gMvm.GCMem==GCNULL){
    return(1);
  }
  
  gMvm.memcb = initTreeChar();  //Metadados das classes
  if(gMvm.memcb!=0){
    return(2);
  }
  gMvm.firstClass = nameclass;
  gMvm.garbage = &GCGarbage;
  //init stack
  gMvm.stackFrameMem = ymalloc(sizeof(TFRAME) * STACKTAM);
  if(gMvm.stackFrameMem==0){
    return(3);
  }
  gMvm.stackFrameFim = gMvm.stackFrameMem + STACKTAM - 1;
  gMvm.stackTam = STACKTAM;
  
  gMvm.stackFrame = gMvm.stackFrameMem;
  //fim stack
  
  return(0);
  
}

//Inicia lista
GCObj * createGCObj(){
  GCObj *go = ymalloc(sizeof(GCObj));
  if(go==GCNULL){
    return(GCNULL);                 
  }
  go->objQtd     = 0;
  go->objLim     = GCQTDOBJINI;
  go->createNode = &GCCreateNodeMem;
  go->free       = &GCZfree;
  go->malloc     = &GCZmalloc;
  go->mark       = &GCZmarkObj;
  go->print      = &GCPrintMem;
  go->disposeAll = &GCPutReadyAll;
  go->isMarked   = &GCIsMarked;
  go->mark2      = &GCMark2;
  go->mempointer = go->memini = ymalloc(sizeof(memnode));
  go->mempointer->next = GCNULL;
  return(go);
}

/*
****** GC Salva tabela
*/

void GCTraverseTable(GCObj *self, tableobj *tb){
  self->mark(self,tb);
  self->mark(self,tb->tb);
  GCTraverseNodeTable(self, tb->tb->root);
  //system("PAUSE");
}

void GCTraverseNodeTable(GCObj *self, node *n){
  int i;
  node *nn;
  if(n==0) return;
  if(n->leaf!=CFALSE){
    while(n!='\0'){
       self->mark(self,n);
       nn=n->child;
       while(nn!=0){
         self->mark(self,nn);
         //printf(" %i",nn->value);
         GCTraverseObject(self, nn->value);
         nn=nn->nextnode;           
       }
       n=n->nextnode;                
    }
  }else{
     while(n!='\0'){
       self->mark(self,n);
       GCTraverseNodeTable(self,n->child);
       n=n->nextnode;
     }
  }
}

/*
** Traverse Var 
*/
void GCTraverseVar(GCObj *self, VAR *v, int ptam){
  int i,ii, i1,itam;
  int qatrib;
  VAR *atrib;
  clazzptr *o1;
  
  if(ptam==0){
    return;
  }
  if(self->isMarked(self,v)==CTRUE){
    return;
  }
  
  self->mark(self,v);
  
  for(i=0; i<ptam; i++){
    if(v->isArray==CTRUE){
      if(v->tamArray > 0){                    
        switch(v->tipo){
          case CRCHAR:
            if(self->isMarked(self,v->ca)==CFALSE){
              self->mark(self,v->ca);
            }
            break;
          case CINTEGER:
            if(self->isMarked(self,v->ia)==CFALSE){
              self->mark(self,v->ia);
            }
            break;
          case CFLOAT:
            if(self->isMarked(self,v->fa)==CFALSE){
              self->mark(self,v->fa);
            }
            break;
          case COBJ:
            if(self->isMarked(self,v->oa)==CFALSE){
              //self->mark(self,v->fa);
              self->mark(self,v->oa);
              itam = v->tamArray;
              //printf(v->nomeobj);
              //printf("\n");
              o1= v->oa;
              for(ii=0; ii<itam; ii++){
                //if(*o1!='\0'){
                if(o1[ii]!='\0'){  
                  //printf("--b--");
                  //printf(o1[i].nomeobj);
                  GCTraverseObject(self, o1[ii]);
                }
                //o1++;                   
              }                                      
            }
            break;
        }
      }                    
    }else{
      switch(v->tipo){
        case COBJ:
          if( v->o!='\0' && self->isMarked(self,v->o)==CFALSE){
            //self->mark(self,v->o);
            //printf("aaaaa->");
            //printf(v->nomeobj);
            // printf("\n");
            GCTraverseObject(self, v->o);
          }   
          break; 
        case CTBTABLE:
          if( v->t!='\0' && self->isMarked(self,v->t)==CFALSE){
            //self->mark(self,v->t);
            GCTraverseTable(self, v->t);                                      
          }
          break;                
      }            
    } 
    v++;                
  }
}

/*
** GC Salva Objeto
*/
void GCTraverseObject(GCObj *self, clazzptr o){
  int i,i1,itam;
  int qtdatrib;
  VAR *atrib;
  clazz *o1;
  
  if(self->isMarked(self, o)==CTRUE){
    return;
  }
  
  self->mark(self,o);
  
  o1 = o;
  
  //printf("ddd->");
  //printf(o1->cb->nome);
  //printf("\n");
  
  qtdatrib = o1->qatrib;
  
  if(qtdatrib == 0){
    return;
  }
  
  atrib  = o1->atrib;
  
  //self->mark(self,atrib); 
  
  GCTraverseVar(self, atrib, qtdatrib);
  
}

void GCTraverseFrame(GCObj *self, TFRAME *fini, TFRAME *fatu){

  if(fini == fatu){
    return;
  }
  
  //printf("GC\n");
  if(fatu->stack!='\0'){
    self->mark(self,fatu->stack);
  }
  
  //marca class do frame atual
  if(fatu->ci!='\0'){
    GCTraverseObject(self,fatu->ci);
  }
  
  GCTraverseVar(self, fatu->var, fatu->qtdVar);
  fatu--;
  GCTraverseFrame(self, fini, fatu);
  
}

void *ymalloc(unsigned long l){
  USEDMEM+=l;
  return(malloc(l));
}

//task 1 21/08/2021
/*
void gcMoveChamador(char *c, int p1){
  int i=0;
  for(i=0;i<50;i++){
     ggc_chamador[i]='\0';
  }
  
  if(p1==1){
    return;
  }
  i=0;
  while(*c!='\0'){
    ggc_chamador[i]=*c;
    c++;
    i++; 
  }
}
*/


