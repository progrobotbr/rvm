#include <stdio.h>
#include "zzdata.h"

//----------- Funcoes Auxiliares ---------------;
BOOL isNumber(string c){ //ok
  if( isNumeric(c) ){
      return(TRUE);
  }else{
      return(FALSE);  
  }
}

BOOL isNumberFloat(string c, int *p1){ //ok
  if( SL(c,SS(".")) ){
    *p1 = *p1 + 1;
    return(TRUE);
  }else{
    return(isNumeric(c));
  }
}

BOOL isLetter(string c){ //ok
  int  i;
  i = Asc(c);
  if( (i >= 65 && i <= 90) || (i >= 97 && i <= 122) ){
    return(TRUE);
  }else{
    return(FALSE);
  }
}

int isCommand(string p1){ //ok
  int  i=0;
  
  for(i=0;i<CQTDCOMAND;i++){
    if( SL(UCase(p1),mCommand[i][1].s)){
      return(i);
    }
  }
  return(0);
}
