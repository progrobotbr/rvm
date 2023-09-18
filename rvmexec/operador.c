
#include "var.h"
#include "tipos.h"
#include "bytecode.h"
#include "conversao.h"
#include "operador.h"

/*
** Operadores da máquina Virtual
*/

//Operações com int

Var addii(Var *p1, Var *p2){
    Var rs;
    rs=*p1;
    rs.i = p1->i + p2->i;
    return(rs);
}

Var subii(Var *p1, Var *p2){
     Var rs;
     rs=*p1;
     rs.i =  p1->i - p2->i;
     return(rs);
}

Var mulii(Var *p1, Var *p2){
     Var rs;
     rs=*p1;
     rs.i =  p1->i * p2->i;
     return(rs);
}

Var divii(Var *p1, Var *p2){
     Var rs;
     rs=*p1;
     rs.i =  p1->i / p2->i;
     return(rs);
}

Var andii(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->i && p2->i)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var orii(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->i || p2->i)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var ltii(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->i < p2->i)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var gtii(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->i > p2->i)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var leii(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->i <= p2->i)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var geii(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->i >= p2->i)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var neii(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->i != p2->i)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var eqii(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->i == p2->i)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

/*
** Operações com Char
*/

Var addcc(Var *p1, Var *p2){
     Var rs;
     rs=*p1;
     rs.c =  p1->c + p2->c;
     return(rs);
}

Var subcc(Var *p1, Var *p2){
     Var rs;
     rs=*p1;
     rs.c =  p1->c - p2->c;
     return(rs);
}

Var mulcc(Var *p1, Var *p2){
     Var rs;
     rs=*p1;
     rs.c =  p1->c * p2->c;
     return(rs);
}

Var divcc(Var *p1, Var *p2){
     Var rs;
     rs=*p1;
     rs.c =  p1->c / p2->c;
     return(rs);
}

Var andcc(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->c && p2->c)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var orcc(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->c || p2->c)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var ltcc(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->c < p2->c)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var gtcc(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->c > p2->c)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var lecc(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->c <= p2->c)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var gecc(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->c >= p2->c)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var necc(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->c != p2->c)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var eqcc(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->c = p2->c)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

/*
** Operações com Long
*/

Var addll(Var *p1, Var *p2){
     Var rs;
     rs=*p1;
     rs.l =  p1->l + p2->l;
     return(rs);
}

Var subll(Var *p1, Var *p2){
     Var rs;
     rs=*p1;     
     rs.l =  p1->l - p2->l;
     return(rs);
}

Var mulll(Var *p1, Var *p2){
     Var rs;
     rs=*p1;     
     rs.l =  p1->l * p2->l;
     return(rs);
}

Var divll(Var *p1, Var *p2){
     Var rs;
     rs=*p1;     
     rs.l =  p1->l / p2->l;
     return(rs);
}

Var andll(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->l && p2->l)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var orll(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->l || p2->l)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var ltll(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->l < p2->l)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var gtll(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->l > p2->l)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var lell(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->l <= p2->l)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var gell(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->l >= p2->l)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var nell(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->l != p2->l)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var eqll(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->l = p2->l)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

/*
** Operações com Float
*/

Var addff(Var *p1, Var *p2){
     Var rs;
     rs=*p1;     
     rs.f =  p1->f + p2->f;
     return(rs);
}

Var subff(Var *p1, Var *p2){
     Var rs;
     rs=*p1;     
     rs.f =  p1->f - p2->f;
     return(rs);
}

Var mulff(Var *p1, Var *p2){
     Var rs;
     rs=*p1;     
     rs.f =  p1->f * p2->f;
     return(rs);
}

Var divff(Var *p1, Var *p2){
     Var rs;
     rs=*p1;     
     rs.f =  p1->f / p2->f;
     return(rs);
}

Var andff(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->f && p2->f)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var orff(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->f || p2->f)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var ltff(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->f < p2->f)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var gtff(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->f > p2->f)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var leff(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->f <= p2->f)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var geff(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->f >= p2->f)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var neff(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->f != p2->f)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}

Var eqff(Var *p1, Var *p2){
     Var rs;
     rs.tipo = CINT;
     rs.isArray = FALSE;
     if(p1->f = p2->f)
       rs.i = 1;
     else
       rs.i = 0;
     return(rs);
}


/*
** Matrizes com as funcoes e seus respectivos tipos 
*/

//Funções de Cálculo
Var (*gAdd[4])(Var *, Var *) = {
    &addcc, &addii, &addll, &addff 
};

Var (*gSub[4])(Var *, Var *) = {
    &subcc, &subii, &subll, &subff 
};

Var (*gMul[4])(Var *, Var *) = {
    &mulcc, &mulii, &mulll, &mulff 
};

Var (*gDiv[4])(Var *, Var *) = {
    &divcc, &divii, &divll, &divff 
};

// Funcoes Lógicas

// Agregação
Var (*gAnd[4])(Var *, Var *) = {
    &andcc, &andii, &andll, &andff 
};

Var (*gOr[4])(Var *, Var *) = {
    &orcc, &orii, &orll, &orff 
};

// Comparação
Var (*gLt[4])(Var *, Var *) = {
    &ltcc, &ltii, &ltll, &ltff 
};

Var (*gLe[4])(Var *, Var *) = {
    &lecc, &leii, &lell, &leff 
};

Var (*gGt[4])(Var *, Var *) = {
    &gtcc, &gtii, &gtll, &gtff 
};

Var (*gGe[4])(Var *, Var *) = {
    &gecc, &geii, &gell, &geff 
};

// Igualdade 
Var (*gNe[4])(Var *, Var *) = {
    &necc, &neii, &nell, &neff 
};

Var (*gEq[4])(Var *, Var *) = {
    &eqcc, &eqii, &eqll, &eqff 
};

/*
** Demais Operadores
*/

//LOADC
Var loadc(int i){
  ConstantVal *c;
  Var v;
  c = gPrg->constants+i;
  v.tipo = c->tipo;
  v.isArray = FALSE;
  v.sizeArray = 0;
  //v.c = *c->nome;
  switch(c->tipo){
    case CCHAR: 
      if(c->tamnome > 1){
        v.isArray = TRUE;
        v.sizeArray = c->tamnome;
        v.ca = c->nome;
      }else{
        v.c = *c->nome;
      }
      break;
    case CINT:
      v.i = (S1) atoi(c->nome);
      break;
    case CLONG:
      v.l = (L1) atol(c->nome);
      break;
    case CFLOAT:
      v.l = (float) atof(c->nome);
      break;
  }
  return(v);              
}

//LOADV
Var loadv(int i){
  Var *o,d;

  HeapVarLocals lHeap;
  lHeap = gFrame->HeapLocal;
  o=lHeap.Var+i;
  
  //Copia valores
  copyVar(o,&d);
  
  return(d);
}

//STORV
void storv(int i, Var rs){
  Var *v;   
  HeapVarLocals lHeap;
  
  lHeap = gFrame->HeapLocal;
  v = lHeap.Var+i;
  
  //Move o valor para a nova variável
  moveVar(&rs,v);
  
}
