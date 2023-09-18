/* Replace "dll.h" with the name of your header */
#include "dll.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TBUF 30

//
//
// PRIMEIRA FUNCAO
//
//
DLLIMPORT VAR CALC5(int pqtdpar, VAR *pstack, void *(*pmalloc)(unsigned long l)){
  /* int p1
     int p2 */
  VAR *p1, *p2;
  VAR rs;
  
  p1 = pstack++;
  p2 = pstack;
  rs = *p1;
  rs.i = p1->i + p2->i;
  return(rs);
            
}


//
//
// CONCATENACAO CON TIPOS 
//
//
DLLIMPORT VAR __CONCATI(int pqtdpar, VAR *pstack, PMALLOC){
  return(CONCATI(pqtdpar, pstack, pmalloc));
}


DLLIMPORT VAR __CONCATC(int pqtdpar, VAR *pstack, PMALLOC){
  return(CONCATC(pqtdpar, pstack, pmalloc));
} 

DLLIMPORT VAR __CONCATCA(int pqtdpar, VAR *pstack, PMALLOC){
  return(CONCATCA(pqtdpar, pstack, pmalloc));
}          
         

/* 
   p1 : array[char]
   p2 : int
*/ 
       
VAR CONCATI(int pqtdpar, VAR *pstack, PMALLOC){
  char *c, *c1, *c2, *c3, *ca;  
  char str[40];  
  VAR *p1, *p2, rs;        
  int i, t, z, tam, hasNull, bfree;
  
  p1 = pstack++;
  p2 = pstack;
  
  hasNull = 0;
  bfree = 1;
  
  if(!(p1->isArray==1 && p1->tipo==1)){
    return(rs);
  }
  
  if(!(p2->isArray==0 && p2->tipo==2)){
    return(rs);
  }          
 
  c = str;
  for(i=0;i<TBUF;i++){
    *c='\0'; c++;
  }
  
  //converte int para string
  sprintf(str,"%i",p2->i);
  //printf("ddd %i",p2->i);
  c=str; tam=0;
  while(*c!='\0'){
    tam++;
    c++;              
  }
  
  //encontra tamanho ideal do array 
  if(p1->ca=='\0'){
     t = 0;  
  }else{
     c = p1->ca;
     for(t=0;t<p1->tamArray; t++){
        if(*c=='\0'){
           hasNull = 1;          
           break;          
        }
        c++;                       
     }
     t++;                 
  }
  
  z = t+tam;
  if(hasNull == 0){
     z++;        
  }
  
  /*
  
  if(z>p1->tamArray){
    c2 = c1 = pmalloc(sizeof(char)*z);
    //printf("[%i-(%i)]",z,p2->i);
  }else{
    //printf("{%i}",p1->tamArray);
    bfree = 0;    
    c2 = c1 = p1->ca;    
  } 
  */
  
  //printf("[%i-(%i)]\n",z,p2->i);
  c2 = c1 = pmalloc(sizeof(char)*z+1);
  
  //copia primeira variável
  c = p1->ca;
  for(i=0;i<p1->tamArray;i++){
    *c1 = *c;
    c1++; c++;
    if(*c=='\0'){
      break;                         
    }
  }
  //copia a segunda variável
  c = str;
  for(i=0;i<tam;i++){
    *c1 = *c;
    c1++; c++;
    if(*c=='\0'){
      break;                         
    }              
  }
  
  *c1 = '\0';        
  
  //acerta memoria
  if(bfree == 1){
    z++;       
    p1->tamArray = z;
    //free(p1->ca);
    p1->ca = c2;
  }
  
  //printf("den %i\n",z);
  /*
  z++;
  rs.tamArray = z;
  rs.isArray = p1->isArray;
  rs.tipo = p1->tipo;
  rs.ca = c2;
  */
  
  rs = *p1;
  
  return(rs);  
}
              
/* 
   p1 : array[char]
   p2 : char
*/ 
       
VAR CONCATC(int pqtdpar, VAR *pstack, PMALLOC){
  char *c, *c1, *c2; 
  VAR *p1, *p2, rs;        
  int i, t ,z, hasNull, bfree;
  
  hasNull = 0;
  bfree   = 1;
  p1 = pstack++;
  p2 = pstack;
  
  rs.tipo = 0;
  
  if(!(p1->isArray==1 && p1->tipo==1)){
    return(rs);
  }
  
  if(!(p2->tipo == 1 && p2->isArray != 1)){
    return(rs);
  }          
 
  //encontra tamanho ideal do array 
  if(p1->ca=='\0'){
     t = 0;  
  }else{
     c = p1->ca;
     for(t=0;t<p1->tamArray; t++){
        if(*c=='\0'){
           hasNull = 1;          
           break;          
        }
        c++;                       
     }
     t++;                 
  }
  
  z = t+1; //um caracter
  if(hasNull == 0){
    z++;       
  } 
  
  if(z>p1->tamArray){
    c2 = c1 = pmalloc(sizeof(char)*z);
  }else{
    bfree = 0;    
    c2 = c1 = p1->ca;   
  } 
       
  //copia primeira variável
  c = p1->ca;
  for(i=0;i<p1->tamArray;i++){
    *c1 = *c;
    c1++; c++;
    if(*c=='\0'){
      break;              
    }
  }
  
  //copia a segunda variável
  *c1 = p2->c;
  c1++;
  *c1 = '\0';        
  
  /*
  //acerta memoria
  if(bfree==1){
    p1->tamArray = z;
    free(p1->ca);
    p1->ca = c2;
  }  
  rs = *p1;
  
  return(rs);
  */
  //acerta memoria
  if(bfree == 1){
    z++;
    p1->tamArray = z;
    //free(p1->ca);
    p1->ca = c2;
  }
  
  /*
  z++;
  rs.tamArray = z;
  rs.isArray = p1->isArray;
  rs.tipo = p1->tipo;
  rs.ca = c2;
  */
  
  rs = *p1;
  
  return(rs);  
}

/* 
   p1 : array[char]
   p2 : array[char]
*/ 
       
VAR CONCATCA(int pqtdpar, VAR *pstack, PMALLOC){
  char *c, *c1, *c2;
  VAR *p1, *p2, rs;        
  int i,t,z, hasNull, bfree;
  
  hasNull = 0;
  bfree = 1;
  p1 = pstack++;
  p2 = pstack;
  
  rs.tipo = 0;
  
  if(!(p1->isArray==1 && p1->tipo==1)){
    return(rs);
  }
  
  if(!(p2->isArray==1 && p2->tipo==1)){
    return(rs);
  }          
 
  //encontra tamanho ideal do array 
  if(p1->ca=='\0'){
     t = 0;  
  }else{
     c = p1->ca;
     for(t=0;t<p1->tamArray; t++){
        if(*c=='\0'){
           hasNull = 1;          
           break;          
        }
        c++;                       
     }
     t++;                 
  }
  
  if(p2->ca=='\0'){
     i = 0;  
  }else{
     c = p2->ca;
     for(i=0;i<p2->tamArray; i++){
        if(*c=='\0'){
           hasNull = hasNull + 1;          
           break;          
        }
        c++;                       
     }
     i++;                 
  }
  
  z = t+i;
  if(hasNull == 0){
     z++;        
  }
  if(hasNull == 2){
     z--;        
  }
  
  /*
  if(z>p1->tamArray){
    c2 = c1 = pmalloc(sizeof(char)*z);
  }else{
    bfree = 0;    
    c2 = c1 = p1->ca;    
  }  
  */
  
  c2 = c1 = pmalloc(sizeof(char)*z+1);
  
  //copia primeira variável
  c = p1->ca;
  for(i=0;i<p1->tamArray;i++){
    *c1 = *c;
    c1++; c++;
    if(*c=='\0'){
      break;                         
    }
  }
  //copia a segunda variável
  c = p2->ca;
  for(i=0;i<p2->tamArray;i++){
    *c1 = *c;
    c1++; c++;
    if(*c=='\0'){
      break;                         
    }              
  }
  
  *c1 = '\0';        
  
  //printf("den %i\n",z);
  //acerta memoria
  if(bfree == 1){
   z++;       
    p1->tamArray = z;
    //free(p1->ca);
    p1->ca = c2;
  }
  
  //printf("den %i\n",z);
  
  rs = *p1;
  
  return(rs);
  
  /*
  //acerta memoria
  if(bfree == 1){
    p1->tamArray = z;
    //free(p1->ca);
    //p1->ca = c2;
  }
  z++;
  rs.tamArray = z;
  rs.isArray = p1->isArray;
  rs.tipo = p1->tipo;
  rs.ca = c2;
  
  //rs = *p1;
  
  return(rs);  
  */
}

//
//
// PRINT
//
//
DLLIMPORT VAR __PRINT(int pqtdpar, VAR *pstack, PMALLOC){
  VAR *p1, rs;
  p1 = pstack;
  if(p1->isArray==1 && p1->tipo==1 && p1->tamArray>0){
     //printf("entrou %i", p1->tamArray);                
     printf(p1->ca);               
  }else{
     //printf("sem valor");   
  }
  return(rs);                      
}

DLLIMPORT VAR __PRINTENT(int pqtdpar, VAR *pstack, PMALLOC){
  VAR rs;
  printf("\n");
  return(rs);    
}
          
DLLIMPORT VAR __PRINTN(int pqtdpar, VAR *pstack, PMALLOC){
  VAR *p1, rs;
  p1 = pstack;
  if(p1->isArray==1) return;
  
  switch(p1->tipo){
    case 2:
         printf("%i",p1->i);
         break;
  }
  
  return(rs);                      
}

DLLIMPORT VAR __PRINTL(int pqtdpar, VAR *pstack, PMALLOC){
  VAR *p1, rs;
   p1 = pstack;
  if(p1->isArray==1) return;
  
  switch(p1->tipo){
    case 3:
         printf("%ld",p1->l);
         break;
  }
  
  return(rs);                      
}

DLLIMPORT VAR __PRINTF(int pqtdpar, VAR *pstack, PMALLOC){
  VAR *p1, rs;
  p1 = pstack;
  if(p1->isArray==1) return;
  
  switch(p1->tipo){
    case 4:
         printf("%f",p1->f);
         break;
    //case 3:
    //     printf("%l",p1->l);
    //     break;
  }
  
  return(rs);                      
}

DLLIMPORT VAR __XPRINT(int pqtdpar, VAR *pstack, PMALLOC){
  VAR *p1, rs;
  
  p1 = pstack;
  
  switch(p1->tipo){
    case 1:
      if(p1->isArray==1) {
        if(p1->tamArray>0){
          printf(p1->ca);               
        }
      }else{
        printf("%c", p1->c);
      }
      break;
    case 2:
      if(p1->isArray==0){ 
        printf("%i",p1->i);
      }
      break;
    case 3:
      if(p1->isArray==0){ 
        printf("%ld",p1->l);
      }
      break;
    case 4:
      //printf("\nprint f %i %f\n", p1->isArray, p1->f );
      if(p1->isArray==0){ 
        printf("%f",p1->f);
      }
      break;
  }
  
  return(rs);                      
}

//
//
// FLOAT
// 
//
DLLIMPORT VAR __TRUNC(int pqtdpar, VAR *pstack, PMALLOC){
  VAR *p1, *p2, rs;        
  int i;
  double f;
  
  p1 = pstack++; //float
  p2 = pstack;   //qtd casas

  i = p2->i;
  f = p1->f;
  
  rs.f = _btrunc(f,i);
  
  rs.tipo = 4;
  rs.isArray = 0;
  rs.tamArray =0;
  return(rs);

}

double _btrunc(double f, int qtd){
  int t, t1;
  double  f1, f2;
  
  t = f;
  f1 = f - t;
  t1 = f1 * pow(10,qtd);
  f1 = t1 / ( pow(10,qtd) );
  f2 = t + f1;
  
  return(f2);     
}     

//
//
// STRING 
//
//
DLLIMPORT VAR __STRINGLEN(int pqtdpar, VAR *pstack, PMALLOC){
  char c;
  VAR *p1, rs;
  p1 = pstack;
  if(p1->isArray==1 && p1->tipo==1){
     rs.tipo = 2;
     rs.i = p1->tamArray;
     if(rs.i>0){
       c = p1->ca[rs.i-1];
       if(c=='\0'){
         rs.i--;
       }
     }
     //printf(p1->ca);               
  }else{
     //printf("sem valor");   
  }
  return(rs);                      
}

//
//
// TABELA - não utilizada - pq está direto na VM
//
//
DLLIMPORT VAR __APPEND(int pqtdpar, VAR *pstack, PMALLOC){
  CBOOL b;
  long lindex;
  VAR *p1, *p2, rs;        
  VARTB vt;
  tableobj *to;
  
  p1 = pstack++;
  p2 = pstack;
  
  vt = p2->o;
  to = (tableobj *)p1->t;
  lindex = to->tb->size+1;
  
  //printf("\n%i", lindex);
  //b = tbInsertRoot(to->tb, vt, lindex);
  b = to->Insert(to->tb, vt, lindex);
  
  rs.tipo = 2;
  rs.i = b;
  
  return(rs);
}

DLLIMPORT VAR __INSERT(int pqtdpar, VAR *pstack, PMALLOC){
  CBOOL b;
  long lindex;
  VAR *p1, *p2, *p3, rs;        
  VARTB vt;
  tableobj *to;
  
  p1 = pstack++;
  p2 = pstack++;
  p3 = pstack;
  
  lindex = p3->i;
  vt = p2->o;
  to = p1->t;
  lindex = to->tb->size+1;
  
  //b = tbInsertRoot(to->tb, vt, lindex);
  b = to->Insert(to->tb, vt, lindex);
  
  rs.tipo = 2;
  rs.i = b;
  
  return(rs);
}

DLLIMPORT VAR __DELETE(int pqtdpar, VAR *pstack, PMALLOC){
  CBOOL b;
  long lindex;
  VAR *p1, *p2, rs;        
  tableobj *to;
  
  p1 = pstack++;
  p2 = pstack;
  
  lindex = p2->i;
  to = p1->t;
  
  //printf("%i\n", lindex)
  b = to->Delete(to->tb,lindex);
  
  rs.tipo = 2;
  rs.i = b;
  
  return(rs);
}

DLLIMPORT VAR __GET(int pqtdpar, VAR *pstack, PMALLOC){
  CBOOL b;
  long lindex;
  VAR *p1, *p2, rs;        
  VARTB vt;
  tableobj *to;
  
  p1 = pstack++;
  p2 = pstack++;
  
  lindex = p2->i;
  to = p1->t;
  
  //node *n = tbGetNodeByIndex(to->tb, lindex);
  node *n = to->getItem(to->tb, lindex);
   
  rs.tipo = 39;
  rs.isArray = 0;
  rs.tamArray = 0;
  if(n!=NULL){
    rs.o = n->value;
  }else{
    rs.o = 0;   
  }
  return(rs);
}

DLLIMPORT VAR __SIZE(int pqtdpar, VAR *pstack, PMALLOC){
  CBOOL b;
  long lindex;
  VAR *p1, *p2, rs;        
  VARTB vt;
  tableobj *to;
  
  p1 = pstack;
  
  lindex = p2->i;
  to = p1->t;
  
  //node *n = tbGetNodeByIndex(to->tb, lindex);
  
  rs.tipo = 2;
  rs.isArray = 0;
  rs.tamArray = 0;
  rs.o = to->tb->size;
  
  return(rs);

}

DLLIMPORT VAR __MODIFY(int pqtdpar, VAR *pstack, PMALLOC){
  CBOOL b;
  long lindex;
  VAR *p1, *p2, *p3, rs;
  VARTB vt;
  tableobj *to;
  long o;
  
  p1 = pstack++;
  p2 = pstack++;
  p3 = pstack;
  
  lindex = p3->i;
  o = p2->o;
  to = p1->t;
  
  b = to->Update(to->tb, o, lindex);
  
  rs.tipo = 2;
  rs.isArray = 0;
  rs.tamArray = 0;
  rs.i = b;
  
  return(rs);      
}

DLLIMPORT VAR __TBREAD(int pqtdpar, VAR *pstack, PMALLOC){
}


//
//
// FILE
//
//
DLLIMPORT VAR __FILEOPEN(int pqtdpar, VAR *pstack, PMALLOC){
  VAR *p1, *p2;
  VAR rs;
  
  p1 = pstack++;
  p2 = pstack;
  
  FILE *fp = fopen(p1->ca, p2->ca);

  rs.tipo = 2;
  rs.isArray = 0;
  rs.tamArray = 0;
  rs.i = (int) fp;
  return(rs);
}

DLLIMPORT VAR __FILEWRITE(int pqtdpar, VAR *pstack, PMALLOC){
  VAR *p1, *p2;
  VAR rs;
  short int itam;
  int i;
  
  p1 = pstack++;
  p2 = pstack;
 
  itam = p2->tamArray;
  FILE *fp = (FILE *) p1->i;
  
  i = fwrite(p2->ca,1,itam,fp);      

  rs.tipo = 2;
  rs.isArray = 0;
  rs.tamArray = 0;
  rs.i = i;
  return(rs);
}

DLLIMPORT VAR __FILEREAD512(int pqtdpar, VAR *pstack, PMALLOC){
  unsigned char buffer[512];
  char *c;
  VAR *p1;
  VAR rs;
  short int itam;
  int i, t;
  
  p1 = pstack;
  
  FILE *fp = (FILE *) p1->i;
  i = fread(buffer,1,512,fp);  
  
  c = pmalloc(sizeof(char)*i); 
  for(t=0;t<i;t++){
    c[t] = buffer[t];            
  }
  
  rs.tipo = 1;
  rs.isArray = 1;
  rs.tamArray = i;
  rs.ca = c;
  return(rs);          
}

DLLIMPORT VAR __FILECLOSE(int pqtdpar, VAR *pstack, PMALLOC){
  VAR *p1, *p2;
  VAR rs;
  
  p1 = pstack;

  FILE *fp = (FILE *) p1->i;
  
  fclose(fp);
  
  rs.tipo = 2;
  rs.isArray = 0;
  rs.tamArray = 0;
  rs.i = 0;
  return(rs);
}

//
//FUNCOES COM __VAR__
//
//

//
//
// ARRAY UTILS
//
//
DLLIMPORT VAR __LANG_UTIL_IS_ARRAY(int pqtdpar, VAR *pstack, PMALLOC){
  VAR *p1, *p2;
  VAR rs;
  
  p1 = pstack;
  
  if(p1->isArray != 0){
    rs.i = 1; 
  }else{
    rs.i = 0;
  }
  
  rs.tipo = 2;
  rs.isArray = 0;
  rs.tamArray = 0;
  
  return(rs);          
}

DLLIMPORT VAR __LANG_UTIL_ARRAY_LEN(int pqtdpar, VAR *pstack, PMALLOC){
  VAR *p1, *p2;
  VAR rs;
  
  p1 = pstack;
  
  if(p1->isArray != 0){
    rs.i = p1->tamArray; 
  }else{
    rs.i = 0;
  }
  
  rs.tipo = 2;
  rs.isArray = 0;
  rs.tamArray = 0;
  
  return(rs);          
}

DLLIMPORT VAR __LANG_UTIL_ISNULL(int pqtdpar, VAR *pstack, PMALLOC){
  VAR *p1, *p2;
  VAR rs;
  
  p1 = pstack;
  if(p1->o != '\0'){
    rs.i = 1;
  }else{
    rs.i = 0;
  }
  
  rs.tipo = 2;
  rs.isArray = 0;
  rs.tamArray = 0;
  
  return(rs);          
}

DLLIMPORT VAR __LANG_UTIL_CREATE_ARRAY(int pqtdpar, VAR *pstack, PMALLOC){
  VAR *p1, *p2;
  VAR rs;
  void **oa;
  
  int i;
  long l;
  
  p1 = pstack++;
  p2 = pstack;
  
  rs.tipo = p1->tipo;  
  rs.isArray = p1->isArray;
  rs.tamArray = p1->tamArray;
  rs.nomeobj = p1->nomeobj;
  rs.c = p1->c;      
  rs.i = p1->i;
  rs.l = p1->l;  
  rs.f = p1->f;
  rs.o = p1->o;
  rs.t = p1->t;
  rs.ca = p1->ca;
  rs.ia = p1->ia;
  rs.la = p1->la;
  rs.fa = p1->fa;
  rs.oa = p1->oa;
  
  //printf("aaa %i %i %i %i %i %i\n",p1->tipo, p1->isArray, p1->tamArray , p2->isArray, p2->tipo, p2->i);
  
  if(p1->isArray == 0 || p2->tipo != 2 || p2->i == 0 ){
    return(rs);
  }
  
  switch(p1->tipo){
    case 1: //char
         rs.tipo = p1->tipo;
         rs.tamArray = p2->i;
         rs.ca = pmalloc(sizeof(char) * p2->i);
         rs.nomeobj =  '\0';
         for(i=0; i<rs.tamArray; i++){
           rs.ca[i] = '\0';
         }
         break;
     case 39: //obj
         rs.tipo = p1->tipo;
         rs.tamArray = p2->i;
         oa =rs.oa = pmalloc(sizeof(void *) * p2->i);
         for(i=0; i<rs.tamArray; i++){
           *oa = '\0';
            oa++; 
         }
          
         break;                
  }
  return(rs);          
}

DLLIMPORT VAR __LANG_UTIL_COPY_ARRAY(int pqtdpar, VAR *pstack, PMALLOC){
  VAR *p1;
  VAR rs;
  void **d;
  void **o;
  
  int i;
  
  p1 = pstack;
  
  rs.tipo = p1->tipo;  
  rs.isArray = p1->isArray;
  rs.tamArray = p1->tamArray;
  rs.nomeobj = p1->nomeobj;
  rs.c = p1->c;      
  rs.i = p1->i;
  rs.l = p1->l;  
  rs.f = p1->f;
  rs.o = p1->o;
  rs.t = p1->t;
  rs.ca = p1->ca;
  rs.ia = p1->ia;
  rs.la = p1->la;
  rs.fa = p1->fa;
  rs.oa = p1->oa;
  
  
  if(p1->isArray == 0){
    return(rs);
  }
  switch(p1->tipo){
    case 1: //char
         rs.ca = pmalloc(sizeof(char) * rs.tamArray);
         for(i=0; i<rs.tamArray; i++){
           rs.ca[i] = p1->ca[i];
         }
         break;
    case 39: //obj
         
         d = rs.oa = pmalloc(sizeof(clazzptr) * p1->tamArray);
         o = p1->oa;
         for(i=0; i<rs.tamArray; i++){
           d[i] = o[i]; 
         }  
         break;
  }
  return(rs);          
}


/*
void * zmalloc(unsigned long l){
     lm+=l;
     printf("\nt%i\n",lm);
     return(malloc(l));
}
*/
          
BOOL APIENTRY DllMain (HINSTANCE hInst     /* Library instance handle. */ ,
                       DWORD reason        /* Reason this function is being called. */ ,
                       LPVOID reserved     /* Not used. */ )
{
    switch (reason)
    {
      case DLL_PROCESS_ATTACH:
        break;

      case DLL_PROCESS_DETACH:
        break;

      case DLL_THREAD_ATTACH:
        break;

      case DLL_THREAD_DETACH:
        break;
    }

    /* Returns TRUE on success, FALSE on failure */
    return TRUE;
}
