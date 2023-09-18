#include "zzdata.h"
#include "zzfuncdecl.h"

#define CTBNULL  0
#define TAMNODE 12
#define T        6

tableobj *createTbObj(){
  tableobj *tb = zmalloc(sizeof(tableobj));
  if(tb!=CTBNULL){
    gMvm.GCMem->mark2(tb,GCNORELEASE);              
    tb->tb=tbCreate();
    if(tb->tb!=CTBNULL){                  
      tb->getItem=&tbGetNodeByIndex;
      tb->Insert=&tbInsertRoot;       
      tb->Delete=&tbDeleteRoot;
      tb->Update=&tbUpdateRoot;
      gMvm.GCMem->mark2(tb,GCRELEASE); 
    }else{
      //zfree(tb);
      gMvm.GCMem->mark2(tb,GCRELEASE); 
      tb=CTBNULL;    
    }
  }
  return(tb);
} 

void freeTbObj(tableobj *tb){
  /*implementar lógica */   
}                           

table *tbCreate(){
  table *tb;
  tb = zmalloc(sizeof(table));
  if(tb!=CTBNULL){
    gMvm.GCMem->mark2(tb,GCNORELEASE);               
    tb->root = tbCreateNode();
    if(tb->root!=CTBNULL){
      tb->root->leaf=CTRUE;
      tb->size = 0;
      tb->count = 0;
      gMvm.GCMem->mark2(tb,GCRELEASE);
    }else{
      //zfree(tb);
      gMvm.GCMem->mark2(tb,GCRELEASE);
      tb=CTBNULL;    
    }
  }
  return(tb);
}
 
node_search tbSearchRoot(table *tb, long pindex){     
  node_search ns;
  ns.node=CTBNULL;
  if(pindex>tb->size){
    return(ns);
  }
  ns=tbSearch(tb->root,pindex,0);
  return(ns);		
}

node_search tbSearch(node *x, long pindex, long ipsum){
  long i,t;
  long isum, isum2;
  node *nn;
  node_search ns;
  
  ns.node=CTBNULL;
  t=x->tam;
  isum2=isum=ipsum;
  nn=x->child;
  
  if(x->leaf==CFALSE){
    for(i=0;i<t;i++){
      isum2+=nn->sum;
      if(isum2>=pindex){
    	break;
      }
      isum=isum2;
      nn=nn->nextnode;
    }
    ns=tbSearch(nn,pindex,isum);
  }else{
    t=pindex-ipsum;
	ns.node=x;
    ns.pos=t;
  }
  return(ns);
}

node *tbSeek(node_search ns){
  long i;
  node *ln,*n;
  n=ns.node;
  if(n==CTBNULL){
    return(n);            
  }  
  ln=n->child;
  for(i=1;i<ns.pos;i++){
	ln=ln->nextnode;
  }
  return(ln);
}

node *tbGetNodeByIndex(table *tb, long pindex){
  node *n;   
  node_search ns;
  ns=tbSearchRoot(tb, pindex);
  n=tbSeek(ns);
  return(n);
}     
    
CBOOL tbInsertRoot(table *tb, clazz *v, long pindex){
  CBOOL b;
  long t;
  node *n;
  node_search ns;
		
  pindex--;
  if(pindex>tb->size+1){
	return(CFALSE);
  }
		
  ns=tbSearchRoot(tb, pindex);
  n=ns.node;
  t=ns.pos;
  b=tbInsert(tb, v, t, n, CTBNULL, CFALSE);
  return(b);
  
}

CBOOL tbInsert(table *tb, clazz *v, long posinnode, node *n1, node *n2, CBOOL pquebra){
  long ipai, isum;
  node *p, *nl1;
	    
  if(n1->leaf==CTRUE){
  	isum=n1->sum;
   	tbNodePutValue(tb,n1,v,posinnode);
  	if(n1->tam==TAMNODE){
  	  nl1 = tbQuebra(n1);
  	  nl1->leaf=CTRUE;
	  p=n1->parent;
	  if(p==CTBNULL){
	  	tb->root=tbCreateNode();
	  	ipai=0;
	  	n1->parent=tb->root;
	  	n1->parentidx=ipai;
	  	nl1->parent=tb->root;
	    nl1->parentidx=ipai+1;
	    tb->root->child=n1;
	    n1->nextnode=nl1;
	    tb->root->sum=n1->sum+nl1->sum;
	    tb->root->tam=2;
	    return(CTRUE);
      }
	  p->sum-=isum;
	  p->sum+=n1->sum;
	  ipai=n1->parentidx;
	  ipai++;
	  tbInsert(tb, CTBNULL,ipai,p,nl1,CTRUE);
	}else{
	  p=n1->parent;
	  if(p==CTBNULL){
	    return(CFALSE);
	  }
	  p->sum++;
	  tbInsert(tb,CTBNULL,0,p,CTBNULL,CFALSE);
    }
  }else{
    if(pquebra==CTRUE){
      tbNodePut(n1,n2,posinnode);
	  if(n1->tam==TAMNODE){
	    nl1 = tbQuebra(n1);
		p=n1->parent;
		if(p==CTBNULL){
		  tb->root=tbCreateNode();
		  ipai=0;
		  n1->parent=tb->root;
		  n1->parentidx=ipai;
		  nl1->parent=tb->root;
		  nl1->parentidx=ipai+1;
		  tb->root->child=n1;
		  n1->nextnode=nl1;
		  tb->root->sum=n1->sum+nl1->sum;
		  tb->root->tam=2;
		  return(CTRUE);
        }
		ipai=n1->parentidx;
		ipai++;
		tbInsert(tb,CTBNULL,ipai,p,nl1,CTRUE);
      }else{
	    p=n1->parent;
	    if(p==CTBNULL){
		  return(CFALSE);
        }
		p->sum++;
		tbInsert(tb,CTBNULL,0,p,CTBNULL,CFALSE);
      }
    }else{
	  p=n1->parent;
	  if(p==CTBNULL){
	    return(CFALSE);
	  }
	  p->sum++;
      tbInsert(tb,CTBNULL,0,p,CTBNULL,CFALSE);
    }
  } 
}

CBOOL tbUpdateRoot(table *tb, clazz *v, long pindex){
  node *n=CTBNULL;
  node_search ns;
  ns=tbSearchRoot(tb, pindex);
  n=ns.node;
  if(n!=CTBNULL){
    n=tbSeek(ns);
    n->value=v;
    return(CTRUE);
  }
  return(CFALSE);
}

CBOOL tbDeleteRoot(table *tb, long k){
  long i;
  node *n=CTBNULL;
  node_search ns;
  ns = tbSearchRoot(tb,k);
  n=ns.node;
  if(n==CTBNULL){
    return(CFALSE);
  }
  i=ns.pos;
  tbDeleteNodeElem(tb, n, i);
  tbDeleteAdjust(tb, n);
  return(CTRUE);
}

CBOOL tbDeleteNodeElem(table *tb, node *n, long pos){
  long i;
  node *nc, *no;
  nc=n->child;
  no=nc;
  for(i=1;i<pos;i++){
    no=nc;
	nc=nc->nextnode;
  }
  if(no!=nc){
	no->nextnode = nc->nextnode;
  }else{
	n->child=no->nextnode;	
  }
  n->tam--;
  tb->count++;
  tb->size--;
}

CBOOL tbDeleteAdjust(table *tb, node *n){
      
  CBOOL b=CFALSE;
  long t=T;
  node *ne,*nd,*np,*nc;
  
  nd=n->nextnode;
  np=n->parent;
  n->sum--;
  
  if(np==CTBNULL){
    if(n->tam==1 && tb->root->leaf == CFALSE){
      tb->root=n->child;
      tb->root->parent = CTBNULL;
    }
	return(CTRUE);
  }
		
  if(n->tam<t){
    nc=np->child;
	ne=CTBNULL;
	while(nc->nextnode!=CTBNULL && nc!=n){ 
	  ne=nc;
	  nc=nc->nextnode;
	}
	if(ne!=CTBNULL){
	  if(ne->tam<=t){
		tbDeleteJoinE(np,ne,n);
	  }else{         
		tbDeleteNorm(np,ne,n);
      }
	  b=CTRUE;
	}
			
	if(nd!=CTBNULL && b==CFALSE){
	  if(nd->tam<=t){ 
	    tbDeleteJoinD(np,nd,n);
	  }else{        
		tbDeleteNorm(np,n,nd);
	  }	
	}
  }
  tbDeleteAdjust(tb, np);
  return(CTRUE);
}
	
CBOOL tbDeleteJoinE(node *np, node *ne, node *n){
  node *ln,*ln1;
  ln=tbDeleteGetLast(ne->child);
  ne->tam+=n->tam;
  ne->sum+=n->sum;
  ne->nextnode=n->nextnode;
  ln1=n->child;
  ln->nextnode=ln1;
  ln1->parent=ne;
  while(ln1->nextnode!=CTBNULL){
    ln1=ln1->nextnode;
    ln1->parent=ne;
  }
  np->tam--;
}

CBOOL tbDeleteJoinD(node *np, node *nd, node *n){
  node *ln,*ln1;
  ln=tbDeleteGetLast(n->child);
  n->tam+=nd->tam;
  n->sum+=nd->sum;
  n->nextnode=nd->nextnode;
  ln1=nd->child;
  ln->nextnode=ln1;
  ln1->parent=n;
  while(ln1->nextnode!=CTBNULL){
    ln1=ln1->nextnode;
    ln1->parent=n;
  }
  np->tam--;
}



CBOOL tbDeleteNorm(node *np, node *ne, node *n){
  long i,t;
  node *nc1, *nc2, *ntp;
  if(ne->tam<n->tam){
    t=n->tam-ne->tam;
    t/=2;
	nc1=ne->child;
	nc2=n->child;
    while(nc1->nextnode!=CTBNULL){
      nc1=nc1->nextnode;
	}
	nc1->nextnode = nc2;
	for(i=0;i<t;i++){
	  nc1=nc1->nextnode;
	  nc1->parent=ne;
	  ne->sum+=nc1->sum;
      n->sum-=nc1->sum;
	  ne->tam++;
	  n->tam--;
	}	
	n->child = nc1->nextnode;
	nc1->nextnode=CTBNULL;
  }else{
    ntp=CTBNULL;
	t=ne->tam-n->tam;
	t/=2;
	nc1=ne->child;
	nc2=n->child;
	long l=ne->tam;
	l-=t;
	
	for(i=0;i<l;i++){
	  ntp=nc1;
	  nc1=nc1->nextnode;
    }
		
	ntp->nextnode=CTBNULL;
	nc1->parent = n;
	n->child = nc1;
	n->tam++;
	ne->tam--;
	n->sum+=nc1->sum;
	ne->sum-=nc1->sum;
	nc1->parent=n;
	
    while(nc1->nextnode!=CTBNULL){
      nc1=nc1->nextnode;
	  n->sum+=nc1->sum;
	  ne->sum-=nc1->sum;
	  n->tam++;
	  ne->tam--;
	  nc1->parent=n;
	}
	
    nc1->nextnode=nc2;
  }
		
}
     
node *tbDeleteGetLast(node *n){
  while(n->nextnode!=CTBNULL){
    n=n->nextnode;
  }
  return(n);
}

CBOOL tbNodePutValue(table *tb, node *n, clazz *v, long pos){
      
  long i;
  node *n1,*nn;
  n1=tbCreateNode();
  n1->value=v;
  n1->sum=1;
  nn=n->child;
  if(nn!=CTBNULL){
    if(pos==0){
	  n->child=n1;
	  n1->nextnode=nn;
	}else{
	  for(i=0;i<pos-1;i++){
	   	nn=nn->nextnode;
	  }
	  n1->nextnode=nn->nextnode;
	  nn->nextnode=n1;
	}
  }else{
    n->child=n1;
  }
  n->tam++;
  n->sum++;
  n1->parentidx=pos;
  n1->parent=n;
  tb->size++;
      
}

CBOOL tbNodePut(node *n1, node *n2, long pos){
  long i;
  node *nn=CTBNULL, *no=CTBNULL;
  nn=n1->child;
  if(nn!=CTBNULL){
    if(pos==0){
	  n1->child=n2;
	  n2->nextnode=nn;
	}else{
	  for(i=0;i<pos-1;i++){
	    no=nn;
	   	nn=nn->nextnode;
      }
	
      no=nn->nextnode;
	  nn->nextnode=n2;
	  n2->nextnode=no;
    }
  }else{
    n1->child=n2;
  }
	   	
  n1->tam++;
  if(n2->leaf==CTRUE){
    n1->sum+=n2->sum;
  }else{
    n1->sum++;
  }
  n2->parent=n1;
  n2->parentidx=pos;
	
}

node *tbQuebra(node *n){
     
  long i,t,z;
  node *n1=CTBNULL,*nn=CTBNULL;
  t=n->tam;

  n->tam=T;
  n1=tbCreateNode();
  n1->tam=n->tam;
  n1->sum=0;
  z=0;

  nn=n->child;
  t=n->tam;
  
  for(i=0;i<TAMNODE;i++){
    if(i==t-1){
	  n1->child=nn->nextnode;
	  nn->nextnode=CTBNULL;
	  nn=n1->child;
	  n1->sum=nn->sum;
	  nn->parent=n1;
	  nn->parentidx=0;
	  z++;
	  continue;
	}else if(i>t){
	  nn->parent=n1;
	  nn->parentidx=z;
	  n1->sum+=nn->sum;
	  z++;
	}
    nn=nn->nextnode;
  }

  t=n->tam;
  n->sum=0;
  nn=n->child;
  for(i=0;i<t;i++){
    n->sum+=nn->sum;
	nn=nn->nextnode;
  }
  
  return(n1);
		
}
         
node *tbCreateNode(){
  node *n=zmalloc(sizeof(node));
  if(n!=CTBNULL){
    n->tam=0;
    n->sum=0;
    n->parentidx=0;
    n->leaf    =CFALSE;
    n->parent  =CTBNULL;
    n->nextnode=CTBNULL;
    n->child   =CTBNULL;
    n->value   =CTBNULL;
    n->pointer =CTBNULL;
  }
  return(n);
}

long tbGetSize(table *tb){
  if(tb!=CTBNULL){
    return(tb->size);
  }
  return(0);
}
