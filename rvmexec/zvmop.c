#include "zzdata.h"
#include "zzfuncdecl.h"
#include <stdlib.h>

/**** CONVERSAO ****/

/**** ROTINAS PARA CONVERSÃO de TIPOS ****/

void nmci(VAR *p){  /* Char para Int */
     p->i = p->c;
     p->tipo = CINTEGER;
}

void nmcl(VAR *p){
     p->l = p->c;
     p->tipo = CLONG;
}

void nmcf(VAR *p){
     p->f = p->c;
     p->tipo = CFLOAT;
}

void nmic(VAR *p){ /* Int para Char */
     p->c = p->i;
     p->tipo = CRCHAR;
}

void nmil(VAR *p){ 
     p->l = p->i;
     p->tipo = CLONG;
}

void nmif(VAR *p){ 
     p->f = p->i;
     p->tipo = CFLOAT;
}

void nmlc(VAR *p){ /* Long para Char */
     p->c = p->l;
     p->tipo = CRCHAR;
}

void nmli(VAR *p){ 
     p->i = p->l;
     p->tipo = CINTEGER;
}

void nmlf(VAR *p){ 
     p->f = p->l;
     p->tipo = CFLOAT;
}

void nmfc(VAR *p){ /* Float para Char */
     p->c = p->f;
     p->tipo = CRCHAR;
}

void nmfi(VAR *p){ 
     p->i = p->f;
     p->tipo = CINTEGER;
}

void nmfl(VAR *p){ 
     p->l = p->f;
     p->tipo = CLONG;
}

/* Matriz base para chamada de conversão */
void (*nm[5][5])(VAR *) = {
        { 0    ,     0 ,     0,      0,     0 }, 
        { 0    ,     0 , &nmci , &nmcl, &nmcf },
        { 0    ,  &nmic,     0 , &nmil, &nmif },
        { 0    ,  &nmlc, &nmli  ,    0, &nmlf },
        { 0    ,  &nmfc, &nmfi  ,&nmfl,     0 }   };

/**** OPERADORES BÁSICOS ****/

/* Operações com int */

void addii(VAR *p1, VAR *p2){
     p2->i+=p1->i;
}

void subii(VAR *p1, VAR *p2){
     p2->i-= p1->i;
}

void mulii(VAR *p1, VAR *p2){
     p2->i*=p1->i;
}

void divii(VAR *p1, VAR *p2){
     p2->i/=p1->i;
}

void andii(VAR *p1, VAR *p2){
     if(p1->i && p2->i)
       p2->i = 1;
     else
       p2->i = 0;
}

void orii(VAR *p1, VAR *p2){
    if(p1->i || p2->i)
       p2->i = 1;
     else
       p2->i = 0;
}

void ltii(VAR *p1, VAR *p2){
     if(p1->i < p2->i)
       p2->i = 1;
     else
       p2->i = 0;
}

void gtii(VAR *p1, VAR *p2){
     if(p1->i > p2->i)
       p2->i = 1;
     else
       p2->i = 0;
}

void leii(VAR *p1, VAR *p2){
     if(p1->i <= p2->i)
       p2->i = 1;
     else
       p2->i = 0;
}

void geii(VAR *p1, VAR *p2){
     if(p1->i >= p2->i)
       p2->i = 1;
     else
       p2->i = 0;
}

void neii(VAR *p1, VAR *p2){
     if(p1->i != p2->i)
       p2->i = 1;
     else
       p2->i = 0;
}

void eqii(VAR *p1, VAR *p2){
     if(p1->i == p2->i)
       p2->i = 1;
     else
       p2->i = 0;
}

/* Operações com Char */

void addcc(VAR *p1, VAR *p2){
     p2->c +=p1->c;
}

void subcc(VAR *p1, VAR *p2){
     p2->c -=  p1->c;
}

void mulcc(VAR *p1, VAR *p2){
     p2->c *=  p1->c;
}

void divcc(VAR *p1, VAR *p2){
     p2->c /=  p1->c;
}

void andcc(VAR *p1, VAR *p2){
     if(p1->c && p2->c)
       p2->i = 1;
     else
       p2->i = 0;
     p2->tipo = 2;
}

void orcc(VAR *p1, VAR *p2){
     if(p1->c || p2->c)
       p2->i = 1;
     else
       p2->i = 0;
     p2->tipo = 2; 
}

void ltcc(VAR *p1, VAR *p2){
     if(p1->c < p2->c)
       p2->i = 1;
     else
       p2->i = 0;
     p2->tipo = 2;
}

void gtcc(VAR *p1, VAR *p2){
     if(p1->c > p2->c)
       p2->i = 1;
     else
       p2->i = 0;
     p2->tipo = 2; 
}

void lecc(VAR *p1, VAR *p2){
     if(p1->c <= p2->c)
       p2->i = 1;
     else
       p2->i = 0;
     p2->tipo = 2;
}

void gecc(VAR *p1, VAR *p2){
     if(p1->c >= p2->c)
       p2->i = 1;
     else
       p2->i = 0;
     p2->tipo = 2;
}

void necc(VAR *p1, VAR *p2){
     if(p1->c != p2->c)
       p2->i = 1;
     else
       p2->i = 0;
     p2->tipo = 2;
}

void eqcc(VAR *p1, VAR *p2){
     if(p1->c == p2->c)
       p2->i = 1;
     else
       p2->i = 0;
p2->tipo = 2;
}

/* Operações com Long */

void addll(VAR *p1, VAR *p2){
     p2->l +=  p1->l;
}

void subll(VAR *p1, VAR *p2){
     p2->l -=  p1->l - p2->l;
}

void mulll(VAR *p1, VAR *p2){
     p2->l *=  p1->l * p2->l;
}

void divll(VAR *p1, VAR *p2){
     p2->l  /=  p1->l / p2->l;
}

void andll(VAR *p1, VAR *p2){
     if(p1->l && p2->l)
       p2->i = 1;
     else
       p2->i = 0;
p2->tipo = 2;
}

void orll(VAR *p1, VAR *p2){
     if(p1->l || p2->l)
       p2->i = 1;
     else
       p2->i= 0;
p2->tipo = 2;
}

void ltll(VAR *p1, VAR *p2){
     if(p1->l < p2->l)
       p2->i = 1;
     else
       p2->i= 0;
p2->tipo = 2;
}

void gtll(VAR *p1, VAR *p2){
     if(p1->l > p2->l)
       p2->i = 1;
     else
       p2->i= 0;
p2->tipo = 2;
}

void lell(VAR *p1, VAR *p2){
     if(p1->l <= p2->l)
       p2->i = 1;
     else
       p2->i= 0;
p2->tipo = 2;
}

void gell(VAR *p1, VAR *p2){
     if(p1->l >= p2->l)
       p2->i = 1;
     else
       p2->i= 0;
p2->tipo = 2;
}

void nell(VAR *p1, VAR *p2){
     if(p1->l != p2->l)
       p2->i = 1;
     else
       p2->i= 0;
p2->tipo = 2;
}

void eqll(VAR *p1, VAR *p2){
     if(p1->l == p2->l)
       p2->i = 1;
     else
       p2->i = 0;
p2->tipo = 2;
}

/* Operações com Float */

void addff(VAR *p1, VAR *p2){
     p2->f +=  p1->f;
}

void subff(VAR *p1, VAR *p2){
     p2->f -=  p1->f;
}

void mulff(VAR *p1, VAR *p2){
     p2->f *=  p1->f;
}

void divff(VAR *p1, VAR *p2){
     p2->f /=  p1->f;
}

void andff(VAR *p1, VAR *p2){
     if(p1->f && p2->f)
       p2->i = 1;
     else
       p2->i = 0;
p2->tipo=2;
}

void orff(VAR *p1, VAR *p2){
     if(p1->f || p2->f)
       p2->i  = 1;
     else
       p2->i = 0;
p2->tipo =2;
}

void ltff(VAR *p1, VAR *p2){
     if(p1->f < p2->f)
       p2->i = 1;
     else
       p2->i = 0;
p2->tipo=2;
}

void gtff(VAR *p1, VAR *p2){
     if(p1->f > p2->f)
       p2->i  = 1;
     else
       p2->i = 0;
p2->tipo=2;
}

void leff(VAR *p1, VAR *p2){
     if(p1->f <= p2->f)
       p2->i  = 1;
     else
       p2->i = 0;
p2->tipo=2;
}

void geff(VAR *p1, VAR *p2){
     if(p1->f >= p2->f)
       p2->i = 1;
     else
       p2->i = 0;
p2->tipo = 2;
}

void neff(VAR *p1, VAR *p2){
     if(p1->f != p2->f)
       p2->i = 1;
     else
       p2->i  = 0;
p2->tipo = 2;
}

void eqff(VAR *p1, VAR *p2){
     if(p1->f == p2->f)
       p2->i = 1;
     else
       p2->i = 0;
p2->tipo=2;
}

/*
**** Matrizes com as funcoes e seus respectivos tipos ****
*/

/* Funções de Cálculo */
void (*gAdd[5])(VAR *, VAR *) = { 0, &addcc, &addii, &addll, &addff };
void (*gSub[5])(VAR *, VAR *) = { 0, &subcc, &subii, &subll, &subff };
void (*gMul[5])(VAR *, VAR *) = { 0, &mulcc, &mulii, &mulll, &mulff };
void (*gDiv[5])(VAR *, VAR *) = { 0, &divcc, &divii, &divll, &divff };

/* Funcoes Lógicas */
/*   Agregação */
void (*gAnd[5])(VAR *, VAR *) = { 0, &andcc, &andii, &andll, &andff };
void (*gOr[5])(VAR *, VAR *)  = { 0, &orcc, &orii, &orll, &orff };
/*   Comparação */
void (*gLt[5])(VAR *, VAR *) = { 0, &ltcc, &ltii, &ltll, &ltff };
void (*gLe[5])(VAR *, VAR *) = { 0, &lecc, &leii, &lell, &leff };
void (*gGt[5])(VAR *, VAR *) = { 0, &gtcc, &gtii, &gtll, &gtff };
void (*gGe[5])(VAR *, VAR *) = { 0, &gecc, &geii, &gell, &geff };
/*   Igualdade */
void (*gNe[5])(VAR *, VAR *) = { 0, &necc, &neii, &nell, &neff };
void (*gEq[5])(VAR *, VAR *) = { 0, &eqcc, &eqii, &eqll, &eqff };

/*
** Demais Operadores
*/

/* LOADC */
/*
void op_loadc(VAR *v, TCLS *ptcls, int i){
  int i1,t;  
  char *c1, *c2;
  //VAR v;
  TCON *c;
  c = ptcls->cons+i;
  v->tipo = c->tipo;
  v->isArray = CFALSE;
  v->tamArray = 0;
  switch(c->tipo){
    case CRCHAR:
      //v.c = *c->nome; 
      v->c = c->c;
      break;
    case CSTRING:
      v->tipo = CRCHAR;   
      t = strlen(c->nome)+1;
      v->tamArray = t;
      v->isArray = CTRUE;
      c1=v->ca = zmalloc(t);
      c2=c->nome;
      for(i1=0;i1<t;i1++){
        *c1=*c2;
        c1++;c2++;               
      } 
      break; 
    case CINTEGER:
      //v.i = (S1) atoi(c->nome);
      v->i = c->i;
      break;
    case CLONG:
      //v.l = (L1) atoi(c->nome);
      v->l = c->l;
      break;
    case CFLOAT:
      //v.f = atof(c->nome);
      v->f = c->f;
      break;
  }        
}
*/
