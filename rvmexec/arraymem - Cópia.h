
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
