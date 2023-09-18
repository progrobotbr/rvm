
/**** DECLARAÇÃO DAS FUNÇÕES UTILIZADAS ****/

/* Funções utilizadas em loadfile.c */
TCON metaMoveCon(TCT1 pct1, TNM pnm);
TVAR metaMoveVar(int i, TLV1 plv1, TNM pnm);
TFUC metaMoveFunc(TFD1 pfd1, TNM pnm);
CBOOL loadClass(char *s, TCLS **pcls);
char * cps(char **ss, U1 *se, int tam);
char * cps2(char **ss, U1 *se, int tam, ArrayMalloc *pmem);

