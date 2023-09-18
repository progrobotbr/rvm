
#include "var.h"
#include "tipos.h"
#include "bytecode.h"
#include "conversao.h"
/*
** Operações com Frame
*/

/*
  FrameSet e Pilha utilizam a mesma memória
  Movimentação:
    FrameSet - de cima para baixo
    Pilha de Operadores - de baixo para cima
*/

//Libera área de variáveis do Frame
void liberaMemFrame(){
  int i,t;  
  Var *v; 
  HeapVarLocals *oHeap = &gFrame->HeapLocal;
  t = oHeap->QtdVar;
  for(i=0;i<t;i++){
    v = oHeap->Var+i;
    if(v->isArray==TRUE)
      switch(v->tipo){
        case CCHAR:
          free(v->ca);
          break;
         case CINT:
          free(v->ia);
          break;
        case CLONG:
          free(v->la);
          break;
        case CFLOAT:
          free(v->fa);
          break;  
      }
  }
  free(oHeap->Var);
}

//POPFRAME
void PopFrame(){
  liberaMemFrame();   
  gFrame++;
}

//PUSHFRAME
void PushFrame(FrameSet f){
  gFrame--;
  *gFrame = f;
}

//Carrega um frame com a gFuncao Ativa
void initFrame(){
  FrameSet z;
  z.FuncaoOpAtivo = gFuncao->nodeop;
  z.idFuncao      = gFuncao->id;
  z.Funcao        = gFuncao;
  z.idPrograma    = gPrg->id;
  z.Prg           = gPrg;
  z.NomeFuncao    = gFuncao->nome;
  z.QtdOperadores = gFuncao->qtdnodeop;
  z.QtdParametros = gFuncao->qtdparametros;
  PushFrame(z);
}

//Inicializa um Heap de um Frame
void initHeap(){
  int i,t;   
  TLV1 oLV1;
  Funcao *oFuncao;   
  HeapVarLocals *oHeap;
  
  oFuncao = gFrame->Funcao;
  oHeap = &gFrame->HeapLocal;
  oHeap->QtdVar = t = oFuncao->qtdvar;
  oHeap->Var = malloc(sizeof(Var) * t);
  for(i=0;i<t;i++){
    oLV1 = oFuncao->vardecl[i];
    //oHeap->Var[i] = initVar(oLV1.tipo, oLV1.isArray, oLV1.tamArray);
    initVar(&oHeap->Var[i], oLV1.tipo, oLV1.isArray, oLV1.tamArray);
  }
}

//Posicionamento inicial do frame no stack
void posicFrameInStack(){
  gFrame = (FrameSet *) gStackMem.StackEnd;     
}
