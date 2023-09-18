#include <stdio.h>
#include <stdlib.h>
#include "zzdata.h"

int rput(FILE *pfp, unsigned char *pv ,string pid){
     int i=0;
     short int x=0;
     CL1 *mCl1;
     QT  *mQt;
     CT1 *mCt1;
     FD1 *mFd1;
     LV1 *mLv1;
     //fwrite(str , 1 , sizeof(str) , fp );
     if(SL(pid,SS("CL1"))){
        i = fwrite("CL1",1,3,pfp);                   
        mCl1 = (CL1 *)pv; 
        i = fwrite(mCl1,1,6,pfp);
        x = mCl1->sNome->size(mCl1->sNome);
        i = fwrite(&x,1,2,pfp);
        i = fwrite(mCl1->sNome->c,1,x,pfp);  
    }else if(SL(pid,SS("CT1"))){  
        i = fwrite("CT1",1,3,pfp);                   
        mCt1 = (CT1 *)pv;                   
        i = fwrite(mCt1, 1 , 6, pfp );  
        x = mCt1->nome->size(mCt1->nome);
        i = fwrite(&x,1,2,pfp);
        i = fwrite(mCt1->nome->c,1,x,pfp);   
    }else if(SL(pid,SS("CTQ"))){
        i = fwrite("CTQ",1,3,pfp);                   
        mQt = (QT *)pv;                   
        i = fwrite(mQt, 1 , 2, pfp );                  
    }else if(SL(pid,SS("FD1"))){
        i = fwrite("FD1",1,3,pfp);                   
        mFd1 = (FD1 *)pv;                    
        i = fwrite(mFd1 , 1, 18, pfp );  
          
        x = mFd1->nome->size(mFd1->nome);
        i = fwrite(&x,1,2,pfp);
        i = fwrite(mFd1->nome->c,1,x,pfp);  
        
        x = mFd1->retnomeobj->size(mFd1->retnomeobj);
        i = fwrite(&x,1,2,pfp);
        i = fwrite(mFd1->retnomeobj->c,1,x,pfp);               
    }else if(SL(pid,SS("FQT"))){
        i = fwrite("FQT",1,3,pfp);                   
        mQt = (QT *)pv;                   
        i = fwrite(mQt, 1 , 2, pfp );                       
    }else if(SL(pid,SS("FVQ"))){ 
        i = fwrite("FVQ",1,3,pfp);                   
        
        mQt = (QT *)pv;                   
        i = fwrite(mQt, 1 , 2, pfp );   
    }else if(SL(pid,SS("FVL"))){
        i = fwrite("FVL",1,3,pfp);                   
          
        mLv1 = (LV1 *)pv;                   
        i = fwrite(mLv1, 1 , 7, pfp );  
        
        x = mLv1->nome->size(mLv1->nomeobj);
        i = fwrite(&x,1,2,pfp);
        i = fwrite(mLv1->nomeobj->c,1,x,pfp);  
        
        x = mLv1->nomeobj->size(mLv1->nome);
        i = fwrite(&x,1,2,pfp);
        i = fwrite(mLv1->nome->c,1,x,pfp);            
    }else if(SL(pid,SS("BC1"))){
          
        i = fwrite("BC1", 1 , 3, pfp );  
    }  
        
    return(i);
}

int rput2(FILE *pfp, unsigned char *pv ,string pid, int ptam){
    int i;
    i = fwrite(pv,1,ptam,pfp);
}

int read(FILE *pfp, unsigned char *pv ,string pid){
     int i=0, z;
     short int *t=NIL;
     unsigned char buffer[1024];
     CL1 *mCl1, *mCl1b;
     CT1 *mCt1, *mCt1b;
     QT *mQt, *mQtb;
     FD1 *mFd1, *mFd1b;
     LV1 *mLv1, *mLv1b;
     
     if(SL(pid,SS("CL1"))){
       mCl1 = (CL1*)pv;
       i = fread(buffer,1,3,pfp);                    
       i = fread(buffer,1,6,pfp);
       mCl1b = (CL1*)buffer;
       *mCl1 = *mCl1b;
       i = fread(buffer,1,2,pfp);
       t = (short int *) buffer;
       z = *t;
       i = fread(buffer,1,z,pfp);
       buffer[z]='\0';
       mCl1->sNome=SS(buffer);
     }else if(SL(pid,SS("CTQ"))){
       mQt = (QT*)pv; 
       i = fread(buffer,1,3,pfp);     
       i = fread(buffer,1,2,pfp);  
       mQtb = (QT*)buffer;
       *mQt = *mQtb; 
     }else if(SL(pid,SS("CT1"))){ 
       mCt1 = (CT1*)pv;
       i = fread(buffer,1,3,pfp);     
       i = fread(buffer,1,6,pfp);  
       mCt1b = (CT1*)buffer;
       *mCt1 = *mCt1b;     
       
       i = fread(buffer,1,2,pfp);
       t = (short int *) buffer;
       z = *t;
       i = fread(buffer,1,z,pfp);
       buffer[z]='\0';
       mCt1->nome=SS(buffer);
             
     }else if(SL(pid,SS("FD1"))){
       mFd1 = (FD1*)pv;    
       i = fread(buffer,1,3,pfp);
       i = fread(buffer,1,18,pfp);
       mFd1b = (FD1 *)buffer;
       *mFd1 = *mFd1b;
       
       i = fread(buffer,1,2,pfp);
       t = (short int *) buffer;
       z = *t;
       i = fread(buffer,1,z,pfp);
       buffer[z]='\0';
       mFd1->nome=SS(buffer);
       
       i = fread(buffer,1,2,pfp);
       t = (short int *) buffer;
       z = *t;
       i = fread(buffer,1,z,pfp);
       buffer[z]='\0';
       mFd1->retnomeobj=SS(buffer);
       
     }else if(SL(pid,SS("FQT"))){
       mQt = (QT*)pv; 
       i = fread(buffer,1,3,pfp);   
       i = fread(buffer,1,2,pfp);  
       mQtb = (QT*)buffer;
       *mQt = *mQtb;        
     }else if(SL(pid,SS("FVQ"))){
       mQt = (QT*)pv;
       i = fread(buffer,1,3,pfp);
       i = fread(buffer,1,2,pfp);  
       mQtb = (QT*)buffer;
       *mQt = *mQtb;        
     }else if(SL(pid,SS("FVL"))){
       mLv1 = (LV1*)pv;
       i = fread(buffer,1,3,pfp);
       i = fread(buffer,1,7,pfp);  
       mLv1b = (LV1*)buffer;
       *mLv1 = *mLv1b;  
       
       i = fread(buffer,1,2,pfp);
       t = (short int *) buffer;
       z = *t;
       i = fread(buffer,1,z,pfp);
       buffer[z]='\0';
       mLv1->nomeobj=SS(buffer);
       
       i = fread(buffer,1,2,pfp);
       t = (short int *) buffer;
       z=*t;
       i = fread(buffer,1,z,pfp);
       buffer[z]='\0';  
       mLv1->nome=SS(buffer); 
       
     }else if(SL(pid,SS("BC1"))){
       i = fread(buffer,1,3,pfp); 
     } 
     return(i);

}

int read2(FILE *pfp,unsigned char * pdata,string pid, int tam){
    int i=0;
    unsigned char buffer[tam+1];
    
    i = fread(buffer,1,tam,pfp);
}

string readall(){
    
  int i=0;
  unsigned char buffer[1025];
  FILE *fp;
  string s1 = SS(""), s2 = SS("");
  string sf = SC3(gPath, gFileSource, gExtSource);
  
  fp = fopen(sf->c, "rb");
  
  i = fread(buffer,1,1024,fp);
  while(i){
     buffer[i] = '\0';
     s1 = SS(buffer);
     //printf(sss1->c);
     s2 = SC(s2, s1);    
     i = fread(buffer,1,1024,fp);
  }

  fclose(fp);
  
  return(s2);
  
}
