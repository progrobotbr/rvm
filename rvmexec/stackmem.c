
#include "var.h"
#include "tipos.h"
#include "bytecode.h"
#include "conversao.h"

/*
  FrameSet e Pilha utilizam a mesma memória
  Movimentação:
    FrameSet - de cima para baixo
    Pilha de Operadores - de baixo para cima
*/

//Iniciliaza área de memória da Stack
void initStackMem(int pTam){
  gStackMem.StackIni = malloc(pTam);
  if(gStackMem.StackIni!=0){
    gStackMem.StackEnd = gStackMem.StackIni + pTam;
  }else{
    printf("Erro ao alocar espaço para stack");
  }
}

//Libera área de memória
void releaseStackMem(){
  free(gStackMem.StackIni);
}

