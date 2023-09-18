#include "zzdata.h"
#include "zzfuncdecl.h"
#include "stdlib.h"

#define IFILEEXEC 1
#define IPRGLIB   2
#define IDLLLIB   3

/**************************
*** PONTO INICIAL DA VM 
***************************/

/*
procurar a palavra bug e o nr. para encontrar a referencia no programa
11.07.2016
TODO: erro quando se chama uma função que retorna algo
TODO: erro delimitação de tamanho
      char nome[10]
      nome = "123...N"
      imprime "123...N", deveria cortar
TODO[23/08/2021][bug 1]-rever no compilador o cálculo da memória do stack, coloquei multiplicado
                        * 100, porém não é o correto 
TODO[23/08/2021][bug 2]-depois da chamada da função quando o retorno não é utilizado, retirar o 
                        item do stack, senão ele vai embora e some do stack       
[28/09/2021][bug 3]-Tipo var na chamada de função
[30/09/2021][bug 4]-calculo no indice do array - quando se soma no array o valor final é float
                      e a função esperava int
[31/08/2021][bug 6]-em moveVarArr foi ajustado para mover o endereço do objeto em questão,
                      verificar constantes (deve ser criada uma cópia
                      rever esse ponto, pois ocorre erro por não respeitar o tamanho original
                        mas pode ser q eu deixe assim... pq cópia de array... teria q ser uma 
                        função nova
[31/08/2021][bug 7]-mover cópia da constante quando for array char   
[04/09/2021][bug 8]-erro na treechar   
                    
*/

int main(int argc, char *argv[]){

  int   rc;
  char *nomeClass;
  TCLS *cb;
  CCLS *ci;
  
  USEDMEM=0;
  USEDMEM2=0;
  ipause = 0;
  ccbb = 0;
  
  //printf("%i",sizeof(TFRAME));
  //system("dir");
  //system("pause");
  //exit(0);
  if(argc <4 ){ 
    printf("Informe o nome da classe\n");     
    exit(0);
  }        
  
  /*
  LM=0;
  MHEAPPOINT = MHEAP = ymalloc(1000000000);
  if(MHEAP=='\0'){
    printf("Não foi possível alocar memória\n");     
    exit(0);
  }
  */
  
  /*
  gPath      = "C:\\Renato\\programas\\rvm\\rvm\\prgs\\";
  gPathDll   = "C:\\Renato\\programas\\rvm\\rvm\\RVM_Orig\\RVMV2\\dll\\rvmbase\\";
  */
  
  gPath      = argv[IPRGLIB];
  gPathDll   = argv[IDLLLIB];
  
  /*
  ** Inicia a Gargage Collector
  */
  switch(initMEMVM(argv[IFILEEXEC])){
    case 1:
      printf("Não foi possível iniciar a garbage collector\n");     
      exit(0);   
      break;
    case 2:
      printf("Não foi possível iniciar a treechar\n");     
      exit(0);      
      break;
    case 3:
      printf("Não foi possível iniciar stack frame\n");     
      exit(0);       
      break;
  }    
  
  rc = loadClass(gMvm.firstClass, &cb);
  if(rc!=0){
    printf("Erro ao carregar class: ");
    printf(gMvm.firstClass);
    printf("\n");
    exit(0);       
  }
  
  rc = putTreeChar(gMvm.firstClass, cb, &gMvm.memcb);
  if(rc==CFALSE){
    printf("Erro ao criar class base\n");
    exit(0);       
  }
  
  /*
  gMvm.memci = createADMem(1000);
  if(gMvm.memci==0){
    printf("Erro ao criar memoria de trabalho\n");
    exit(0);       
  }
  */
  
  //init stack
  //gMvm.stackFrameMem = zmalloc(sizeof(TFRAME) * 50);
  //gMvm.stackFrameFim = gMvm.stackFrameMem + 49;
  //gMvm.stackTam = 50;
  //fim stack
  
  ci = createInstance(gMvm.firstClass, gMvm.memcb, gMvm.memci);
  if(ci==0){
    printf("Erro ao criar classe inicial\n");
    exit(0);       
  }
  
  //gMvm.stackFrame = gMvm.stackFrameMem;
  rc = createStackFrame(&gMvm.stackFrame, ci, CMAIN);
  if(rc!=0){
    printf("Erro ao criar frame stack base\n");
    exit(0);       
  }

  /*system("pause");*/
  //printf("Inicio de processamento\n");
  /*
  ** -- Execução --
  */
  execVm();
  /*
  ** -- Fim      -- 
  */
  
  /*message();*/
  //printf("Fim de processamento\n");
  //system("pause");
  exit(0);
  
}

