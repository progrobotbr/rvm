
struct _admem {
  CCLS *mem;
  long tam;     
  long index;
  int tamitem;
};       

typedef struct _admem ADMem;

ADMem *createADMem(long tamini);
CCLS  *createADMItem(ADMem self);
int resizeADMem(ADMem *self);
CCLS *appendADMItem(ADMem *self);
CCLS *findADMItemByKey(ADMem *self, long pid);
void deleteADMem(ADMem *self);
void deleteADMItem(ADMem *self, long pindex);
