/* 
**  Byte Codes utilizados na VM 
*/

/****** Dicionário ********************************
OADD      soma dois operandos
OSUBR     subtração de dois operandos
OMUL      multiplicação de dois operandos
ODIV      divisao dedois ops
OIFFALSE  #n   muda para instrução #n se falso
OEQ       igualdade entre dois ops
OGT       greater than entre dois ops (edp)
OGTE      greater than and equal edp
OLT       lower than edp
OLTE      lower than and equal edp
OAND      and edp
OOR       or  edp
OGOTO     #n  vai para o operando #n
OCALLF    #c  carrega uma funcao #c no frame
OCALLNATV #c,#p chama função nativa #c com qtd de parametros #p
ORET      retorna para função chamadora, retornando para frame anterior a variavel atual da pilha 
ORETNULL  retorna para função chamadora sem retornar parametro
OUSE      carrega programa na memória
OLOADC    #n carrega constante de id #n
OLOADV    #n carrega variável #n 
OSTORV    #n armazena variável #n
OGLOBL    #n carrega variável global #n, fica em gPrg atual
OGLOBS    #n grava variável global #n, fica em gPrg atual
**************************************************/

#define OADD      50
#define OSUBR     51
#define OMUL      52
#define ODIV      53
#define OIFFALSE  60
#define OEQ       61
#define OGT       62
#define OGTE      63
#define OLT       64
#define OLTE      65
#define OAND      66
#define OOR       67
#define OGOTO     70
#define OCALLF    71      
#define OCALLNATV 72  
#define ORET      73       
#define ORETNULL  74   
#define OUSE      75       
#define OLOADC    80     
#define OLOADV    81     
#define OSTORV    82
#define OLODVM    83
#define OSTOVM    84 
#define OGLOBL    85  
#define OGLOBS    86   


/*
** Matriz de bytecode
*/
U1 gByteCode[255];
