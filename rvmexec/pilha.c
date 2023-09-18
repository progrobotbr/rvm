
#include "var.h"
#include "tipos.h"
#include "bytecode.h"
#include "conversao.h"

/*
** Operações com pilha 
*/

/*
  FrameSet e Pilha utilizam a mesma memória
  Movimentação:
    FrameSet - de cima para baixo
    Pilha de Operadores - de baixo para cima
*/


//POP
Var Pop(){
  Var v;
  v = gPilha->Var;
  gPilha--;
  //if gPilha chegou fim ...
  return(v);
}

//PUSH
void Push(Var v){
  PilhaObjeto oPilha;
  oPilha.Var = v;   
  gPilha++;
  *gPilha = oPilha;
}

//Posiciona no início do stack
void posicPilhaInStackIni(){
  gPilha = (PilhaObjeto *) gStackMem.StackIni;
}

//Aponta para frame ativo
void posicPilhaInStackFrm(){
  gPilha = gFrame->Pilha;
}
