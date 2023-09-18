
#include "var.h"
#include "tipos.h"
#include "bytecode.h"
#include "conversao.h"
#include "operador.h"
#include "pilha.h"

/*
** Motor da máquina Virtual
*/
               
#define NORMALIZE(t,p1,p2)  if(p1.tipo==p2.tipo) \
                              t=p1.tipo; \
                            else \
                              if(p1.tipo>p2.tipo){ \
                                t=p1.tipo; \
                                nm[p2.tipo][p1.tipo](&p2); \
                              }else{ \
                                t=p2.tipo; \
                                nm[p1.tipo][p2.tipo](&p1); \
                              }
               
int gRc;     //Contém código final de processamento
char *gMsg;  //Mensagem de retorno

void execVm(){
  U1 t, byteOp;
  int i,iTamNode;
  Var p1, p2, rs;
  NodesOp *gOpNode, *gOpNodeFim;
  
  iTamNode = sizeof(NodesOp);
  gOpNode = gFrame->Funcao->nodeop;
  gOpNodeFim = gFrame->Funcao->nodeop + gFrame->Funcao->qtdnodeop - 1;
  gRc=TRUE;
  
  while(gRc){
    byteOp = gOpNode->Op;
    switch(byteOp){
      case OADD:
        p1 = Pop();
        p2 = Pop();
        NORMALIZE(t,p1,p2);
        rs = gAdd[t](&p1,&p2);  
        Push(rs);
        gOpNode++;
        break;
      case OSUBR:
        p1 = Pop();
        p2 = Pop();
        NORMALIZE(t,p1,p2); 
        rs = gSub[t](&p1,&p2);  
        Push(rs);
        gOpNode++;
        break;
      case OMUL:
        p1 = Pop();
        p2 = Pop();
        NORMALIZE(t,p1,p2); 
        rs = gMul[t](&p1,&p2); 
        Push(rs);
        gOpNode++;
        break;
      case ODIV:
        p1 = Pop();
        p2 = Pop();
        NORMALIZE(t,p1,p2); 
        rs = gDiv[t](&p1,&p2); 
        Push(rs);
        gOpNode++;
        break;
      case OLOADC:
        i = *gOpNode->parametros;
        rs = loadc(i);
        Push(rs);
        gOpNode++;
        break;
      case OLOADV:
        i = *gOpNode->parametros;
        rs = loadv(i);
        Push(rs);
        gOpNode++;
        break;
      case OSTORV:
        i = *gOpNode->parametros;
        rs = Pop();
        storv(i,rs);
        gOpNode++;
        break;
      case OEQ:
        p2 = Pop();
        p1 = Pop();
        NORMALIZE(t,p1,p2); 
        rs = gEq[t](&p1,&p2); 
        Push(rs);      
        gOpNode++;
        break;           
      case OGT:
        gOpNode++;
        break;
      case OLT:
        p2 = Pop();
        p1 = Pop();
        NORMALIZE(t,p1,p2); 
        rs = gLt[t](&p1,&p2); 
        Push(rs);   
        gOpNode++;
        break;
      case OIFFALSE:
        i = *gOpNode->parametros;
        p1 = Pop();
        if(p1.i==FALSE){
          gOpNode = gFrame->Funcao->nodeop + i - 1;
        }else{
          gOpNode++;     
        }  
        break;
      case OGOTO:
        i = *gOpNode->parametros;
        gOpNode = gFrame->Funcao->nodeop + i - 1;
        break;
      case OCALLF:
        gOpNode++;   
        break;
      case ORET:
        gOpNode++;
        break;
      case OCALLNATV:
        gOpNode++;
        break;
      default:
        gOpNode++;
        break;    
    }
    if(gOpNode > gOpNodeFim)
      gRc = FALSE;
  }
}

