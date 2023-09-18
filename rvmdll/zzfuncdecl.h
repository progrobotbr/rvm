
/**** DECLARAÇÃO DAS FUNÇÕES UTILIZADAS ****/

/* Funções utilizadas em loadfile.c */
char * nomeFile(char *pnome, ArrayMalloc *pmem);
TCON metaMoveCon(int i, TCT1 pct1, TNM pnm);
TVAR metaMoveVar(int i, TLV1 plv1, TNM pnm);
TFUC metaMoveFunc(TFD1 pfd1, TNM pnm);
CBOOL loadClass(char *s, TCLS **pcls);
char * cps(char **ss, U1 *se, int tam);
char * cps2(char **ss, U1 *se, int tam, ArrayMalloc *pmem);

/****************************
** arrayMalloc 
*****************************/
ArrayMalloc *createArrayMalloc(long tamini);
CBOOL resizeArrayMalloc(ArrayMalloc *self);
CBOOL appendArrayMalloc(ArrayMalloc *self, void *item);
void *safeMalloc(ArrayMalloc *self, int ptam);
void deleteArrayMalloc(ArrayMalloc *self, CBOOL ball);

/****************************
** loadclass.h
*****************************/
int loadClass(char *s, TCLS **pcls);

/****************************
** class.h
*****************************/
CCLS * createInstance(char *pnome, TREENODE *pclassbase, ADMem *pdamem);
TFUC * getFuncClassByIndex(TCLS *pcb, int index);
TFUC * getFuncClassByName(TCLS *pcb, char *pnome);
VAR * getAttribClass(char *pnome, long pindex);
char * getConstante(TCLS *cb, int pindex);

/****************************
** treechar.h
*****************************/
void * initTreeChar();
void * findTreeChar(char *c, TREENODE **self);
CBOOL putTreeChar(char *c, void *val, TREENODE **self);
TREENODE *createTreeNode(char c);

/****************************
** arraydynamic.h
*****************************/
ADMem *createADMem(long tamini);
CCLS  *createADMItem(ADMem self);
int resizeADMem(ADMem *self);
CCLS *appendADMItem(ADMem *self);
CCLS *findADMItemByKey(ADMem *self, long pid);
void deleteADMem(ADMem *self);
void deleteADMItem(ADMem *self, long pindex);

/****************************
** zvm.h
*****************************/
TFRAME * op_createStackFrameByIndex(int index, VAR **pstack, CCLS *pci);
TFRAME * popStackFrame(CBOOL ppopret, TFRAME *ptf, VAR *stack);
TFRAME * op_createStackFrameByName(int pidobj, char *pnomefunc, VAR **pstack);
VAR op_loadc(TCLS *ptcls, int i);
void moveVar(VAR *o, VAR *d);

   




