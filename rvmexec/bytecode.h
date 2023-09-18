/* 
**  Byte Codes utilizados na VM 
*/

/****** Dicion�rio ********************************
OADD      soma dois operandos
OSUBR     subtra��o de dois operandos
OMUL      multiplica��o de dois operandos
ODIV      divisao dedois ops
OIFFALSE  #n   muda para instru��o #n se falso
OEQ       igualdade entre dois ops
OGT       greater than entre dois ops (edp)
OGTE      greater than and equal edp
OLT       lower than edp
OLTE      lower than and equal edp
OAND      and edp
OOR       or  edp
OGOTO     #n  vai para o operando #n
OCALLF    #c  carrega uma funcao #c no frame
OCALLNATV #c,#p chama fun��o nativa #c com qtd de parametros #p
ORET      retorna para fun��o chamadora, retornando para frame anterior a variavel atual da pilha 
ORETNULL  retorna para fun��o chamadora sem retornar parametro
OUSE      carrega programa na mem�ria
OLOADC    #n carrega constante de id #n
OLOADV    #n carrega vari�vel #n 
OSTORV    #n armazena vari�vel #n
OGLOBL    #n carrega vari�vel global #n, fica em gPrg atual
OGLOBS    #n grava vari�vel global #n, fica em gPrg atual
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
