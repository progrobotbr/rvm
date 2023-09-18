/*
** Programa: M�quina Virtual 
** Autor   : R.A.L
** Data    : Set/2008
** Vers�o  : 0.000.01
*/

#include <stdio.h>
#include <stdlib.h>

#define STACKTAM 20000

#include "tipos.h"
#include "bytecode.h"
#include "conversao.h"
#include "operador.h"
#include "loadfile.h"
#include "pilha.h"
#include "stackmem.h"
#include "frame.h"
#include "vm.h"

//Corpo principal do programa
int main(int argc, char *argv[]){

  //Inicializa��o
  putQtdParByteCode(); 
  initPrograma("c:\\filesai.bin");
  initStackMem(STACKTAM);
  posicFrameInStack();
  posicPilhaInStackIni();
  lookFunction("__main__");
  initFrame();
  initHeap();

  /*
  ** -- Execu��o --
  */
  execVm();
  /*
  ** -- Fim      -- 
  */

  //Shutdown
  liberaMemFrame(); //�ltimo frame ativo - __main__
  releaseStackMem();
  limpaPrg();
  
  system("pause");
  
  return 0;
  
}

