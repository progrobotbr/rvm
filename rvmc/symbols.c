#include <stdio.h>
#include "zzdata.h"

//-------------------------------------------------------------------;
void initSymbols(){
     
  gQtdSymbols = -1;
  gQtdVar     = -1;
  gQtdFunc    = -1;
  gQtdFuncId  = -1;
  gQtdConst   = -1;
  marray_sym = newarray(sizeof(Elem));
  
}

int putVar(string pNome, int ptipo, BOOL pisArray, int pArrayTam, string pNomeClass){
                
  Variable tvar;  initVar(&tvar);
  Elem     telem; initElem(&telem);
  int      rputVar = 0;
  
  gQtdSymbols = 1 + gQtdSymbols;
  //ReDim Preserve mSymbols(qtdSymbols);
  mSymbols =(Elem *) redim(marray_sym, gQtdSymbols+1, TRUE);
  
  tvar.nome = pNome;
  tvar.tipo = ptipo;
  tvar.isArray = pisArray;
  tvar.arrayTam = pArrayTam;
  tvar.nomeobj = pNomeClass;
  telem.id = gQtdVar;
  telem.nome = pNome;
  telem.var = tvar;
  telem.objtp = CVARIABLE;
  gQtdVar = gQtdVar + 1;
  mSymbols[gQtdSymbols] = telem;
  rputVar = gQtdSymbols;
  return(rputVar);
  
}

int putFunc(string pNome, int ptipo, string pNomeObj, BOOL pisArray, BOOL pbIsNative){
                 
  Funcao  tfunc; initFuncao(&tfunc);
  Elem  telem;   initElem(&telem);
  int rputFunc=0;
  
  gQtdSymbols = gQtdSymbols+1;
  gQtdFunc    = gQtdFunc+1;
  gQtdFuncId  = gQtdFuncId+1;
  
  //ReDim Preserve mSymbols(qtdSymbols);
  mSymbols = (Elem*) redim(marray_sym,gQtdSymbols+1,TRUE);
  
  tfunc.id         = gQtdFuncId;
  tfunc.nome       = pNome;
  tfunc.rettipo    = ptipo;
  tfunc.retnomeobj = pNomeObj;
  tfunc.retarray   = pisArray;
  tfunc.isNative   = pbIsNative;
  tfunc.array_varLocal = newarray(sizeof(Variable));
  telem.id     = gQtdFunc;
  telem.nome   = pNome;
  telem.Funcao = tfunc;
  telem.objtp  = CFUNCAO;
  mSymbols[gQtdSymbols] = telem;
  rputFunc = gQtdSymbols;
  
  return(rputFunc);
  
}

void putFuncClass(string pNomeClass, Funcao tfunc){
  string  sNomeObj=SS("");
  Elem  telem; initElem(&telem);
  array array_sym;
  
  gQtdSymbols = 1 + gQtdSymbols;
  gQtdFunc = 1 + gQtdFunc;
  gQtdFuncClass = 1 + gQtdFuncClass;
  sNomeObj = SC(SC(pNomeClass, SS(".")),tfunc.nome);
  
  mSymbols = (Elem *)redim(marray_sym, gQtdSymbols+1, TRUE);
  //ReDim Preserve mSymbols(qtdSymbols);
  telem.id = gQtdFunc;
  telem.nome = sNomeObj;
  telem.Funcao = tfunc;
  telem.objtp = CFUNCAO;
  telem.bngrava = TRUE;
  
  mSymbols[gQtdSymbols] = telem;
  
}


int putVarFunc(int pId, int pTipoLoc, string pNomeVar, int pTipoVar, BOOL pisArray, int pArrayTam, string pNomeClass){
                    
  int       i=0;
  BOOL      bPar=FALSE;
  Variable  tvar;  initVar(&tvar);
  Funcao    tfunc; initFuncao(&tfunc);
  Elem      telem; initElem(&telem);
  int rputVarFunc=0;
  
  rputVarFunc = -1;
  
  if( mSymbols[pId].id == GLOBALS && mSymbols[pId].objtp == CFUNCAO ){
    gQtdVar = gQtdVar + 1;
  }
  
  tvar.nome = pNomeVar;
  tvar.tipo = pTipoVar;
  tvar.arrayTam = pArrayTam;
  if( pisArray == TRUE ){
    tvar.isArray = 1;
  }else{
    tvar.isArray = 0;
  }
  tvar.nomeobj = pNomeClass;
  
  tfunc = mSymbols[pId].Funcao;
 
  if( pTipoLoc == CTIPOPAROUT || pTipoLoc == CTIPOPARIN ){
    bPar = TRUE;
  }else{
    bPar = FALSE;
  }
  
  tvar.isParameter = bPar;
  
  i = tfunc.qtdVar;
  i = i + 1;
  
  //ReDim Preserve tfunc->varLocal(i);
  tfunc.varLocal = (Variable *) redim(tfunc.array_varLocal, i, TRUE);
  
  tvar.isParameter = bPar;
  tfunc.varLocal[tfunc.qtdVar] = tvar;
  tfunc.qtdVar = i;
  if( bPar == TRUE ){
    tfunc.parQtdVar = 1 + tfunc.parQtdVar;
  }

  mSymbols[pId].Funcao = tfunc;
  rputVarFunc = i;
  return(rputVarFunc);
  
}

int putConst(string pNome, int ptipo){
  int  i=0;
  int rputConst=0;
  Elem  telem; initElem(&telem);
  
  i = getIdElem(pNome, CCONST);
  if( i > -1 ){
    rputConst = i;
    return(rputConst);
  }
  gQtdSymbols = 1 + gQtdSymbols;
  gQtdConst = 1 + gQtdConst;
  
  mSymbols = (Elem *) redim(marray_sym, gQtdSymbols+1,TRUE);
  //ReDim Preserve mSymbols(qtdSymbols);
  telem.id = gQtdConst;
  telem.nome = pNome;
  telem.objtp = CCONST;
  telem.tipoData = ptipo;
  
  mSymbols[gQtdSymbols] = telem;
  rputConst = gQtdConst;
  
  return(rputConst);
  
}

int getId(string p0, int pObjTipo){
  int   i=0;
  int   rgetId=0;
  Elem  telem; initElem(&telem);
  rgetId = -1;
  
  for(i=0; i<=gQtdSymbols; i++){
    telem = mSymbols[i];
    if(SL(telem.nome,p0) && telem.objtp == pObjTipo){
      rgetId = i;
      return(rgetId);
    }
  }
  return(rgetId);
}

int getIDF(string p0){
  int   i=0;
  int   rgetIDF=0;
  Elem  telem; initElem(&telem);
  rgetIDF = -1;
  
  for( i = 0; i<=gQtdSymbols; i++){
    telem = mSymbols[i];
    if( SL(telem.nome,p0) && telem.objtp == CFUNCAO ){
      rgetIDF = telem.Funcao.id;
      return(rgetIDF);
    }
  }
  return(rgetIDF);
}

int getIdElem(string p0, int pObjTipo){
  int i=0, rgetIdElem=0;
  Elem  telem; initElem(&telem);
  rgetIdElem = -1;
  
  for( i = 0; i<=gQtdSymbols; i++){
    telem = mSymbols[i];
    if( SL(telem.nome,p0) && telem.objtp == pObjTipo ){
      rgetIdElem = telem.id;
      return(rgetIdElem);
    }
  }
  return(rgetIdElem);
}

int getIdVarFunc(int pidFunc, string pNome){
  int i=0;
  int rgetIdVarFunc=0;
  Funcao  tfunc; initFuncao(&tfunc);
  
  rgetIdVarFunc = -1;
  tfunc = mSymbols[pidFunc].Funcao;
  for( i = 0; i<tfunc.qtdVar; i++){
    if( SL(tfunc.varLocal[i].nome,pNome) ){
      rgetIdVarFunc = i - 1;
      return(rgetIdVarFunc);
    }
  }
  return(rgetIdVarFunc);
}

void putAssembly(int pId, string pPrg){
  Funcao  tfunc;
  initFuncao(&tfunc);
  tfunc = mSymbols[pId].Funcao;
  tfunc.prgAssembly = SC(tfunc.prgAssembly,pPrg);
  mSymbols[pId].Funcao = tfunc;
}

string getAssembly(){
  string rgetAssembly = mSymbols[0].Funcao.prgAssembly;
  return(rgetAssembly);
}

void putNomeClass(string pNome){
  gNomeClass_ = pNome;
}
//---------------------------------------------;
//  ///          Grava Arquivo            ///;
void mv_pt_arr_3(char *o, char *d){
   d[0] = o[0];
   d[1] = o[1];
   d[2] = o[2];
}

void gravaVarFunc(int pQtdVar, Variable *pvar){

  int  i=0;
  int  t=0;
  string  sTip=SS("");
  string  sTam=SS("");
  LV1  mVar;
  QT   mGen;  //Gen -> genérico;
  
  if( pQtdVar == 0 ){
    return;
  }
  
  t = pQtdVar; //verificar
  
  sTip = SS("FVL");
  sTam = SS("FVQ");
 
  //t = UBound(pvar);
  t = pQtdVar;
  //mv_pt_arr_3(sTam->c,mGen.linha);
  mGen.qtdItem = t;
  
  //Put #1, , mGen;
  rput(gGravaFp,(U1 *) &mGen,SS("FVQ"));
  
  for( i = 0; i<t; i++){
    //mv_pt_arr_3(sTip->c, mVar.linha);
    mVar.id    = i;
    mVar.tipo  = pvar[i].tipo;
    mVar.isArray  = pvar[i].isArray;
    mVar.tamArray = pvar[i].arrayTam;
    mVar.nome = pvar[i].nome;
    if( pvar[i].isParameter == TRUE ){
      mVar.isParameter = 1;
    }else{
      mVar.isParameter = 0;
    }
    mVar.nomeobj = pvar[i].nomeobj;
    //Put #1, , mVar;
    rput(gGravaFp,(U1 *)&mVar,SS("FVL"));
  }
  
}

void gravaFunc(int pId){
  int  i=0;
  int  iTamStack=0;
  Elem  telem; initElem(&telem);;
  Funcao  tfunc; initFuncao(&tfunc);
  Variable  tvar; initVar(&tvar);
  FD1  mFd1;
  LV1  mLv1;
  int  iQtdOp=0;
  string s=SS("");
   
  tfunc = mSymbols[pId].Funcao;
  
  lg1(tfunc.nome);
//  //Valida globals;
//  if( mSymbols(pId)->id = GLOBALS ){
//    return();{
//  }
//;

  lg1(SS("inigenbytefun"));
  
  /****** DEBUG *******/
  /*
  if(SL(tfunc.nome,SS("CALC2"))){
    gdebuglg2 = 1;
  }else{
    gdebuglg2=0;
  }
  */                              
  iQtdOp = getByteCode(tfunc.prgAssembly, &iTamStack);
  lg1(SS("inigenbytefun"));
  
  if(gdebuglg2==1){
     imprimeByteCode();               
  }
  
  s = SS("FD1");
  //mv_pt_arr_3(s->c, mFd1.linha);
  //mFd1->linha = SS("FD1");
  mFd1.id = mSymbols[pId].id;
  //mFd1.ntamopcode = gQtdBuffer;
  mFd1.ntamopcode = array_mbuffer->len;
  mFd1.nome = tfunc.nome;
  mFd1.qtdVar = tfunc.qtdVar;
  mFd1.parQtdVar = tfunc.parQtdVar;
  mFd1.rettipo = tfunc.rettipo;
  mFd1.retnomeobj = tfunc.retnomeobj;
  //mFd1.ntamopcode = gQtdBuffer;
  mFd1.ntamstack = iTamStack;
  if( tfunc.retarray == TRUE ){
    mFd1.retarray = 1;
  }else{
    mFd1.retarray = 0;
  }
  if( tfunc.isNative == TRUE ){
    mFd1.isNative = 1;
  }else{
    mFd1.isNative = 0;
  }
  
  mFd1.byteop = iQtdOp;
  
  lg1(SS("inigravavarfun"));
  
  //Put #1, , mFd1;
  rput(gGravaFp,(U1 *)&mFd1,SS("FD1"));
  
  gravaVarFunc(tfunc.qtdVar, tfunc.varLocal);
  
  lg1(SS("fimgravavarfun"));
  
  if( iQtdOp > 0 ){
    lg1(SS("inigravabytefun"));  
    //Put #1, , "BC1";
    rput(gGravaFp,(U1 *)"BC1",SS("BC1"));
    //Put #1, , mBuffer;
    rput2(gGravaFp,mBuffer,SS("BUF"), array_mbuffer->len);
    lg1(SS("fimgravabytefun"));  
  }
  
}


void gravaAtributos(){
  int  i=0;
  Variable  tvar; initVar(&tvar);
  
  for( i = 0; i<=gQtdSymbols; i++){
      if( mSymbols[i].id == GLOBALS && mSymbols[i].objtp == CFUNCAO ){
         gravaFunc(i);
         return;
      }
  }
}

void gravaHeaderClass(){
  int  i=0;
  int  iQtdFunc=0;
  CL1  mCl1;
  string s=SS("");
  
  for( i = 0; i<=gQtdSymbols; i++){
    if( mSymbols[i].objtp == CFUNCAO && mSymbols[i].bngrava == FALSE ){
      iQtdFunc = iQtdFunc + 1;
    }
  }
  s = SS("CL1");
  //mCl1.linha = "CL1";
  //mv_pt_arr_3(s->c,mCl1.linha);
  mCl1.iqtdcons = gQtdConst+1;
  mCl1.iQtdFunc = iQtdFunc;
  mCl1.iqtdvglo = gQtdVar+1;
  mCl1.sNome = gNomeClass_;
  //Put #1, , mCl1;
  rput(gGravaFp,(U1 *)&mCl1,SS("CL1"));
  
}

void gravaQtdFunc(){
  int  i=0;
  int  iQtdFunc=0;
  QT  mCTQ;
  Elem  telem; initElem(&telem);
  string s=SS("");
  
  iQtdFunc = 0;
  for( i = 0; i<=gQtdSymbols; i++){
    if( mSymbols[i].objtp == CFUNCAO && mSymbols[i].bngrava == FALSE ){
      iQtdFunc = iQtdFunc + 1;
    }
  }
  
  s = SS("FQT");
  //mCTQ->linha = SS("FQT");
  //mv_pt_arr_3(s->c, mCTQ.linha);
  mCTQ.qtdItem = iQtdFunc;
  //Put #1, , mCTQ;
  rput(gGravaFp,(U1 *)&mCTQ,SS("FQT"));
}

void gravaConstantes(){
  //CTQ;
  //CT1;
  int  i=0;
  int  iQtdConst=0;
  CT1  mCt1;
  QT   mCTQ;
  Elem  telem; initElem(&telem);
  string s=SS("");
  
  iQtdConst = 0;
  for( i = 0; i<=gQtdSymbols; i++){
    if( mSymbols[i].objtp == CCONST ){
      iQtdConst = iQtdConst + 1;
    }
  }
  
  s = SS("CTQ");
  //mv_pt_arr_3(s->c, mCTQ.linha);
  //mCTQ->linha = SS("CTQ");
  mCTQ.qtdItem = iQtdConst;
  //Put #1, , mCTQ;
  rput(gGravaFp,(U1 *)&mCTQ,SS("CTQ"));
  
  for( i = 0; i<=gQtdSymbols; i++){
    if( mSymbols[i].objtp == CCONST ){
      telem = mSymbols[i];
      s = SS("CT1");
      //mv_pt_arr_3(s->c, mCt1.linha); // = SS("CT1");
      mCt1.id = telem.id;
      mCt1.tipoData = telem.tipoData;
      mCt1.tam = Len(telem.nome);
      mCt1.nome = telem.nome;
      //Put #1, , mCt1;
      rput(gGravaFp,(U1 *)&mCt1,SS("CT1"));
    }
  }
  
}

//---------------------------------------------;
void GravaArquivoF(){
  int  i=0;
  string  sNomeFile=SS("");
  
  sNomeFile = SC3(gPath,gNomeClass_,gExtComp);

  //Open sNomeFile for( Binary Access #1  Write;
  gGravaFp = fopen(SG(sNomeFile),"wb");
  
  gravaHeaderClass();lg1(SS("grhr"));
  gravaConstantes();lg1(SS("grcs"));
  gravaAtributos();lg1(SS("gratr"));
  gravaQtdFunc();lg1(SS("grqtf"));
  
  for( i = 0; i<=gQtdSymbols; i++){
      if( mSymbols[i].id > GLOBALS && mSymbols[i].objtp == CFUNCAO && mSymbols[i].bngrava == FALSE ){
         lg1(SS("grfun")); 
         gravaFunc(i);
      }
  }
  
  lg1(SS("grfim"));  
  fclose(gGravaFp);
}


int getByteCode(string pDados,int * ptamStack){
  
  BOOL  bGoto=FALSE;
  int  i=0;
  short int i1=0;
  int  iIdx=0;
  int  iQtdOp=0;
  int  iStack=0;
  int  iStack1=0;
  int  iStack2=0;
  unsigned char b1=' ';
  unsigned char *b2=NIL;
  string  sOpNome=SS("");
  token oTok=newToken();
  int  *lLin=NIL;
  array array_llin = newarray(sizeof(int));
  int rgetByteCode=0;
  iQtdOp = 0;
  
  iIdx = 0;
  i = 0;
  iStack1 = 0;
  iStack2 = 0;
  
  lg2(SS("f1"));
  initParseToken(pDados);
  lg2(SS("f2"));
  while( oTok->tipo != Tag_CENDPROGRAM){
    oTok = getToken();
    if( !SL(Trim(oTok->valor),SS("")) && oTok->tipo != Tag_CENDPROGRAM ){
      if( oTok->tipo == Tag_CINTEGER ){
        iIdx = iIdx + 2;
      }else{
        i = i + 1;
        iIdx = iIdx + 1;
        //ReDim Preserve lLin(i);
        lg2(SC3(SS("f2a"),oTok->valor,Str(i)));
        lg2(SS("f2a"));
        lLin = (int *)redim(array_llin,i+1,TRUE);
        lLin[i] = iIdx;
        lg2(SS("f2b"));
        //calcula stack;
        sOpNome = LCase(oTok->valor);
        iStack = getStackCodByName(sOpNome);
        iStack1 = iStack1 + iStack;
        if( iStack1 > iStack2 ){
          iStack2 = iStack1;
        }
        //fim calcula stack;
      }
    }
  }
  
  lg2(SS("f3"));
  *ptamStack = iStack2;
  
  //;
  // Geração dos bytes codes;
  //;
  
  //if(gdebuglg2 ==1) {
  //   printf("a");          
  //}
  
  oTok = newToken();
  
  initParseToken(pDados);
  initBufferBytes();

  bGoto = FALSE;
  iIdx = 0;
  while( oTok->tipo != Tag_CENDPROGRAM){
    
    //if(array_mbuffer->len > 185){
      // printf("a");                   
    //}
    oTok = getToken();
    if( !SL(Trim(oTok->valor),SS("")) && oTok->tipo != Tag_CENDPROGRAM ){
      if( oTok->tipo == Tag_CINTEGER ){
        if( bGoto == TRUE ){
          i = CInt(oTok->valor);
          i = lLin[i];
          i--;
        }else{
          i = CInt(oTok->valor);
        }
        i1 = i;
        b2 = (unsigned char *)&i1;
        bufferBytes(b2[0]);
        bufferBytes(b2[1]);
        bGoto = FALSE;
      }else{
        sOpNome = LCase(oTok->valor);
        b1 = getOpCodByName(sOpNome);
        bufferBytes(b1);
        iQtdOp = iQtdOp + 1;
        if(SL(sOpNome,SS("iffalse"))){
            bGoto = TRUE;
        }else if(SL(sOpNome,SS("goto"))){
            bGoto = TRUE;
        }
      }
      rgetByteCode = iQtdOp;
      iIdx = iIdx + 1;
    }
    
  }
  
  lg2(SS("f4"));
  return(rgetByteCode);
  
}


void bufferBytes(unsigned char b){
  gQtdBuffer = gQtdBuffer + 1;
  //ReDim Preserve mBuffer(gQtdBuffer);
  mBuffer = (unsigned char *) redim(array_mbuffer,gQtdBuffer,TRUE);
  mBuffer[gQtdBuffer-1] = b;
}

void initBufferBytes(){
  gQtdBuffer = 0;
  //ReDim mBuffer(1);
  array_mbuffer = newarray(sizeof(unsigned char));
  mBuffer = (unsigned char *) redim(array_mbuffer,1,FALSE);
  
}

//;
// Ler arquivo;
//;
BOOL ReadClass(string pNome){
  int  i=0;
  int  t=0;
  int  i1=0;
  int  iQtdFun=0;
  int  iQtdVar=0;
  int  iQtdCos=0;
  string  sFile=SS("");
  string  sNome=SS("");
  //Dim Byte  mBuffer();
  char *sStr=NIL;
  QT   mGen;
  LV1  mVar;
  CL1  mCl1;
  CT1  mCt1;
  QT  mQt;
  FD1  mF;
  Funcao  tfunc; initFuncao(&tfunc);
  BOOL rReadClass=FALSE;
  array array_funcao;
  
  if( pegaIdFunc(SC(pNome,SS("._globals_"))) > 0 ){
    rReadClass = TRUE;
    return(rReadClass);
  }
  
  sFile = SC3(gPath,pNome,gExtComp);
  //Open sFile for( #1  Binary;
  gReadFp = fopen(SG(sFile), "rb");
  assert(gReadFp!=0,SC(SS("E173-Arquivo binário ao encontrado "),sFile));
  //input;
  //Get #1, , mCl1;
  read(gReadFp,(U1 *)&mCl1,SS("CL1"));
  
  iQtdFun = mCl1.iQtdFunc;
  iQtdVar = mCl1.iqtdvglo;
  iQtdCos = mCl1.iqtdcons;
  
  //pula constantes;
  //Get #1, , mQt;
  read(gReadFp, (U1 *)&mQt,SS("CTQ"));
  iQtdCos = mQt.qtdItem;
  for(i = 0; i<iQtdCos; i++){;
    //Get #1, , mCt1;
    read(gReadFp,(U1 *)&mCt1,SS("CT1"));
  }
  
  //pega Atributos _globals_
  //Get #1, , mF;
  read(gReadFp, (U1 *)&mF, SS("FD1"));
  tfunc.nome       = mF.nome;
  tfunc.qtdVar     = mF.qtdVar;
  tfunc.parQtdVar  = mF.parQtdVar;
  tfunc.retnomeobj = mF.retnomeobj;
  tfunc.rettipo    = mF.rettipo;
  if( mF.isNative == 1 ){
    tfunc.isNative = TRUE;
  }else{
    tfunc.isNative = FALSE;
  }
  if( mF.retarray == 1 ){
    tfunc.retarray = TRUE;
  }else{
    tfunc.retarray = FALSE;
  }
  
  if( mF.qtdVar > 0 ){
    //Get #1, , mGen;
    read(gReadFp,(U1 *)&mGen,SS("FVQ"));
    t = mGen.qtdItem;
    
    //ReDim tfunc->varLocal(t);
    array_funcao = newarray(sizeof(struct _Variable));
    tfunc.varLocal = (struct _Variable *) redim( array_funcao, t, FALSE);
    
    for( i1 = 0; i1<t; i1++){
      //Get #1, , mVar;
      read(gReadFp,(U1 *)&mVar,SS("FVL"));
      sNome = SC(SC(mCl1.sNome,SS(".")),mVar.nome);
      putConst(sNome, CCONST);
      tfunc.varLocal[i1].nome     = mVar.nome;
      tfunc.varLocal[i1].tipo     = mVar.tipo;
      tfunc.varLocal[i1].isArray  = mVar.isArray;
      tfunc.varLocal[i1].arrayTam = mVar.tamArray;
      tfunc.varLocal[i1].nomeobj  = mVar.nomeobj;
      if( mVar.isParameter == 1 ){
        tfunc.varLocal[i1].isParameter = FALSE;
      }else{
        tfunc.varLocal[i1].isParameter = TRUE;
      }
    }
  }
  
  putFuncClass(mCl1.sNome, tfunc);
    
  //Quantidade de funções;
  //Get #1, , mQt;
  read(gReadFp,(U1 *)&mQt,SS("FQT"));  
  //Pega funções;
  for( i = 0; i < mCl1.iQtdFunc-1; i++ ){
    //Get #1, , mF;
    read(gReadFp,(U1 *)&mF,SS("FD1"));
    
    sNome = SC(SC(mCl1.sNome, SS(".")),mF.nome);
  
    tfunc.nome = mF.nome;
    tfunc.qtdVar = mF.qtdVar;
    tfunc.parQtdVar = mF.parQtdVar;
    tfunc.retnomeobj = mF.retnomeobj;
    tfunc.rettipo = mF.rettipo;
  
    if( mF.qtdVar > 0 ){
      //Get #1, , mGen;
      read(gReadFp,(U1 *)&mGen,SS("FVQ"));
      t = mGen.qtdItem;
      
      //ReDim tfunc->varLocal(t);
      array_funcao = newarray(sizeof(struct _Variable));
      tfunc.varLocal = (struct _Variable *)redim( array_funcao, t, FALSE);
      //tfunc->varLocal = (struct _Variable *)array_funcao->obj;
    
      for( i1 = 0; i1<t; i1++){
        //Get #1, , mVar;
        read(gReadFp,(U1 *)&mVar,SS("FVL"));
        tfunc.varLocal[i1].nome = mVar.nome;
        tfunc.varLocal[i1].tipo = mVar.tipo;
        tfunc.varLocal[i1].isArray = mVar.isArray;
        tfunc.varLocal[i1].arrayTam = mVar.tamArray;
        tfunc.varLocal[i1].isParameter = mVar.isParameter;
        tfunc.varLocal[i1].nomeobj = mVar.nomeobj;
      }
    }
  
    if( mF.byteop > 0 ){
      //Get #1, , sStr;
      read(gReadFp,(U1 *)sStr,SS("BC1"));
      //Get #1, , mBuffer;
      //mBuffer = Input(mF->ntamopcode, #1);
      read2(gReadFp,mBuffer,SS("OPC"),mF.ntamopcode);
    }
    
     putFuncClass(mCl1.sNome, tfunc);
    
  }
  
  close(gReadFp);
  
  rReadClass = TRUE;
  return(rReadClass);  
  
}


//;
// Validação;
//;
BOOL validVarBase(int pFuncId, string pvar){
  BOOL  b=FALSE;
  int  i=0;
  int  t=0;
  Elem  telem; initElem(&telem);
  BOOL rvalidVarBase=FALSE;
  
  b = TRUE;
  if( pFuncId > 0 ){
    i = getIdVarFunc(pFuncId, pvar);
    if( i > 0 ){
      b = FALSE;
    }
  }else{
    t = -1;
    for( i = 1; i<=gQtdSymbols; i++){
      telem = mSymbols[i];
      if( SL(telem.nome,pvar) && telem.objtp == CVARIABLE ){
        b = FALSE;
        break;
      }
    }
  }
  
  rvalidVarBase = b;
  return(rvalidVarBase);
  
}

BOOL validFuncBase(string pNomeFunc)  {
  BOOL  b=FALSE;
  int  i=0;
  int  t=0;
  Elem  telem; initElem(&telem);
  BOOL rvalidFuncBase=FALSE;
  
  b = FALSE;
  t = -1;
  for( i = 1; i<=gQtdSymbols; i++){
    telem = mSymbols[i];
    if( SL(telem.nome,pNomeFunc) && telem.objtp == CFUNCAO ){
      b = TRUE;
      break;
    }
  }
  
  rvalidFuncBase = b;
  return(rvalidFuncBase);
  
}

BOOL pegaVarFuncClass(int pidFunc, string pNomeVar, string pNomeClass, Variable *pvar, BOOL pNewOk, int * pId, BOOL * pbGlobal, BOOL * pisArray){
  BOOL  b=FALSE;
  int  i=0;
  int  i1=0;
  int  iidFunc=0;
  int  t=0;
  Funcao  tfunc;  initFuncao(&tfunc);
  Variable  tvar; initVar(&tvar);
  Elem  telem;    initElem(&telem);
  BOOL rpegaVarFuncClass=FALSE;
  
  rpegaVarFuncClass = FALSE;
  
  if( !SL(pNomeClass, SS("")) ){
    iidFunc = pegaIdFunc(SC(pNomeClass,SS("._globals_")));
    if( iidFunc == -1 ){
       //Err->Raise(vbObjectError + 513, "Compilador", "variável não inicializada: " & pNomeVar);
    }
    t = 0;
  }else{
    iidFunc = pidFunc;
    t = 1;
  }
    
  for( i1 = 0; i1 <= t; i1++){
    tfunc = mSymbols[iidFunc].Funcao;
    for( i = 0; i<tfunc.qtdVar; i++){
      tvar = tfunc.varLocal[i];
      if( SL(tvar.nome,pNomeVar) ){
        *pvar = tvar;
        b = TRUE;
        rpegaVarFuncClass = b;
        *pId = i;
        if( tvar.isArray == 1 ){
          *pisArray = TRUE;
        }else{
          *pisArray = FALSE;
        }
        if( tvar.tipo == Tag_COBJ && ( pNewOk == TRUE || tvar.isParameter == TRUE ) ){ //inicializa;
          mSymbols[iidFunc].Funcao.varLocal[i].isnewok = TRUE;
          pvar->isnewok = TRUE;
        }
        return(rpegaVarFuncClass);
      }
    }
        
    *pbGlobal = TRUE;
    iidFunc = GLOBALS;  //Valida globals;
    
  }
  
  return(rpegaVarFuncClass);
  
}

//esta função traz o id na tabela de símbolos;
int pegaIdFunc(string pNomeFunc){
  int i=0;
  int rpegaIdFunc = -1;
  for( i = 0; i<=gQtdSymbols; i++){
    if( mSymbols[i].objtp == CFUNCAO && SL(mSymbols[i].nome,pNomeFunc) ){
      rpegaIdFunc = i;
      return(rpegaIdFunc);
    }
  }
  return(rpegaIdFunc);
}

//esta função traz o id real da função;
int pegaIdFunc2(string pNomeFunc){
  int i=0;
  int rpegaIdFunc2 = -1;
  for( i = 0; i<=gQtdSymbols; i++){
    if( mSymbols[i].objtp == CFUNCAO && SL(mSymbols[i].nome,pNomeFunc) ){
      rpegaIdFunc2 = mSymbols[i].id;
      return(rpegaIdFunc2);
    }
  }
  return(rpegaIdFunc2);
}

BOOL pegaRetFunc(string pNomeFunc, int * ptipo, BOOL * pisArray, string pclass, BOOL * pIsNative){
  int  id=0;
  BOOL rpegaRetFunc=FALSE;
  Funcao  tfunc; initFuncao(&tfunc);
  
  id = pegaIdFunc(pNomeFunc);
  if( id == -1 ){
    rpegaRetFunc = FALSE;
    return(rpegaRetFunc);
  }
  
  tfunc = mSymbols[id].Funcao;
  *ptipo = tfunc.rettipo;
  *pisArray = tfunc.retarray;
  pclass->mv(pclass,tfunc.retnomeobj->c);
  *pIsNative = tfunc.isNative;
  rpegaRetFunc = TRUE;
  return(rpegaRetFunc);
  
}

void putReturnOk(int pCtxFuncId , node pbool){
  Funcao  tfunc; initFuncao(&tfunc);
  tfunc = mSymbols[pCtxFuncId].Funcao;
  tfunc.isReturnOk = TRUE;
  tfunc.retbool = pbool;
  mSymbols[pCtxFuncId].Funcao = tfunc;
}

int validFuncReturnOkBase(int pCtxFuncId,BOOL pcheckret, int ptipo, string pclass, BOOL parray){
  Funcao tfunc; initFuncao(&tfunc);
  node  b=NIL;
  int rvalidFuncReturnOkBase=0;
  
  rvalidFuncReturnOkBase = 0;
  
  tfunc = mSymbols[pCtxFuncId].Funcao;
  
  if( pcheckret == TRUE ){
    if( tfunc.isReturnOk != TRUE ){
      rvalidFuncReturnOkBase = 1;
      return(rvalidFuncReturnOkBase);
    }
    if( ptipo > 0 ){
      b = tfunc.retbool;
      if( isNothing(b) ){
        rvalidFuncReturnOkBase = 2;
        return(rvalidFuncReturnOkBase);
      }
      if( ptipo != b->validtipo && (ptipo == Tag_COBJ || b->validtipo == Tag_COBJ) ){
        rvalidFuncReturnOkBase = 3;
        return(rvalidFuncReturnOkBase);
      }
      if( ptipo == Tag_COBJ ){
        if( !SL(pclass,b->validnomeobj) ){
          rvalidFuncReturnOkBase = 4;
          return(rvalidFuncReturnOkBase);
        }
      }
      if( parray != b->isArray ){
        rvalidFuncReturnOkBase = 5;
        return(rvalidFuncReturnOkBase);
      }
      if( parray == TRUE ){
         if( ptipo != b->validtipo ){
           rvalidFuncReturnOkBase = 7;
           return(rvalidFuncReturnOkBase);
        }
      }
    }
  }else{
    b = tfunc.retbool;
    if( tfunc.isReturnOk == TRUE && Not isNothing(b) ){
      rvalidFuncReturnOkBase = 6;
      return(rvalidFuncReturnOkBase);
    }
  }
  
  return(rvalidFuncReturnOkBase);
    
}

string validFuncLocalParBase(int pCtxFuncId, string pNomeFunc, string pReplace, node pNoPar){
  BOOL  b=FALSE;
  BOOL  b1=FALSE;
  int  i=0, i1=0;
  int  t=0;
  int  tpar=0;
  int  ipos=0;
  int  itip=0;
  int  irc=0;
  string  sNomeVar=SS("");
  string  sNomeClass=SS("");
  string  sNomeClassBase=SS("");
  int  idFunc=0;
  Variable  tvar; initVar(&tvar);
  Funcao    tfunc; initFuncao(&tfunc);
  node      tnode=NIL;
  node      tnode1=NIL;
  int     *vpar=NIL;
  string  *vobj=NIL;
  BOOL    *varr=NIL;
  string rvalidFuncLocalParBase=SS("");
  array array_vpar = newarray(sizeof(int));
  array array_vobj = newarray(sizeof(string));
  array array_varr = newarray(sizeof(BOOL));
  string sMsg=SS("");
  string sReplace=SS("");
  
  idFunc = getId(pNomeFunc, CFUNCAO);
  
  if( idFunc < 0 ){
    sMsg = SC(SS("E174-funcaoo nao encontrada: "), pNomeFunc);
    rvalidFuncLocalParBase = sMsg;
    return(rvalidFuncLocalParBase);
  }
  
  tfunc = mSymbols[idFunc].Funcao;
  t = tfunc.parQtdVar;
  
  tpar = 0;
  b1 = TRUE;
  tnode = pNoPar;
  
  
  if( tnode->qtdFilhos > 0 ){
     while( b1 == TRUE){
      tnode1 = tnode->getFilho(tnode, 1);
      if( isNothing(tnode1) ){
        b1 = FALSE;
      }else{
        //ReDim Preserve vpar(tpar);
        //ReDim Preserve vobj(tpar);
        //ReDim Preserve varr(tpar);
        vpar = (int *)redim(array_vpar, tpar+1, TRUE);
        vobj = (string *)redim(array_vobj, tpar+1, TRUE);
        varr = (BOOL *)redim(array_varr, tpar+1, TRUE);
        vpar[tpar] = tnode1->validtipo;
        vobj[tpar] = tnode1->validnomeobj;
        varr[tpar] = tnode1->isArray;
        tpar = tpar + 1;
        
        if( tnode->qtdFilhos > 1 ){
          tnode = tnode->getFilho(tnode, 2);
        }else{
          b1 = FALSE;
        }
      }
    }
  }
  
  if( tpar != t ){
    sMsg = SC(SC(SC(SS("E175-quantidade de parametros incorretos: "),Str(tpar)),SS(", esperado:")),Str(t));
    rvalidFuncLocalParBase = sMsg;
    return(rvalidFuncLocalParBase);
  }
  
  i1 = 0;
  for(i = t; i>0; i--){ //To 1 Step -1           //devido à recursão a ordem está invertida ** atentar;
    tvar = tfunc.varLocal[i-1];
    
    if( vpar[i1] != -1 ){
        
      //bug 1 - inicio
      //Deixa passar qualquer variável
      if(SL(tvar.nomeobj,SS("__VAR__"))){
        i1 = i1 + 1;
        continue;                                 
      }
      //bug 1 - fim   
      
      if( ((tvar.isArray == 1 || varr[i1] == TRUE) && Not (tvar.isArray == 1 && varr[i1] == TRUE)) ){
        sMsg = SC(SS("E176-erro na passagem de parametros com tipos array: "),tvar.nome);
        rvalidFuncLocalParBase = sMsg;
        return(rvalidFuncLocalParBase);
      }
              
      if( tvar.tipo == vpar[i1] ){
        if( vpar[i1] == Tag_COBJ || vpar[i1] == Tag_CTBTABLE){
          sReplace = tvar.nomeobj;
          if(! SL(pReplace,SS(""))){
            if(SL(sReplace,SS("__T__"))){
              sReplace = pReplace;                          
            }
          }                              
          if( !SL(sReplace,vobj[i1]) ){
            sMsg = SC(SS("E177-objeto diferente do esperado: "),vobj[i1]);
            rvalidFuncLocalParBase = sMsg;
            return(rvalidFuncLocalParBase);
          }
        }
      }else{
        sMsg = SC(SS("E178-parametro com tipo invalido, entrada em "),tvar.nome);
        rvalidFuncLocalParBase = sMsg;
        return(rvalidFuncLocalParBase);
      }
    }else{
      sMsg = SC(SS("E179-variavel nao encontrada: "),tvar.nome);
      rvalidFuncLocalParBase = sMsg;
      return(rvalidFuncLocalParBase);
    }
    i1 = i1 + 1;
  }
  
  rvalidFuncLocalParBase = SS("0");
  return(rvalidFuncLocalParBase);

}

BOOL validVarAssignBase(int pidFunc, string pNomeVar, string pNomeClass){
   BOOL  b=FALSE;
   BOOL  bGlobal=FALSE;
   BOOL  bisArray=FALSE;
   int  iId=0;
   int rvalidVarAssignBase=0;
   Variable  tvar; initVar(&tvar);
   
   b = pegaVarFuncClass(pidFunc, pNomeVar, pNomeClass, &tvar, FALSE, &iId, &bGlobal, &bisArray);

   rvalidVarAssignBase = b;
   return(rvalidVarAssignBase);
}

int validVarAssignObjBase(int pidFunc, string pNomeVarE, string pNomeVarD){
   BOOL  b1=FALSE;
   BOOL  b2=FALSE;
   BOOL  bGlobal=FALSE;
   BOOL  bIsArray=FALSE;
   int  iId=0;
   Variable  tvare; initVar(&tvare);
   Variable  tvard; initVar(&tvard);
   int rvalidVarAssignObjBase=0;
   
   rvalidVarAssignObjBase = 1;
   
   b1 = pegaVarFuncClass(pidFunc, pNomeVarE, SS(""), &tvare, FALSE, &iId, &bGlobal, &bIsArray);
   
   if( b1 == FALSE ){
     rvalidVarAssignObjBase = 2;
     return(rvalidVarAssignObjBase);
   }
   b2 = pegaVarFuncClass(pidFunc, pNomeVarD, SS(""), &tvard, FALSE, &iId, &bGlobal, &bIsArray);
   if( b2 == FALSE ){
     rvalidVarAssignObjBase = 3;
     return(rvalidVarAssignObjBase);
   }
   
   if( tvare.tipo != Tag_COBJ ){
     rvalidVarAssignObjBase = 4;
     return(rvalidVarAssignObjBase);
   }
   
   if( tvard.tipo != Tag_COBJ ){
     rvalidVarAssignObjBase = 5;
     return(rvalidVarAssignObjBase);
   }
      
   if( !SL(tvare.nomeobj,tvard.nomeobj) ){
     rvalidVarAssignObjBase = 6;
     return(rvalidVarAssignObjBase);
   }
   
   rvalidVarAssignObjBase = 0;
   return(rvalidVarAssignObjBase);
   
}

int validVarAssignObjNewBase(int pidFunc, string pNomeVarE, string pNomeVarEClass, string pNomeClass){
   BOOL  b1=FALSE;
   BOOL  b2=FALSE;
   BOOL  bIsArray=FALSE;
   BOOL  bGlobal=FALSE;
   int  iId=0;
   Variable  tvare; initVar(&tvare);
   Variable  tvard; initVar(&tvard);
   int rvalidVarAssignObjNewBase=0;
   
   rvalidVarAssignObjNewBase = 1;
   
   //
   // pega variável e indica que ela foi inicializada;
   //
   b1 = pegaVarFuncClass(pidFunc, pNomeVarE, pNomeVarEClass, &tvare, TRUE, &iId, &bGlobal, &bIsArray);
   if( b1 = FALSE ){
     rvalidVarAssignObjNewBase = 2;
     return(rvalidVarAssignObjNewBase);
   }
   
   if( tvare.tipo != Tag_COBJ ){
     rvalidVarAssignObjNewBase = 3;
     return(rvalidVarAssignObjNewBase);
   }
   
   if( !SL(tvare.nomeobj,pNomeClass) ){
     rvalidVarAssignObjNewBase = 4;
     return(rvalidVarAssignObjNewBase);
   }
       
   rvalidVarAssignObjNewBase = 0;
   
   return(rvalidVarAssignObjNewBase);
   
}

int validObjIsInstanceadBase(int pidFunc, string pNomeVarE){
  BOOL  b1=FALSE;
  BOOL  b2=FALSE;
  BOOL  bIsArray=FALSE;
  BOOL  bGlobal=FALSE;
  int  iId=0;
  Variable  tvare; initVar(&tvare);
  Variable  tvard; initVar(&tvard);
  int rvalidObjIsInstanceadBase=0;
   
  rvalidObjIsInstanceadBase = 1;
   
  b1 = pegaVarFuncClass(pidFunc, pNomeVarE, SS(""), &tvare, FALSE, &iId, &bGlobal, &bIsArray);
  if( b1 == FALSE ){
    rvalidObjIsInstanceadBase = 2;
    return(rvalidObjIsInstanceadBase);
  }
   
  if( tvare.tipo != Tag_COBJ ){
    rvalidObjIsInstanceadBase = 3;
    return(rvalidObjIsInstanceadBase);
  }
   
  if( tvare.isnewok == TRUE ){
    rvalidObjIsInstanceadBase = 0;
  }else{
    rvalidObjIsInstanceadBase = 4;
  }
  
  return(rvalidObjIsInstanceadBase);
   
}


void initElem(Elem *e){
  e->id=0;
  e->nome=SS("");
  e->objtp=0;
  initVar(&e->var);
  initFuncao(&e->Funcao);
  e->tipoData=0; //usado para constantes;
  e->bngrava=FALSE; //não grava;
}
void initVar(Variable *v){
  v->nome=SS("");
  v->tipo=0;
  v->isArray=0;
  v->arrayTam=0;
  v->isParameter=FALSE;
  v->nomeobj=SS("");
  v->isnewok=FALSE;//in
}
void initFuncao(Funcao *f){
  f->id=0;
  f->nome=SS("");
  f->qtdVar=0;
  f->parQtdVar=0;
  f->varLocal=NIL;
  f->array_varLocal=NIL;
  f->rettipo=0;
  f->retnomeobj=SS("");
  f->retarray=FALSE;
  f->retbool=NIL;
  f->ntamopcode=0;
  f->prgAssembly=SS("");
  f->isNative=FALSE;
  f->isReturnOk=FALSE;
}

void initParseToken(string p1){
  mTexto = p1;
  mIdx   = 1;
  mTam   = Len(mTexto);
}

/*******************************************************************************
** Função utilizada para debug
**
**  utilizada em GravaFunc, pode-se gerar o bytecode para uma função específica
**    setar a variável
**    gdebuglg2 = 1
**
********************************************************************************/

void imprimeByteCode(){
  int i,i1=0;
  short int ii;
  char c1[] = " ";
  char c2[] = "  ";
  char c3[] = "   ";
  
  printf("\n");
  for(i=0; i<gQtdBuffer;i++){
     i1++;      
     ii = mBuffer[i];
     if(ii<10){
        printf("%s%i",c3,ii);       
     }else if(ii<100){
        printf("%s%i",c2,ii);   
     }else{
        printf("%s%i",c1,ii);    
     }
                
     printf(";");
     
     if(i1==10){
        printf("\n");   
        i1=0;   
     }           
  }
  printf("\nTotal bytecodes: %i\n", i+1);
  system("PAUSE");      
}     
    



