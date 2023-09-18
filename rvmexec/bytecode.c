
#include "var.h"
#include "tipos.h"
#include "bytecode.h"
#include "conversao.h"

//Parâmetros dos Bytecodes
void putQtdParByteCode(){
  int i;
     
  for(i=0;i<255;i++)
    gByteCode[i] = 0;
  gByteCode[OLOADC] = 1;
  gByteCode[OLOADV] = 1;
  gByteCode[OSTORV] = 1;
  gByteCode[OLODVM] = 2;
  gByteCode[OSTOVM] = 2;
  gByteCode[OIFFALSE] = 1;
  gByteCode[OGOTO] = 1;
  gByteCode[OCALLF] = 1;
  
}  
