#include <stdio.h>
#include "zzdata.h"

array newarray(int size_tipo){
      array t = malloc(sizeof(struct _array));
      t->len=0;
      t->size_tipo = size_tipo;
      return(t);
}           

unsigned char * redim( array ar, int tamarray, BOOL preserve){
    int i=0,t=0,z=0; 
    int varsize=0;
    unsigned char * objold;
    unsigned char * objnew;
    int sizeold=0;
    
    varsize = ar->size_tipo;
    sizeold = ar->len;
    objold  = ar->obj;
    t = tamarray * varsize;
    ar->obj = (unsigned char *) malloc(t);
    objnew = ar->obj;
    ar->len = tamarray;
    
    if(preserve == TRUE && tamarray > 0){
         z = sizeold * varsize;      
         for(i=0;i<t;i++){
            if(i>=z){
               break;
            }
            *objnew = *objold;
            objnew++;
            objold++;
         }                   
    }
    
    return(ar->obj);
 
} 

