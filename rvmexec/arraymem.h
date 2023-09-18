
struct _arrayitem {
  long id;     
  unsigned char isActive;
  unsigned char *mem;       
};

typedef struct _arrayitem ArrayItem;

struct _arraymem {
  ArrayItem *mem;
  long tam;     
  long index;
};       

typedef struct _arraymem ArrayMem;


ArrayMem *createArrayMem();
int resizeArray(ArrayMem *self);
ArrayItem *appendArrayItem(ArrayMem *self);
ArrayItem *findItemArrayByKey(ArrayMem *self, long pid);
void deleteArray(ArrayMem *self);
void deleteArrayItem(ArrayMem *self, long pindex);
