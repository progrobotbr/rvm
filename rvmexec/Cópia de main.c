#include <stdio.h>
#include <stdlib.h>
#define CTQ 1
#define VGQ 2
#define CT1 3
#define IP1 4
#define LV1 5
#define FD1 6
#define BC1 7
#define FQT 8

#define TAMCT1 3

#define TRUE 1
#define FALSE 0

typedef unsigned char U1;
typedef short int     S1;
typedef unsigned short int     S2;
typedef long int      L1;
typedef float         F1;

typedef struct {
  short int qtditem;
} TQT;

typedef struct {  // 2+ 1 + 2 = 5
  S1 id;
  U1 tipo;
  S1 tamnome;
  char *nome;
}TCT1;

typedef struct {
  short int id;
  unsigned char tipo;
  unsigned char isArray;
  short int tamArray;
  short int tamnome;
  char *nome;
} TLV1;

typedef struct {
  short int id;
  short int nparsai;
  short int nparent;
  short int nlocvar;
  short int qtdop;
  short int qtdbinary;
  short int tamnome;
  char *nome;
} TFD1;

//Constantes
typedef struct {
  int id;
  unsigned char tipo;
  int tamnome;
  char *nome;     
} ConstantVal;

//Tipo Básico
typedef struct {
   unsigned char tipo;  
   unsigned char isArray;
   short int sizeArray;
   union {   
     char c;      
     int i;
     long int l;  
     double f;
     char *ca;
     int *ia;
     long int *la;
     double *fa;
  };
} Var;

//Operadores Nodes
typedef struct {
  unsigned char Op;
  int qtdeparametros;
  int *parametros;
} NodesOp;

//Funcao
typedef struct Funcao{
  int id;
  char *nome;
  int qtdparametros;
  int qtdvar;
  int qtdbinary;
  int qtdnodeop;
  NodesOp *nodeop;
  int qtdlv1;
  TLV1 *vardecl;
} Funcao;

//Programa
typedef struct Prg{
  int id;
  char *nome;
  int qtdconst;
  int qtdvar;
  int qtdfunc;
  ConstantVal *constants;
  Var *variaveis;
  Funcao *funcao;
  struct Prg *next;
} Prg;

Prg *gPrg;

int getCode(unsigned char *b){
    char c1,c2;
    switch(*b){
      case 'B':
        return(BC1);
        break;
      case 'C':
        b++;b++;
        if(*b=='Q')
          return(CTQ);
        else
          return(CT1);
        break;
      case 'V':
        return(VGQ);
        break;
      case 'I':
        return(IP1);
        break;
      case 'L':
        return(LV1);
        break;
      case 'F':
        b++;
        c1=*b;
        b++;
        c2 = *b;
        if(c1=='Q' && c2 == 'T')
          return(FQT);
        if(c1=='D' && c2 == '1')
          return(FD1);
        break;
    }  
}

char * cps1(char *se, int tam){
  int i;
  char *v,*v1;
  v = v1 = malloc(tam+1);
  for(i=0;i<tam;i++){
    *v = *se;
    se++;v++;
  }
  *v = '\0';
  return(v1);
}

char * cps(char **ss, char *se, int tam){
  int i;
  char *v;
  v = *ss = malloc(tam+1);
  for(i=0;i<tam;i++){
    *v = *se;
    se++;v++;
  }
  *v = '\0';

}

int mvQT(FILE *fp, TQT *cqt){
  
  int i; U1 *u1; S1 *s1; U1 buffer[50];
  
  i = fread(buffer,1,2,fp);
  
  if(i<0) return(FALSE);
    
  s1 = (S1 *) buffer;
  cqt->qtditem = *s1;
  return(TRUE);
}

int mvCT1(FILE *fp, TCT1 *ct1){
  
  int i; U1 *u1; S2 *s1; U1 buffer[50];
  
  i = fread(buffer,1,5,fp);
  
  if(i<0) return(FALSE);
    
  s1 = (U1 *) buffer;
  ct1->id = *s1;
  u1 = buffer+2;
  ct1->tipo = *u1;
  s1 = (U1 *) buffer+3;
  ct1->tamnome = *s1;
  i = fread(buffer,1,ct1->tamnome,fp);
  
  if(i<0) return(FALSE);
  cps(&ct1->nome, buffer,ct1->tamnome);   
  printf("\n%s",ct1->nome);
  return(TRUE);
}

int mvLV1(FILE *fp, TLV1 *lv1){
 
  int i; U1 *u1; S1 *s1; U1 buffer[50];
  
  i = fread(buffer,1,8,fp);
  
  if(i<0) return(FALSE);
    
  s1 = buffer;
  lv1->id = *s1;
  u1 = buffer+2;
  lv1->tipo = *u1;
  u1 = buffer+3;
  lv1->isArray;
  s1 = buffer+4;
  lv1->tamArray = *s1;
  s1 = buffer+6;
  lv1->tamnome = *s1;

  i = fread(buffer,1,lv1->tamnome,fp);
  
  if(i<0) return(FALSE);
  
  cps(&lv1->nome,buffer,lv1->tamnome);
  
  return(TRUE);
}

int mvFD1(FILE *fp, TFD1 *fd1){
 
   short int id;
  short int nparsai;
  short int nparent;
  short int nlocvar;
  short int ntamopcode;
  short int byteop;
  short int tamnome;
  char *nome;
  int i; U1 *u1; S1 *s1; U1 buffer[50];
  
  i = fread(buffer,1,14,fp);
  
  if(i<0) return(FALSE);
    
  s1 = buffer;
  fd1->id = *s1;
  s1 = buffer+2;
  fd1->nparsai = *s1;
  s1 = buffer+4;
  fd1->nparent = *s1;
  s1 = buffer+6;
  fd1->nlocvar = *s1;
  s1 = buffer+8;
  fd1->qtdbinary = *s1;
  s1 = buffer+10;
  fd1->qtdop = *s1;
  s1 = buffer+12;
  fd1->tamnome = *s1;

  i = fread(buffer,1,fd1->tamnome,fp);
  
  if(i<0) return(FALSE);
  
  cps(&fd1->nome,buffer,fd1->tamnome);
  
  return(TRUE);

}

void initConstant(Prg *pPrg, TQT *pQt){
   pPrg->qtdconst  = pQt->qtditem; 
   pPrg->constants = malloc(sizeof(ConstantVal)* pQt->qtditem);
}

void putConstant(int pId, Prg *pPrg, TCT1 *pCt1){
     ConstantVal *Cv;
     Cv = pPrg->constants;
     Cv[pId].id = pId;
     Cv[pId].tipo = pCt1->tipo;
     Cv[pId].tamnome = pCt1->tamnome;
     cps(&Cv[pId].nome,pCt1->nome,pCt1->tamnome);
}

NodesOp *geraNodeOp(char * pBuf, int pQtdbinary, int pQtdnodeop){
  int i, t, qtdpar;
  S1 *s;
  U1 b, b2[2];
  NodesOp *noi,*nop;
  
  noi = nop = malloc(sizeof(NodesOp)*pQtdnodeop);
  /*
  for(i=0;i<pQtdbinary;i++){
    b = *pBuf;
    pBuf++;
    t = gByteCode[b].qtdpar;
    nop[i].Op = b;
    nop[i].qtdeparametros = t;
    nop[i].parametros = malloc(sizeof(int)*t);
    for(t=0;t<qtdpar;t++){
      b2[0] = *pBuf; pBuf++;
      b2[1] = *pBuf; pBuf++;
      s = b2;
      nop[i].parametros[t] = *s;
    }
  }
  */
  return(noi);
}

int loadPrograma(FILE *fp){
     
  int bIDT,i,iConst,iVar,iFuncao;
  short int t;
  unsigned char *sIDT;
  unsigned char buffer[100];
  char *nome;
  char *sMain = "__main__";
  TQT  ctq;
  TQT  vgq;
  TQT  fqt;
  TLV1 ip1;
  TCT1 ct1;
  TLV1 lv1;
  TFD1 fd1;
  Prg *oPrg;
  Funcao *oFuncao;
  S1 *s1;
  U1 *u1;
  U1 *fBuf;
  
  i=TRUE;
  iConst = 0;
  iVar = 0;
  iFuncao = 0;
  
  gPrg = oPrg = malloc(sizeof(Prg));
  
  while(i){
      i = fread(buffer,1,3,fp);
      bIDT = getCode(buffer);
      switch(bIDT){
        case CTQ:           //Quantidade de constantes
          i=mvQT(fp,&ctq);
          initConstant(oPrg,&ctq);
          break;
        case FQT:           //Quantidade de funcoes no arquivo
          i=mvQT(fp,&fqt);
          oPrg->qtdfunc = fqt.qtditem;
          oFuncao = oPrg->funcao = malloc(sizeof(Funcao) * fqt.qtditem);
          break;  
        case CT1:           //Constantes
          i=mvCT1(fp,&ct1);
          putConstant(iConst, oPrg, &ct1);
          iConst++;
          break;
        case VGQ:
          i=mvQT(fp,&vgq);
          break; 
        case IP1:
          break;
        case LV1:           //Variaveis
          i=mvLV1(fp,&lv1);
          oFuncao->vardecl[iVar] = lv1;
          iVar++;
          break;
        case FD1:
          i=mvFD1(fp,&fd1); //Funções
          if(!strcmp(fd1.nome,sMain)){
            oPrg->qtdvar =  fd1.nlocvar;
            oPrg->variaveis = malloc(sizeof(Var) * fd1.nlocvar);
          }else{
            oFuncao++;
            iFuncao++;
          }
          oFuncao->id = iFuncao;
          oFuncao->nome = fd1.nome;
          oFuncao->qtdvar = fd1.nlocvar;
          oFuncao->qtdparametros = fd1.nparent;
          oFuncao->qtdbinary = fd1.qtdbinary;
          oFuncao->qtdnodeop = fd1.qtdop;
          oFuncao->vardecl = malloc(sizeof(TLV1) * fd1.nlocvar);
          oFuncao->qtdlv1 = fd1.nlocvar;
          break;
        case BC1:           //Carrega bytecodes na função
          fBuf = malloc(oFuncao->qtdbinary);
          i = fread(fBuf,1,oFuncao->qtdbinary,fp);
          oFuncao->nodeop = geraNodeOp(fBuf,oFuncao->qtdbinary,oFuncao->qtdnodeop);
          free(fBuf);
          break;
      }
      if(i<0) i=FALSE;     
  }
  return(TRUE);
}

int initPrograma(char *s){
  int bRet;
  FILE *fp;
  fp = fopen(s,"rb");
  
  if(fp==NULL){
    printf("\nPau Geral\n");
    return(0);
  }
  
  bRet = loadPrograma(fp);
  
  fclose(fp);
  
  return(bRet);
}

void limpaPrg(){
  int i,t,q,z;
  TLV1 *oTlv;
  ConstantVal *Cv;
  Funcao *Fv,*Fv1;
  char * sMain = "__main__";
  
  t = gPrg->qtdconst;
  Cv = gPrg->constants;
  for(i=0;i<t;i++){
    free(Cv[i].nome);
  }
  free(gPrg->constants);
  
  Fv = gPrg->funcao;
  t=gPrg->qtdfunc;
  for(i=0;i<t;i++){
                   
    Fv1 = Fv;
    Fv++;
    q=Fv1->qtdvar;
   
    oTlv = Fv1->vardecl;
    for(z=0;z<q;z++){
      free(oTlv->nome);
      oTlv++;
    }

    free(Fv1->nome);
    free(Fv1->vardecl); 
    free(Fv1->nodeop);
    
  }
  
  free(gPrg->funcao);
  
  //Limpa Constantes
  //Limpa Variaveis
  //Limpa Funcao
}

int main(int argc, char *argv[])
{
  char *arq = "c:\\filesai.bin";
  initPrograma(arq);
  limpaPrg();
  //system("PAUSE");	
  return 0;
}

