#include <stdio.h>
#include "zzdata.h"
/*** string ***/
 
BOOL string_isnull( string self ){
     if(self == NIL)
         return(TRUE);
     else
         return(FALSE);
}

string newString(char *c){
       string self;
       self = malloc(sizeof(struct _string));
       self->c = '\0';
       self->tam=0;
       self->mv = &string_mv;
       self->size = &string_size;
       self->isNull = &string_isnull;
       self->cmp = &string_cmp;
       self->concat = &string_concat;
       self->mid = &string_mid;
       self->trim = &string_trim;
       self->asc = &string_asc;
       self->ucase = &string_ucase;
       self->lcase = &string_lcase;
       self->isnum = &string_isnum;
       self->mv(self, c);
       
       return(self);
} 
  
int string_size( string self ){
    int i=0;
    char *c = self->c;
    while(*c!='\0'){
        c++;            
        i++;
    }
    return(i);
}

string string_concat(string self, string other){
       int i=0;
       char *c, *c1, *c2;
       string s=SS("");
       i = self->size(self) + other->size(other);
       c = malloc(sizeof(char)*i+1);
       c1 = self->c;
       c2 = c;
       while(*c1!='\0'){
          *c2 = *c1;
          c1++;
          c2++;
       }
       c1 = other->c;
       while(*c1!='\0'){
          *c2 = *c1;
          c1++;
          c2++;
       }
       *c2 = '\0';
       s = SS(c);             
       return(s);
}

BOOL string_cmp(string self, string other){
     if(strcmp(self->c, other->c)==0){
       return(TRUE);
     }else{
       return(FALSE);
     }
}

void string_mv( string self, char *c ){
     int i=0;
     char *c1,*c2, *c3;
     c3 = c1 = c;
     
     while(*c1!='\0'){
         i++;
         c1++;            
     }
     
     c1 = c2 = malloc(sizeof(char)*i+1);
     
     while(*c3!='\0'){
         *c2 = *c3;
         c2++; 
         c3++;            
     }
     
     *c2 = '\0';
     self->c = c1;
     
     //self->tam = i;
} 

string string_mid( string self, int ini, int len ){
     int i=0,t=0,fim=0;
     char *c, *c1, *c2;
     string s = SS("");
     i = self->size(self);
     fim = ini + len-1;
     if(ini<1 || len < 1){
            return(s); 
     }
     ini--;
     if(ini > fim){
            return(s);
     }
     if((ini+len)>i){
            len = i - ini;          
     }
     if(ini > i || fim > i){
            return(s);
     }
     
     c2 = c1 = malloc(sizeof( char ) * len + 1 );
     c = self->c;
     for(t=ini;t<fim;t++){
        *c2 = c[t];
        c2++;                  
     }
     *c2 = '\0';
     s->c = c1;
     return(s);                     
} 

string string_trim( string self ){
       
     int i,t,ini, len;
     char *c;
     string s = SS("");
     
     i = self->size(self);
     ini=len=0;
     c = self->c;
     
     while(*c!='\0'){
        if(*c!=' '){
          break;
        }
        c++;
        ini++;    
     }
     
     c = self->c;
     if(i==1){
       len = 1;       
     }else{
       for(t=i-1;t>0;t--){
         len =t-ini+1;             
         if(c[t]!=' '){
            break;        
         }
       }
     }
     ini++;
     s = Mid(self, ini, len);
     
     return(s);
    
}  

int string_asc(string self){
    char c;
    int i = self->size(self);
    if(i>0){
        c = self->c[0];
        i = c;
        return(i);    
    }
    return(0);
            
}

string string_ucase(string self){
     char *c;
     char c1;
     int i=0;
     string rstring_ucase = SS(self->c);
     c = rstring_ucase->c;
     while(*c){
        c1 = *c;
        c1=toupper(c1);
        *c = c1;
        c++;
     }
     return(rstring_ucase);
}

string string_lcase(string self){
     char *c;
     char c1;
     int i=0;
     string rstring_lcase = SS(self->c);
     c = rstring_lcase->c;
     while(*c){
        c1 = *c;
        c1=tolower(c1);
        *c = c1;
        c++;
     }
     return(rstring_lcase);
}

BOOL string_isnum(string self){
    
    char *c = self->c;
    int i   = 0;
    int ip  = 0;
    while(c[i]){
       if(c[i]=='.'){
            if(ip==0){
               ip=1;
            }else{
               return(FALSE);   
            }
       }
       if(!(c[i]>=48 && c[i]<=57)){  
          return(FALSE);              
       }
       i++;         
    }
    if(i==0){
       return(FALSE);
    } 
    return(TRUE);
}

string string_int_str(int i){
    char buf[20];
    string rstring_int_str;
    itoa(i, buf, 10);
    rstring_int_str=SS(buf);
    
    return(rstring_int_str);
}

int string_str_int(string s){
    int i = atoi(s->c);
    return(i);
}

char *replace_str2(const char *str, const char *old, const char *new)
{
	char *ret, *r;
	const char *p, *q;
	size_t oldlen = strlen(old);
	size_t count, retlen, newlen = strlen(new);
	int samesize = (oldlen == newlen);

	if (!samesize) {
		for (count = 0, p = str; (q = strstr(p, old)) != NULL; p = q + oldlen)
			count++;
		/* This is undefined if p - str > PTRDIFF_MAX */
		retlen = p - str + strlen(p) + count * (newlen - oldlen);
	} else
		retlen = strlen(str);

	if ((ret = malloc(retlen + 1)) == NULL)
		return NULL;

	r = ret, p = str;
	while (1) {
		/* If the old and new strings are different lengths - in other
		 * words we have already iterated through with strstr above,
		 * and thus we know how many times we need to call it - then we
		 * can avoid the final (potentially lengthy) call to strstr,
		 * which we already know is going to return NULL, by
		 * decrementing and checking count.
		 */
		if (!samesize && !count--)
			break;
		/* Otherwise i.e. when the old and new strings are the same
		 * length, and we don't know how many times to call strstr,
		 * we must check for a NULL return here (we check it in any
		 * event, to avoid further conditions, and because there's
		 * no harm done with the check even when the old and new
		 * strings are different lengths).
		 */
		if ((q = strstr(p, old)) == NULL)
			break;
		/* This is undefined if q - p > PTRDIFF_MAX */
		ptrdiff_t l = q - p;
		memcpy(r, p, l);
		r += l;
		memcpy(r, new, newlen);
		r += newlen;
		p = q + oldlen;
	}
	strcpy(r, p);

	return ret;
}
string string_replace(string s, string f, string v){
    string ss = SS(replace_str2(s->c, f->c, v->c));      
}

/*** Fim String ***/ 
