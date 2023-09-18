/*
** Programa: Máquina Virtual 
** Autor   : R.A.L
** Data    : Set/2008
** Versão  : 0.000.01
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

  //Inicialização
  putQtdParByteCode(); 
  initPrograma("c:\\filesai.bin");
  initStackMem(STACKTAM);
  posicFrameInStack();
  posicPilhaInStackIni();
  lookFunction("__main__");
  initFrame();
  initHeap();

  /*
  ** -- Execução --
  */
  execVm();
  /*
  ** -- Fim      -- 
  */

  //Shutdown
  liberaMemFrame(); //Último frame ativo - __main__
  releaseStackMem();
  limpaPrg();
  
  system("pause");
  
  return 0;
  
}

