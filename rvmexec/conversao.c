
#include "var.h"
#include "tipos.h"
#include "bytecode.h"
#include "conversao.h"


/*
  Funções de Apoio
*/

/*
    t  -> Tipo da variável de retorno
    p1 -> Primeira variável
    p2 -> Segunda variável
*/

// Rotinas para conversão de tipos

void nmci(Var *p){  //Char para Int
     p->i = p->c;
     p->tipo = CINT;
}

void nmcl(Var *p){
     p->l = p->c;
     p->tipo = CLONG;
}

void nmcf(Var *p){
     p->f = p->c;
     p->tipo = CFLOAT;
}

void nmic(Var *p){ //Int para Char
     p->c = p->i;
     p->tipo = CCHAR;
}

void nmil(Var *p){ 
     p->l = p->i;
     p->tipo = CLONG;
}

void nmif(Var *p){ 
     p->f = p->i;
     p->tipo = CFLOAT;
}

void nmlc(Var *p){ //Long para Char
     p->c = p->l;
     p->tipo = CCHAR;
}

void nmli(Var *p){ 
     p->i = p->l;
     p->tipo = CINT;
}

void nmlf(Var *p){ 
     p->f = p->l;
     p->tipo = CFLOAT;
}

void nmfc(Var *p){ //Float para Char
     p->c = p->f;
     p->tipo = CCHAR;
}

void nmfi(Var *p){ 
     p->i = p->f;
     p->tipo = CINT;
}

void nmfl(Var *p){ 
     p->l = p->f;
     p->tipo = CLONG;
}

//Matriz base para chamada de conversão
void (*nm[4][4])(Var *) = {
        { '\0' , &nmci , &nmcl, &nmcf },
        { &nmic, '\0'  , &nmil, &nmif },
        { &nmlc, &nmli  , '\0', &nmlf },
        { &nmfc, &nmfi  ,&nmfl, '\0'  }
                          };

