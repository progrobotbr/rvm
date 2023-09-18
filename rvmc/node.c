#include <stdio.h>
#include "zzdata.h"

/*** Início Node ***/ 

node newNode(){
     node n = malloc(sizeof(struct _node));
     n->mFilhos = '\0';
     n->id = 0;
     n->idClass = 0;
     n->tipo = 0;
     n->valor = SS("");
     n->linha = 0;
     n->idConst = 0;
     n->validtipo = 0;
     n->validnomeobj = SS("");
     n->isAttribute = FALSE;
     n->isArrayCall = FALSE;
     n->isArray = FALSE;
     n->idxArray = 0;
     n->isNative = FALSE;
     n->qtdFilhos = 0;
     n->initFilhos = &node_initFilhos;
     n->putFilho = &node_putFilho;
     n->getFilho = &node_getFilho;
     return(n);
}

void node_initFilhos(node self, int p1){
     int i=0;
     self->qtdFilhos = p1;
     self->mFilhos = malloc(sizeof(node) * p1);
     for(i=0;i<p1;i++){
         self->mFilhos[i] = '\0';
     }
}

void node_putFilho(node self, int p1, node p2){
      self->mFilhos[p1-1] = p2;
}

node node_getFilho(node self, int p1){
  return(self->mFilhos[p1-1]);
}


BOOL isNothing( node n ){
    if(n == NULL){
         return(TRUE);
    }else{
         return(FALSE);
    }
}   


node createNode(token p1){ //ok

  int  i=0;
  node rcreateNode = newNode();
  i = mCommand[p1->tipo][2].i;
  if( i > 0 ){
     rcreateNode->initFilhos(rcreateNode,i);
  }
  rcreateNode->valor = p1->valor;
  rcreateNode->tipo  = p1->tipo;
  rcreateNode->linha = gToken->linha;
  
  return(rcreateNode);
  
}

node createNode1(int p1){ //ok
  //p1 - número de filhos;
  node rcreateNode1 = newNode();
  if( p1 > 0 ){
     rcreateNode1->initFilhos(rcreateNode1,p1);
  }else{
    rcreateNode1->qtdFilhos = p1;
  }
  return(rcreateNode1);
}


/*** Fim node ***/
