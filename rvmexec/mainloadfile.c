#include <stdio.h>
#include <stdlib.h>
#include "zzdata.h"
#include "zzfuncdecl.h"

int main11(int argc, char *argv[]){
  int i;
  TCLS *cls, *clsf;
  TREENODE *tree;
  TFUC *tf;
  
  tree = initTreeChar();
  
  clsf =  findTreeChar("QUA", &tree);
  if(clsf!=0){
    printf("\nFunção já carregada");          
  }else{            
    i = loadClass("c:\\QUA.bic", &cls);
    putTreeChar("QUA",cls, &tree);
    printf("\nerro load class QUA: %i\n",i);
  }
  
  tf =  findTreeChar("CALCVEZES", &cls->ffunc);
  
  if(clsf!=0){
    printf("\nFunção já carregada");          
  }else{            
    i = loadClass("c:\\QUI.bic", &cls);
    putTreeChar("QUI", cls, &tree);
    printf("\nerro load class QUI: %i\n",i);
  }
  
  clsf =  findTreeChar("QUI", &tree);
  if(clsf!=0){
    printf("\nFunção já carregada");          
  }
  
  clsf =  findTreeChar("QUA", &tree);
  if(clsf!=0){
     printf("\nfunção encontrada: ");printf(clsf->nome);          
  }      
  clsf =  findTreeChar("QUI", &tree);
  if(clsf!=0){
     printf("\nfunção encontrada: ");printf(clsf->nome);          
  }
  printf("\n");            
  
   
  
  putTreeChar("RENATO", cls, &tree);
  putTreeChar("RENOTO", cls, &tree);
  
  printf("\nprocura1");
  /*system("PAUSE");	*/
  
  
  putTreeChar("REBABA", cls, &tree);
  putTreeChar("RECABA", cls, &tree);
  putTreeChar("ZUZA", cls, &tree);
  putTreeChar("ZECA", cls, &tree);
  putTreeChar("ZECB", cls, &tree);
  putTreeChar("WEKA", cls, &tree);
  printf("\nprocura2");
  /*system("PAUSE");	*/
  
  
  putTreeChar("REDABA", cls, &tree);
  /*printf("\nprocura3");*/
  /*system("PAUSE");	*/
  
  putTreeChar("JUCA", cls, &tree);
  printf("\nprocura");
  /*system("PAUSE");	*/
  
  
  putTreeChar("alhoporo", cls, &tree);
  putTreeChar("ccca", cls, &tree);
  putTreeChar("CCCA", cls, &tree);
  printf("\nprocura");
  /*system("PAUSE");	*/
  
  cls =  findTreeChar("alhoporo", &tree);
  printf("\nResultado %i\n",i);
  
  system("PAUSE");	
  return 0;
}
