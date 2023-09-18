#include <stdio.h>
#include <stdlib.h>
#include "zzdata.h"
#include "zzfuncdecl.h"

int loadClass(char *s, TCLS **pcls){
  int i, i1, t, t1;
  ArrayMalloc *mem; 
  char mem1[1000];
  FILE *fp;
  TCL1 cl1;
  TCT1 ct1;
  TQT1 cqt1;
  TFD1 cfd1;
  TLV1 clv1;
  TNM  nm;

  /*metadado da classe*/
  TCLS *cls;
  TFUC *clsf;
  TVAR *clsv;
  TFUC vclsf;
  //printf("--aa--\n");
  mem = createArrayMalloc(50);  
  CASSERTCL(mem!=0,2);
  
  s = nomeFile(gPath, s, ".bic", mem1);
  CASSERT(grc==0, grc);
  
  fp = fopen(s,"rb");
  CASSERT(fp!=NULL, 1);
  
  CASSERTCL(mvCL1(fp, &cl1, &nm, mem),3);
  
  /* classe - cabeçalho */
  cls = safeMalloc(mem, sizeof(TCLS));
  CASSERTCL(cls!=0,4);
  
  cls->nome   = nm.nome1;
  cls->qconst = cl1.iqtdcons;
  cls->qatrib = cl1.iqtdvglo;
  cls->qfunc  = cl1.iqtdfunc;
  
  if(cls->qconst>0){
    cls->cons   = safeMalloc(mem, sizeof(TCON)*cl1.iqtdcons);
    CASSERTCL(cls->cons!=0, 5);
  }
  
  if(cls->qatrib>0){
    cls->atrib  = safeMalloc(mem, sizeof(TVAR)*cl1.iqtdvglo);
    CASSERTCL(cls->atrib!=0, 6);
  }
  cls->func   = safeMalloc(mem, sizeof(TFUC)*cl1.iqtdfunc);
  CASSERTCL(cls->func!=0, 7);
  
  cls->ffunc=initTreeChar();
  cls->fatrib=initTreeChar();
  
  /* constantes */
  if(cls->qconst>0){
    CASSERTCL(mvQT1(fp, &cqt1, "CTQ"),8);
    t = cqt1.qtditem;
    for(i=0;i<t;i++){
      CASSERTCL(mvCT1(fp, &ct1, &nm, mem),9);
      cls->cons[i] = metaMoveCon(i, ct1, nm); /*verificar aqui, suscetível a erro */
    }
  }
  
   /*atributos */
  /*if(cls->qatrib>0){*/
    CASSERTCL(mvFD1(fp, &cfd1, &nm, mem),10);
    if(cfd1.qtdVar>0){
      CASSERTCL(mvQT1(fp, &cqt1, "FVQ"),11);
      t = cqt1.qtditem;
      for(i=0;i<t;i++){
        CASSERTCL(mvLV1(fp, &clv1, &nm, "FVL", mem),12);
        cls->atrib[i] = metaMoveVar(i, clv1, nm);
        putTreeChar(cls->atrib[i].nome ,cls->atrib+i, &cls->fatrib);
      }
    }
  /*}*/
  
  /* funções */
  CASSERTCL(mvQT1(fp, &cqt1, "FQT"),13); /* qtd funções */
  t = cqt1.qtditem;
  for(i=1;i<t;i++){
                                
    CASSERTCL(mvFD1(fp, &cfd1, &nm, mem),14);
    vclsf = metaMoveFunc(cfd1, nm);
    if(cfd1.qtdVar>0){

      vclsf.tvar = safeMalloc(mem, sizeof(TVAR)*cfd1.qtdVar);
      CASSERTCL(vclsf.tvar!=0, 15);
    
      CASSERTCL(mvQT1(fp, &cqt1,"FVQ"),16); /* qtd variáveis */
      t1 = cqt1.qtditem;
      for(i1=0;i1<t1;i1++){                            
        CASSERTCL(mvLV1(fp, &clv1, &nm, "FVL", mem),17);
        vclsf.tvar[i1] = metaMoveVar(i1, clv1, nm);
      }
    }
    
    if(cfd1.byteop>0){
      CASSERTCL(mvBC1(fp,&vclsf, mem),18); /*pega bytecodes */
    }  
    
    cls->func[i-1] = vclsf;
    clsf = cls->func + i - 1;
    putTreeChar(clsf->nome,clsf, &cls->ffunc);
                                                                 
  }       
  
  //printf("--bb--\n");
  
  fclose(fp);
  deleteArrayMalloc(mem, CFALSE);
  
  *pcls = cls;
  
  return(0);
  
}

CBOOL mvCL1(FILE *fp , TCL1 * pcl1, TNM * pnm, ArrayMalloc *mem){
  int i; U1 buffer[50];
  TCL1 *mCL1;
  TNM *mNM;
  
  i = fread(buffer,1,3,fp);
  
  //printf("entrou1-\n");
  CASSERT(cmplin(buffer,"CL1")==CTRUE, CFALSE);
  //printf("saiu1-\n");
  
  //printf("entrou2-\n");
  i = fread(buffer,1,6,fp);
  //printf("saiu2-\n");
  
  //printf("entrou3-\n");
  if(i<0) return(CFALSE);
  mCL1 = (TCL1*) buffer;
  *pcl1 = *mCL1;
  //printf("saiu3-\n");
  
  //printf("entrou4-\n");
  i = fread(buffer,1,2,fp);
  //printf("entrou4a%i-\n",i);
  if(i<0) return(CFALSE);
  mNM = (TNM*) buffer;
  pnm->tamnome1 = mNM->tamnome1;
  //printf("saiu4-\n");
  
  //printf("entrou5-\n");
  i = fread(buffer,1,pnm->tamnome1,fp);
  //printf("entrou5bb-%i-\n",pnm->tamnome1);
  //printf(buffer);
  if(i<0) return(CFALSE);
  cps2(&pnm->nome1, buffer,pnm->tamnome1,mem);
  //printf("saiu5-\n");
  //printf("|s");
  
  return(CTRUE);   
  
} 

CBOOL mvQT1(FILE *fp , TQT1 * pqt1, char *key){ 
  int i; U1 buffer[50], itam;
  TQT1 *mQT1;
  
  i = fread(buffer,1,3,fp);
  
  CASSERT(cmplin(buffer,key)==CTRUE, CFALSE);
  
  i = fread(buffer,1,2,fp);
  if(i<0) return(CFALSE);
  mQT1 = (TQT1*) buffer;
  *pqt1 = *mQT1;
  
  return(CTRUE);    
}      

CBOOL mvCT1(FILE *fp , TCT1 * pct1, TNM * pnm, ArrayMalloc *mem){ 
  int i; U1 buffer[50];
  TCT1 *mCT1;
  TNM *mNM;
  
  i = fread(buffer,1,3,fp); 
  CASSERT(cmplin(buffer,"CT1")==CTRUE, CFALSE);
  
  i = fread(buffer,1,6,fp); /*verificar como ficou com o novo tamanho */
  CASSERT(i>0, CFALSE);
  mCT1 = (TCT1*) buffer;
  *pct1 = *mCT1;
  
  i = fread(buffer,1,2,fp);
  CASSERT(i>0, CFALSE);
  mNM = (TNM*) buffer;
  pnm->tamnome1 = mNM->tamnome1;
 
  i = fread(buffer,1,pnm->tamnome1,fp);
  CASSERT(i>0, CFALSE);
  
  cps2(&pnm->nome1,buffer,pnm->tamnome1,mem); 
  return(CTRUE);  
     
} 

CBOOL mvFD1(FILE *fp , TFD1 * pfd1, TNM * pnm,ArrayMalloc *mem){ 
  int i; U1 buffer[50];
  TFD1 *mFD1;
  TNM *mNM;
      
  i = fread(buffer,1,3,fp);
  
  CASSERT(cmplin(buffer,"FD1")==CTRUE, CFALSE);
  
  i = fread(buffer,1,18,fp);
  if(i<0) return(CFALSE);
  mFD1 = (TFD1*) buffer;
  *pfd1 = *mFD1;
  
  i = fread(buffer,1,2,fp); /* nome1 */
  if(i<0) return(CFALSE);
  mNM = (TNM*) buffer;
  pnm->tamnome1 = mNM->tamnome1;
  i = fread(buffer,1,pnm->tamnome1,fp);
  if(i<0) return(CFALSE);
  cps2(&pnm->nome1,buffer,pnm->tamnome1,mem);
  
  i = fread(buffer,1,2,fp); /* nome2 */
  if(i<0) return(CFALSE);
  mNM = (TNM*) buffer;
  pnm->tamnome2 = mNM->tamnome1;
  i = fread(buffer,1,pnm->tamnome2,fp);
  if(i<0) return(CFALSE);
  cps2(&pnm->nome2,buffer,pnm->tamnome2,mem);
  
  return(CTRUE);  

}          

CBOOL mvLV1(FILE *fp , TLV1 * plv1, TNM * pnm, char *key, ArrayMalloc *mem){ 
  int i; U1 buffer[50];
  TLV1 *mLV1;
  TNM *mNM;
      
  i = fread(buffer,1,3,fp);
  
  CASSERT(cmplin(buffer,key)==CTRUE, CFALSE);
  
  i = fread(buffer,1,7,fp);
  if(i<0) return(CFALSE);
  mLV1 = (TLV1*) buffer;
  *plv1 = *mLV1;
  
  i = fread(buffer,1,2,fp); /*   nome */
  if(i<0) return(CFALSE);
  mNM = (TNM*) buffer;
  pnm->tamnome1 = mNM->tamnome1;
  i = fread(buffer,1,pnm->tamnome1,fp);
  if(i<0) return(CFALSE);
  cps2(&pnm->nome1,buffer,pnm->tamnome1,mem); 
  
  i = fread(buffer,1,2,fp); /*   nome */
  if(i<0) return(CFALSE);
  mNM = (TNM*) buffer;
  pnm->tamnome2 = mNM->tamnome1;
  i = fread(buffer,1,pnm->tamnome2,fp);
  if(i<0) return(CFALSE);
  cps2(&pnm->nome2,buffer,pnm->tamnome2,mem);

  return(CTRUE);

}

CBOOL mvBC1(FILE *fp , TFUC *pfuc, ArrayMalloc *pmem){ 
  int i;
  long l;
  unsigned char *lbytes;
  char buffer[3];

  i = fread(buffer,1,3,fp);
  CASSERT(cmplin(buffer,"BC1")==CTRUE,CFALSE);
  
  l = pfuc->ntamopcode;
  
  lbytes = safeMalloc(pmem, l);
  
  CASSERT(lbytes!=0,CFALSE);
  
  i = fread(lbytes,1,l,fp);
  
  CASSERT(i!=0,CFALSE);
  
  pfuc->bc = lbytes;
  
  return(CTRUE);
}           

TCON metaMoveCon(int i, TCT1 pct1, TNM pnm){
  TCON tc;
  tc.id   = i;
  tc.tipo = pct1.tipo;
  tc.tam  = pct1.tam;
  tc.nome = pnm.nome1;
  switch(tc.tipo){
    case CRCHAR:
      tc.c = *tc.nome;
      break;
    case CINTEGER:
      tc.i = atoi(tc.nome);
      break;
      break;
    case CLONG:
      tc.l = atol(tc.nome);
      break;
    case CFLOAT:
      tc.f = atof(tc.nome);
      break;
  }
  return(tc);
}
     
TVAR metaMoveVar(int pid, TLV1 plv1, TNM pnm){
  TVAR tv;
  tv.id         = pid;
  tv.tipo       =plv1.tipo;
  tv.isArray    =plv1.isArray;
  tv.tamArray   =plv1.tamArray;
  tv.isParameter=plv1.isParameter;  
  tv.nome       =pnm.nome2;
  tv.nomeobj    =pnm.nome1;
  return(tv);
}

TFUC metaMoveFunc(TFD1 pfd1, TNM pnm){
  TFUC tf;
  tf.qtdVar    =pfd1.qtdVar;
  tf.qtdPar    =pfd1.qtdPar;
  tf.rettipo   =pfd1.rettipo;
  tf.retarray  =pfd1.retarray;
  tf.ntamopcode=pfd1.ntamopcode;
  tf.ntamstack =pfd1.ntamstack;
  tf.byteop    =pfd1.byteop;
  tf.isNative  =pfd1.isNative; 
  tf.nome      =pnm.nome1;
  tf.nometipoobj=pnm.nome2;
  return(tf);
}     
     
CBOOL cmplin(char *p1, char *p2){
   int i;
   for(i=0;i<3;i++){
      if(*(p1+i)!=*(p2+i)){
         return(CFALSE);
         i++;
      }                  
   }
   return(CTRUE);              
}
      
char * cps(char **ss, U1 *se, int tam){
  int i;
  U1 *v;
  U1 *se2;
  se2 = se;
  v = *ss = ymalloc(tam+1);
  for(i=0;i<tam;i++){
    *v = *se2;
    se2++;v++;
  }
  *v = '\0';
}

char * cps2(char **ss, U1 *se, int tam, ArrayMalloc *pmem){
  int i;
  U1 *v;
  U1 *se2;
  se2 = se;
  /*v = *ss = ymalloc(tam+1);*/
  //printf("_malloc_\n");
  v = safeMalloc(pmem,tam+1);
  //printf("es1-\n");
  *ss = v;
  for(i=0;i<tam;i++){
    *v = *se2;
    se2++;v++;
  }
  *v = '\0';
}

//char * nomeFile(char *ppath, char *pnome, char *pext, ArrayMalloc *pmem){
char * nomeFile(char *ppath, char *pnome, char *pext, char *pmem){
  char *s0, *s1, *s2, *s3;
  int i;
  
  grc = 0;
  i=0;
  s0 = pnome;
  
  //path
  s1 = ppath;
  while(*s1!='\0'){
    s1++;               
    i++;               
  }                 
  //nome
  while(*s0!='\0'){
    i++;
    s0++;                 
  }
  
  if(i==0){
    grc = 55;       
    s3='\0';
    return(s3);
  }
         
  i+=5;
  
  //s2=s3=safeMalloc(pmem, i);
  s2=s3=pmem;
  if(s2 == '\0'){
    grc = 57;
    return(s2); 
  }    
  
  s1=ppath;  
  while(*s1!='\0'){
    *s2=*s1;
    s2++;s1++;              
  }
  
  s0 = pnome;
  while(*s0!='\0'){
    *s2=*s0;
    s2++;s0++;              
  }
  
  s0 = pext;
  while(*s0!='\0'){
    *s2=*s0;
    s2++;s0++;              
  }
  *s2 = '\0';
  
  return(s3);
  
}
