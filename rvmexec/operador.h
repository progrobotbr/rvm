
Var (*gAdd[4])(Var *, Var *);
Var (*gSub[4])(Var *, Var *);
Var (*gMul[4])(Var *, Var *);
Var (*gDiv[4])(Var *, Var *);

Var (*gLt[4])(Var *, Var *);
Var (*gLe[4])(Var *, Var *);
Var (*gGt[4])(Var *, Var *);
Var (*gGe[4])(Var *, Var *);
// Igualdade 
Var (*gNe[4])(Var *, Var *);
Var (*gEq[4])(Var *, Var *);

Var loadc(int i);
Var loadv(int i);
void storv(int i, Var rs);
