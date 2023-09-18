
/**** DECLARAÇÃO DAS FUNÇÕES UTILIZADAS ****/

/* Funções utilizadas em loadfile.c */
char * nomeFile(char *ppath, char *pnome, char *ext, char *pmem);
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
VAR  * getAttribClass(char *pnome, clazzptr pindex);
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
TFRAME * op_createStackFrameByIndex(int index, VAR **pstack, CCLS *pci, TFRAME *ptf, TFRAME **pold, TFRAME **pitf);
TFRAME * popStackFrame(CBOOL ppopret, TFRAME *ptf, VAR *stack);
TFRAME * op_createStackFrameByName(clazzptr pidobj, char *pnomefunc, VAR **pstack, TFRAME *ptf, TFRAME **pold, TFRAME **pitf);
int op_call_native(int plocal, TFUC *tf, CCLS* pci, char *pnomefunc, VAR **pstack);
//void op_loadc(VAR *v, TCLS *ptcls, int i);
void moveVar(VAR *o, VAR *d);
VAR initVarArray(unsigned char tipo, unsigned char isArray, short int tamArray);
int getVarArray(VAR *po, VAR *pd, int pindex);
int setVarArray(VAR *po, VAR *pd, int pindex);
void moveVarArr(VAR *o, VAR *d);
int stackMemResize(TFRAME **pold, TFRAME **pitf);

/****************************
** table.h
*****************************/
table *tbCreate();
node_search tbSearchRoot(table *tb, long pindex);
node  *tbGetNodeByIndex(table *tb, long pindex);
CBOOL  tbInsertRoot(table *tb, clazz *v, long pindex);
CBOOL  tbDeleteRoot(table *tb, long k);
CBOOL  tbUpdateRoot(table *tb, clazz *v,long pindex);

node_search tbSearch(node *x, long pindex, long ipsum);
node *tbSeek(node_search ns);
CBOOL tbInsert(table *tb, clazz *v, long posinnode, node *n1, node *n2, CBOOL pquebra);
CBOOL tbDeleteAdjust(table *tb, node *n);
CBOOL tbDeleteJoinE(node *np, node *ne, node *n);
CBOOL tbDeleteJoinD(node *np, node *nd, node *n);
CBOOL tbDeleteNorm(node *np, node *ne, node *n);
node *tbDeleteGetLast(node *n);
CBOOL tbDeleteNodeElem(table *tb, node *n, long pos);
CBOOL tbNodePutValue(table *tb, node *n, clazz *v, long pos);
CBOOL tbNodePut(node *n1, node *n2, long pos);
node *tbQuebra(node *n);

void printStackFrame(int rc, TFRAME *itf, TFRAME *tf);

node *tbCreateNode();
long  tbGetSize();

/*objetos*/
tableobj *createTbObj();
void freeTbObj(tableobj *tb);

void * zmalloc(unsigned long l);
void * zrealloc(void *p, unsigned long l);
void zfree(void *p);

/***** GC ******/
int GCCreateNodeMem(GCObj *self, void *pmem, unsigned long size);
void GCZmarkObj(GCObj *self, void *v);
void GCZfree(GCObj *self);
void GCPrintMem(GCObj *self);
void *GCZmalloc(GCObj *self, unsigned long size, char ptipo);
CBOOL GCIsMarked(GCObj *self, void *v);
void GCPutReadyAll(GCObj *self);
GCObj * createGCObj();
void GCTraverseTable(GCObj *self, tableobj *tb);
void GCTraverseNodeTable(GCObj *self, node *n);
void GCTraverseObject(GCObj *self, clazzptr o);
void GCTraverseVar(GCObj *self, VAR *v, int ptam);
void GCTraverseFrame(GCObj *self, TFRAME *fini, TFRAME *fatu);
void GCGarbage(TMEMVM *pm);
void GCMark2(void *v, int pFlag);
int initMEMVM(char *nameclass);
void *ymalloc(unsigned long l);
