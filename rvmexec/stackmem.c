
#include "var.h"
#include "tipos.h"
#include "bytecode.h"
#include "conversao.h"

/*
  FrameSet e Pilha utilizam a mesma mem�ria
  Movimenta��o:
    FrameSet - de cima para baixo
    Pilha de Operadores - de baixo para cima
*/

//Iniciliaza �rea de mem�ria da Stack
void initStackMem(int pTam){
  gStackMem.StackIni = malloc(pTam);
  if(gStackMem.StackIni!=0){
    gStackMem.StackEnd = gStackMem.StackIni + pTam;
  }else{
    printf("Erro ao alocar espa�o para stack");
  }
}

//Libera �rea de mem�ria
void releaseStackMem(){
  free(gStackMem.StackIni);
}

