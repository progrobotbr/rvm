
typedef char * PPMEM;

typedef struct _arrayitem ArrayItem;

struct _arrayMalloc {
  PPMEM *mem;
  long tam;     
  long index;
};       

typedef struct _arrayMalloc ArrayMalloc;
/*typedef ArrayMalloc * MEM;*/

ArrayMalloc *createArrayMalloc(long tamini);
CBOOL resizeArrayMalloc(ArrayMalloc *self);
CBOOL appendArrayMalloc(ArrayMalloc *self, void *item);
void * safeMalloc(ArrayMalloc *self, int ptam);
void deleteArrayMalloc(ArrayMalloc *self, CBOOL ball);
