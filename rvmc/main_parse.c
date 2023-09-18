#include <stdio.h>
#include <stdlib.h>
#include "zzdata.h"

// bug 1 - 20/08/2021 - criação do parâmetro var - onde aceita qualquer coisa
// bug 2 - 01/09/2021 - var no retorno da função... pode ter acarretado outro 
// bug 3 - 09/09/2021 - implementacao de long
//                         problema
//*******************************************
//                INICIO
//*******************************************

int main(int argc, char *argv[]){
  BOOL imprimeASM = FALSE; 
  string sfile=SS(""), sparse=SS("");
  
  if(argc <= 2){
     printf("E001-Sintaxe correta:\nrvmc [programa] [diretorio] <xx>");
     //system("PAUSE");	
     return 0;
  }
  //verifica se mostra assembler
  if(argc == 4){
     imprimeASM = TRUE;      
  }                 
  initEnvironment(argv); 
   
  sfile = readall();
  initParse(sfile, TRUE);
  sparse = Parse(imprimeASM);
  
  //system("PAUSE");	
  return 0;
  
}
//*******************************************
// FIM
//*******************************************

void initEnvironment(char *argv[]){
  gFileSource = SS(argv[1]);
  gPath = SS(argv[2]); //"C:\\renato\\rvmcompl\\prgs\\");
  gExtSource = SS(DOTRVM);  
  gExtComp = SS(DOTBIC);
  gErrNum = 0;
  gErrQtMsg = 1;
  gErrMsg = SS("");
  gdebuglg2 = 0;
  gdebugnode = FALSE;
}

void initCommands(string p1){
  
  //variaveis globais
  int i  =0;
  mTexto = p1;
  mIdx   = 1;
  mTam   = Len(mTexto);
  mLinha = 1;
  g2Line = 1;
  g2NumeraLinha = FALSE;
  gFuncId = 0;
  
  initSymbols();
  
  for(i=0; i<=CQTDCOMAND; i++){
      mCommand[i][ CNOME].s = SS("");
  } 
  
  for(i=0; i<=CMAQCOMMANDS; i++){
      mMaqCommands[i][1].s = SS("");
  }
     

  //mMaqCommands   
  mMaqCommands[1][ 1].s = SS("add ");
  mMaqCommands[1][ 2].i = 50;
  mMaqCommands[1][ 3].i = -1;
  mMaqCommands[2][ 1].s = SS("sub ");
  mMaqCommands[2][ 2].i = 51;
  mMaqCommands[2][ 3].i = -1;
  mMaqCommands[3][ 1].s = SS("mul ");
  mMaqCommands[3][ 2].i = 52;
  mMaqCommands[3][ 3].i = -1;
  mMaqCommands[4][ 1].s = SS("div ");
  mMaqCommands[4][ 2].i = 53;
  mMaqCommands[4][ 3].i = -1;
  mMaqCommands[5][ 1].s = SS("iffalse ");
  mMaqCommands[5][ 2].i = 60;
  mMaqCommands[5][ 3].i = -1;
  mMaqCommands[6][ 1].s = SS("eq ");
  mMaqCommands[6][ 2].i = 61;
  mMaqCommands[6][ 3].i = -1;
  mMaqCommands[7][ 1].s = SS("gt ");
  mMaqCommands[7][ 2].i = 62;
  mMaqCommands[7][ 3].i = -1;
  mMaqCommands[8][ 1].s = SS("gte ");
  mMaqCommands[8][ 2].i = 63;
  mMaqCommands[8][ 3].i = -1;
  mMaqCommands[9][ 1].s = SS("lt ");
  mMaqCommands[9][ 2].i = 64;
  mMaqCommands[9][ 3].i = -1;
  mMaqCommands[10][ 1].s = SS("lte ");
  mMaqCommands[10][ 2].i = 65;
  mMaqCommands[10][ 3].i = -1;
  mMaqCommands[11][ 1].s = SS("and ");
  mMaqCommands[11][ 2].i = 66;
  mMaqCommands[11][ 3].i = -1;
  mMaqCommands[12][ 1].s = SS("or ");
  mMaqCommands[12][ 2].i = 67;
  mMaqCommands[12][ 3].i = -1;
  mMaqCommands[13][ 1].s = SS("goto ");
  mMaqCommands[13][ 2].i = 70;
  mMaqCommands[13][ 3].i = 0;
  mMaqCommands[14][ 1].s = SS("callf ");
  mMaqCommands[14][ 2].i = 71;
  mMaqCommands[14][ 3].i = 0;
  mMaqCommands[15][ 1].s = SS("callnatv ");
  mMaqCommands[15][ 2].i = 72;
  mMaqCommands[15][ 3].i = 0;
  mMaqCommands[16][ 1].s = SS("ret ");
  mMaqCommands[16][ 2].i = 73;
  mMaqCommands[16][ 3].i = 1;
  mMaqCommands[17][ 1].s = SS("retnull ");
  mMaqCommands[17][ 2].i = 74;
  mMaqCommands[17][ 3].i = 0;
  mMaqCommands[18][ 1].s = SS("new ");
  mMaqCommands[18][ 2].i = 75;
  mMaqCommands[18][ 3].i = 1;
  mMaqCommands[19][ 1].s = SS("loadc ");
  mMaqCommands[19][ 2].i = 80;
  mMaqCommands[19][ 3].i = 1;
  mMaqCommands[20][ 1].s = SS("loadv ");
  mMaqCommands[20][ 2].i = 81;
  mMaqCommands[20][ 3].i = 1;
  mMaqCommands[21][ 1].s = SS("storv ");
  mMaqCommands[21][ 2].i = 82;
  mMaqCommands[21][ 3].i = -1;
  mMaqCommands[22][ 1].s = SS("loadvy ");  //load var local array
  mMaqCommands[22][ 2].i = 83;
  mMaqCommands[22][ 3].i = 1;
  mMaqCommands[23][ 1].s = SS("storvy ");  //store var local array
  mMaqCommands[23][ 2].i = 84;
  mMaqCommands[23][ 3].i = -1;
  mMaqCommands[24][ 1].s = SS("gloadv ");  //load var attribute
  mMaqCommands[24][ 2].i = 85;
  mMaqCommands[24][ 3].i = 1;
  mMaqCommands[25][ 1].s = SS("gstorv ");  //store var attribute
  mMaqCommands[25][ 2].i = 86;
  mMaqCommands[25][ 3].i = -1;
  mMaqCommands[26][ 1].s = SS("gloadvy "); //load var attribute array
  mMaqCommands[26][ 2].i = 87;
  mMaqCommands[26][ 3].i = 1;
  mMaqCommands[27][ 1].s = SS("gstorvy "); //store var attribute array
  mMaqCommands[27][ 2].i = 88;
  mMaqCommands[27][ 3].i = -1;
  mMaqCommands[28][ 1].s = SS("ocallf ");  //call method of other class
  mMaqCommands[28][ 2].i = 89;
  mMaqCommands[28][ 3].i = 0;
  mMaqCommands[29][ 1].s = SS("oloadv ");  //load class attribute of other class
  mMaqCommands[29][ 2].i = 90;
  mMaqCommands[29][ 3].i = 1;
  mMaqCommands[30][ 1].s = SS("ostorv ");  //store class attribute of other class
  mMaqCommands[30][ 2].i = 91;
  mMaqCommands[30][ 3].i = -1;
  mMaqCommands[31][ 1].s = SS("oloadvy "); //load class attribute array of other class
  mMaqCommands[31][ 2].i = 92;
  mMaqCommands[31][ 3].i = -1;
  mMaqCommands[32][ 1].s = SS("ostorvy "); //store class attribute array of other class
  mMaqCommands[32][ 2].i = 93;
  mMaqCommands[32][ 3].i = -2;
  mMaqCommands[33][ 1].s = SS("newy ");    //cria um array
  mMaqCommands[33][ 2].i = 94;
  mMaqCommands[33][ 3].i = 1;
  mMaqCommands[34][ 1].s = SS("end ");     //end
  mMaqCommands[34][ 2].i = 95;
  mMaqCommands[34][ 3].i = 0;
  mMaqCommands[35][ 1].s = SS("ne ");     //ne
  mMaqCommands[35][ 2].i = 96;
  mMaqCommands[35][ 3].i = 0;
  //tabelas
  mMaqCommands[36][ 1].s = SS("tbins ");     //tbinsert
  mMaqCommands[36][ 2].i = 97;
  mMaqCommands[36][ 3].i = 0;
  mMaqCommands[37][ 1].s = SS("tbapp ");     //tbappend
  mMaqCommands[37][ 2].i = 98;
  mMaqCommands[37][ 3].i = 0;
  mMaqCommands[38][ 1].s = SS("tbdel ");     //tbdelete
  mMaqCommands[38][ 2].i = 99;
  mMaqCommands[38][ 3].i = 0;
  mMaqCommands[39][ 1].s = SS("tbmod ");     //tbmodify
  mMaqCommands[39][ 2].i = 100;
  mMaqCommands[39][ 3].i = 0;
  mMaqCommands[40][ 1].s = SS("tbrea ");     //tbread
  mMaqCommands[40][ 2].i = 101;
  mMaqCommands[40][ 3].i = 0;
  
  //mCommand
  mCommand[Tag_CBEG][ CNOME].s = SS("BEG");
  mCommand[Tag_CEND][ CNOME].s = SS("END");
  mCommand[Tag_CIF][ CNOME].s = SS("IF");
  mCommand[Tag_CELSE][ CNOME].s = SS("ELSE");
  mCommand[Tag_CWHILE][ CNOME].s = SS("WHILE");
  mCommand[Tag_CCVAR][ CNOME].s = SS("VARIABLE");
  mCommand[Tag_CDEF][ CNOME].s = SS("DEF");
  mCommand[Tag_CRETURN][ CNOME].s = SS("RETURN");
  mCommand[Tag_CCBREAK][ CNOME].s = SS("BREAK");
  mCommand[Tag_CCDECLCHAR][ CNOME].s = SS("CHAR");
  mCommand[Tag_CCDECLINT][ CNOME].s = SS("INT");
  mCommand[Tag_CCDECLFLOAT][ CNOME].s = SS("FLOAT");
  mCommand[Tag_CCDECLLONG][ CNOME].s = SS("LONG"); //bug 3
  mCommand[Tag_CCDECLOBJ][ CNOME].s = SS("OBJECT");
  mCommand[Tag_CCLASS][ CNOME].s = SS("CLASS");
  mCommand[Tag_CNEW][ CNOME].s = SS("NEW");
  mCommand[Tag_CNEWARRAY][ CNOME].s = SS("NEWARRAY");
  mCommand[Tag_CENDCLASS][ CNOME].s = SS("ENDCLASS");
  mCommand[Tag_CENDDEF][ CNOME].s = SS("ENDDEF");
  mCommand[Tag_CENDIF][ CNOME].s = SS("ENDIF");
  mCommand[Tag_CENDWHILE][ CNOME].s = SS("ENDWHILE");
  mCommand[Tag_CDEFNATIVE][ CNOME].s = SS("DEFNATIVE");
  mCommand[Tag_CTBDECLTB][ CNOME].s = SS("TABLE");
  //mCommand[Tag_CTBDECLWA][ CNOME].s = SS("WORKAREA");
  //mCommand[Tag_CTO][ CNOME].s = SS("TO");
  //mCommand[Tag_CFROM][ CNOME].s = SS("FROM");
  //mCommand[Tag_CIN][ CNOME].s = SS("IN");
  //mCommand[Tag_CINTO][ CNOME].s = SS("INTO");
  //mCommand[Tag_CLOOP][ CNOME].s = SS("LOOP");
  //mCommand[Tag_CREAD][ CNOME].s = SS("READ");
  //mCommand[Tag_CAPPEND][ CNOME].s = SS("APPEND");
  //mCommand[Tag_CMODIFY][ CNOME].s = SS("MODIFY");
  //mCommand[Tag_CINSERT][ CNOME].s = SS("INSERT");
  //mCommand[Tag_CDELETE][ CNOME].s = SS("DELETE");
  //mCommand[Tag_CINDEX][ CNOME].s = SS("INDEX");
  //mCommand[Tag_CENDLOOP][ CNOME].s = SS("ENDLOOP");  
  mCommand[Tag_CCLASSBODY][ CNOME].s = SS("");//SS("CCLASSBODY");
  mCommand[Tag_CDECLVAR][ CNOME].s = SS("");  //SS("DECLVAR");
  mCommand[Tag_CINTEGER][ CNOME].s = SS("");  //SS("INTEGER");   
  mCommand[Tag_CLE][ CNOME].s = SS("");       //SS("LE"); 
  mCommand[Tag_CCOMMAND][ CNOME].s = SS("");  //SS("COMMAND");
  mCommand[Tag_CCBOOL][ CNOME].s = SS("");    //SS("CBOOL");   
  mCommand[Tag_CASSIGN ][ CNOME].s = SS("");  //SS("ASSIGN"); 
  mCommand[Tag_CASSIGNLOC][ CNOME].s = SS("");//SS("ASSIGNLOC");
  mCommand[Tag_CCALC][ CNOME].s = SS("");//SS("CALC");
  
  mCommand[Tag_CBEG][ CNUMFILHOS].i = 1;
  mCommand[Tag_CEND][ CNUMFILHOS].i = 0;
  mCommand[Tag_CIF][ CNUMFILHOS].i = 2;
  mCommand[Tag_CELSE][ CNUMFILHOS].i = 3;
  mCommand[Tag_CWHILE][ CNUMFILHOS].i = 2;
  mCommand[Tag_CCVAR][ CNUMFILHOS].i = 0;
  mCommand[Tag_CFLOAT][ CNUMFILHOS].i = 0;
  mCommand[Tag_CDEF][ CNUMFILHOS].i = 3;
  mCommand[Tag_CRETURN][ CNUMFILHOS].i = 1;
  mCommand[Tag_CCBREAK][ CNUMFILHOS].i = 1;
  mCommand[Tag_CCDECLCHAR][ CNUMFILHOS].i = 1;
  mCommand[Tag_CCDECLINT][ CNUMFILHOS].i = 1;
  mCommand[Tag_CCDECLLONG][ CNUMFILHOS].i = 1;
  mCommand[Tag_CCDECLFLOAT][ CNUMFILHOS].i = 1;
  mCommand[Tag_CCDECLOBJ][ CNUMFILHOS].i = 1;
  
}

//Parse
void initParse(string p1, BOOL bMoveTok){

  initCommands(p1);
     
  if( bMoveTok == TRUE ){
     moveToken();
  }
  
}

string Parse(BOOL pimprimeASM){

  string s=SS("");
  string rParse=SS("");
  int iId=0;
 
  putFunc(SS("_globals_"), 0, SS(""), FALSE, FALSE);
  
  gProg = Class();
  
  if(gErrNum==0){
    printf("\nS001-Compilado com sucesso\n");
  }else{
    printf("\n%s\n",gErrMsg->c);
    return(NIL);
  }
 
  CHALT();
  
  s = emit2Lang2(gProg); //lógica 2;
  
  printf("\nS002-Gravacao do arquivo bic\n\n");
  GravaArquivoF();
  //s = emit2Lang2(gProg);
  //iId = getId("__main__", CFUNCAO);
  //Call putAssembly(iId, s);
  rParse = s;
  
  //Imprime ASM
  if(pimprimeASM==TRUE){
    printf("%s\n",s->c);
  }
  
  return(rParse);
  
}


//------ Funcoes da Linguagem -------------;
string tg(int p1){  //ok
  string rtg = mCommand[p1][1].s; //Retorna string representando um comando da linguage: WHILE IF ->->->;
  return(rtg);
}

node Class(){ //ok
     
  string sNome = SS("");
  node objNode = NIL;
  
  CHALT();
  
  node rClass = createNode1(1);
  
  matchTokenMsg(SS("CLASS"), SS("E002-esperado comando CLASS"));CHALT();
  sNome = gToken->valor;
  putNomeClass(sNome);
  putConst(sNome, Tag_CCLASS);
  matchTokenTypeMsg(Tag_CCVAR, SS("E003-esperado nome da classe"));CHALT();
  matchTokenMsg(SS("BEG"), SS("E004-esperado comando BEG em início de Classe"));CHALT();
  
  objNode = ClassBody();
  
  CHALT();
  
  rClass->putFilho(rClass, 1, objNode);
  rClass->tipo = Tag_CCLASS;
  rClass->valor=sNome;
  matchTokenMsg(SS("ENDCLASS"), SS("E005-esperado comando ENDCLASS no fim da definicao da Classe"));CHALT();
  
  return(rClass);
  
}

node ClassBody(){ //ok

   BOOL  bDecl=FALSE;
   node  objNode=NIL;
   
   CHALT();
   
   node rClassBody = createNode1(2);
   objNode = Decl();
   
   CHALT();
   
   if( ! isNothing(objNode) ){
     rClassBody->putFilho(rClassBody, 1, objNode);
     objNode = ClassBody();           //Recursão;
     
     CHALT();
      
     rClassBody->putFilho(rClassBody, 2, objNode);
     rClassBody->tipo = Tag_CCLASSBODY;
     rClassBody->valor = SS("CLASSBODY");

   }else{
            
     if( gToken->tipo == Tag_CDEF ){
       objNode = Def(FALSE);
       CHALT();
     } else if( gToken->tipo == Tag_CDEFNATIVE ){
       objNode = Def(TRUE);
     }else{
       assert(gToken->tipo == Tag_CENDCLASS,SC(SS("E005-elemento nao identificado: "),gToken->valor));
       rClassBody = NIL;
       return(rClassBody);
     }
     
     if( Not isNothing(objNode) ){
       rClassBody->putFilho(rClassBody, 1, objNode);
       objNode = ClassBody();         //Recursão;
       CHALT();
       rClassBody->putFilho(rClassBody, 2, objNode);
       rClassBody->tipo = Tag_CCLASSBODY;
       rClassBody->valor = SS("CLASSBODY");
     }else{
       rClassBody = NIL;
     }
   }
   
   return(rClassBody);
   
}

node Def(BOOL pbIsNative){
  BOOL  bol;   
  BOOL  bHasType=FALSE;
  BOOL  bIsArray=FALSE;
  int  i=0;
  int  iTipo=0;
  string  sNomeObj=FALSE;
  string  Name=SS("");
  node  s=NIL;
  node  b=NIL;
  
  node rDef = NIL;
  
  CHALT();
  
  bHasType = FALSE;
  bIsArray = FALSE;
  sNomeObj = SS("");
  iTipo = -1;
  if( gToken->tipo == Tag_CDEF ||  gToken->tipo == Tag_CDEFNATIVE ){
    
    moveToken();
    
    if( gToken->tipo == Tag_CCDECLCHAR ){
      iTipo = Tag_CCHAR1;
      bHasType = TRUE;
      moveToken();
      if( SL(gToken->valor,SS("[")) ){
        moveToken();
        matchTokenMsg(SS("]"), SS("E007-esperado ] para fechar array"));CHALT();
        bIsArray = TRUE;
      }
    } else if( gToken->tipo == Tag_CCDECLINT ){
      iTipo = Tag_CINTEGER;
      bHasType = TRUE;
      moveToken();
      if( SL(gToken->valor,SS("[")) ){
        moveToken();
        matchTokenMsg(SS("]"), SS("E008-esperado ] para fechar array"));CHALT();
        bIsArray = TRUE;
      }
    } else if( gToken->tipo == Tag_CCDECLLONG ){
      iTipo = Tag_CLONG;
      bHasType = TRUE;
      moveToken();
      if( SL(gToken->valor,SS("[")) ){
        moveToken();
        matchTokenMsg(SS("]"), SS("E008-esperado ] para fechar array"));CHALT();
        bIsArray = TRUE;
      }  
    } else if( gToken->tipo == Tag_CCDECLFLOAT ){
      iTipo = Tag_CFLOAT;
      bHasType = TRUE;
      moveToken();
      if( SL(gToken->valor, SS("[")) ){
        moveToken();
        matchTokenMsg(SS("]"), SS("E009-esperado ] para fechar array"));CHALT();
        bIsArray = TRUE;
      }
    } else if( gToken->tipo == Tag_CCDECLOBJ ){
       iTipo = Tag_COBJ;
       bHasType = TRUE;
       moveToken();
       matchTokenMsg(SS("("), SS("E010-esperado ( na declaracao de objeto"));CHALT();
       matchTokenTypeWMoveMsg(Tag_CCVAR, SS("E011-esperado o do objeto de referencia"));CHALT();
       sNomeObj = gToken->valor;
       bol = ReadClass(sNomeObj);
       assert(bol == TRUE, SC(SS("E012-classe nao encontrada "), gToken->valor));
       moveToken();
       matchTokenMsg(SS(")"), SS("E013-esperado ) na declaracao de objeto"));CHALT();
       if( SL(gToken->valor, SS("[")) ){
         moveToken();
         matchTokenMsg(SS("]"), SS("E014-esperado ] para fechar array"));CHALT();
         bIsArray = TRUE;
       }
    } else if( gToken->tipo == Tag_CTBDECLTB ){ //testar
       iTipo = Tag_CTBTABLE;
       bHasType = TRUE;
       moveToken();
       matchTokenMsg(SS("("), SS("E015-esperado ( na declaracao da tabela"));CHALT();
       matchTokenTypeWMoveMsg(Tag_CCVAR, SS("E016-esperado o do objeto de referencia"));CHALT();
       sNomeObj = gToken->valor;
       bol = ReadClass(sNomeObj);
       assert(bol == TRUE, SC(SS("E017-classe nao encontrada "), gToken->valor));
       bol = ReadClass(SS("bstable"));
       assert(bol == TRUE, SC(SS("E018-classe base bstable não encontrada "),gToken->valor));
       moveToken();
       matchTokenMsg(SS(")"), SS("E019-esperado ) na declaracao de tabela"));CHALT();
     
    }       
    
    matchTokenTypeWMoveMsg(Tag_CFUNC, SS("E020-esperado o nome na definicao da funcao"));CHALT();
    Name = gToken->valor;
    validFuncMsg2(Name, SC(SS("E021-nao e possivel a redeclaracao da funcao: "),Name));CHALT();
    gFuncId = putFunc(Name, iTipo, sNomeObj, bIsArray, pbIsNative); //número da função;
    putConst(Name, Tag_CFUNC);
    moveToken();
    matchTokenMsg(SS("("), SS("E022-esperado ( na definicao da funcao"));CHALT();
    s = pegaParDef(TRUE);CHALT()
    matchTokenMsg(SS(")"), SS("E023-esperado ) na definicao da funcao"));CHALT();
    if( pbIsNative == TRUE ){
      b = NIL;
      rDef = wordDef(i, Name, s, b);
      rDef->tipo = Tag_CDEFNATIVE;
    }else{
       matchTokenMsg(tg(Tag_CBEG), SC(SS("E024-esperado comando BEG na definicao da funcao "),Name));CHALT();
       b = Stmts(); //comandos;
       CHALT();
       validFuncReturnOk(gFuncId, Name, bHasType, iTipo, sNomeObj, bIsArray);CHALT();
      
       matchTokenMsg(SS("ENDDEF"), SC(SS("E025-esperado comando ENDDEF na definicao da funcao "),Name));CHALT();
      
       rDef = wordDef(i, Name, s, b);
       rDef->tipo = Tag_CDEF;
    }
           
    rDef->validtipo = iTipo;
    rDef->validnomeobj = sNomeObj;
    
    gFuncId = 0; //Zero atua como um boolean;
    
    return(rDef);
    
  }
}

node Stmt(){
   string  sMsg=SS("");
   string  sTokenValor=SS("");
   string  sPart1=SS("");
   string  sPart2=SS("");
   int  iTokenTipo=0;
   node  b=NIL;
   node  s=NIL;
   node  t=NIL;
   node rStmt=NIL;
   int  i=0;
   ElemAssign  tAgn;
   
   CHALT();
   
   //if(mLinha==15){
   //   mLinha = 15;
   //}
               
   sMsg = SS("");
   i = gToken->linha;
      
   //if( i == 14 ){
   //  i = 14;
   //}
   
   
   switch(gToken->tipo){
     case Tag_CIF:
       matchToken(tg(Tag_CIF));CHALT();
       matchTokenMsg(SS("("), SS("E026-esperado ( no comando IF"));CHALT();
       b = Bool(FALSE);CHALT();
       matchTokenMsg(SS(")"), SS("E027-esperado ) no comando IF"));CHALT();
       matchTokenMsg(SS("BEG"), SS("E028-esperado comando BEG no comando IF"));CHALT();
       s = Stmts();CHALT();
       if( gToken->tipo != Tag_CELSE ){
         rStmt = wordIf(i, b, s);
       }else{
         matchToken(tg(Tag_CELSE));CHALT();
         t = Stmts();CHALT();
         rStmt = wordElse(i, b, s, t);
       }
       matchTokenMsg(SS("ENDIF"), SS("E029-esperado comando ENDIF no comando ELSE"));  CHALT();
       break;     
     case Tag_CWHILE:
       matchToken(tg(Tag_CWHILE));CHALT();
       matchTokenMsg(SS("("), SS("E030-esperado ( no comando WHILE"));CHALT();
       b = Bool(FALSE);CHALT();
       matchTokenMsg(SS(")"), SS("E031-esperado ) no comando WHILE"));CHALT();
       matchTokenMsg(SS("BEG"), SS("E032-esperado comando BEG no comando ELSE"));CHALT();
       s = Stmts();CHALT();
       rStmt = wordWhile(i, b, s);
       matchTokenMsg(SS("ENDWHILE"), SS("E033-esperado comando ENWHILE no comando ELSE"));CHALT();
       break;
     case Tag_CFUNC:
       sTokenValor = gToken->valor;      //Pega o nome da função - calc(p1,p2);
       //printf(gToken->valor->c);
       rStmt = callFunction(sTokenValor, iTokenTipo);CHALT();   //chama funções locais{
       //bug 2 - colocar eliminar retorno de parâmetros
       //if( Not isNothing(p1->getFilho(p1,1))  ){
       //rStmt->mFilhos = '\0';
       //rStmt->qtdFilhos = 0;
       break;
     case Tag_CRETURN:
       moveToken();
       matchTokenMsg(SS("("), SS("E034-esperado ( em RETURN"));CHALT();
       if( gToken->valor != SS(")") ){
         b = Bool(FALSE);CHALT();
       }else{
         b = NIL;
       }
       matchTokenMsg(SS(")"), SS("E035-esperado ) em RETURN"));CHALT();
       putReturnOk(gFuncId, b);
       rStmt = wordReturn(i, b);CHALT();
       break;
     case Tag_CCBREAK:
       rStmt = wordBreak(i);CHALT();
       moveToken();
       break;
     case Tag_CCDECLCHAR:
     case Tag_CCDECLINT:
     case Tag_CCDECLLONG:
     case Tag_CCDECLFLOAT:
     case Tag_CCDECLOBJ:
     case Tag_CTBDECLTB:
     //case Tag_CTBDECLWA:
       rStmt = wordDecl(i);CHALT();
       break; 
     case Tag_CCVAR:
     case Tag_CARRAY:
       tAgn = assignGetLdEsq();CHALT();
       if( SL(tAgn->funcObj, SS("")) ){
           matchTokenMsg(SS("="), SS("E036-esperado o carater = de atribuicao"));CHALT();
       }
       
       rStmt = assignGetLdDir(tAgn);CHALT();
       break;
       
     //Tabelas;
     /*
     case Tag_CAPPEND:
       rStmt = tbAppend();
       CHALT();
       break;
       
     case Tag_CINSERT:
       rStmt = tbInsert();
       CHALT();
       break;
       
     case Tag_CDELETE:
       rStmt = tbDelete();
       CHALT();
       break;
       
     case Tag_CMODIFY:
       rStmt = tbModify();
       CHALT();
       break;
       
     case Tag_CREAD:
       rStmt = tbRead();
       CHALT();
       break;
       
     case Tag_CLOOP:
       rStmt = tbLoop();
       CHALT();
       break;
     */
     default:
       sMsg = SC(SS("E037-elemento nao reconhecido: "),gToken->valor);
       Err_Raise(sMsg);
  
   }
   
   return(rStmt);

}

node Stmts(){
  
  node rStmts=NIL;
  
  CHALT();
  
  //Else é um statement contido em IF;
  if( gToken->tipo == Tag_CENDCLASS ||
      gToken->tipo == Tag_CENDDEF ||
      gToken->tipo == Tag_CENDIF ||
      gToken->tipo == Tag_CENDWHILE ||
      gToken->tipo == Tag_CELSE ||
      gToken->tipo == Tag_CENDPROGRAM ||
      gToken->tipo == Tag_CENDLOOP){
    rStmts = NIL;
  }else{
    rStmts = Seq(Stmts(), Stmt());    //Cria deep nodes, como uma escada;
    CHALT();
    rStmts->valor = SS("STMTS");
    rStmts->tipo = Tag_CCOMMAND;
  }
  return(rStmts);
}

node Decl(){
  int  i=0;
  node rDecl=NIL;
  
  CHALT();
  
  if( gToken->tipo == Tag_CCDECLCHAR ||
      gToken->tipo == Tag_CCDECLINT ||
      gToken->tipo == Tag_CCDECLLONG ||
      gToken->tipo == Tag_CCDECLFLOAT ||
      gToken->tipo == Tag_CCDECLOBJ ||
      gToken->tipo == Tag_CTBDECLTB ){
    i = gToken->linha;
    gFuncId = GLOBALS;
    rDecl = wordDecl(i);CHALT();
    rDecl->tipo = Tag_CDECLVAR;
    rDecl->valor = SS("DECLVAR");
    rDecl->isAttribute = TRUE;
  }else{
    rDecl = NIL;
  }
  return(rDecl);
}


node Seq(node p2, node p1){
  node rSeq=NIL;
     
  CHALT();
  
  if( isNothing(p1) && isNothing(p2) ){
    rSeq = createNode1(0);
    return(rSeq);
  }
  if( Not isNothing(p2) ){
     rSeq = createNode1(2);
     rSeq->putFilho(rSeq, 1, p1);
     rSeq->putFilho(rSeq, 2, p2);
  }else{
     rSeq = createNode1(1);
     rSeq->putFilho(rSeq, 1, p1);
  }
  //Seq.Valor = "SEQ";
  //Seq.Tipo = Tag->CSEQ;
  rSeq->linha = gToken->linha;
  return(rSeq);
}

node wordIf(int p0, node p1, node p2){
  
  CHALT();
     
  node rwordIf = createNode1(2);
  rwordIf->putFilho(rwordIf, 1, p1);
  rwordIf->putFilho(rwordIf, 2, p2);
  rwordIf->valor = SS("IF");
  rwordIf->tipo = Tag_CIF;
  rwordIf->linha = p0;
  return(rwordIf);
}

node wordElse(int p0, node p1, node p2, node p3){
  
  CHALT();
     
  node rwordElse = createNode1(3);
  rwordElse->putFilho(rwordElse, 1, p1);
  rwordElse->putFilho(rwordElse, 2, p2);
  rwordElse->putFilho(rwordElse, 3, p3);
  rwordElse->valor = SS("IFELSE");
  rwordElse->tipo = Tag_CELSE;
  rwordElse->linha = p0;
  return(rwordElse);
}

node wordWhile(int p0, node p1, node p2){
  
  CHALT();
     
  node rwordWhile = createNode1(2);
  rwordWhile->putFilho(rwordWhile, 1, p1);
  rwordWhile->putFilho(rwordWhile, 2, p2);
  rwordWhile->valor = SS("WHILE");
  rwordWhile->tipo = Tag_CWHILE;
  rwordWhile->linha = p0;
  return(rwordWhile);
}

node wordFunc(int p0, string p1, node p2){
  
  CHALT();
     
  node rwordFunc = createNode1(1);
  rwordFunc->putFilho(rwordFunc, 1, p2);
  rwordFunc->valor = p1;
  rwordFunc->tipo = Tag_CFUNC;
  rwordFunc->linha = p0;
  return(rwordFunc);
}

node wordDef(int p0, string p1, node p2, node p3)  {
  
  CHALT();
     
  node rwordDef = createNode1(2);
  rwordDef->putFilho(rwordDef, 1, p2);
  rwordDef->putFilho(rwordDef, 2, p3);
  rwordDef->valor = p1;
  rwordDef->tipo = Tag_CDEF;
  rwordDef->linha = p0;
  return(rwordDef);
}

node wordReturn(int p0, node p1){
     
  CHALT();
     
  node rwordReturn = createNode1(1);
  rwordReturn->putFilho(rwordReturn, 1, p1);
  rwordReturn->valor = SS("RETURN");
  rwordReturn->tipo = Tag_CRETURN;
  rwordReturn->linha = p0;
  return(rwordReturn);
}

node wordBreak(int p0){
     
  CHALT();
     
  node rwordBreak = createNode1(0);
  rwordBreak->valor = SS("BREAK");
  rwordBreak->tipo = Tag_CCBREAK;
  rwordBreak->linha = p0;
  return(rwordBreak);
}

node wordDecl(int p0){
     
  CHALT();
     
  BOOL  b=FALSE;
  BOOL  bClass=FALSE;
  BOOL  bIsArray=FALSE;
  int   i=0;
  int   iTamArray=0;
  string  sNomeClass=SS("");
  string  sValor=SS("");
  node  oNode;
  
  sNomeClass =SS("");
  bClass = FALSE;
  bIsArray = FALSE;
  node rwordDecl = createNode1(1);
  rwordDecl->linha = p0;
  rwordDecl->tipo = gToken->tipo;
  
  moveToken();
  
  oNode = createNode1(0);
  
  switch(rwordDecl->tipo){
    case Tag_CCDECLCHAR:
      i = Tag_CCHAR1;
      break;
    case Tag_CCDECLINT:
      i = Tag_CINTEGER;
      break;
    case Tag_CCDECLLONG:
      i = Tag_CLONG;
      break;
    case Tag_CCDECLFLOAT:
      i = Tag_CFLOAT;
      break;
    case Tag_CCDECLOBJ:
      bClass = TRUE;
      i = Tag_COBJ;
      matchTokenMsg(SS("("), SS("E038-esperado ( em declaracao de Objeto"));CHALT();
      sNomeClass = gToken->valor;
      //Carrega a classe;
      b = ReadClass(gToken->valor);
      assert(b == TRUE, SC(SS("E039-classe nao encontrada "), gToken->valor));
      matchTokenTypeMsg(Tag_CCVAR, SS("E040-esperado nome do objeto na tipificacao"));CHALT();
      matchTokenMsg(SS(")"), SS("E041-esperado ) em declaracao de Objeto"));CHALT();
      break;
    case Tag_CTBDECLTB:
    case Tag_CTBDECLWA:
      //
      //colocada esta lógica aqui, pois tabela não pode ser tipo array;
      //
      if( rwordDecl->tipo == Tag_CTBDECLTB ){
        i = Tag_CTBTABLE;
      }else{
        i = Tag_CTBWA;
      }
      
      //i = Tag_COBJ;
      matchTokenMsg(SS("("),SS("E042-esperado ( em declaracao de tabela ou workarea"));CHALT();
      sNomeClass = gToken->valor;
      b = ReadClass(SS("bstable"));
      assert(b == TRUE, SC(SS("E043-classe base bstable nao encontrada "),gToken->valor));
      
      b = ReadClass(gToken->valor);
      assert(b == TRUE, SC(SS("E044-classe de referencia para tabela/workarea nao encontrada "),gToken->valor));
      matchTokenTypeMsg(Tag_CCVAR, SS("E045-esperado nome do objeto na tipificacao"));CHALT();
      matchTokenMsg(SS(")"), SS("E046-esperado ) em declaracao de Objeto"));CHALT();
      
      oNode->valor = gToken->valor;
      oNode->tipo = i;
      matchTokenTypeMsg(Tag_CCVAR, SS("E047-Esperado nome do elemento (tabela ou workarea)"));CHALT();
      validVarMsg(oNode->valor, SC(SS("E048-Não é possível redeclarar variavel "),oNode->valor));CHALT();
      rwordDecl->putFilho(rwordDecl, 1, oNode);
      rwordDecl->id = putVarFunc(gFuncId, CTIPOVAR, oNode->valor, oNode->tipo, bIsArray, iTamArray, sNomeClass);
      
      return(rwordDecl);
      break;
  }
  
  if( gToken->tipo == Tag_CCVAR ){
    oNode->valor = gToken->valor;
    moveToken();
  } else if( gToken->tipo == Tag_CARRAY ){
    oNode->valor = gToken->valor;
    moveToken();
    matchTokenMsg(SS("["), SS("E049-esperado [ em declaracao de array"));CHALT();
    if(gToken->tipo==Tag_CINTEGER){
      sValor = gToken->valor;
      matchTokenTypeMsg(Tag_CINTEGER, SS("E050-esperado inteiro em quantidade na definicao do array"));CHALT();                             
      iTamArray = CInt(sValor);
    }else{
      iTamArray = 0;    
    }        
    matchTokenMsg(SS("]"), SS("E051-esperado ] em declaracao de array"));CHALT();
    bIsArray = TRUE;
  }else{
    //;
    // aqui dará erro, somente para emitir a mensagem;
    //;
    assert(gToken->tipo == Tag_CCVAR, SS("E052-Esperado nome do elemento"));
  }
  
  validVarMsg(oNode->valor, SC(SS("E053-Nao e possível redeclarar variavel "),oNode->valor));CHALT();
  
  oNode->tipo = i;
  rwordDecl->putFilho(rwordDecl, 1, oNode);
      
  rwordDecl->id = putVarFunc(gFuncId, CTIPOVAR, oNode->valor, oNode->tipo, bIsArray, iTamArray, sNomeClass);
  
  return(rwordDecl);
  
}

//;
// Funções de Tabela;
//;
//append wa to tb;
node tbAppend(){
     
  BOOL  b=FALSE;
  int  t1=0;
  int  t2=0;
  string  s1=SS("");
  string  s2=SS("");
  node  oNode=NIL;
  node  oNodeTb=NIL;
  node  oNodeWa=NIL;
  node rtbAppend=NIL;
  
  BOOL  b1=FALSE;
  BOOL  bIsArray=FALSE;
  BOOL  bGlobal1=FALSE;
  BOOL  bGlobal2=FALSE;
  int  iId1=0;
  int  iId2=0;
  Variable  tvaro; initVar(&tvaro);
  Variable  tvart; initVar(&tvart);
  
  CHALT();
  
  oNode = createNode1(2);
  
  oNode->tipo = Tag_CTBAPPEND;
  moveToken();
  matchTokenTypeWMoveMsg(Tag_CCVAR, SC(SS("E054-Esperado nome do elemento: "),gToken->valor));CHALT();
  
  s1 = gToken->valor;
  b1 = pegaVarFuncClass(gFuncId, s1, SS(""), &tvaro, FALSE, &iId1, &bGlobal1, &bIsArray);
  assert(b1 == TRUE, SC(SS("E055-variavel nao definida: "), s1) );
  assert( tvaro.tipo == Tag_COBJ, SC(SS("E056-a variavel nao e do tipo objeto: "), s1 ));
  
  moveToken();
  matchToken(SS("TO"));CHALT();
  matchTokenTypeWMoveMsg(Tag_CCVAR, SC(SS("E057-Esperado nome do elemento: "),gToken->valor));CHALT();
  
  s2 = gToken->valor;
  b1 = pegaVarFuncClass(gFuncId, s2, SS(""), &tvart, FALSE, &iId2, &bGlobal2, &bIsArray);
  assert(b1 == TRUE, SC(SS("E058-variavel nao definida: "),s2));
  assert( tvart.tipo == Tag_CTBTABLE, SC(SS("E059-a variavel nao e do tipo tabela: "), s2 ));
  assert( SL(tvaro.nomeobj, tvart.nomeobj) , SC4(SS("E060-a tabela "), s2, SS(" nao suporta o objeto "), s1) );
  
  moveToken();
  
  oNodeTb = createNode1(0);
  oNodeWa = createNode1(0);
  
  oNodeWa->id = iId1;
  oNodeWa->valor = s1;
  oNodeWa->validnomeobj = tvaro.nomeobj;
  oNodeWa->isAttribute = bGlobal1;
  oNodeWa->tipo = Tag_CCVAR;
  oNodeTb->id = iId2;
  oNodeTb->valor = s2;
  oNodeTb->validnomeobj = tvart.nomeobj;
  oNodeTb->isAttribute = bGlobal2;
  oNodeTb->tipo = Tag_CCVAR;
  
  oNode->putFilho(oNode, 1, oNodeWa);
  oNode->putFilho(oNode, 2, oNodeTb);
  
  rtbAppend = oNode;
  return(rtbAppend);
  
}

//;
//insert wa in tb index n;
//;
node tbInsert(){
  BOOL  b=FALSE;
  int  t1=0;
  int  t2=0;
  int  iDx=0;
  string  s1=SS("");
  string  s2=SS("");
  string  s3=SS("");
  node  oNode=NIL;
  node  oNodeTb=NIL;
  node  oNodeWa=NIL;
  node  oNodeIdx=NIL;
  node  rtbInsert=NIL;
  
  BOOL  b1=FALSE;
  BOOL  bIsArray=FALSE;
  BOOL  bGlobal=FALSE;
  int  iId=0;
  Variable  tvaro; initVar(&tvaro);
  Variable  tvart; initVar(&tvart);
  Variable  tvarv; initVar(&tvarv);
   
  CHALT();
  
  oNode = createNode1(3);
  oNode->tipo = Tag_CTBINSERT;
  
  moveToken();
  
  matchTokenTypeWMoveMsg(Tag_CCVAR, SC(SS("E061-Esperado nome do elemento: "),gToken->valor));CHALT();
  s1 = gToken->valor;
  
  b1 = pegaVarFuncClass(gFuncId, s1, SS(""), &tvaro, FALSE, &iId, &bGlobal, &bIsArray);
  assert( b1 == TRUE, SC(SS("E062-variavel nao definida: "), s1) );
  assert( tvaro.tipo == Tag_COBJ, SC(SS("E062-a variavel nao e do tipo objeto: "), s1 ));
 
  moveToken();
  matchToken(SS("IN"));CHALT();
  matchTokenTypeWMoveMsg(Tag_CCVAR, SC(SS("E063-Esperado nome do elemento: "),gToken->valor));CHALT();
  
  s2 = gToken->valor;
  b1 = pegaVarFuncClass(gFuncId, s2, SS(""), &tvart, FALSE, &iId, &bGlobal, &bIsArray);
  assert(b1 == TRUE, SC(SS("E064-variavel nao definida: "),s2));
  assert( tvart.tipo == Tag_CTBTABLE, SC(SS("E065-a variavel nao e do tipo tabela: "), s2 ));
  assert( SL(tvaro.nomeobj, tvart.nomeobj) , SC4(SS("E066-a tabela "), s2, SS(" nao suporta o objeto "), s1) );

  moveToken();
  matchToken(SS("INDEX"));CHALT();
  
  s3 = gToken->valor;
  if( gToken->tipo == Tag_CCVAR){
    b1 = pegaVarFuncClass(gFuncId, s3, SS(""), &tvarv, FALSE, &iId, &bGlobal, &bIsArray);
    assert( b1 == TRUE, SC(SS("E067-variavel nao definida: "),s3));
    assert( tvarv.tipo == Tag_CINTEGER, SC(SS("E068-variavel deve ser do tipo int: "),s3) );
  }else{
    assert( gToken->tipo == Tag_CINTEGER, SC(SS("E069-Espero um numero do tipo inteiro e nao:"),s3) ); 
  }
  
  oNodeTb = createNode1(0);
  oNodeWa = createNode1(0);
  oNodeIdx = createNode1(0);
  oNodeWa->valor = s1;
  oNodeWa->validnomeobj = s1;
  oNodeTb->valor = s2;
  oNodeTb->validnomeobj = s2;
  oNodeIdx->valor = s3;
  oNodeIdx->tipo = gToken->tipo;
  
  moveToken();
  
  oNode->putFilho(oNode, 1, oNodeWa);
  oNode->putFilho(oNode, 2, oNodeTb);
  oNode->putFilho(oNode, 3, oNodeIdx);
  
  rtbInsert = oNode;
  
  return(rtbInsert);
  
}

//;
//delete tb index n;
//;
node tbDelete(){
  BOOL  b=FALSE;
  int  t1=0;
  int  t2=0;
  int  iDx=0;
  string  s1=SS("");
  string  s2=SS("");
  string  s3=SS("");
  node oNode=NIL;
  node oNodeTb=NIL;
  node oNodeIdx=NIL;
  node tbDelete=NIL;
  node rtbDelete=NIL;
  
  BOOL  b1=FALSE;
  BOOL  bIsArray=FALSE;
  BOOL  bGlobal=FALSE;
  int  iId=0;
  Variable  tvaro; initVar(&tvaro);
  Variable  tvart; initVar(&tvart);
  Variable  tvarv; initVar(&tvarv);

  CHALT();
  
  oNode = createNode1(2);
  oNode->tipo = Tag_CTBDELETE;
  
  moveToken();
  
  matchTokenTypeWMoveMsg(Tag_CCVAR, SC(SS("E070-Esperado nome do elemento: "),gToken->valor));CHALT();
 
  s1 = gToken->valor;
  b1 = pegaVarFuncClass(gFuncId, s1, SS(""), &tvaro, FALSE, &iId, &bGlobal, &bIsArray);
  assert( b1 == TRUE, SC(SS("E071-variavel nao definida: "), s1) );
  assert( tvaro.tipo == Tag_COBJ, SC(SS("E072-a variavel nao e do tipo objeto: "), s1 ));

  matchToken(SS("FROM"));CHALT();
  matchTokenTypeWMoveMsg(Tag_CCVAR, SC(SS("E073-Esperado nome do elemento: "),gToken->valor));CHALT();
 
  s2 = gToken->valor;
  b1 = pegaVarFuncClass(gFuncId, s2, SS(""), &tvart, FALSE, &iId, &bGlobal, &bIsArray);
  assert(b1 == TRUE, SC(SS("E075-variavel nao definida: "),s2));
  assert( tvart.tipo == Tag_CTBTABLE, SC(SS("E076-a variavel nao e do tipo tabela: "), s2 ));
  assert( SL(tvaro.nomeobj, tvart.nomeobj) , SC4(SS("E077-a tabela "), s2, SS(" nao suporta o objeto "), s1) );
  
  matchToken(SS("INDEX"));CHALT();
  
  s3 = gToken->valor;
  if( gToken->tipo == Tag_CCVAR){
    b1 = pegaVarFuncClass(gFuncId, s3, SS(""), &tvarv, FALSE, &iId, &bGlobal, &bIsArray);
    assert( b1 == TRUE, SC(SS("E078-variavel nao definida: "),s3));
    assert( tvarv.tipo == Tag_CINTEGER, SC(SS("E079-variavel deve ser do tipo int: "),s3) );
  }else{
    assert( gToken->tipo == Tag_CINTEGER, SC(SS("E080-Espero um numero do tipo inteiro e nao:"),s3) ); 
  }
  
  oNodeTb = createNode1(0);
  oNodeIdx = createNode1(0);
  oNodeTb->valor = s1;
  oNodeTb->validnomeobj = s2;
  oNodeIdx->valor = gToken->valor;
  oNodeIdx->tipo = gToken->tipo;
  
  moveToken();
  
  oNode->putFilho(oNode, 2, oNodeTb);
  oNode->putFilho(oNode, 3, oNodeIdx);
  
  rtbDelete = oNode;
  
  return(rtbDelete);
  
}

//;
//modify tb from wa index n;
//;
node tbModify(){
  BOOL   b=FALSE;
  int    t1=0;
  int    t2=0;
  int    iDx=0;
  string s1=SS("");
  string s2=SS("");
  string s3=SS("");
  node   oNode=NIL;
  node   oNodeTb=NIL;
  node   oNodeWa=NIL;
  node   oNodeIdx=NIL;
  node   tbModify=NIL;
  node   rtbModify=NIL;

  BOOL  b1=FALSE;
  BOOL  bIsArray=FALSE;
  BOOL  bGlobal=FALSE;
  int  iId=0;
  Variable  tvaro; initVar(&tvaro);
  Variable  tvart; initVar(&tvart);
  Variable  tvarv; initVar(&tvarv);
  
  CHALT();
  
  oNode = createNode1(3);
  oNode->tipo = Tag_CTBMODIFY;
  
  moveToken();
  
  matchTokenTypeWMoveMsg(Tag_CCVAR, SC(SS("E081-Esperado nome do elemento: "),gToken->valor));CHALT();
 
  s1 = gToken->valor;
  b1 = pegaVarFuncClass(gFuncId, s1, SS(""), &tvart, FALSE, &iId, &bGlobal, &bIsArray);
  assert( b1 == TRUE, SC(SS("E082-variavel nao definida: "), s1) );
  assert( tvart.tipo == Tag_CTBTABLE, SC(SS("E083-a variavel nao e do tipo tabela: "), s1 ));
  
  moveToken();
  matchToken(SS("FROM"));CHALT();
  matchTokenTypeWMoveMsg(Tag_CCVAR, SC(SS("E083-Esperado nome do elemento: "),gToken->valor));CHALT();
 
  s2 = gToken->valor;
  b1 = pegaVarFuncClass(gFuncId, s2, SS(""), &tvaro, FALSE, &iId, &bGlobal, &bIsArray);
  assert(b1 == TRUE, SC(SS("E084-variavel nao definida: "),s2));
  assert( tvaro.tipo == Tag_COBJ, SC(SS("E085-a variavel nao e do tipo objeto: "), s2 ));
  assert( SL(tvaro.nomeobj, tvart.nomeobj) , SC4(SS("E086-a tabela "), s1, SS(" nao suporta o objeto "), s2) );
  
  moveToken();
  matchToken(SS("INDEX"));CHALT();
  
  s3 = gToken->valor;
  if( gToken->tipo == Tag_CCVAR){
    b1 = pegaVarFuncClass(gFuncId, s3, SS(""), &tvarv, FALSE, &iId, &bGlobal, &bIsArray);
    assert( b1 == TRUE, SC(SS("E087-variavel nao definida: "),s3));
    assert( tvarv.tipo == Tag_CINTEGER, SC(SS("E088-variavel deve ser do tipo int: "),s3) );
  }else{
    assert( gToken->tipo == Tag_CINTEGER, SC(SS("E089-Esperado um numero do tipo inteiro e nao:"),s3) ); 
  }
  
  oNodeTb = createNode1(0);
  oNodeWa = createNode1(0);
  oNodeIdx = createNode1(0);
  oNodeWa->valor = s1;
  oNodeWa->validnomeobj = s1;
  oNodeTb->valor = s2;
  oNodeTb->validnomeobj = s2;
  oNodeIdx->valor = gToken->valor;
  oNodeIdx->tipo = gToken->tipo;
  
  moveToken();
  
  oNode->putFilho(oNode, 1, oNodeWa);
  oNode->putFilho(oNode, 2, oNodeTb);
  oNode->putFilho(oNode, 3, oNodeIdx);
  
  rtbModify = oNode;
  
  return(rtbModify);
}

//;
//read tb to wa index n;
//;
node tbRead(){
   BOOL  b=FALSE;
   int   t1=0;
   int   t2=0;
   int   iDx=0;
   string  s1=SS("");
   string  s2=SS("");
   string  s3=SS("");
   node  oNode=NIL;
   node  oNodeTb=NIL;
   node  oNodeWa=NIL;
   node  oNodeIdx=NIL;
   node  rtbRead=NIL;
   string smsg=SS("");
   
   BOOL  b1=FALSE;
   BOOL  bIsArray=FALSE;
   BOOL  bGlobal=FALSE;
   int  iId=0;
   Variable  tvaro; initVar(&tvaro);
   Variable  tvart; initVar(&tvart);
   Variable  tvarv; initVar(&tvarv);
  
   CHALT(); 
   
   oNode = createNode1(3);
   oNode->tipo = Tag_CTBREAD;
  
   moveToken();
  
   matchTokenTypeWMoveMsg(Tag_CCVAR, SC(SS("E090-Esperado nome do elemento: "),gToken->valor));CHALT();
   s1 = gToken->valor;
   b1 = pegaVarFuncClass(gFuncId, s1, SS(""), &tvart, FALSE, &iId, &bGlobal, &bIsArray);
   assert(b1 == TRUE, SC(SS("E091-variavel nao definida: "), s1) );
   assert( tvart.tipo == Tag_CTBTABLE, SC(SS("E092-a variavel nao e do tipo tabela: "), s1 ));   
 
   moveToken();
   matchToken(SS("TO"));CHALT();
   matchTokenTypeWMoveMsg(Tag_CCVAR, SC(SS("E093-Esperado nome do elemento: "),gToken->valor));CHALT();
 
   s2 = gToken->valor;
   b1 = pegaVarFuncClass(gFuncId, s2, SS(""), &tvaro, FALSE, &iId, &bGlobal, &bIsArray);
   assert(b1 == TRUE, SC(SS("E094-variavel nao definida: "),s2));
   assert( tvaro.tipo == Tag_COBJ, SC(SS("E095-a variavel nao e do tipo objeto: "), s2 ));
   assert( SL(tvaro.nomeobj, tvart.nomeobj) , SC4(SS("E096-a tabela "), s1, SS(" nao suporta o objeto "), s2) );
 
   moveToken();
   matchToken(SS("INDEX"));CHALT();
   
   s3 = gToken->valor;
   if( gToken->tipo == Tag_CCVAR){
     b1 = pegaVarFuncClass(gFuncId, s3, SS(""), &tvarv, FALSE, &iId, &bGlobal, &bIsArray);
     assert( b1 == TRUE, SC(SS("E097-variavel nao definida: "),s3));
     assert( tvarv.tipo == Tag_CINTEGER, SC(SS("E098-variavel deve ser do tipo int: "),s3) );
   }else{
     assert( gToken->tipo == Tag_CINTEGER, SC(SS("E099-Espero um numero do tipo inteiro e nao:"),s3) ); 
   }
  
   oNodeTb = createNode1(0);
   oNodeWa = createNode1(0);
   oNodeIdx = createNode1(0);
   oNodeWa->valor = s1;
   oNodeWa->validnomeobj = s1;
   oNodeTb->valor = s2;
   oNodeTb->validnomeobj = s2;
   oNodeIdx->valor = gToken->valor;
   oNodeIdx->tipo = gToken->tipo;
   
   moveToken();
  
   oNode->putFilho(oNode, 1, oNodeWa);
   oNode->putFilho(oNode, 2, oNodeTb);
   oNode->putFilho(oNode, 3, oNodeIdx);
  
   rtbRead = oNode;
   return(rtbRead);
}
//;
//loop tb into wa;
//  bla bla;
//endloop;
//;
node tbLoop(){
  BOOL  b=FALSE;
  int  t1=0;
  int  t2=0;
  int  iDx=0;
  string  s1=SS("");
  string  s2=SS("");
  node  oNode=NIL;
  node  oNodeTb=NIL;
  node  oNodeIdx=NIL;
  node  oNodeWa=NIL;
  node  oNodeSs=NIL;
  node  rtbLoop=NIL;

  BOOL  b1=FALSE;
  BOOL  bIsArray=FALSE;
  BOOL  bGlobal=FALSE;
  int  iId=0;
  Variable  tvaro; initVar(&tvaro);
  Variable  tvart; initVar(&tvart);
     
  CHALT();
  
  oNode = createNode1(3);
  oNode->tipo = Tag_CTBLOOP;
  
  moveToken();
  
  matchTokenTypeWMoveMsg(Tag_CCVAR, SC(SS("E100-Esperado nome do elemento: "),gToken->valor));CHALT();
  s1 = gToken->valor;
  b1 = pegaVarFuncClass(gFuncId, s1, SS(""), &tvart, FALSE, &iId, &bGlobal, &bIsArray);
  assert(b1 == TRUE, SC(SS("E101-variavel nao definida: "),s1));
  assert( tvart.tipo == Tag_CTBTABLE, SC(SS("E102-a variavel nao e do tipo tabela: "), s2 ));
  
  moveToken();
  matchToken(SS("INTO"));CHALT();

  s2 = gToken->valor;
  b1 = pegaVarFuncClass(gFuncId, s2, SS(""), &tvaro, FALSE, &iId, &bGlobal, &bIsArray);
  assert( b1 == TRUE, SC(SS("E103-variavel nao definida: "), s2) );
  assert( tvaro.tipo == Tag_COBJ, SC(SS("E103-a variavel nao e do tipo objeto: "), s2 ));
  assert( SL(tvaro.nomeobj, tvart.nomeobj) , SC4(SS("E104-a tabela "), s1, SS(" nao suporta o objeto "), s2) );
 
  moveToken();
  oNodeSs = Stmts(); CHALT();
  
  matchToken(SS("ENDLOOP"));CHALT();
  
  oNodeTb = createNode1(0);
  oNodeWa = createNode1(0);
  
  oNodeWa->valor = s1;
  oNodeWa->validnomeobj = s1;
  oNodeTb->valor = s2;
  oNodeTb->validnomeobj = s2;
//  oNodeIdx->valor = gToken->valor;
  
  oNode->putFilho(oNode, 1, oNodeWa);
  oNode->putFilho(oNode, 2, oNodeTb);
  oNode->putFilho(oNode, 3, oNodeSs);
  
  rtbLoop = oNode;
  
  return(rtbLoop);
}
  

//;
// Funções assign;
//;
node assignGetLdDir(ElemAssign pAgn){
  string  sMsg=SS("");
  node rassignGetLdDir=NIL;
  
  CHALT();
  
  if( gToken->tipo == Tag_CNEW ){ //vv = new obj;
    rassignGetLdDir = assignNewObj(pAgn);CHALT();
  } else if( gToken->tipo == Tag_CNEWARRAY ){ //vv = newarray(10);
    rassignGetLdDir = assignNewArray(pAgn);CHALT();
  } else if( !SL(pAgn->funcObj,SS("")) ){
    rassignGetLdDir = callFunctionObj(pAgn->ldEsq1, pAgn->funcObj);CHALT();
  }else{
    rassignGetLdDir = assignVar(pAgn);CHALT(); //vv = v1 ->->->;
  
  }
  
  return(rassignGetLdDir);
  
}

ElemAssign assignGetLdEsq(){
  BOOL  bIsArray=FALSE;
  BOOL  bGlobal =FALSE;
  BOOL  bIsNative=FALSE;
  int  iId=0;
  int  iTipo=0;
  string  sNomeClass=SS("");
  string  sNomeClass1=SS("");
  string  sNomeClass2=SS("");
  string  sNomeTot=SS("");
  ElemAssign  tAgn;
  ElemAssign rassignGetLdEsq;
  
  CHALT();
  
  tAgn = (ElemAssign) malloc(sizeof(struct _ElemAssign));
    
  tAgn->ldEsq1 = SS("");
  tAgn->ldEsq1Cls = SS("");
  tAgn->ldEsq1Gbl = FALSE;
  tAgn->ldEsq1Id = -1;
  tAgn->ldEsq1Tipo = -1;
  tAgn->ldEsq2 = SS("");
  tAgn->ldEsq2Cls = SS("");
  tAgn->atribConst = SS("");
  tAgn->ldEsq2Tipo = -1;
  tAgn->funcObj = SS("");
  tAgn->funcObjCls = SS("");
  tAgn->funcObjTipo = -1;
  tAgn->isArray = FALSE;
  tAgn->oIdxArray = NIL;
  
  rassignGetLdEsq = tAgn;
  
  if( gToken->tipo != Tag_CCVAR && gToken->tipo != Tag_CARRAY ){
     matchTokenTypeWMoveMsg(Tag_CCVAR, SS("E104-esperado nome do elemento"));CHALT();
  }

  // v1 =;
  tAgn->ldEsq1 = gToken->valor;
  iTipo = pegaTipoVar(gFuncId, tAgn->ldEsq1, SS(""), &sNomeClass, &iId, &bGlobal, &bIsArray);
  assert(iTipo > 0, SC(SS("E105-variavel nao declarada: "),tAgn->ldEsq1));
  tAgn->ldEsq1Id = iId;
  tAgn->ldEsq1Gbl = bGlobal;
  tAgn->ldEsq1Tipo = iTipo;
  tAgn->ldEsq1Cls = sNomeClass;
  tAgn->isArray = bIsArray;
  tAgn->oIdxArray = NIL;
  if( gToken->tipo == Tag_CARRAY ){
    assert(bIsArray == TRUE, SC(SS("E106-variavel não é tipo array: "),tAgn->ldEsq1));
    moveToken();
    matchTokenMsg(SS("["), SS("E107-esperado [ para início de array"));CHALT();
    tAgn->isArray = FALSE; //deixou de ser array;
    tAgn->oIdxArray = Bool(FALSE);
    matchTokenMsg(SS("]"), SS("E108-esperado ] de final de array"));CHALT();
    rassignGetLdEsq = tAgn;
    return(rassignGetLdEsq);
  }
  
  moveToken();
  if( SL(gToken->valor, SS(".")) ){
    moveToken();
    if( gToken->tipo == Tag_CFUNC ){ //obj.func(...;
      tAgn->funcObj = gToken->valor;
      if( !SL(sNomeClass,SS("")) ){
        sNomeTot = SC(SC(sNomeClass,SS(".")),tAgn->funcObj);
      }else{
        sNomeTot = tAgn->funcObj;
      }
      //;
      // implementar is array aqui;
      //;
      
      pegaRetFunc(sNomeTot, &iTipo, &bIsArray, sNomeClass1, &bIsNative);
      tAgn->funcObjTipo = iTipo;
      tAgn->funcObjCls = sNomeClass1;
      
    }else{  //obj.v1 =;
      sNomeClass = SS("");
      int ibool = gToken->tipo == Tag_CCVAR || gToken->tipo == Tag_CARRAY;
      assert(ibool, SS("E109-esperado nome do membro"));
      //Call matchTokenTypeWMoveMsg(Tag->CCVAR, "esperado nome do membro");
       
      tAgn->ldEsq2 = gToken->valor;
      iTipo = pegaTipoVar(gFuncId, tAgn->ldEsq2, tAgn->ldEsq1Cls, &sNomeClass2, &iId, &bGlobal, &bIsArray);
      assert(iTipo > -1, SC(SS("E182-membro nao declarado: "),tAgn->ldEsq2));
      
      tAgn->ldEsq2Tipo = iTipo;
      tAgn->ldEsq2Cls = sNomeClass2;
      tAgn->isArray = bIsArray;
      if( !SL(tAgn->ldEsq1Cls,SS("")) ){
        tAgn->atribConst = SC(SC(tAgn->ldEsq1Cls,SS(".")),tAgn->ldEsq2);
      }
      moveToken();
      if( SL(gToken->valor, SS("[")) ){
        assert(bIsArray == TRUE, SC(SS("E110-variavel não encontrada: "),tAgn->ldEsq2));
        tAgn->isArray = FALSE;
        moveToken();
        tAgn->oIdxArray = Bool(FALSE);
        matchTokenMsg(SS("]"), SS("E111-esperado ] de final de array"));CHALT();
      }else{
         matchTokenWMoveMsg(SS("="), SS("E112-esperado = de associação"));CHALT();
      }
    }
  }
  
  rassignGetLdEsq = tAgn;
  return(rassignGetLdEsq);
  
}
  
node assignNewArray(ElemAssign pAgn){
  int   iTipo=0;
  node  b=NIL;
  node  oNode=NIL;
  node  oNode1=NIL;
  node  rassignNewArray=NIL;
  
  CHALT();
  
  moveToken();
  
  matchTokenMsg(SS("("), SS("E113-esperado o caracter ( para definir o tamanho do array"));CHALT();
  if( gToken->tipo != Tag_CCDECLCHAR && 
      gToken->tipo != Tag_CCDECLINT &&
      gToken->tipo != Tag_CCDECLLONG &&
      gToken->tipo != Tag_CCDECLFLOAT &&
      gToken->tipo != Tag_CCDECLOBJ ){
      matchTokenTypeMsg(Tag_CCDECLINT, SS("D114-esperado o tipo: char, int, long, float ou objeto para declarar array"));CHALT();
  }
  
  iTipo = gToken->tipo;
  switch(iTipo){
    case Tag_CCDECLCHAR:
      iTipo = Tag_CCHAR1;
      break;
    case Tag_CCDECLINT:
      iTipo = Tag_CINTEGER;
      break;
    case Tag_CCDECLLONG:
      iTipo = Tag_CLONG;
      break;
    case Tag_CCDECLFLOAT:
      iTipo = Tag_CFLOAT;
      break;
    case Tag_CCDECLOBJ:
      iTipo = Tag_COBJ;
      break;
  }
  
  moveToken();
  
  matchTokenMsg(SS(","), SS("E115-esperado o caracter , para finalizar comando array"));CHALT();
  b = Bool(FALSE);
  CHALT();
  matchTokenMsg(SS(")"), SS("E116-esperado o caracter ) para finalizar comando array"));CHALT();
  
  oNode = createNode1(0);
  oNode1 = createNode1(1);
  
  if( !SL(pAgn->ldEsq2,SS("")) ){
    oNode->tipo = Tag_CASSIGNATR;
    oNode->valor = pAgn->atribConst;
    oNode->idClass = pAgn->ldEsq1Id;
    assert(pAgn->isArray == TRUE, SC(SS("E117-a variavel deve ser array: "),pAgn->atribConst));
    assert(pAgn->ldEsq2Tipo == iTipo, SC(SS("E118-tipos diferentes: "), pAgn->atribConst));
  }else{
    oNode->tipo = Tag_CASSIGNLOC; //variavel da classe local;
    oNode->id = pAgn->ldEsq1Id;
    oNode->isAttribute = pAgn->ldEsq1Gbl;
    assert(pAgn->isArray == TRUE, SC(SS("E119-a variavel deve ser array: "),pAgn->ldEsq1));
    assert(pAgn->ldEsq1Tipo == iTipo, SC(SS("E120-tipos diferentes no array: "),pAgn->ldEsq1));
  }
  
  oNode1->tipo = Tag_CNEWARRAY;
  oNode1->valor = SS("NEWARRAY");
  oNode1->validtipo = iTipo;
  
  oNode1->putFilho(oNode1, 1, b);
  
  rassignNewArray = createNode1(2);
  rassignNewArray->putFilho(rassignNewArray, 1, oNode1);
  rassignNewArray->putFilho(rassignNewArray, 2, oNode);
  rassignNewArray->linha = gToken->linha;
  rassignNewArray->tipo = Tag_CASSIGN;
  rassignNewArray->valor = SS("ASSIGN");
  
  return(rassignNewArray);
  
}

node assignNewObj(ElemAssign pAgn){
  BOOL  b=FALSE;
  int  iTipo=0;
  node  oNode=NIL;
  node  oNode1=NIL;
  string  sVarRef=SS("");
  node rassignNewObj=NIL;
  
  CHALT();
  
  moveToken();
  matchTokenTypeWMoveMsg(Tag_CCVAR, SC(SC(SS("E121-linha "),Str(gToken->linha)),SS("-esperado o nome da tipo do objeto")));CHALT();
  
  iTipo = -1;
  
  //Carrega a classe;
  b = ReadClass(gToken->valor);
  assert(b == TRUE, SC(SS("E122-classe não encontrada "),gToken->valor));
    
  if( !SL(pAgn->ldEsq2Cls, SS("")) ){
    //If gToken->valor != pAgn->ldEsq2Cls ){
    //   Err->Raise(vbObjectError + 513, "Compilador", "linha " & gToken->linha & "-objetos com tipos diferentes: " & gToken->valor & "-" & pAgn->ldEsq2Cls);
    //End if(;
    
    validVarAssignObjNewMsg(gFuncId, pAgn->ldEsq2, pAgn->ldEsq1Cls, gToken->valor);CHALT();
    
    oNode = createNode1(0);
    oNode->tipo = Tag_CASSIGNATR;
    oNode->valor = pAgn->atribConst;
    putConst(pAgn->atribConst, CCONST);
    //Além de validar, ela indica se o objeto foi instanciado;
    
  }else{
    //If gToken->valor != pAgn->ldEsq1Cls ){
    //   Err->Raise(vbObjectError + 513, "Compilador", "linha " & gToken->linha & "-objetos com tipos diferentes: " & gToken->valor & "-" & pAgn->ldEsq2Cls);
    //End if(;
    
    validVarAssignObjNewMsg(gFuncId, pAgn->ldEsq1, SS(""), gToken->valor);CHALT();
    
    //if( pAgn->isArray == TRUE ){
     if( Not isNothing(pAgn->oIdxArray) ){  //task    
      oNode = createNode1(1);
      oNode->isArrayCall = TRUE; //task
      oNode->putFilho(oNode, 1, pAgn->oIdxArray);
    }else{
      oNode = createNode1(0);
      oNode->isArrayCall = FALSE; //task
    }
    oNode->tipo = Tag_CASSIGNLOC;
    oNode->id = pAgn->ldEsq1Id;
    oNode->isAttribute = pAgn->ldEsq1Gbl;
  }
  
  oNode1 = createNode1(0);
  oNode1->tipo = Tag_CNEWCLASS;
  oNode1->valor = gToken->valor;
  putConst(gToken->valor, CCONST);
  
  rassignNewObj = createNode1(2);
  rassignNewObj->putFilho(rassignNewObj, 1, oNode1);
  rassignNewObj->putFilho(rassignNewObj, 2, oNode);
  rassignNewObj->linha = gToken->linha;
  rassignNewObj->tipo = Tag_CASSIGN;
  rassignNewObj->valor = SS("ASSIGN");
  
  moveToken();
  
  return(rassignNewObj);
   
}

node callFunctionObj(string pParte1, string pParte2){ //, pTokenTipo  Integer)  Object{
  BOOL  bIsArray=FALSE;
  BOOL  bGlobal=FALSE;
  BOOL  bIsNative=FALSE;
  int  iId=0;
  int  iIdClass=0;
  int  iTipo=0;
  int  iisTable=0;
  string  sNomeTot=SS("");
  string  sNomeClass=SS("");
  string  sNomeClass2=SS("");
  string  sMsg=SS("");
  node    b=NIL;
  node    Node=NIL;
  node rcallFunctionObj=NIL;
  
  CHALT();
  
  iTipo = pegaTipoVar(gFuncId, pParte1, SS(""), &sNomeClass, &iId, &bGlobal, &bIsArray);
  iIdClass = iId;
  if( iTipo == -1 ){
    sMsg = SC3(SS("E123-variavel "), pParte1, SS(" não encontrada"));
    Err_Raise(sMsg);
  }
  //Call validVarAssignMsg(gFuncId, pParte1, sNomeClass)  //valida a variavel  objeto;
  if(iTipo == Tag_CTBTABLE){
    iisTable = 1;       
    sNomeTot = SC(SS("BSTABLE."),pParte2);       
  }else{
    sNomeTot = SC(SC(sNomeClass,SS(".")),pParte2);
  }
  validFuncMsg(sNomeTot, SC(SS("E124-função não encontrada: "), sNomeTot));CHALT();
  
  //sNome = gToken->Valor      //Pega o nome da função - calc(p1,p2);
  putConst(sNomeTot, CCONST);
  moveToken();
  matchTokenMsg(SS("("), SC(SS("E125-esperado ( em chamada à função: "),sNomeTot));CHALT();
  b = pegaArgs(TRUE);CHALT();   //Args;
  validFuncChamadaMsg(sNomeClass, sNomeTot, b);CHALT();
  matchTokenMsg(SS(")"), SC(SS("E126-esperado ) em chamada à função: "),sNomeTot));CHALT();
  
  pegaRetFunc(sNomeTot, &iTipo, &bIsArray, sNomeClass2, &bIsNative);
  Node = wordFunc(gToken->linha, sNomeTot, b);
  Node->tipo = Tag_CLASSMETHOD;
  Node->valor = sNomeTot;
  if(iisTable == 1 || SL(sNomeClass2,SS("__T__"))){
    Node->validnomeobj = sNomeClass;
  }else{
    Node->validnomeobj = sNomeClass2;
  }
  Node->validtipo = iTipo;
  Node->idClass = iIdClass;
  Node->isAttribute = bGlobal;
  //task
  //talvez mover 
  //Node->isarray...
  rcallFunctionObj = Node;
  
  return(rcallFunctionObj);
  
}

node callFunction(string pTokenValor, int pTokenTipo){
  BOOL  bIsNative=FALSE;
  BOOL  bIsArray=FALSE;
  int  iTipo=0;
  string  sNome=SS("");
  string  sNomeClass=SS("");
  node  oNode=NIL;
  node  b=NIL;
  node rcallFunction=NIL;
  
  CHALT();
  
  sNome = gToken->valor;     //Pega o nome da função - calc(p1,p2)
  putConst(sNome, CCONST);
  moveToken();
  matchTokenMsg(SS("("), SC(SS("E127-esperado ( em chamada à função "),sNome));CHALT();
  b = pegaArgs(TRUE);CHALT();   //Args
  validFuncChamadaMsg(SS(""), sNome, b);CHALT();
  matchTokenMsg(SS(")"), SC(SS("E128-esperado ) em chamada à função "),sNome));CHALT();
  oNode = wordFunc(gToken->linha, sNome, b);
  pegaRetFunc(sNome, &iTipo, &bIsArray, sNomeClass, &bIsNative);
  //Set callFunction = createNode1(1){
  rcallFunction = oNode;
  rcallFunction->id = pegaIdFunc2(sNome);
  rcallFunction->valor = sNome;
  rcallFunction->tipo = Tag_CALLFUNC;
  rcallFunction->validnomeobj = sNomeClass;
  rcallFunction->validtipo = iTipo;
  rcallFunction->isNative = bIsNative;
  rcallFunction->linha = gToken->linha;
  rcallFunction->isArray = bIsArray;
  //Call callFunction->putFilho(1, oNode){
  return(rcallFunction); 
  
}

node assignVar(ElemAssign pAgn){
  BOOL  bGlobal=FALSE;
  BOOL  bIsArray=FALSE;
  int  iId=0;
  int  iTipo=0;
  string  sVar=SS("");
  string  sClass=SS("");
  node  oNode=NIL;
  node  oNode1=NIL;
  node rassignVar=NIL;
  
  CHALT();
   
  if( Not isNothing(pAgn->oIdxArray) ){
    oNode = createNode1(1);
    oNode->isArrayCall = TRUE;
    oNode->putFilho(oNode, 1, pAgn->oIdxArray);
  }else{
    oNode = createNode1(0);
    oNode->isArrayCall = FALSE;
  }
    
  if( !SL(pAgn->ldEsq2,SS("")) ){ //atributo de outra classe;
    oNode->tipo = Tag_CASSIGNATR;
    oNode->valor = pAgn->atribConst;
    oNode->idClass = pAgn->ldEsq1Id;
    putConst(pAgn->atribConst, CCONST);
    iTipo = pAgn->ldEsq2Tipo;
    sClass = pAgn->ldEsq2Cls;
    sVar = pAgn->ldEsq2;
  }else{
    oNode->tipo = Tag_CASSIGNLOC; //variavel da classe local;
    oNode->id = pAgn->ldEsq1Id;
    oNode->isAttribute = pAgn->ldEsq1Gbl;
    iTipo = pAgn->ldEsq1Tipo;
    sClass = pAgn->ldEsq1Cls;
    sVar = pAgn->ldEsq1;
  }
  
  oNode1 = Bool(FALSE);CHALT();
  
  //valida tabela
  if( iTipo == Tag_CTBTABLE ){
     assert( iTipo == oNode1->validtipo, SS("E128-associacao nao valida, deve ser tipo tabela") );
     assert( SL(sClass,oNode1->validnomeobj), SS("E129-tipos de tabelas diferentes"));
  }
  
  //bug 2
  if(!SL(oNode1->validnomeobj,SS("__VAR__"))){ 
     
    if( iTipo == Tag_COBJ || oNode1->validtipo == Tag_COBJ ){
      assert(SL(sClass,oNode1->validnomeobj), SC4(SS("E130-atribuição para classes diferentes: "),pAgn->ldEsq1,SS("."), pAgn->ldEsq2));
    }
  
    if( !(pAgn->ldEsq1Tipo == Tag_CCHAR1 && oNode1->validtipo == Tag_CCHAR1 )){
      assert(Not ((pAgn->isArray == TRUE || oNode1->isArray == TRUE) && (pAgn->isArray != oNode1->isArray)), SC(SS("E181-variavel recebe somente tipo array: "),sVar));
    
      if( pAgn->isArray == TRUE && oNode1->isArray == TRUE ){
        assert(iTipo == oNode1->validtipo,SS("E131-os tipos devem ser iguais em atribuição com array"));
      }
    }
  }
              
  rassignVar = createNode1(2);
  rassignVar->tipo = Tag_CASSIGN;
  rassignVar->valor = SS("ASSIGN");
  rassignVar->putFilho(rassignVar, 1, oNode1);
  rassignVar->putFilho(rassignVar, 2, oNode);
  rassignVar->linha = gToken->linha;
  
  return(rassignVar);
  
}

node Bool( BOOL pCalledByFunc  ){
  node rBool = NIL;
  node oNode = RelOr(pCalledByFunc);
  
  CHALT();
  
  rBool = createNode1(1);
  rBool->putFilho(rBool, 1, oNode);
  rBool->valor = SS("BOOL");
  rBool->tipo = Tag_CCBOOL;
  rBool->validtipo = oNode->validtipo;
  rBool->validnomeobj = oNode->validnomeobj;
  rBool->isArray = oNode->isArray;
  return(rBool);
}

node RelOr(BOOL pCalledByFunc){
  node  oNode=NIL;
  node  oNode1=NIL;
  node  oNodeTerm=NIL;
  node  rRelOr=NIL;
  
  CHALT();
  
  oNodeTerm = RelCmpEq(pCalledByFunc);CHALT();
  
  if( !SL(gToken->valor,SS("||")) && !SL(gToken->valor,SS("&&")) ){
    rRelOr = oNodeTerm;
    return(rRelOr);
  }

  while( SL(gToken->valor,SS("||")) || SL(gToken->valor,SS("&&"))){
    oNode = createNode1(2);
    oNode->tipo = gToken->tipo;
    oNode->putFilho(oNode, 1, oNodeTerm);
    oNode->valor = gToken->valor;
    oNode->tipo = Tag_CCALC;
    moveToken();
    oNode1 = RelOr(pCalledByFunc);CHALT();
    oNode->putFilho(oNode, 2, oNode1);
    oNode->validtipo = oNode1->validtipo;
    oNode->validnomeobj = oNode1->validnomeobj;
  }
  rRelOr = oNode;
  return(rRelOr);
}

node RelCmpEq(BOOL pCalledByFunc){
   node  oNode=NIL;
   node  oNode1=NIL;
   node  oNodeTerm=NIL;
   node  rRelCmpEq=NIL;
  
   CHALT();
   
   oNodeTerm = RelCmp(pCalledByFunc);CHALT();
  
  if( !SL(gToken->valor,SS(">=")) && !SL(gToken->valor,SS("<=")) ){
    rRelCmpEq = oNodeTerm;
    return(rRelCmpEq);
  }

  while( SL(gToken->valor,SS(">=")) ||  SL(gToken->valor,SS("<="))){
    oNode = createNode1(2);
    oNode->putFilho(oNode, 1, oNodeTerm);
    oNode->valor = gToken->valor;
    oNode->tipo = gToken->tipo;
    oNode->tipo = Tag_CCALC;
    moveToken();
    oNode1 = RelCmpEq(pCalledByFunc);CHALT();
    oNode->putFilho(oNode, 2, oNode1);
    oNode->validtipo = oNode1->validtipo;
    oNode->validnomeobj = oNode1->validnomeobj;
  }
  
  rRelCmpEq = oNode;
  return(rRelCmpEq);
}

node RelCmp(BOOL pCalledByFunc){
  node  oNode=NIL;
  node  oNode1=NIL;
  node  oNodeTerm=NIL;
  node  rRelCmp=NIL;
  
  CHALT();
   
  oNodeTerm = RelEq(pCalledByFunc);CHALT();
  
  if( !SL(gToken->valor,SS(">")) &&  !SL(gToken->valor, SS("<")) ){
    rRelCmp = oNodeTerm;
    return(rRelCmp);
  }

   while( SL(gToken->valor,SS(">")) || SL(gToken->valor,SS("<"))){
     oNode = createNode1(2);
     oNode->putFilho(oNode, 1, oNodeTerm);
     oNode->valor = gToken->valor;
     oNode->tipo = Tag_CCALC;
     moveToken();
     oNode1 = RelCmp(pCalledByFunc);CHALT();
     oNode->putFilho(oNode, 2, oNode1);
     oNode->validtipo = oNode1->validtipo;
     oNode->validnomeobj = oNode1->validnomeobj;
  }
  rRelCmp = oNode;
  return(rRelCmp);
}

node RelEq(BOOL pCalledByFunc){
  node  oNode=NIL;
  node  oNodeEq=NIL;
  node  oNodeTerm=NIL;
  node rRelEq=NIL;
  
  CHALT();
  
  oNodeTerm = CalcMais(pCalledByFunc);CHALT();
  
  if( !SL(gToken->valor,SS("==")) && !SL(gToken->valor,SS("<>")) ){
    rRelEq = oNodeTerm;
    return(rRelEq);
  }

   while( SL(gToken->valor,SS("==")) || SL(gToken->valor,SS("<>"))){
    oNode = createNode1(2);
    oNode->tipo = gToken->tipo;
    oNode->putFilho(oNode, 1, oNodeTerm);
    oNode->valor = gToken->valor;
    oNode->tipo = Tag_CEQ;
    moveToken();
    oNodeEq = RelEq(pCalledByFunc);CHALT();
    oNode->putFilho(oNode, 2, oNodeEq);
    oNode->validtipo = oNodeEq->validtipo;
    oNode->validnomeobj = oNodeEq->validnomeobj;
  }
  rRelEq = oNode;
  return(rRelEq);
}

node CalcMais(BOOL pCalledByFunc){
  node  oNode=NIL;
  node  oNodeMais=NIL;
  node  oNodeTerm=NIL;
  node  rCalcMais=NIL;
  
  CHALT();
  
  oNodeTerm = CalcVezes(pCalledByFunc);CHALT();
  
  if( !SL(gToken->valor,SS("+")) && !SL(gToken->valor,SS("-")) ){
    rCalcMais = oNodeTerm;
    return(rCalcMais);
  }
  
   while( SL(gToken->valor,SS("+")) || SL(gToken->valor,SS("-"))){
    oNode = createNode1(2);
    oNode->tipo = Tag_CCALC;
    oNode->putFilho(oNode, 1, oNodeTerm);
    oNode->valor = gToken->valor;
    moveToken();
    oNodeMais = CalcMais(pCalledByFunc);CHALT();
    oNode->putFilho(oNode, 2, oNodeMais);
    oNode->tipo = Tag_CCALC;
    oNode->validtipo = oNodeMais->validtipo;
    oNode->validnomeobj = oNodeMais->validnomeobj;
    validAssignTipoCalcMsg(oNodeTerm->validtipo, oNodeMais->validtipo);CHALT();
  }
  rCalcMais = oNode;
  return(rCalcMais);
}

node CalcVezes(BOOL pCalledByFunc){
  node  oNode=NIL;
  node  oNode1=NIL;
  node  oNodeTerm=NIL;
  node  rCalcVezes=NIL;
  
  CHALT();
  
  oNodeTerm = CalcFator(pCalledByFunc);CHALT();
  
  if( !SL(gToken->valor,SS("*")) &&  !SL(gToken->valor,SS("/")) ){
    rCalcVezes = oNodeTerm;
    return(rCalcVezes);
  }
  
   while( SL(gToken->valor,SS("*")) ||  SL(gToken->valor,SS("/"))){
    oNode = createNode1(2);
    oNode->tipo = Tag_CCALC;
    oNode->putFilho(oNode, 1, oNodeTerm);
    oNode->valor = gToken->valor;
    moveToken();
    oNode1 = CalcVezes(pCalledByFunc);CHALT();
    oNode->putFilho(oNode, 2, oNode1);
    oNode->tipo = Tag_CCALC;
    oNode->validtipo = oNode1->validtipo;
    oNode->validnomeobj = oNode1->validnomeobj;
    validAssignTipoCalcMsg(oNodeTerm->validtipo, oNode1->validtipo);CHALT();
  }
  rCalcVezes = oNode;
  return(rCalcVezes);
}

node CalcFator(BOOL pCalledByFunc){
  node  oNode=NIL;
  node  oNodeTerm=NIL;
  node  rCalcFator=NIL;
  //Set oNodeTerm = getTerm(pCalledByFunc);
  
  CHALT();
  
  if( !SL(gToken->valor,SS("(")) ){
     oNodeTerm = getTerm(pCalledByFunc);CHALT();
     rCalcFator = oNodeTerm;
     return(rCalcFator);
  }
  
  matchToken(SS("("));CHALT();
  
  oNode = Bool(pCalledByFunc);CHALT();
  oNode->tipo = Tag_CPAROPEN;
  oNode->valor = SS("PARENTESES");
  oNode->validtipo = oNode->validtipo;
  oNode->validnomeobj = oNode->validnomeobj;
  
  matchToken(SS(")"));CHALT();
  
  rCalcFator = oNode;
  return(rCalcFator);
  
}

node getTerm(BOOL pCalledByFunc){
  BOOL  bIsArray=FALSE;
  BOOL  bGlobal=FALSE;
  int  i=0;
  int  iId=0;
  int  iIdClass=0;
  int  iTipo=0;
  int  iTipo1=0;
  int  idFunc=0;
  string  sNome=SS("");
  string  sTipo=SS("");
  string  sNomeClass=SS("");
  string  sNomeClassBase=SS("");
  string  sParte1=SS("");
  string  sParte2=SS("");
  //Object  oFunc;
  Funcao  tfunc; initFuncao(&tfunc);
  node  oNode=NIL;
  node  oNode1=NIL;
  node  b=NIL;
  node  rgetTerm=NIL;
  
  CHALT();
  
  bGlobal = FALSE;
  
  if( gToken->tipo == Tag_CCVAR ||
      gToken->tipo == Tag_CARRAY ||
      gToken->tipo == Tag_CCHAR1 ||
      gToken->tipo == Tag_CINTEGER ||
      gToken->tipo == Tag_CFLOAT ||
      gToken->tipo == Tag_CSTRING ||
      gToken->tipo == Tag_COBJ ){
    
    //;
    // Coloca constante na tabela de simbolos;
    //;
    if( gToken->tipo != Tag_CCVAR &&
        gToken->tipo != Tag_CARRAY ){
      iTipo = putConst(gToken->valor, gToken->tipo);
      rgetTerm = createNode1(0);
      rgetTerm->valor = gToken->valor;
      rgetTerm->tipo = gToken->tipo;
      rgetTerm->idConst = iTipo;
      rgetTerm->validnomeobj = SS("");
      rgetTerm->validtipo = gToken->tipo;
      if( gToken->tipo == Tag_CSTRING ){
        rgetTerm->isArray = TRUE;
        rgetTerm->tipo = Tag_CCHAR1;
        rgetTerm->validtipo = Tag_CCHAR1;
        //oNode.;
      }
      moveToken();
    }else{
      sParte1 = gToken->valor;
      iTipo1 = gToken->tipo;
      moveToken();
      if( SL(gToken->valor,SS(".")) ){
        moveToken();
        if( gToken->tipo == Tag_CCVAR ||
            gToken->tipo == Tag_CARRAY ){
          sParte2 = gToken->valor;
          iTipo = pegaTipoVar(gFuncId, sParte1, SS(""), &sNomeClassBase, &iId, &bGlobal, &bIsArray);
          iIdClass = iId;
          validObjIsInstanceadMsg(gFuncId, sParte1);CHALT();
          iTipo = pegaTipoVar(gFuncId, sParte2, sNomeClassBase, &sNomeClass, &iId, &bGlobal, &bIsArray);
          if( iTipo < 0 ){
             Err_Raise(SC(SS("E180-membro nao encontrado: "), sParte2));CHALT();
          } 
          //Verifica Array;
          moveToken();
          if( SL(gToken->valor,SS("[")) ){
            assert(bIsArray == TRUE, SC(SS("E132-variavel não é array: "),sParte2));
            moveToken();
            b = Bool(FALSE);CHALT();
            matchTokenMsg(SS("]"), SS("E133-esperado o caracter ] para fechar array"));CHALT();
            rgetTerm = createNode1(1);
            rgetTerm->putFilho(rgetTerm, 1, b);
            rgetTerm->isArrayCall = TRUE;
            rgetTerm->isArray = FALSE;
            rgetTerm->tipo = Tag_CLASSATTRIBARRAY;
          }else{
            rgetTerm = createNode1(0);
            rgetTerm->isArrayCall = FALSE;
            rgetTerm->tipo = Tag_CLASSATTRIB;
            rgetTerm->isArray = bIsArray;
          }
          
          rgetTerm->idClass = iIdClass;
          rgetTerm->valor = SC(SC(sNomeClassBase,SS(".")),sParte2);
          //getTerm.tipo = Tag->CLASSATTRIB;
          rgetTerm->validnomeobj = sNomeClass;
          rgetTerm->validtipo = iTipo;
          
        } else if( gToken->tipo == Tag_CFUNC ){
          sParte2 = gToken->valor;
          iTipo = pegaTipoVar(gFuncId, sParte1, SS(""), &sNomeClassBase, &iId, &bGlobal, &bIsArray);
          if(iTipo!=Tag_CTBTABLE){
            validObjIsInstanceadMsg(gFuncId, sParte1);CHALT();
          }
          rgetTerm = callFunctionObj(sParte1, sParte2);CHALT();
        }
      }else{
        if( pCalledByFunc == FALSE ){ //Evita que entre aqui quando for chamado por função;
          iTipo = pegaTipoVar(gFuncId, sParte1, SS(""), &sNomeClass, &iId, &bGlobal, &bIsArray);
          if( iTipo < 0 ){
             Err_Raise(SC(SS("E134-variavel não encontrada: "), sParte1));CHALT();
          }
        }
        
        //Verifica Array;
        //moveToken;
          
        if( SL(gToken->valor,SS("[")) ){
          moveToken();
          if( pCalledByFunc == FALSE ){
            assert(bIsArray == TRUE, SC(SS("E135-variavel não é array: "),sParte1));
            b = Bool(FALSE);CHALT();
          }
          matchTokenMsg(SS("]"), SS("E136-esperado o caracter ] para fechar array"));CHALT();
          if( pCalledByFunc == FALSE ){
            rgetTerm = createNode1(1);
            rgetTerm->putFilho(rgetTerm, 1, b);
            rgetTerm->isArrayCall = TRUE;
            rgetTerm->isArray = FALSE;
            rgetTerm->tipo = Tag_CCVARARRAY;
          }else{
            rgetTerm = createNode1(0);
            rgetTerm->isArrayCall = FALSE;
            rgetTerm->isArray = TRUE;
            rgetTerm->tipo = Tag_CCVAR;
          }
        }else{
          rgetTerm = createNode1(0);
          rgetTerm->isArrayCall = FALSE;
          rgetTerm->isArray = bIsArray;
          rgetTerm->tipo = Tag_CCVAR; //indica que é uma variavel;
        }
          
        rgetTerm->id = iId;
        rgetTerm->isAttribute = bGlobal;
        rgetTerm->valor = sParte1;
        rgetTerm->validnomeobj = sNomeClass;
        rgetTerm->validtipo = iTipo;
        //Call moveToken;
      }
      
    }
    
  } else if( gToken->tipo == Tag_CFUNC ){ //tratamento de função;
    sNome = gToken->valor;      //Pega o nome da função - calc(p1,p2);
    iTipo = gToken->tipo;
    rgetTerm = callFunction(sNome, iTipo);CHALT();
  }else{
     Err_Raise(SC(SS("E137-erro sintaxe, elemento não esperado na expressao: "),gToken->valor));CHALT();
  }
  
  return(rgetTerm);
}

//-------------- Pega Argumentos --------------;
node pegaArgs(BOOL pFirst){
  
  //;
  // Se pFirst = true, significa que foi passado pela raiz;
  // pegaArgs pode ter 0, 1 ou 2 nós:;
  //  0 - não foi passado parâmetros;
  //  1 - foi passado somente um parâmetro ou chegou-se ao final;
  //      da cadeia de parâmetros;
  //  2 - possui mais de 1 parâmetro e monta um encadeamento de nód args;
  //;
  node  oNode=NIL;
  node  oNode1=NIL;
  node  rpegaArgs=NIL;
  
  CHALT();
  
  if( SL(gToken->valor,SS(")")) &&  pFirst == TRUE ){
    rpegaArgs = createNode1(0); //Nao foi passado argumentos;
    rpegaArgs->valor = SS("ARGS");
    rpegaArgs->tipo = Tag_CCARGS;
    return(rpegaArgs);
  }
  
  //Set onode = getTerm(True);
  oNode = Bool(FALSE);CHALT();
  
  if( SL(gToken->valor,SS(")")) ){
    rpegaArgs = createNode1(1);
    rpegaArgs->tipo = Tag_CCARGS;
    rpegaArgs->valor = SS("ARGS");
    rpegaArgs->putFilho(rpegaArgs, 1, oNode);
    return(rpegaArgs);
  }
  
   while( SL(gToken->valor,SS(","))){
    rpegaArgs = createNode1(2);
    rpegaArgs->tipo = Tag_CCARGS;
    rpegaArgs->valor = SS("ARGS");
    rpegaArgs->putFilho(rpegaArgs, 1, oNode);
    moveToken();
    rpegaArgs->putFilho(rpegaArgs, 2, pegaArgs(FALSE));CHALT();
  }
  
   matchTokenWMoveMsg(SS(")"), SS("E138-esperado ) para fechar a expressao"));CHALT();
   
   return(rpegaArgs);
  
}

//-------------- Pega Argumentos --------------;
node pegaParDef(BOOL pFirst){
  
  BOOL  b=FALSE;
  string  sNomeClass=SS("");
  node  oNode=NIL;
  node  oNode1=NIL;
  node  oNode2=NIL;
  token  lToken;
  node rpegaParDef=NIL;
  
  CHALT();
  
  sNomeClass = SS("");
  rpegaParDef = NIL;
    
  if( SL(gToken->valor,SS(")")) ){
    return(rpegaParDef);
  }
  
  while( Not SL(gToken->valor,SS(")")) ){
    if( pFirst == FALSE ){
       matchTokenMsg(SS(","), SS("E139-esperado o carater ,"));CHALT(); //pula virgula;
    }
    lToken = gToken;
    
//   Início tratamento do objeto;
    if( lToken->tipo == Tag_CCDECLOBJ ){
       matchTokenMsg(SS("OBJECT"), SS("E140-esperada a declaracao Object"));CHALT();
       matchTokenMsg(SS("("), SS("E141-esperado ( em declaracao de Objeto"));CHALT();
       sNomeClass = gToken->valor;
       b = ReadClass(gToken->valor);
       assert(b == TRUE, SC(SS("E142-classe nao encontrada "), gToken->valor));
       matchTokenTypeMsg(Tag_CCVAR, SS("E143-esperado nome do objeto na tipificação"));CHALT();
       matchTokenWMoveMsg(SS(")"), SS("E144-esperado ) em declaracao de Objeto"));CHALT();
    } else if( lToken->tipo == Tag_CTBDECLTB ){ //testar 
       matchTokenMsg(SS("TABLE"), SS("E145-esperada a declaracao Tabela"));CHALT();
       matchTokenMsg(SS("("), SS("E146-esperado ( em declaracao da Tabela"));CHALT();
       sNomeClass = gToken->valor;
       b = ReadClass(SS("bstable"));
       assert(b == TRUE, SC(SS("E147-classe base bstable nao encontrada "),gToken->valor));
       b = ReadClass(gToken->valor);
       assert(b == TRUE, SC(SS("E148-classe nao encontrada "), gToken->valor));
       matchTokenTypeMsg(Tag_CCVAR, SS("E149-esperado nome do objeto na tipificação"));CHALT();
       matchTokenWMoveMsg(SS(")"), SS("E150-esperado ) em declaracao da Tabela"));CHALT();    
    }
//   Fim tratamento objeto;

    moveToken();
    
    oNode1 = getTerm(TRUE);CHALT();
    
    if( lToken->tipo == Tag_CCDECLCHAR ){
      oNode1->tipo = Tag_CCHAR1;
    } else if( lToken->tipo == Tag_CCDECLINT ){
      oNode1->tipo = Tag_CINTEGER;
    } else if( lToken->tipo == Tag_CCDECLLONG ){
      oNode1->tipo = Tag_CLONG;
    } else if( lToken->tipo == Tag_CCDECLOBJ ){
      oNode1->tipo = Tag_COBJ;
      //bug 1 - início _VAR__ no parâmetro
      if(SL(sNomeClass,SS("__VAR__"))){ 
         oNode1->tipo = Tag_CVAROBJ;                                   
      }
      //bug 1 - início _VAR__ no parâmetro
    } else if( lToken->tipo == Tag_CTBDECLTB ){
      oNode1->tipo = Tag_CTBTABLE;
    }else{
      oNode1->tipo = Tag_CFLOAT;
    }
    oNode2 = pegaParDef(FALSE);CHALT();
    if( isNothing(oNode2) ){
      oNode = createNode1(1);
    }else{
      oNode = createNode1(2);
      oNode->putFilho(oNode, 2, oNode2);
    }
    oNode->tipo = Tag_CCARGS;
    oNode->valor = SS("ARGS");
    
    oNode1->id = putVarFunc(gFuncId, CTIPOPARIN, oNode1->valor, oNode1->tipo, oNode1->isArray, 0, sNomeClass);
    
    oNode->putFilho(oNode, 1, oNode1);
    
    rpegaParDef = oNode;
    
    return(rpegaParDef);
    
  }
  
}

//------------------ 2a-> linguagem ---------------------;
node list2Lang(node p1){

  int  i=0;
  int  t=0;
  node rlist2Lang=NIL;
  
  CHALT();
  
  if( isNothing(p1) ){
    rlist2Lang = NIL;
    return(rlist2Lang);
  }
  
  g2Lang = SC(SC(g2Lang,p1->valor),vbCrLf);
  
  t = p1->qtdFilhos;
  for(i=0;i<t;i++ ){
     list2Lang(p1->getFilho(p1, i));
  }
  
}

string emit2Lang(node p1){
  string  s=SS("");
  string  t=SS("");
  string  u=SS("");
  string  y=SS("");
  string  z=SS("");
  string remit2Lang=SS("");
  int  id=0;
  int  idClass=0;
  node p2;
  node _p;
  
  CHALT();
  
  debug(p1);
  
  switch(p1->tipo){
    case Tag_CIF:
      s = emit2Lang(p1->getFilho(p1,1));
      t = putC(getOpNome(tag2_OIFFALSE), FALSE);
      _p = p1->getFilho(p1,2);
      if(_p != NIL){ //evitar blocos vazios
        u = emit2Lang(p1->getFilho(p1,2));
        t = SC(SC(t,Str(g2Line)),vbCrLf);
        s = SC(SC(s,t),u);
      }else{
        t = SC(SC(t,Str(g2Line)),vbCrLf);
        s = SC(s,t);
      }
      break;
      
    case Tag_CELSE:
      s = emit2Lang(p1->getFilho(p1,1));
      t = putC(getOpNome(tag2_OIFFALSE), FALSE);
      _p = p1->getFilho(p1,2);
      if(_p != NIL){ //evitar blocos vazios
        u = emit2Lang(p1->getFilho(p1,2));
        y = putC(getOpNome(tag2_OGOTO), FALSE);
        t = SC(SC(t,Str(g2Line)),vbCrLf);
        z = emit2Lang(p1->getFilho(p1,3));
        y = SC(SC(y,Str(g2Line)),vbCrLf);
        s = SC(SC(SC(SC(s,t),u),y),z);
      }else{
        y = putC(getOpNome(tag2_OGOTO), FALSE);
        t = SC(SC(t,Str(g2Line)),vbCrLf);
        y = SC(SC(y,Str(g2Line)),vbCrLf);
        s = SC(SC(s,t),y);    
      }      
      break;
      
    case Tag_CWHILE:
      t = Str(g2Line);
      s = emit2Lang(p1->getFilho(p1,1));
      u = putC(getOpNome(tag2_OIFFALSE), FALSE);
      _p = p1->getFilho(p1,2);
      if(_p != NIL){ //evitar blocos vazios
        y = emit2Lang(p1->getFilho(p1,2));
        t = putC(SC(getOpNome(tag2_OGOTO),t), FALSE);
        y = Replace(y, SS("@@BR"), Str(g2Line));
        u = SC(SC(u,Str(g2Line)),vbCrLf);
        s = SC(SC(SC(s,u),y),t);
      }else{
        t = putC(SC(getOpNome(tag2_OGOTO),t), FALSE);
        u = SC(SC(u,Str(g2Line)),vbCrLf);
        s = SC(SC(s,u),t);    
      }      
      break; 
       
    case Tag_CCBREAK:
      s = putC(SC(getOpNome(tag2_OGOTO),SS("@@BR")), TRUE);
      break;
      
    case Tag_CALLFUNC:
      if( p1->isNative == TRUE ){
        id = getIdS(p1->valor, CCONST);
        //id = id - 1;
        u = emit2Lang(p1->getFilho(p1, 1));
        s = putC(SC(getOpNome(tag2_OCALLNATV),Str(id)), TRUE);
      }else{
        id = getIDF(p1->valor);
        //id = id - 2; //porque a global nao conta???;
        id = id - 1;
        u = emit2Lang(p1->getFilho(p1, 1));
        s = putC(SC(getOpNome(tag2_OCALLF),Str(id)), TRUE);
      }
      s = SC(u,s);
      break;
      
    case Tag_CRETURN:
      u = SS("");
      if( Not isNothing(p1->getFilho(p1,1))  ){
        u = emit2Lang(p1->getFilho(p1,1));
        s = putC(getOpNome(tag2_ORET), TRUE);
      }else{
        s = putC(getOpNome(tag2_ORETNULL), TRUE);
      }
      s = SC(u,s);
      break;
      
    case Tag_CCARGS:
      if( p1->qtdFilhos > 0 ){
        t = emit2Lang(p1->getFilho(p1,1));
      }
      if( p1->qtdFilhos > 1 ){
        s = emit2Lang(p1->getFilho(p1,2));
      }
      s = SC(t,s);
      break;
      
    case Tag_CCOMMAND:
      if( p1->qtdFilhos > 0 ){
        s = emit2Lang(p1->getFilho(p1,1));
      }
      if( p1->qtdFilhos > 1 ){
        t = emit2Lang(p1->getFilho(p1,2));
      }
      s = SC(s,t);
      break;
      
    case Tag_CCOMMANDS:
      s = emit2Lang(p1->getFilho(p1,1));
      if( p1->qtdFilhos > 1 ){
        t = emit2Lang(p1->getFilho(p1,2));
      }
      s = SC(s,t);
      break;
       
    case Tag_CCBOOL:
      s = emit2Lang(p1->getFilho(p1,1));
      break;
      
    case Tag_CCALC:
      s = emit2Lang(p1->getFilho(p1,1));
      t = emit2Lang(p1->getFilho(p1,2));
      u = putC(calcSimbol(p1->valor), TRUE);
      s = SC(SC(s, t), u);
      break;
      
    case Tag_CPAROPEN:
      s = emit2Lang(p1->getFilho(p1,1));
      break;
      
    case Tag_CEQ:
      s = emit2Lang(p1->getFilho(p1,2));
      t = emit2Lang(p1->getFilho(p1,1));
      u = putC(calcSimbol(p1->valor), TRUE);
      s = SC(SC(s,t),u);
      break;
      
    case Tag_CDEF:
      gFuncId = getId(p1->valor, CFUNCAO);
      s = emit2Lang(p1->getFilho(p1,2));
      putAssembly(gFuncId, s);
      gFuncId = 0;
      s = SS("");
      break;
      
    case Tag_CASSIGN:
      s = emit2Lang(p1->getFilho(p1,1));
      t = emit2Lang(p1->getFilho(p1,2));
      s = SC(s,t);
      break;
      
    case Tag_CINTEGER:
    case Tag_CFLOAT:
    case Tag_CCHAR1:
      assert(p1->idConst != 0, SS(""));
      id = p1->idConst;
      //id = id - 1;
      s = putC(SC(getOpNome(tag2_OLOADC),Str(id)), TRUE);
      break;
      
    case Tag_CCVAR:
      id = p1->id;
      //id = id - 1;
      if( p1->isAttribute == TRUE ){
        s = putC(SC(getOpNome(tag2_OGLOADV),Str(id)), TRUE);
      }else{
        s = putC(SC(getOpNome(tag2_OLOADV),Str(id)), TRUE);
      }
      break;
      
    case Tag_CCVARARRAY:
      id = p1->id;
      //id = id - 1;
      u = emit2Lang(p1->getFilho(p1,1));
      if( p1->isAttribute == TRUE ){
        s = putC(SC(getOpNome(tag2_OGLOADVY),Str(id)), TRUE);
      }else{
        s = putC(SC(getOpNome(tag2_OLOADVY),Str(id)), TRUE);
      }
      s = SC(u,s);
      break;
      
    case Tag_CASSIGNATR:
      idClass = p1->idClass;
      //idClass = idClass - 1; 2311
      //idClass = idClass;
      u = putC(SC(getOpNome(tag2_OLOADV),Str(idClass)), TRUE);
      id = getIdS(p1->valor, CCONST);
      //id = id - 1;
      if( p1->isArrayCall == TRUE ){
        t = emit2Lang(p1->getFilho(p1,1));
        s = putC(SC(getOpNome(tag2_OOSTORVY),Str(id)), TRUE);
        s = SC(SC(t,u),s);
      }else{
        s = putC(SC(getOpNome(tag2_OOSTORV),Str(id)), TRUE);
        s = SC(u,s);
      }
      break;
      
    case Tag_CASSIGNLOC:
      id = p1->id;
      //id = id - 1;
      if( p1->isArrayCall == TRUE ){
        t = emit2Lang(p1->getFilho(p1,1));
        if( p1->isAttribute == TRUE ){
          s = putC(SC(getOpNome(tag2_OGSTORVY),Str(id)), TRUE);
        }else{
          s = putC(SC(getOpNome(tag2_OSTORVY),Str(id)), TRUE);
        }
        s = SC(t,s);
      }else{
        if( p1->isAttribute == TRUE ){
          s = putC(SC(getOpNome(tag2_OGSTORV),Str(id)), TRUE);
        }else{
          s = putC(SC(getOpNome(tag2_OSTORV),Str(id)), TRUE);
        }
      }
      break;
      
    case Tag_CLASSATTRIB:
      idClass = p1->idClass;
      //idClass = idClass - 1;
      id = getIdS(p1->valor, CCONST);
      //id = id - 1;
      u = putC(SC(getOpNome(tag2_OLOADV),Str(idClass)), TRUE);
      s = putC(SC(getOpNome(tag2_OOLOADV),Str(id)), TRUE);
      s = SC(u,s);
      break;
      
    case Tag_CLASSATTRIBARRAY:
      id = getIdS(p1->valor, CCONST);
      //id = id - 1;
      idClass = p1->idClass;
      //idClass = idClass - 1;
      //idClass = idClass;
      t = emit2Lang(p1->getFilho(p1,1));
      u = putC(SC(getOpNome(tag2_OLOADV),Str(idClass)), TRUE);
      s = putC(SC(getOpNome(tag2_OOLOADVY),Str(id)), TRUE); //executa pop na pilha para pegar o idx do array;
      s = SC(SC(t,u),s);
      break;
      
    case Tag_CLASSMETHOD: //opcode de carregamento do objeto;
      idClass = p1->idClass;
      //idClass = idClass - 1;
      id = getIdS(p1->valor, CCONST);
      //id = id - 1;
      t = emit2Lang(p1->getFilho(p1,1));
      if(p1->isAttribute == TRUE){
        u = putC(SC(getOpNome(tag2_OGLOADV),Str(idClass)), TRUE);
      }else{
        u = putC(SC(getOpNome(tag2_OLOADV),Str(idClass)), TRUE);
      }
      s = putC(SC(getOpNome(tag2_OOCALLF),Str(id)), TRUE);
      s = SC(SC(t,u),s);
      break;
      
    case Tag_CNEWARRAY: //falta o nome de objeto;
      id = p1->validtipo; //indica o tipo de variavel;
      //id = id - 1;
//      Select Case id;
//        Case Tag->CCDECLCHAR;
//          id = Tag->CCHAR1;
//        Case Tag->CCDECLINT;
//          id = Tag->CINTEGER;
//        Case Tag->CCDECLFLOAT;
//          id = Tag->CFLOAT;
//        Case Tag->CCDECLOBJ;
//          id = Tag->COBJ;
//      EndSelect;
      t = emit2Lang(p1->getFilho(p1,1));
      s = putC(SC(getOpNome(tag2_ONEWY),Str(id)), TRUE);
      s = SC(t,s);
      break;
       
    case Tag_CNEWCLASS:
      id = getIdS(p1->valor, CCONST);
      //id = id - 1;
      s = putC(SC(getOpNome(tag2_ONEW),Str(id)), TRUE);
      break; 
      
//  tabela
    case Tag_CTBAPPEND:
      t = emit2Lang(p1->getFilho(p1,1));
      u = emit2Lang(p1->getFilho(p1,2));
      s = putC(SS("tbapp "), TRUE);
      s = SC3(t,u,s);    
      break;
     
    case Tag_CTBINSERT:
      t = emit2Lang(p1->getFilho(p1,1));
      u = emit2Lang(p1->getFilho(p1,2));
      y = emit2Lang(p1->getFilho(p1,3));
      s = putC(SS("tbins "), TRUE);
      s = SC4(t,u,y,s);
      break;

    case Tag_CTBDELETE:
      t = emit2Lang(p1->getFilho(p1,1));
      u = emit2Lang(p1->getFilho(p1,2));
      y = emit2Lang(p1->getFilho(p1,3));
      s = putC(SS("tbdel "), TRUE);
      s = SC4(t,u,y,s);
      break;
    
    case Tag_CTBREAD:
      t = emit2Lang(p1->getFilho(p1,1));
      u = emit2Lang(p1->getFilho(p1,2));
      y = emit2Lang(p1->getFilho(p1,3));
      s = putC(SS("tbrea "), TRUE);
      s = SC4(t,u,y,s);
      break;
    
    case Tag_CTBLOOP:
      /*
      p2 = p1->getFilho(p1,1); 
      t = emit2Lang(p1->getFilho(p1,1));
      y = putC(SS("tblit "), Str(p2->id), TRUE);
      
      u = emit2Lang(p1->getFilho(p1,2));
      y = putC(SS("tblit "), Str(p2->id), TRUE);
      x = putC(getOpNome(tag2_OIFFALSE), FALSE);
      z = emit2Lang(p1->getFilho(p1,3));
      s = SC(SC(x,Str(g2Line)),vbCrLf);
      s = 
      
      t = Str(g2Line);
      s = emit2Lang(p1->getFilho(p1,1));
      u = putC(getOpNome(tag2_OIFFALSE), FALSE);
      y = emit2Lang(p1->getFilho(p1,2));
      t = putC(SC(getOpNome(tag2_OGOTO),t), FALSE);
      y = Replace(y, SS("@@BR"), Str(g2Line));
      u = SC(SC(u,Str(g2Line)),vbCrLf);
      s = SC(SC(SC(s,u),y),t);
      */ 
      break; 
   }
   
   remit2Lang = s;
   return(remit2Lang);
   
}

string emit2Lang2(node p1){
  int  i=0;
  int  t=0;
  int  iId=0;
  string  s=SS("");
  string  sNome=SS("");
  string  sPrg=SS("");
  node  n1=NIL;
  node  n2=NIL;
  string remit2Lang2=SS("");
  
  CHALT();
  
  s = SS("");
  t = p1->qtdFilhos;
  
  debug(p1);
  
  for(i=0;i<t;i++){
    n1 = p1->getFilho(p1, i+1);
    if( Not isNothing(n1) ){
      if( n1->tipo == Tag_CDEF ){
        sNome = n1->valor;
        gFuncId = getId(sNome, CFUNCAO);
        n2 = n1->getFilho(n1, 2);
        if( Not isNothing(n2) ){ //Função sem corpo;
          g2Line = 1;
          sPrg = emit2Lang(n2);
          if( !SL(sPrg,SS("")) ){
            sPrg = SC(sPrg,mMaqCommands[tag2_OEND][1].s); //ALTERAR
          }
          s = SC6(s,sNome,SS(":"),vbCrLf,sPrg,vbCrLf);
          //MsgBox sPrg;
          putAssembly(gFuncId, sPrg);
        }
      }else{
        s = SC(s,emit2Lang2(n1));
      }
    }
  }
  
  remit2Lang2 = SC(s,remit2Lang2);
  return(remit2Lang2);
  
}

string putC(string p1, BOOL bEnter){
  string  sEnt=SS("");
  string rputC=SS("");
  
  if( bEnter == TRUE ){
    sEnt = vbCrLf;
  }else{
    sEnt = SS("");
  }
  if( g2NumeraLinha == TRUE ){
    rputC = SC5(SS("L"),Str(g2Line),SS(": "),p1,sEnt);
  }else{
    rputC = SC(p1,sEnt);
  }
  g2Line = g2Line + 1;
  
  return(rputC);
}

string calcSimbol(string p1){
  string rcalcSimbol=SS("");     
  if(SL(p1,SS("+"))){
      rcalcSimbol = SS("add");
  }else if(SL(p1,SS("-"))){
      rcalcSimbol = SS("sub");
  }else if(SL(p1,SS("*"))){
      rcalcSimbol = SS("mul");
  }else if(SL(p1,SS("/"))){
      rcalcSimbol = SS("div");
  }else if(SL(p1,SS("<"))){
      rcalcSimbol = SS("lt");
  }else if(SL(p1,SS(">"))){
      rcalcSimbol = SS("gt");
  }else if(SL(p1,SS("=="))){
      rcalcSimbol = SS("eq");
  }else if(SL(p1,SS("<>"))){ 
      rcalcSimbol = SS("ne");   
  }else if(SL(p1,SS("<="))){
      rcalcSimbol = SS("lte");
  }else if(SL(p1,SS(">="))){
      rcalcSimbol = SS("gte");
  }else if(SL(p1,SS("&&"))){
      rcalcSimbol = SS("and");
  }else if(SL(p1,SS("||"))){
      rcalcSimbol = SS("or");
  }
  return(rcalcSimbol);
}

//---- Funcao que pega id de simbolo -----;
int getIdS(string p0, int ptipo){

  int rgetIdS = 0;
  if( gFuncId > 0 && ptipo == CVARIABLE ){
    rgetIdS = getIdVarFunc(gFuncId, p0);
  }else{
    rgetIdS = getIdElem(p0, ptipo);
  }
  
  if( rgetIdS == -1 ){
    //Trata erro;
  }
  return(rgetIdS);
  
}

//---- verifica variavel ----;
void validVarMsg(string pvar, string pmsg){
  if( validVarBase(gFuncId, pvar) == FALSE ){
     Err_Raise(SC(SS("-"),pmsg));
  }
}

//---- verifica função local;
void validFuncMsg(string pNomeFunc, string pmsg){
  if( validFuncBase(pNomeFunc) == FALSE ){
     Err_Raise(SC(SS("-"), pmsg));
  }
}

//---- verifica função local;
void validFuncMsg2(string pNomeFunc, string pmsg){
  if( validFuncBase(pNomeFunc) == TRUE ){ //achou a função;
     Err_Raise(SC(SS("-"),pmsg));
  }
}

//---- verifica parâmetros da função na chamada;
void validFuncChamadaMsg(string pReplace, string pNomeFunc, node b){
  string  sMsg;
  sMsg = validFuncLocalParBase(gFuncId, pNomeFunc, pReplace, b);
  if( !SL(sMsg,SS("0")) ){
    sMsg = SC(SS("-"),sMsg);
    Err_Raise(sMsg);
  }
}

void validVarAssignMsg(int pidFunc, string pNomeVar, string pNomeClass){
  BOOL  b=FALSE;
  string  sMsg=SS("");
  b = validVarAssignBase(pidFunc, pNomeVar, pNomeClass);
  if( b == FALSE ){
    sMsg = SC3(SS("E151-variavel "),pNomeVar,SS(" nao encontrada"));
    Err_Raise(sMsg);
  }
}

void validVarAssignObjMsg(int pidFunc, string pNomeVarE, string pNomeVarD){
  int  i=0;
  string  sMsg=SS("");
  sMsg = SS("");
  i = validVarAssignObjBase(pidFunc, pNomeVarE, pNomeVarD);
  switch(i){
    case 1:
      sMsg = SS("E152-erro em identificação de variavel");
      break;
    case 2:
      sMsg = SC(SS("E153-variavel nao encontrada: "),pNomeVarE);
      break;
    case 3:
      sMsg = SC(SS("E154-variavel nao encontrada: "),pNomeVarD);
      break;
    case 4:
      sMsg = SC(SS("E155-variavel nao é objeto: "),pNomeVarE); 
      break;
    case 5:
      sMsg = SC(SS("E156-variavel nao é objeto: "),pNomeVarD);
      break;
    case 6:
      sMsg = SC4(SS("E157-tipos diferentes das variaveis: "),pNomeVarE,SS("-"),pNomeVarD);
      break;
  }
  if( !SL(sMsg,SS("")) ){
     Err_Raise(sMsg);
  }
}

void validVarAssignObjNewMsg(int pidFunc, string pNomeVarE, string pNomeVarEClass, string pNomeClass){
  int  i=0;
  string  sMsg=SS("");
  i = validVarAssignObjNewBase(pidFunc, pNomeVarE, pNomeVarEClass, pNomeClass);
  sMsg = SS("");
  switch(i){
    case 1:
     sMsg = SS("E158-erro em identificação de variavel");
     break;
    case 2:
     sMsg = SC(SS("E159-variavel nao encontrada: "),pNomeVarE);
     break;
    case 3:
     sMsg = SC(SS("E160-variavel nao e objeto: "),pNomeVarE);
     break;
    case 4:
     sMsg = SC4(SS("E161-tipo de objeto diferente do associado: "),pNomeVarE,SS("."),pNomeClass);
     break;
  } 
  if( !SL(sMsg,SS("")) ){
     Err_Raise(sMsg);
  }
}

void validAssignTipoCalcMsg(int pTipoE, int pTipoD){
  string  sMsg=SS("");
  sMsg = SS("E162-calculos devem ser efetuados com tipos INT ou LONG");
  if( pTipoE != Tag_CINTEGER && pTipoE != Tag_CFLOAT && pTipoE != Tag_CLONG){
      Err_Raise(sMsg);
  }
  if( pTipoD != Tag_CINTEGER && pTipoD != Tag_CFLOAT && pTipoD != Tag_CLONG){
      Err_Raise(sMsg);
  }
}

 void validObjIsInstanceadMsg(int pidFunc, string pNomeVarE){
   int  i=0;
   string  sMsg=SS("");
   sMsg = SS("");
   i = validObjIsInstanceadBase(pidFunc, pNomeVarE);
   switch(i){
   case 1:
     sMsg = SS("E163-erro em identificacao de variavel");
     break;
   case 2:
     sMsg = SC(SS("E164-variavel nao encontrada: "), pNomeVarE);
     break;
   case 3:
     sMsg = SC(SS("E165-variavel nao e objeto: "), pNomeVarE);
     break;
   case 4:
     //sMsg = SC(SS("objeto nao instanciado: "), pNomeVarE);
     break;
  }
  if( !SL(sMsg,SS("")) ){
     Err_Raise(sMsg);
  }
}

void validFuncReturnOk(int pCtxFuncId, string pnomef, BOOL pcheckret, int ptipo, string pclass, BOOL parray){
   int  i=0;
   string  sMsg=SS("");
   sMsg = SS("");
   i = validFuncReturnOkBase(pCtxFuncId, pcheckret, ptipo, pclass, parray);
   switch(i){
     case 1:
       sMsg = SC(SS("E166-falta comando return na funcao: "),pnomef);
       break;
     case 2:
       sMsg = SC(SS("E167-a funcao deve retornar valor: "),pnomef);
       break;
     case 3:
       sMsg = SC(SS("E168-tipo de retorno diferente do tipo esperado na função: "),pnomef);
       break;
     case 4:
       sMsg = SC(SS("E169-objeto de retorno diferente do esperado na função: "),pnomef);
       break;
     case 5:
       sMsg = SC(SS("E170-erro de tipos com array no retorno da função: "), pnomef);
       break;
     case 6:
       sMsg = SC(SS("E171-a função nao retorna valores: "),pnomef);
       break;
     case 7:
       sMsg = SC(SS("E172-tipo de retorno no array está incorreto, funcao: "),pnomef);
       break;
  }
  
  if( ! SL(sMsg,SS("")) ){
     Err_Raise(sMsg);
  }
  
}

/*
void assert(BOOL pbol, string pmsg){
  if( pbol == FALSE ){
     Err->Raise(vbObjectError + 513, "Compilador", "linha " & gToken->linha & "-" & pmsg);
  }
}

*/
int pegaTipoVar(int pidFunc, string pNomeVar, string pNomeClass, string *pclass, int *pId, BOOL *pbGlobal, BOOL *pisArray){
   BOOL  b=FALSE;
   string  sMsg=SS("");
   Variable  tvar; initVar(&tvar);
   int rpegaTipoVar = -1;
   b = pegaVarFuncClass(pidFunc, pNomeVar, pNomeClass, &tvar, FALSE, pId, pbGlobal, pisArray);
   if( b == TRUE ){
     rpegaTipoVar = tvar.tipo;
     *pclass = tvar.nomeobj;
  }
  return(rpegaTipoVar);
}

string getOpNome(int p1){
  string rgetOpNome = mMaqCommands[p1][1].s;
  return(rgetOpNome);
}

unsigned char getOpCod(int p1){
  unsigned char rgetOpCod = mMaqCommands[p1][2].i;
  return(rgetOpCod);
}

unsigned char getOpCodByName(string p1){
  int i;
  unsigned char rgetOpCodByName = 0;
  for(i = 0;i<=CMAQCOMMANDS;i++){
    if(SL(Trim(mMaqCommands[i][1].s),p1)){
      rgetOpCodByName =mMaqCommands[i][2].i;
      return(rgetOpCodByName);
      }
  }
}

int getStackCodByName(string p1){
  int i=0;
  int rgetStackCodByName = 0;
  for(i = 0;i<=CMAQCOMMANDS; i++){
    if( SL(Trim(mMaqCommands[i][1].s),p1)){
      rgetStackCodByName = mMaqCommands[i][3].i;
      return(rgetStackCodByName);
    }
  }
}

BOOL validIsWorkArea(string s1, int pi){
     
     BOOL b = TRUE;
     return(b);
     
}

BOOL validIsTable(string s1, int pi){
 
     BOOL b = TRUE;
     return(b);
     
}

void rquit(int pErr, string s){
     string ss = SC5(SS("linha "),Str(gToken->linha),SS("-"),s, vbCrLf);
     //string ss = SC(s, vbCrLf);
     gErrNum = 4;
     gErrMsg = ss;
     gErrQtMsg = TRUE;
     //intf(ss->c);
     //stem("PAUSE");	
     //it(1);
}


void debug(node n){

  /*
  if(gidebug == 7){
  gidebug = 8;
  }else{
    gidebug++;    
  }
  */
  if(gdebugnode==1){
    string s = tg(n->tipo);
    printf("%i - qtd filhos: %i comando %i - %s.\n", gidebug, n->qtdFilhos, n->tipo, s->c);
  }
  //system("PAUSE");

} 

/*
void CHALT(){
     if(gErrNum != 0){
       return;
     }
}
*/

void lg1(string s){
  if(gdebuglg2==1) printf("\nlog:%s",s->c);   
}

void lg2(string s){
  if(gdebuglg2==1)  printf("\nlog:%s",s->c);   
}


