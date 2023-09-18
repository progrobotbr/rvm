#include "zzdata.h"
#include "zzfuncdecl.h"
#include <windows.h>
HINSTANCE ghdll;
/* MOTOR DA VM */

#define POP(x) x=*stack;stack--;
#define PUSH(x) stack++;*stack=x;
#define CHECK_DIV_0(p1,p2) switch(p2.tipo){\
                              case CRCHAR:\
                                   if(p2.c==0){\
                                      rc = 80;\
                                   }\
                                   break;\
                              case CINTEGER:\
                                   if(p2.i==0){\
                                      rc = 80;\
                                   }\
                                   break;\
                              case CLONG:\
                                   if(p2.l==0){\
                                      rc = 80;\
                                   }\
                                   break;\
                              case CFLOAT:\
                                   if(p2.f==0){\
                                      rc = 80;\
                                   }\
                                   break;\
                              }

#define CHECK_DIV2_0(p)  if(p.f==0){\
                           rc = 80;\
                         }
#define ERR_RAISE(x) rc=x; printf("\nRC: %i",rc);gMvm.rc = rc; printStackFrame(rc, itf, tf); return;

//x-código da mensagem
//p-opcode
//m-mensagem
//o-objeto
#define ERR_RAISE_MSG(x,p,o,m) rc=x; printf("\nRC: %i -(%s)-%s-%s",rc, p, o, m);gMvm.rc = rc; printStackFrame(rc, itf, tf); return;

#define GETCONSTANTE(o1, i1) o1->cons[i1].nome

#define ADDFF(p1,p2) p2->f+=p1->f

#define MOVEVAR(oo, dd)  if(dd->isArray){\
                           moveVarArr(oo, dd);\
                         }else{\
                           switch(oo->tipo){\
                             case CRCHAR:\
                               switch(dd->tipo){\
                                 case CRCHAR:\
                                   if(oo->isArray){\
                                     if(oo->ca != '\0'){\
                                       dd->c = *oo->ca;\
                                     }else{\
                                       dd->c = ' ';\
                                     }\
                                   }else{\
                                     dd->c = oo->c;\
                                   }\
                                   break;\
                                 case CINTEGER:\
                                   dd->i = oo->c;\
                                   break;\
                                 case CLONG:\
                                   dd->l = oo->c;\
                                   break;\
                                 case CFLOAT:\
                                   dd->f = oo->c;\
                                   break;\
                               }\
                               break;\
                             case CINTEGER:\
                               switch(dd->tipo){\
                                 case CRCHAR:\
                                   dd->c = oo->i;\
                                   break;\
                                 case CINTEGER:\
                                   dd->i = oo->i;\
                                   break;\
                                 case CLONG:\
                                   dd->l = oo->i;\
                                   break;\
                                 case CFLOAT:\
                                   dd->f = oo->i;\
                                   break;\
                               }\
                               break;\
                             case CLONG:\
                               switch(dd->tipo){\
                                 case CRCHAR:\
                                   dd->c = oo->l;\
                                   break;\
                                 case CINTEGER:\
                                   dd->i = oo->l;\
                                   break;\
                                 case CLONG:\
                                   dd->l = oo->l;\
                                   break;\
                                 case CFLOAT:\
                                   dd->f = oo->l;\
                                   break;\
                               }\
                               break;\
                             case CFLOAT:\
                               switch(dd->tipo){\
                                 case CRCHAR:\
                                   dd->c = oo->f;\
                                   break;\
                                 case CINTEGER:\
                                   dd->i = oo->f;\
                                   break;\
                                 case CLONG:\
                                   dd->l = oo->f;\
                                   break;\
                                 case CFLOAT:\
                                   dd->f = oo->f;\
                                   break;\
                               }\
                               break;\
                             case COBJ:\
                               dd->o = oo->o;\
                               break;\
                          }\
                        }
                        
#define CMPLT(oo,dd)   switch(oo->tipo){\
                         case CRCHAR:\
                           switch(dd->tipo){\
                              case CRCHAR:\
                                   oo->i = oo->c < dd->c;\
                                   oo->tipo = CINTEGER;\
                                   break;\
                              case CINTEGER:\
                                   oo->i = oo->c < dd->i;\
                                   oo->tipo = CINTEGER;\
                                   break;\
                              case CLONG:\
                                   oo->i = oo->c < dd->l;\
                                   oo->tipo = CINTEGER;\
                                   break;\
                              case CFLOAT:\
                                   oo->i = oo->c < dd->f;\
                                   oo->tipo = CINTEGER;\
                                   break;\
                           }\
                           break;\
                        case CINTEGER:\
                           switch(dd->tipo){\
                              case CRCHAR:\
                                   oo->i = oo->i < dd->c;\
                                   oo->tipo = CINTEGER;\
                                   break;\
                              case CINTEGER:\
                                   oo->i = oo->i < dd->i;\
                                   oo->tipo = CINTEGER;\
                                   break;\
                              case CLONG:\
                                   oo->i = oo->i < dd->l;\
                                   oo->tipo = CINTEGER;\
                                   break;\
                              case CFLOAT:\
                                   oo->i = oo->i < dd->f;\
                                   oo->tipo = CINTEGER;\
                                   break;\
                           }\
                           break;\
                         case CLONG:\
                           switch(dd->tipo){\
                              case CRCHAR:\
                                   oo->i = oo->l < dd->c;\
                                   oo->tipo = CINTEGER;\
                                   break;\
                              case CINTEGER:\
                                   oo->i = oo->l < dd->i;\
                                   oo->tipo = CINTEGER;\
                                   break;\
                              case CLONG:\
                                   oo->i = oo->l < dd->l;\
                                   oo->tipo = CINTEGER;\
                                   break;\
                              case CFLOAT:\
                                   oo->i = oo->l < dd->f;\
                                   oo->tipo = CINTEGER;\
                                   break;\
                           }\
                           break;\
                         case CFLOAT:\
                            switch(dd->tipo){\
                              case CRCHAR:\
                                   oo->i = oo->f < dd->c;\
                                   oo->tipo = CINTEGER;\
                                   break;\
                              case CINTEGER:\
                                   oo->i = oo->f < dd->i;\
                                   oo->tipo = CINTEGER;\
                                   break;\
                              case CLONG:\
                                   oo->i = oo->f < dd->l;\
                                   oo->tipo = CINTEGER;\
                                   break;\
                              case CFLOAT:\
                                   oo->i = oo->f < dd->f;\
                                   oo->tipo = CINTEGER;\
                                   break;\
                           }\
                           break;\
                         }                        
//bug4
#define CONVINT(ovar, iint)  switch(ovar.tipo){\
                               case CINTEGER:\
                                 iint = ovar.i;\
                                 break;\
                               case CLONG:\
                                 iint = ovar.l;\
                                 break;\
                               case CFLOAT:\
                                 iint = ovar.f;\
                                 break;\
                               default:\
                                 iint = 0;\
                                 break;\
                               }
void execVm(){

  register unsigned char *bc, t;
  char *nome;
  int idx; //bug 4
  short int *si;
  register int rc, i;
  VAR p1, p2, rs, *px1, *pp1, *pp2;
  VAR *stack;;
  TFRAME *tf, *itf, *tfp;

  itf = tf = gMvm.stackFrame;
  stack = tf->stack;
  bc = tf->bc;
  rc=0;
  
  //
  ipause = 0;
  idebqtop = -1; //-1 desliga trace
  //idebqtop = 0; //0 liga trace
  //
  //while(rc==0){
  for(;;){               
    //if(idebqtop == 483){
      // printf("a");         
    //}  
    /*
    TFUC   *tfff=0;
    CCLS   *ciii=0;
    TCLS   *cbbb=0;
    CHAR   *cnnn=0;
    
    ciii = findADMItemByKey(gMvm.memci, 3);
    iiii++;
    if(ciii!=0){
      cbbb = ciii->cb;
      tfff = getFuncClassByName(cbbb, "PRINTILN");
    }
    printf("fff %i %i\n",iiii,tfff);
    
    if(iiii==47757){
      iiii=47757;
    } 
    */
    /* 
    if(ccbb!=0)   
    printf("l%s %i\n",ccbb->nome, ipause++);
    if(ipause==2904393){
      ipause=2904393;
    }
    */
    switch(*bc){
      case _ADD:
        l1(bc);l3();   
        //POP(p1);
        //POP(p2);
        //NORMALIZE(t,p1,p2);
        //gAdd[t](&p1,&p2);
        pp1 = stack--; 
        NORMFLOAT2(pp1);
        NORMFLOAT2(stack);
        //addff(&p1,&p2);
        //addff(pp1,stack);
        ADDFF(pp1,stack);
        //PUSH(p2);
        bc++;
        continue;
        
      case _SUBR:
        l1(bc);l3();   
        POP(p1);
        POP(p2);
        //NORMALIZE(t,p1,p2); 
        //gSub[t](&p1,&p2);  
        NORMFLOAT(p1);
        NORMFLOAT(p2);
        subff(&p1,&p2);
        PUSH(p2);
        bc++;
        continue;
        
      case _MUL:
        l1(bc);l3();   
          
        POP(p1);
        POP(p2);
        //NORMALIZE(t,p1,p2); 
        NORMFLOAT(p1);
        NORMFLOAT(p2);
        //gMul[t](&p1,&p2); 
        mulff(&p1,&p2);
        
        PUSH(p2);
        bc++;
        continue;
        
      case _DIV:
        l1(bc);l3();   
        
        POP(p1);
        POP(p2);
        //NORMALIZE(t,p1,p2); 
        NORMFLOAT(p1);
        NORMFLOAT(p2)
        CHECK_DIV2_0(p1);
        if(rc==0){
          //gDiv[t](&p1,&p2); 
          divff(&p1,&p2);
          PUSH(p2);
          bc++;
        }
        continue;
        
      case _IFFALSE:
        l1(bc);   
        
        bc++;
        ///si = (short int *) bc;
        ///bc++;bc++;
        ////l2(si);l3();   
        ///POP(p1);
        ///if(p1.i==CFALSE){
        if(stack->i==CFALSE){                   
          //bc = tf->bc + *si;
          bc = tf->bc + *((short int *)bc);
        }else{
          bc+=2;    
        }
        stack--;
        continue;
        
      case _EQ:
        l1(bc); l3();  
           
        POP(p1);
        POP(p2);
        NORMALIZE(t,p1,p2); 
        gEq[t](&p1,&p2); 
        PUSH(p2);      
        bc++;
        continue;
        
      case _NEQ:
        l1(bc); l3();  
           
        POP(p1);
        POP(p2);
        NORMALIZE(t,p1,p2); 
        gNe[t](&p1,&p2); 
        PUSH(p2);      
        bc++;
        continue;
        
      case _GT:
        l1(bc); l3();    
        POP(p1);
        POP(p2);
        NORMALIZE(t,p1,p2); 
        gGt[t](&p2,&p1); //invertido
        PUSH(p1);      
        bc++;   
        continue;
        
      case _GTE:
        l1(bc); l3();
        POP(p1);
        POP(p2);
        NORMALIZE(t,p1,p2); 
        gGe[t](&p2,&p1); //invertido
        PUSH(p1);      
        bc++;      
        continue;
        
      case _LT:
        l1(bc); l3(); 
        /*   
        POP(p1);
        POP(p2);
        NORMALIZE(t,p1,p2); 
        gLt[t](&p2,&p1); //invertido
        PUSH(p1);   
        bc++;
        */
        
        pp1 = stack;
        stack--;
        //NORMALIZE2(t,stack, pp1);
        //gLt[t](stack,pp1);
        CMPLT(stack, pp1);
        //*stack = *pp1; //esta parte não é legal
        bc++;
        
        continue;
        
      case _LTE:
        l1(bc); l3(); 
           
        POP(p1);
        POP(p2);
        NORMALIZE(t,p1,p2); 
        gLe[t](&p2,&p1); //invertido
        PUSH(p1);   
        bc++;
        continue;
        
      case _AND:
        l1(bc); l3(); 
           
        POP(p1);
        POP(p2);
        NORMALIZE(t,p1,p2); 
        gAnd[t](&p1,&p2); 
        PUSH(p2);   
        bc++;
        
        continue;
        
      case _OR:
        l1(bc);  l3();
           
        POP(p1);
        POP(p2);
        NORMALIZE(t,p1,p2); 
        gOr[t](&p1,&p2); 
        PUSH(p2);   
        bc++;
        continue;
        
      case _GOTO:
        l1(bc);    
        bc++;
        //si = (short int *) bc;
        
        //l2(si);l3(); 
        
        //bc+=2; //bc++;bc++;
        bc = tf->bc + *((short int *) bc);
        //task 1 - 23.08.2021 - estouro de pilha
        stack = tf->stack;
        continue;
        
      case _CALLF:
        l1(bc); 
          
        bc++;
        si = (short int *) bc;
        bc++;bc++;   
        tf->bc_pt = bc;
        i = *si;
        l2(si);
        tf->stackpt = stack;
        /*printf("testefunc\n");*/
        tfp = tf; //salva o ponto atual
        tf = op_createStackFrameByIndex(i, &stack, tf->ci, tf, &tfp, &itf);  /*** executa push no frame ***/
        /*printf("testefuncsai\n");*/
        if(tf==0){
          tf = tfp;        
          //rc = 5;
          ERR_RAISE(5);
        }else{ 
          l5(tf->nomefunc);l3(); 
          bc = tf->bc_pt = tf->bc;    
        }
        continue;
        
      case _CALLNATV:
        l1(bc); 
        //printf("dd\n");
           
        bc++;
        si = (short int *) bc;
        bc+=2;
        i = *si;
        
        l2(si); 

        nome = getConstante(tf->cb, i); 
        l5(tf->nomefunc);l3(); 
        rc = op_call_native(CTRUE, NULL, tf->ci, nome, &stack);
        if(rc!=0){
          //rc=120;
          ERR_RAISE(120);
        }        
        continue;
        
      case _RET:
        l1(bc); 
        /*tf = popStackFrame(CTRUE, tf, stack);*/
        tfp = tf;
        tf = popStackFrame(CTRUE, tf, stack);
        if(tf==gMvm.stackFrameMem){
          tf = tfp;                         
          //rc = 200;
          ERR_RAISE(200);
        }else{
          bc = tf->bc_pt;  
          stack = tf->stackpt; 
          l4("RET"); l3(); 
        }
        //printf("\ntt\n");system("PAUSE");
        continue;
        
      case _RETNULL:
        l1(bc);  l3();
        tfp = tf;  
        tf = popStackFrame(CFALSE, tf, stack);
        if(tf==gMvm.stackFrameMem){
          tf = tfp;                         
          //rc = 201;
          ERR_RAISE(201);
        }else{
          bc = tf->bc_pt;
          stack = tf->stackpt;   
          l4("RET"); l3(); 
        }
        continue;
        
      case _NEW:
        l1(bc);   
        bc++;
        si = (short int *)bc;
        bc++;bc++;
        i = *si;
        l2(si);  
        nome = getConstante(tf->cb, i);
        //printf(nome);
        l4(nome);l3(); 
        i=op_CreateInstance(nome, &rs);
        if(i>0){
          //rc = 85;
          ERR_RAISE(85);
        }else{
          PUSH(rs);    
        }
                 
        continue;
        
      case _LOADC:
        l1(bc);    
        bc++;
        stack++;
       
        int i1,t;  
        char *c1, *c2;
        TCON *c;
        c               = tf->cb->cons+*((short int *)bc);
        stack->tipo     = c->tipo;
        stack->nomeobj  = '\0';
        stack->isArray  = CFALSE;
        //stack->tamArray = 0;
        switch(c->tipo){
          case CRCHAR:
            stack->c = c->c;
            break;
            
          case CSTRING:
            stack->tipo = CRCHAR;   
            t = strlen(c->nome)+1;
            stack->tamArray = t;
            stack->isArray = CTRUE;
            
            //stack->ca = c->nome; - bug 7 
            //bug 7 - gerar cópia do array
            c1=stack->ca = ymalloc(t);
            if(c1=='\0') {
              ERR_RAISE(78); //printf("\n\nERRO CONSTANTE\n\n");
            }
            
            c2=c->nome;
            for(i1=0;i1<t;i1++){
              *c1=*c2;
              c1++;c2++;               
            }
            
            break; 
            
          case CINTEGER:
            stack->i = c->i;
            break;
          case CLONG:
            stack->l = c->l;
            break;
          case CFLOAT:
            stack->f = c->f;
            break;
          }        
        //Fim Constante

        bc+=2;
        
        continue;
        
      case _LOADV:
        l1(bc);    
        bc++;
        //si = (short int *)bc;
        //bc++;bc++;
        
        //i = *si;
        ////l2(si);l3(); 
        //rs = tf->var[i];
        //rs = tf->var[*((short int *)bc)];
        //PUSH(rs);
        stack++;
        *stack = tf->var[*((short int *)bc)];
        bc+=2;
        
        continue;
        
      case _STORV:
        l1(bc);    
        bc++;
        //si = (short int *)bc;
        //bc++;bc++;
        //bc+=2;
        //i=*si;
        //l2(si);l3();
        //POP(rs);
        pp1 = tf->var+*((short int *)bc);
        
        MOVEVAR(stack, pp1);
        //moveVar(stack, tf->var+*((short int *)bc));
        stack--;
        //moveVar(stack, tf->var+*((short int *)bc));
        
        /*
        pp1 = tf->var+*((short int *)bc);
        pp1->i = stack->i; 
        
        stack--;
        */
        bc+=2;
        
        continue;
        
      case _LOADVY:
        l1(bc);    
        bc++;
        si = (short int *)bc;
        bc++;bc++;
        i=*si;
        l2(si);l3();
        POP(p1);
        p2 = tf->var[i];
        //switch(p1.tipo){ //bug4
          //case CINTEGER:
            //   idx = p1.i;
            //   break;
          //case CLONG:
            //   idx = p1.l;
            //   break;
          //case CFLOAT:
            //   idx = p1.f;
            //   break;
          //default:
            //   idx = 0;
            //   break;
        //}
        
        CONVINT(p1, idx) 
        
        //if(getVarArray(&p2, &rs, p1.i)==0){ // bug 4
        if(getVarArray(&p2, &rs, idx)==0){ // bug 4                           
          //rc = 21;
          ERR_RAISE(21);
        }else{
          PUSH(rs);
        }
        continue;
        
      case _STORVY:
        l1(bc);    
        bc++;
        si = (short int *)bc;
        bc++;bc++;
        i=*si;
        l2(si);l3(); 
        POP(p1);
        POP(rs);
        px1 = tf->var+i;
        
        //bug 4
        CONVINT(p1, idx) 
        
        //if(setVarArray(&rs, px1, p1.i)==0){ bug 4
        if(setVarArray(&rs, px1, idx)==0){
          //rc = 22;
          ERR_RAISE(22);
        }
        continue;
        
      case _GLOADV:
        l1(bc);    
        bc++;
        si = (short int *)bc;
        bc++;bc++;  
        i=*si;
        l2(si);l3(); 
        p1 = tf->ci->atrib[i];
        PUSH(p1); 
        continue;
        
      case _GSTORV:
        l1(bc);     
        bc++;
        si = (short int *)bc;
        bc++;bc++;
        i=*si;
        
        l2(si);l3(); 

        POP(p1);
        moveVar(&p1, tf->ci->atrib+i);           
        continue;
        
      case _GLOADVY:
        l1(bc);   
        bc++;
        si = (short int *)bc;
        bc++;bc++;
        i=*si;
        
        l2(si);l3(); 

        POP(p1);
        p2 = tf->ci->atrib[i];
        //bug 4
        CONVINT(p1, idx) 
        
        //if(getVarArray(&p2, &rs, p1.i)==0){ //bug 4
        if(getVarArray(&p2, &rs, idx)==0){ //bug 4                             
          //rc = 28;
          ERR_RAISE(28);
        }else{
          PUSH(rs);
        }
        continue;
        
      case _GSTORVY:
        l1(bc);    
        bc++;
        si = (short int *)bc;
        bc++;bc++;
        i=*si;
        l2(si);l3(); 
        POP(p1);
        POP(rs);
        px1 = tf->ci->atrib+i;
        //bug 4
        CONVINT(p1, idx) 
        //if(setVarArray(&rs, px1, p1.i)==0){ //bug 4
        if(setVarArray(&rs, px1, idx)==0){ //bug 4
          //rc = 34;
          ERR_RAISE(34); //estouro de array
        }
        continue;
        
      case _OCALLF: //callf de um objeto
        l1(bc);   
        bc++;
        si = (short int *)bc;
        bc++;bc++;   
        i=*si;
        l2(si);
        tf->bc_pt = bc;
        POP(p1);
        nome = getConstante(tf->cb, i);
        l5(nome);l3();
        //tf->stackpt = stack;  
        tfp = tf;
        if(p1.o=='\0'){
          ERR_RAISE_MSG(59, "_OCALLF", nome, "Objecto nao inicializado");
        }
        tf = op_createStackFrameByName(p1.o, nome, &stack, tf, &tfp, &itf);  /*** executa push no frame ***/
        if(tf==0){
          tf = tfp;        
          //rc = 60;
          ERR_RAISE_MSG(60, "_OCALLF", nome, "Erro ao chamar funcao");
        }else{
          bc = tf->bc_pt = tf->bc;
        }
        continue;
        
      case _OLOADV:  //load object
        l1(bc);   
        bc++;
        si = (short int *)bc;
        bc++;bc++;      
        i=*si;
        
        l2(si); 
        POP(p1); 
        nome = getConstante(tf->cb, i);
        //nome = GETCONSTANTE(tf->cb, i);
        l6(nome);l3();
        if(p1.o==0){
          //rc = 47;
          ERR_RAISE(47);
          break;
        }         
        px1 = getAttribClass(nome, p1.o);
        if(px1==0){
          //rc = grc;
          ERR_RAISE(grc);     
        }else{     
          rs = *px1;
          PUSH(rs);
        }
        continue;    
        
      case _OSTORV:
        l1(bc);    
        bc++;
        si = (short int *)bc;
        bc++;bc++;    
        i=*si; // Esta dessincronizado aqui 
        
        l2(si);
        POP(p1);
        POP(p2);
        nome = getConstante(tf->cb, i);
        l6(nome);l3();
        if(p1.o==0){
          //rc = 47;
          ERR_RAISE(47);
          break;
        } 
        px1 = getAttribClass(nome, p1.o);
        if(px1==0){
          //rc = grc;
          ERR_RAISE(grc);     
        }else{  
          moveVar(&p2, px1);
        }  
        continue;    
        
      case _OLOADVY:
        l1(bc);    
        bc++;
        si = (short int *)bc;
        bc++;bc++;    
        i=*si;
        l2(si);   
        POP(p1);
        POP(p2);
        nome = getConstante(tf->cb, i);
        l6(nome);l3();
        if(p1.o==0){
          //rc = 47;
          ERR_RAISE(47);
          break;
        } 
        px1 = getAttribClass(nome, p1.o);
        if(px1 == 0){
           //rc = grc;
           ERR_RAISE(grc);
        }else{
          if(getVarArray(px1, &rs, p2.i)==0){
            //rc = 21;
            ERR_RAISE(21);
          }else{
            PUSH(rs);
          }
        }     
        continue;  
        
      case _OSTORVY:  
        l1(bc); 
   
        bc++;
        si = (short int *)bc;
        bc++;bc++;    
        i=*si;
        l2(si); 
        POP(p1);
        POP(p2);
        POP(rs);
        nome = getConstante(tf->cb, i);
        l6(nome);l3();
        if(p1.o==0){
          //rc = 47;
          ERR_RAISE(47);
          break;
        } 
        px1 = getAttribClass(nome, p1.o);
        if(px1==0){
          rc = grc;
        }else{         
          if(setVarArray(&rs, px1, p2.i)==0){
            //rc = 21;
            ERR_RAISE(21);
          }
        }
        continue;
        
      case _NEWY:
        l1(bc); 
   
        bc++;
        si = (short int *)bc;
        bc++;bc++;    
        i=*si;
        l2(si);l3(); 
        POP(p1);
        p2 = initVarArray(i, CTRUE, p1.i);
        if(grc==0){
          PUSH(p2);
        }
        continue;
        
      case _END:
        l1(bc);l3();   
        if(itf==tf){         
          rc = 1;
          return; //Sucesso
        }else{
          /* retnull */
          tfp = tf;    
          tf = popStackFrame(CFALSE, tf, stack);
          if(tf==gMvm.stackFrameMem){
            tf = tfp;                         
            //rc = 2;
            ERR_RAISE(rc);
           }else{
            bc = tf->bc_pt;
            stack = tf->stackpt;   
          }    
        }
        continue; 
      
      default:
        //rc = 100;    
        ERR_RAISE(100);
        break;
    }
  }
  /*
  gMvm.rc = rc;
  if(rc!=1){
    printf("\nRC: %d\n", rc);
    printStackFrame(itf,tf);
  } 
  */ 
}

/**** FUNCOES AUXILIARES ****/

/**** OPERAÇÔES COM STACK ****/

void freeTFrame(TFRAME *pfr){
  /*** limpa conteudo ***/
}

void popFrame(){
  TFRAME *fr = gMvm.stackFrame;
  freeTFrame(fr);
  gMvm.stackFrame--;
}

TFRAME * pushFrame(){
  TFRAME *fr;     
  gMvm.stackFrame++;
  fr = gMvm.stackFrame;
  return(fr);     
}

int createStackFrame(TFRAME **ptf, CCLS *pci, char *pnomefunc){
  int i, t;
  TFRAME *tfm;
  TFUC *tfc;
  TCLS *cb;
  VAR  *v;
  TVAR *tv;
  /*printf("func_frbyidx0\n");*/
  (*ptf)++;
  tfm=*ptf;
  /*printf("func_frbyidx00\n");*/
  cb = pci->cb;
  tfc = getFuncClassByName(cb, pnomefunc);
  CASSERT(tfc !=0, 1);
  tfm->bc = tfc->bc;
  tfm->tfuc = tfc;
  tfm->nomeclass = cb->nome;
  tfm->nomefunc  = tfc->nome;
  tfm->qtdVar    = 0; //tfc->qtdVar;
  tfm->qtdPar    = tfc->qtdPar;
  tfm->ci        = pci;
  tfm->cb        = cb;   
  tfm->tvar      = tfc->tvar;
  tfm->stack     = '\0';
  /*printf("func_frbyidx1\n");*/
  /* cria área de variáveis*/
  t = tfc->qtdVar;
  if(t>0){
    v = tfm->var = zmalloc(sizeof(VAR)*t);
    for(i=0;i<t;i++){
      v->tipo = 0;
      v++;
    }
    tfm->qtdVar = tfc->qtdVar;
    v = tfm->var;
    tv = tfc->tvar;
    for(i=0;i<t;i++){
      createVARfromTVAR(v, tv);
      v++; tv++;
    }
  }        
  /*printf("func_frbyidx2\n");*/
  /* cria o stack de operações */
  t = tfc->ntamstack;
  tfm->ntamstack = t;
  if(t>0){
    tfm->stack = zmalloc(sizeof(VAR)*(t*2));
  }                     
  /*printf("func_frbyidx3\n");*/
  return(0);
}

int op_call_native(int plocal, TFUC *tf, CCLS* pci, char *pnomefunc, VAR **pstack){
 
 void *(*pmalloc)(unsigned long l); 
 typedef VAR(*pfunc)(int pqtdpar, VAR *pstack, void *(*pmalloc)(unsigned long l));
  
  //ArrayMalloc *mem;
  char mem[1000];
  
  int       iqtdPar;
  pfunc     native;
  HINSTANCE hdll;
  TCLS     *cb;
  VAR      *stack, *st;
  VAR       rs;
  char     *sNomeDll;
  
  //mem = createArrayMalloc(1);
  
  if(plocal == CTRUE){
    cb = pci->cb;
    tf = getFuncClassByName(cb, pnomefunc);   
  }      
  
  CASSERT(tf!=0,1);
  
  iqtdPar = tf->qtdPar;
  *pstack -= iqtdPar-1;
  st = *pstack;
  //*pstack -= 1;
  *pstack -= 1;
  stack = *pstack;
  
  sNomeDll = nomeFile(gPathDll, "rvmdll", ".dll", mem);
  CASSERT(grc==0,52);
  
  if(ghdll==0){
    ghdll = hdll = LoadLibrary(sNomeDll);
  }else{
    hdll = ghdll;    
  }  
  CASSERT(hdll!=0,1);
  
  pmalloc = &zmalloc;
  native = (pfunc)GetProcAddress(hdll, pnomefunc);
  CASSERT(native!=0,2);
  rs = native(iqtdPar, st, pmalloc);
  
  /*printf(rs.ca);*/
  
  if(tf->rettipo!=-1){
    PUSH(rs);
    *pstack = stack;
  }
  
  //deleteArrayMalloc(mem, CTRUE);
  
  return(0);
  
}

TFRAME * op_createStackFrameByIndex(int index, VAR **pstack, CCLS *pci, TFRAME *ptf, TFRAME **pold, TFRAME **pitf){
   int     i,t;
   TCLS   *cb;
   TFRAME *tfr;
   TFUC   *tf;
   TVAR   *tv;
   VAR    *v, *v1, v2;
   VAR    *stack;
   //printf("func_frbyidx0\n");
   cb = pci->cb;
   //printf("func_frbyidx00\n");
   tf = getFuncClassByIndex(cb, index);
   CASSERT(tf!=0, 0);
   //printf("func_frbyidx\n");
   
   //gMvm.stackFrame++;
   stackMemResize(pold, pitf);
   tfr = gMvm.stackFrame;
   tfr->stack = 0;
   tfr->ci = '\0';
   //printf("func_frbyidx1\n");
   /**** Variaveis do frame ****/
   t = tf->qtdVar;
   tfr->qtdVar = 0;
   if(t>0){
     //printf("func_frbyidx02\n");printf("%d\n",t);     
     //ymalloc(50);//printf("func_frbyidx0002\n");
     tfr->var = zmalloc(sizeof(VAR)*t);
     tfr->qtdVar = t;
     //printf("func_frbyidx002\n");printf("%d\n",tfr->var);
     //printf("func_frbyidx0-02\n"); 
     v = tfr->var;
     for(i=0;i<t;i++){
       v->tipo = 0;
       v++;
     }
     v = tfr->var;
     tv = tf->tvar;
     for(i=0;i<t;i++){
       createVARfromTVAR(v, tv);
       v++; tv++;              
     }
   }
 
   //printf("func_frbyidx2\n");
   /**** variaveis de passagem de parametro ****/
   t = tf->qtdPar;
   tfr->qtdPar = t;
   stack = *pstack;
   for(i=0;i<t;i++){
      POP(v2);
      v1 = tfr->var+i;
      moveVar(&v2, v1);
   }
   
   ptf->stackpt = stack;
   
   tfr->bc        = tf->bc;
   tfr->ci        = pci;
   tfr->cb        = cb;
   tfr->tfuc      = tf;
   tfr->nomefunc  = tf->nome;
   tfr->nomeclass = cb->nome;
   tfr->rc        = 0;

   /* cria o stack de operações */ 
   tfr->ntamstack = tf->ntamstack;
   if(tf->ntamstack>0){
     //tfr->stack = zmalloc(sizeof(VAR)*(tf->ntamstack*2));
     //task
     tfr->stack = zmalloc(sizeof(VAR)*(tf->ntamstack*100)); 
     //tfr->stack = zmalloc(sizeof(VAR)*(tf->ntamstack*100)); //bug 1
   }else{
     tfr->stack = zmalloc(sizeof(VAR)*(1*10));     
   }                     
   
   *pstack = tfr->stack;
   
   return(tfr);
   
}

TFRAME * op_createStackFrameByName(clazzptr pidobj, char *pnomefunc, VAR **pstack, TFRAME *ptf, TFRAME **pold, TFRAME **pitf){
  char   *cn;     
  int     i,t;     
  CCLS   *ci;
  TCLS   *cb;
  TFRAME *tfr;
  TFUC   *tf;
  TVAR   *tv;
  VAR    *v, *v1, v2;
  VAR    *stack;
   
  //ci = findADMItemByKey(gMvm.memci, pidobj);
  ci = pidobj;
   CASSERT(ci!=0, 0);
  
  cb = ci->cb;
  
  /**** Ajusta o nome ****/
  cn=pnomefunc;
  while(*cn!='\0'){
    if(*cn=='.'){
      cn++;
      break;
    }
    cn++;          
  }
  
  //if(LM==113251){
  //  LM=113251;
  //}
                  
  tf = getFuncClassByName(cb, cn);
  CASSERT(tf!=0, 0);
  
  /**** Chamada nativa ****/
  if(tf->isNative==CTRUE){
    i = op_call_native(CFALSE, tf, 0, tf->nome, pstack);
    CASSERT(i==0,0);
    return(ptf);
  }
  
  //gMvm.stackFrame++;
  stackMemResize(pold, pitf);
  tfr = gMvm.stackFrame;
  tfr->qtdVar = 0;
  tfr->stack  = '\0';
  tfr->ci     = '\0';
  
  /**** Variaveis do frame ****/
  t = tf->qtdVar;
  if(t>0){
    tfr->var = zmalloc(sizeof(VAR)*t);
    tfr->qtdVar = t;
    v = tfr->var;
    for(i=0;i<t;i++){
      v->tipo = 0;
      v++;
    }
    v = tfr->var;
    tv = tf->tvar;
    for(i=0;i<t;i++){
      createVARfromTVAR(v, tv);
      v++; tv++;              
    }
  }
   
  /**** Variaveis de passagem de parametro ****/
  t = tf->qtdPar;
  stack = *pstack;
  for(i=0;i<t;i++){
    POP(v2);
    v1 = tfr->var + i;
    moveVar(&v2, v1); 
  }
  
  ptf->stackpt = stack;
   
  tfr->bc        = tf->bc;
  tfr->qtdVar    = tf->qtdVar;
  tfr->qtdPar    = tf->qtdPar;
  tfr->ci        = ci;
  tfr->cb        = cb;
  tfr->tfuc      = tf;
  tfr->nomefunc  = tf->nome;
  tfr->nomeclass = cb->nome;
  tfr->rc        = 0;
  
  /* Cria o stack de operações */
  tfr->ntamstack = tf->ntamstack;
  if(tf->ntamstack>0){
    //tfr->stack = zmalloc(sizeof(VAR)*(tf->ntamstack*2));
    tfr->stack = zmalloc(sizeof(VAR)*(tf->ntamstack*100)); //bug 1
  }else{
    tfr->stack = zmalloc(sizeof(VAR)*(1*10));    
   }                     
 
  *pstack = tfr->stack;
   
  return(tfr);
    
}

void liberarZvmVar(VAR *pv){
  if(pv->isArray==CTRUE){ 
    switch(pv->tipo){
      case CRCHAR:
        if(pv->ca==NULL) break;   
        zfree(pv->ca);
        pv->ca = NULL;  
        break;
      case CINTEGER:
        if(pv->ia==NULL) break;   
        zfree(pv->ia);
        pv->ia = NULL; 
        break;
      case CLONG:
        if(pv->la==NULL) break;   
        zfree(pv->la); 
        pv->la = NULL;
        break;
      case CFLOAT:
        if(pv->fa==NULL) break;   
        zfree(pv->fa); 
        pv->fa = NULL;
        break;
      case COBJ:
        if(pv->oa==NULL) break;   
        zfree(pv->oa);
        pv->oa = NULL;
        break;
     }    
  }
}     
    
void liberarZvmVars(int pqtdVar, VAR *pv){
  int i;
  VAR *v=pv;
  for(i=0;i<pqtdVar;i++){
     liberarZvmVar(pv);                    
     pv++;                    
  }
  /*free(v);*/
}

void liberarZvmStack(TFRAME *tf){
  if(tf->ntamstack > 0){
    zfree(tf->stack);
  }
}

TFRAME * popStackFrame(CBOOL ppopret, TFRAME *ptf, VAR *stack){
  TFRAME *tf;
  VAR *v;
  
  /*
  liberarZvmVars(ptf->qtdVar, ptf->var);
  if(ptf->qtdVar>0){
    zfree(ptf->var);
  }
  */
  
  if(ppopret == CTRUE){  
    v = stack;
  }
 
  gMvm.stackFrame--;
  tf = gMvm.stackFrame;
  
  if(ppopret == CTRUE){
    tf->stackpt++;
    *tf->stackpt = *v;
  }           
  
  /*
  liberarZvmStack(ptf);
  */
  
  return(tf);
}

/**** VAR ****/
int setVarArray(VAR *po, VAR *pd, int pindex){
  int i = 1;
  if( pindex < 0 || pindex > ( pd->tamArray-1)){
      return(0);
  }   
  switch(pd->tipo){
    case CRCHAR:
      if(po->isArray == TRUE){
        if(po->tamArray>0){
          pd->ca[pindex] = po->ca[0];                 
        }else{
          pd->ca[pindex] = ' ';    
        }
      }else{                  
        pd->ca[pindex] = po->c;
      }
      break;
    case CINTEGER:
      pd->ia[pindex] = po->i;
      break;
    case CLONG:
      pd->la[pindex] = po->l;
      break;
    case CFLOAT:
      pd->fa[pindex] = po->f;
      break;
    case COBJ:
      pd->oa[pindex] = po->o;
      break;  
    default:
      i = 0;
      break;
  }
  return(i);
}
     
int getVarArray(VAR *po, VAR *pd, int pindex){
  int i = 1;   
  if( pindex < 0 || pindex > ( po->tamArray - 1) ){
      return(0);
  }  
  pd->tipo     = po->tipo;
  pd->isArray  = CFALSE;
  pd->tamArray = 0;
  pd->nomeobj  = 0;
  switch(pd->tipo){
    case CRCHAR:
      pd->c = po->ca[pindex];
      break;
    case CINTEGER:
      pd->i = po->ia[pindex];
      break;
    case CLONG:
      pd->l = po->la[pindex];
      break;
    case CFLOAT:
      pd->f = po->fa[pindex];
      break;
    case COBJ:
      pd->o = po->oa[pindex];
      break;
    default:
      i = 0;
      break;  
  }
  return(i);
}

/*
** Iniciliza variavel e passa para objeto
*/
VAR initVarArray(unsigned char tipo,
                 unsigned char isArray,
                 short int     tamArray){
    
    int i;
    char      *ca;
    int       *ia;
    long      *la;
    double    *fa;
    clazzptr  *oa;              
    VAR v1;
    
    grc = 0;
    v1.tipo = tipo;
    v1.isArray = isArray;
    v1.tamArray = tamArray;
    
    if(isArray==CTRUE){
      switch(tipo){
        case CRCHAR:
          ca = v1.ca = zmalloc(sizeof(char)*tamArray);
          if(ca == 0){
            grc = 93;
            break;
          }
          for(i=0;i<tamArray;i++){
            *ca = '\0';
            ca++;               
          }
          break;
        case CINTEGER:
          ia = v1.ia = zmalloc(sizeof(int)*tamArray); 
          if(ia == 0){
            grc = 93;
            break;
          }
          for(i=0;i<tamArray;i++){
            *ia = 0;
            ia++;               
          }
          break;
        case CLONG:
          la =v1.la = zmalloc(sizeof(long)*tamArray);
          if(la == 0){
            grc = 93;
            break;
          }
          for(i=0;i<tamArray;i++){
            *la = 0;
            la++;               
          }
          break;
        case CFLOAT:
          fa = v1.fa = zmalloc(sizeof(double)*tamArray);
          if(fa == 0){
            grc = 93;
            break;
          }
          for(i=0;i<tamArray;i++){
            *fa = 0;
            fa++;               
          }
          break;
        case COBJ:
          oa = v1.oa = zmalloc(sizeof(clazzptr)*tamArray);
          if(oa == 0){
            grc = 93;
            break;
          }
          for(i=0;i<tamArray;i++){
            *oa = 0;
            oa++;               
          }
          break;  
      }
    }
    return(v1);
}

/* filha de moveVar */
void moveVarArr(VAR *o, VAR *d){
  int i, tamArray;
  char       *c1, *c2;
  int        *i1, *i2;
  long       *l1, *l2;
  double     *f1, *f2;
  clazzptr   *cz1, *cz2;     
  
  d->tamArray = o->tamArray;
 
  /*   
  switch(d->tipo){
    case CRCHAR:
      if(o->ca != d->ca){   
        free(d->ca);
      }  
      break;   
    case CINTEGER:
      if(o->ia != d->ia){   
        free(d->ia);
      }     
      break;
    case CLONG:
      if(o->la != d->la){   
        free(d->la);
      }  
      break;
    case CFLOAT:
      if(o->fa != d->fa){   
        free(d->fa);
      }  
      break;
    case COBJ:
      if(o->oa != d->oa){   
        free(d->oa);
      }     
      break;
  }
  */
    
  d->tipo = o->tipo;
  //tamArray = d->tamArray;
      
  switch(o->tipo){
    case CRCHAR:
      //bug 6 
      d->ca = o->ca;   
      //c1 = d->ca = zrealloc(d->ca, sizeof(char)*tamArray);
      //c2 = o->ca;
      //for(i=0;i<tamArray;i++){
      //    *c1 = *c2;
      //    c1++; c2++;               
      //}   
      return;
    case CINTEGER:
      //bug 6 
      d->ia = o->ia;
      //i1 = d->ia = zrealloc(d->ia, sizeof(int)*tamArray);
      //i2 = o->ia;
      //for(i=0;i<tamArray;i++){
      //    *i1 = *i2;
      //    i1++; i2++;               
      //}   
      return;
    case CLONG:
      //bug 6 
      d->la = o->la;
      //l1 = d->la = zrealloc(d->la, sizeof(long)*tamArray);
      //l2 = o->la;
      //for(i=0;i<tamArray;i++){
      //    *l1 = *l2;
      //    l1++; l2++;               
      //}   
      return;
    case CFLOAT:
      d->fa = o->fa;
      //bug 6
      //f1 = d->fa = zrealloc(d->fa, sizeof(double)*tamArray);
      //f2 = o->fa;
      //for(i=0;i<tamArray;i++){
      //    *f1 = *f2;
      //    f1++; f2++;               
      //}   
      return;
    case COBJ:
      //bug 6
      d->oa = o->oa;
      //d->oa = zrealloc(d->oa, sizeof(clazzptr)*tamArray);
      //cz1 = d->oa;
      //cz2 = o->oa;
      //for(i=0;i<tamArray;i++){
      //    *cz1 = *cz2;
      //    cz1++; cz2++;               
      //}   
      return;
  }
}

void moveVar(VAR *o, VAR *d){
 
  if(d->isArray){
                    
    moveVarArr(o, d);                    
             
  }else{
           
    switch(o->tipo){
      case CRCHAR:
         switch(d->tipo){
          case CRCHAR:
            if(o->isArray){
              if(o->ca != '\0'){
                d->c = *o->ca;
              }else{
                d->c = ' ';    
              }                            
            }else{                  
              d->c = o->c;
            }     
            return;
          case CINTEGER:
            d->i = o->c;  
            return;   
          case CLONG:
            d->l = o->c;
            return;                            
          case CFLOAT:
            d->f = o->c;                   
            return;
          case CVAROBJ: //bug-3
            d->tipo = o->tipo;
            d->isArray = o->isArray;
            d->tamArray = o->tamArray;
            if(o->isArray){
              if(o->ca != '\0'){
                d->ca = o->ca;
              }else{
                d->c = ' ';    
              }                            
            }else{                  
              d->c = o->c;
            }      
            return;           
        }
        return;
      case CINTEGER:
        switch(d->tipo){
          case CRCHAR:
            d->c = o->i;   
            return;
          case CINTEGER:
            d->i = o->i;  
            return;   
          case CLONG:
            d->l = o->i;  
            return;                          
          case CFLOAT:
            d->f = o->i;                   
            return;
          case CVAROBJ: //bug-3
            d->tipo = o->tipo;
            d->isArray = o->isArray;
            d->tamArray = o->tamArray;
            d->i = o->i;     
            return;                
        }
        return;
      case CLONG:
        switch(d->tipo){
          case CRCHAR:
            d->c = o->l;   
            return;
          case CINTEGER:
            d->i = o->l;  
            return;   
          case CLONG:
            d->l = o->l;
            return;
          case CFLOAT:
            d->f = o->l;                   
            return;
          case CVAROBJ:
            d->tipo = o->tipo; //bug 3
            d->isArray = o->isArray;
            d->tamArray = o->tamArray;
            d->l = o->l;   
            return;                
        }
        return;
      case CFLOAT:
        switch(d->tipo){
          case CRCHAR:
            d->c = o->f;   
            return;
          case CINTEGER:
            //d->i = o->f;  
            lua_number2integer(d->i,o->f);	
            return;   
          case CLONG:
            d->l = o->f;                            
          case CFLOAT:
            d->f = o->f;                   
            return;
          case CVAROBJ: //bug-3
            d->tipo = o->tipo;
            d->isArray = o->isArray;
            d->tamArray = o->tamArray;
            d->f = o->f;       
            return;           
        }
        return;
      case COBJ:
        d->o = o->o;
        if(d->tipo == CVAROBJ){ //bug-3
           d->tipo    = o->tipo;
           d->isArray = o->isArray;
           d->tamArray = o->tamArray;
           d->nomeobj = o->nomeobj;   
        }
        return;
      case CTBTABLE:
        d->tipo = CTBTABLE;  
        d->t = o->t;
        return;   
    } 
  }                  
}


/*  backup
void moveVar(VAR *o, VAR *d){
  int i, tamArray;
  char   *c1, *c2;
  int    *i1, *i2;
  long   *l1, *l2;
  double *f1, *f2;
    
  if(d->isArray){
                    
    d->tamArray = o->tamArray;
    
    switch(d->tipo){
      case CRCHAR:
        if(o->ca != d->ca){   
          free(d->ca);
        }  
        break;   
      case CINTEGER:
        if(o->ia != d->ia){   
          free(d->ia);
        }     
        break;
      case CLONG:
        if(o->la != d->la){   
          free(d->la);
        }  
        break;
      case CFLOAT:
        if(o->fa != d->fa){   
          free(d->fa);
        }  
        break;
      case COBJ:
        if(o->oa != d->oa){   
          free(d->oa);
        }     
        break;
    }
    
    d->tipo = o->tipo;
    tamArray = d->tamArray;
      
    switch(o->tipo){
      case CRCHAR:
        c1 = d->ca = ymalloc(sizeof(char)*tamArray);
        c2 = o->ca;
        for(i=0;i<tamArray;i++){
            *c1 = *c2;
            c1++; c2++;               
        }   
        return;
      case CINTEGER:
        i1 = d->ia = ymalloc(sizeof(int)*tamArray);
        i2 = o->ia;
        for(i=0;i<tamArray;i++){
            *i1 = *i2;
            i1++; i2++;               
        }   
        return;
      case CLONG:
        l1 = d->la = ymalloc(sizeof(long)*tamArray);
        l2 = o->la;
        for(i=0;i<tamArray;i++){
            *l1 = *l2;
            l1++; l2++;               
        }   
        return;

      case CFLOAT:
        d->fa = o->fa;
        f1 = d->fa = ymalloc(sizeof(double)*tamArray);
        f2 = o->fa;
        for(i=0;i<tamArray;i++){
            *f1 = *f2;
            f1++; f2++;               
        }   
        return;

      case COBJ:
        d->oa = o->oa;
        l1 = d->oa = ymalloc(sizeof(long)*tamArray);
        l2 = o->oa;
        for(i=0;i<tamArray;i++){
            *l1 = *l2;
            l1++; l2++;               
        }   
        return;
      }                     
             
   }else{
           
      switch(o->tipo){
        case CRCHAR:
          switch(d->tipo){
            case CRCHAR:
              if(o->isArray){
                if(o->ca != '\0'){
                  d->c = *o->ca;
                }else{
                  d->c = ' ';    
                }                            
              }else{                  
                d->c = o->c;
              }     
              return;
            case CINTEGER:
              d->i = o->c;  
              return;   
            case CLONG:
              d->l = o->c;                            
            case CFLOAT:
              d->f = o->c;                   
              return;      
          }
          return;
        case CINTEGER:
          switch(d->tipo){
            case CRCHAR:
              d->c = o->i;   
              return;
            case CINTEGER:
              d->i = o->i;  
              return;   
            case CLONG:
              d->l = o->i;                            
            case CFLOAT:
              d->f = o->i;                   
              return;      
          }
          return;
        case CLONG:
          switch(d->tipo){
            case CRCHAR:
              d->c = o->l;   
              return;
            case CINTEGER:
              d->i = o->l;  
              return;   
            case CLONG:
              d->l = o->l;
              return;
            case CFLOAT:
              d->f = o->l;                   
              return;      
          }
          return;
        case CFLOAT:
          switch(d->tipo){
            case CRCHAR:
              d->c = o->f;   
              return;
            case CINTEGER:
              //d->i = o->f;  
              lua_number2integer(d->i,o->f);	
              return;   
            case CLONG:
              d->l = o->f;                            
            case CFLOAT:
              d->f = o->f;                   
              return;      
          }
          return;
        case COBJ:
          d->o = o->o;
          return;
      } 
   }                  
}
*/

int stackMemResize(TFRAME **pold, TFRAME **pitf){
  TFRAME *tf;
  long l, lidx;
  if(gMvm.stackFrame > ( gMvm.stackFrameFim - 1 ) ){
   //bug 5
   //lidx = *pold - gMvm.stackFrameMem;
   lidx = *pold - gMvm.stackFrameMem - 1 ;                 
    l = gMvm.stackTam+STACKTAM; //bug 5
    tf = ymalloc(sizeof(TFRAME)*l);
    memcpy(tf, gMvm.stackFrameMem, sizeof(TFRAME) * gMvm.stackTam);
    gMvm.stackFrameMem = tf;
    //gMvm.stackTam+=100;  //bug 5
    gMvm.stackTam+=STACKTAM;  
    gMvm.stackFrameFim = gMvm.stackFrameMem + gMvm.stackTam-1;  
    gMvm.stackFrame = gMvm.stackFrameMem + lidx;
    *pold = gMvm.stackFrame; 
    *pitf = gMvm.stackFrameMem+1;
    //printf("stack %i", gMvm.stackTam);
    //system("PAUSE");
  }
  gMvm.stackFrame++;
}


/////////////////////////////
// PRINT STACK
/////////////////////////////
void printStackFrame(int rc, TFRAME *itf, TFRAME *tf){
     
  //printf("\nRC: %d\n", rc);
     
  printf("\n[STACK]\n"); 
  
  while(itf != tf){
    printf(" %s %s\n",tf->nomeclass,tf->nomefunc); 
    tf--;     
  }
  if(itf==tf){
    printf(" %s %s\n",tf->nomeclass,tf->nomefunc); 
  }
  
  printf("\n");
     
}
/////////////////////////////
// DEBUG DEBUG DEBUG DEBUG
/////////////////////////////
void l1(unsigned char *c){
  if(idebqtop==-1) return;   
  printf("%i - %i - ",idebqtop, *c);   
}

void l2(short int *si){
  if(idebqtop==-1) return;   
  unsigned char *b = (unsigned char *) si ;   
  printf("%i - %i",b[0], b[1]);   
}

void l3(){
     
  if(idebqtop==-1) return;
  printf("\n");
  idebqtop++;
  
  if(idebqtop==686){ //118  //69
    printf("t");                
  }
  
  if(ipause == 1){
     msystem("PAUSE");
  }   
}

void l4(char *n){
     if(idebqtop==-1) return;
     printf(" - %s ", n);
}

void l5(char *n){
     if(idebqtop==-1) return;     
     printf(" - func %s ", n);
}

void l6(char *n){
     if(idebqtop==-1) return;     
     printf(" - atrib %s ", n);
}

void msystem(char *c){
     getchar();
}

