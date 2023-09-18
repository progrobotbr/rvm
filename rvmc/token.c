#include <stdio.h>
#include "zzdata.h"
//inicio token

token newToken(){
      token tk = malloc(sizeof(struct _token));
      tk->valor = SS("");
      tk->tipo  = 0;
      tk->erro  = SS("");
      tk->linha = 0;
}


void moveToken(){  //ok
  gToken = getToken();
}

token getToken(){ //ok
   
   int    i=0;
   string c=SS("");
   string c1=SS("");
   string c2=SS("");
   string sToken=SS("");
   int    countPoint=0;
   
   c=SS(" ");     //Caracter atual;
   c2=SS(" ");    //Caracter à frente;
   sToken=SS(""); //Forma palavra;
   
   token rgetToken = newToken();
    
   while( mIdx <= mTam){
   
     //;
     // Limpa Comentários, sintaxe:;
     //  --comentário 1;
     //  --comentário 3;
     //;
     c = Mid(mTexto, mIdx, 1);
   
     //
     //Limpa tab
     if(Asc(c) == 9){
       mIdx = mIdx + 1;
       continue;
     }
     //;
     // Limpa Caracteres Especiais (Enter, Espaço);
     //;
     if( !(SL(c,SS(" "))) && Asc(c) != 13 && Asc(c) != 10 ){
       //;
       // Comentários;
       //;
       //parte --
       if( SL(c,SS("-")) ){
         c1 = Mid(mTexto, mIdx + 1, 1);
         if( SL(c1,SS("-")) ){
           mIdx = mIdx + 1;
           while( Asc(c) != 13 || mIdx == mTam ){
             mIdx = mIdx + 1;
             c = Mid(mTexto, mIdx, 1);
           }
         }else{
           break;
         }
       }else{
         break;
       }
      
     }
     
     if( Asc(c) == 13 ){
       mLinha = mLinha + 1;
     }

     mIdx = mIdx + 1;
     
   }
   
   //;
   // Verifica se é Fim de Programa;
   //;
   if( mIdx > mTam ){
     rgetToken->tipo = Tag_CENDPROGRAM;
     rgetToken->valor = SS("ENDOFPROGRAM");
     return(rgetToken);
   }
   
   rgetToken->linha = mLinha;
   
   //;
   // Pega número: 435 34,45;
   //;
   if( isNumber(c) ){
     countPoint = 0;
     while( mIdx <= mTam){
       sToken = SC(sToken,c);
       mIdx = mIdx + 1;
       c = Mid(mTexto, mIdx, 1);
       if( Not isNumberFloat(c, &countPoint) ){
         break;
       }
     }
     rgetToken->valor = sToken;
     if( countPoint > 0 ){
       rgetToken->tipo = Tag_CFLOAT;
     }else{
       if( countPoint > 1 ){
         rgetToken->erro = SS("E");
       }else{
         rgetToken->tipo = Tag_CINTEGER;
       }
     }
     return(rgetToken);
   }
   
   //;
   // Pega palavras: if, else, while, var01 ->->->;
   //;
   if( isLetter(c) || SL(c,SS("_")) ){
     while( mIdx <= mTam ){
       sToken = SC(sToken,c);
       mIdx = mIdx + 1;
       c = Mid(mTexto, mIdx, 1);
       if( Not isLetter(c) && Not isNumber(c) && !SL(c,SS("_" ))){
         break;
       }
     }
     sToken = UCase(sToken);
     i = isCommand(sToken);
     rgetToken->valor = sToken;
     if( i > 0 ){
       rgetToken->tipo = i;
     }else{
        while( mIdx <= mTam ){
         c = Mid(mTexto, mIdx, 1);
         if( !SL(c,SS(" ")) ){
           break;
         }
         mIdx = mIdx + 1;
       }
       if( SL(c,SS("(")) ){
         rgetToken->tipo = Tag_CFUNC;
       } else if( SL(c,SS("[")) ){
         rgetToken->tipo = Tag_CARRAY;
       }else{
         rgetToken->tipo = Tag_CCVAR;
       }
     }
     return(rgetToken);
   }
   
   //;
   // Verifica carateres especiais;
   //;
   c1 = Mid(mTexto, mIdx + 1, 1);
   if(SL(c,SS("<"))){ //Menor igual (<=);
       if( SL(c1,SS("=")) ){
         mIdx = mIdx + 2;
         rgetToken->tipo = Tag_CLE;
         rgetToken->valor = SC(c,c1);
       }else if(SL(c1,SS(">"))){
         mIdx = mIdx + 2;
         rgetToken->tipo = Tag_CNE;
         rgetToken->valor = SC(c,c1);
       }else{
         mIdx = mIdx + 1;
         rgetToken->tipo = Tag_CLT;
         rgetToken->valor = c;
       }
       return(rgetToken);
   } else if(SL(c,SS(">"))){ //Maior igual (>=);
       if( SL(c1,SS("=")) ){
         mIdx = mIdx + 2;
         rgetToken->tipo = Tag_CGE;
         rgetToken->valor = SC(c,c1);
       }else{
         mIdx = mIdx + 1;
         rgetToken->tipo = Tag_CGT;
         rgetToken->valor = c;
       }
       return(rgetToken);
   } else if(SL(c,SS("="))) { //Igualdade (==);
       if( SL(c1,SS("=")) ){
         mIdx = mIdx + 2;
         rgetToken->tipo = Tag_CEQ;
         rgetToken->valor = SC(c,c1);
         return(rgetToken);
       }
   } else if(SL(c,SS("&"))) {  //And (&&);
       if( SL(c1,SS("&")) ){
         mIdx = mIdx + 2;
         rgetToken->tipo = Tag_CAND;
         rgetToken->valor = SC(c, c1);
         return(rgetToken);
       }
   } else if(SL(c,SS("|"))) { //Or (||);
       if( SL(c1,SS("|")) ){
         mIdx = mIdx + 2;
         rgetToken->tipo = Tag_COR;
         rgetToken->valor = SC(c, c1);
         return(rgetToken);
       }
   } else if(SL(c,SS("("))) { 
       rgetToken->tipo = Tag_CPAROPEN;
       rgetToken->valor = c;
       mIdx = mIdx + 1;
       return(rgetToken);
   } else if(SL(c, SS(")"))) {
       rgetToken->tipo = Tag_CPARCLOS;
       rgetToken->valor=c;
       mIdx = mIdx + 1;
       return(rgetToken);
   } else if(SL(c, SS("\""))) { 
       sToken=SS(""); 
       mIdx = mIdx + 1;
       c = Mid(mTexto, mIdx, 1);
       while( !SL(c, SS("\n")) && !SL(c,SS("\"")) && mIdx < mTam){
         sToken = SC(sToken,c);
         mIdx = mIdx + 1;
         c = Mid(mTexto, mIdx, 1);
       }
       if( SL(c,SS("\"")) ){
         mIdx = mIdx + 1;
       }
       
       rgetToken->tipo = Tag_CSTRING;
       rgetToken->valor = sToken;
       return(rgetToken);
   }
   
   //;
   // Caracteres Especiais;
   //;
   mIdx = mIdx + 1;
   rgetToken->tipo = Tag_CCARESP;
   rgetToken->valor = c;
   //gErrNum = 4;
   //gErrMsg = SC(SS("Caracter não entendido "),c);
   return(rgetToken);
   //*Renato*//
}


BOOL matchToken(string p1){ //ok
  string  sMsg=SS("");
  //sNome = gToken->Valor;
  //matchToken = FALSE;
  if( SL(gToken->valor, p1) ){
    moveToken();
    return(TRUE);
  }else{
    sMsg = SC(SS("E184-Esperada a palavra reservada "),p1);
    Err_Raise(sMsg);
    return(FALSE);
  }
}

BOOL matchTokenMsg(string p1, string pErr){ //ok
  string  sMsg=SS("");
  //sNome = gToken->Valor;
  //matchTokenMsg = FALSE;
  if( SL(gToken->valor, p1) ){
    //matchTokenMsg = TRUE;
    moveToken();
    return(TRUE);
  }else{
    sMsg = SC(SC(SC(SS("Err_linha:"),Str(gToken->linha)),SS(" - ")),pErr);
    Err_Raise(sMsg);
    return(FALSE);
  }
}

BOOL matchTokenWMoveMsg(string p1, string pErr){ //ok
  string  sMsg=SS("");
  //sNome = gToken->Valor;
  //matchTokenWMoveMsg = FALSE;
  if( SL(gToken->valor, p1) ){
    return(TRUE);
  }else{
    sMsg = SC(SC(SC(SS("Err_linha:"),Str(gToken->linha)),SS(" - ")),pErr);
    Err_Raise(sMsg);
    return(FALSE);
  }
}

BOOL matchTokenType(int p1){ //ok
  string  sMsg=SS("");
  BOOL rmatchTokenType=0;
  //sNome = gToken->valor;
  if( gToken->tipo==p1 ){
    moveToken();
    return(TRUE);
  }else{
    sMsg = SC(SC(SC(SS("E186-Anterior a: "),gToken->valor),SS(" - Linha: ")),Str(gToken->linha));
    Err_Raise(sMsg);
    return(FALSE);
  }
}

BOOL matchTokenTypeMsg(int p1, string pErr){ //ok
  string  sMsg=SS("");
  //sNome = gToken->Valor;
  //matchTokenTypeMsg = FALSE;
  if( gToken->tipo == p1 ){
    moveToken();
    return(TRUE);
  }else{
    sMsg = SC(SC(SC(SS("Err_linha:"),Str(gToken->linha)),SS(" - ")),pErr);
    Err_Raise(sMsg);
    return(FALSE);
  }
}

BOOL matchTokenTypeWMoveMsg(int p1, string pErr){ //ok
  string  sMsg=SS("");
  //sNome = gToken->Valor;
  //matchTokenTypeWMoveMsg = FALSE;
  if( gToken->tipo == p1 ){
    //matchTokenTypeWMoveMsg = TRUE;
    ////Call moveToken;
    return(TRUE);
  }else{
    sMsg = SC(SC(SC(SS("Err_linha:"),Str(gToken->linha)),SS(" - ")),pErr);
    Err_Raise(sMsg);
    return(FALSE);
  }
}
/*** fim token ***/

