
 string mTexto;
 int mIdx;
 int mTam;

 mCommand(1 To CQTDCOMAND, 1 To Variant As 2);
 token gToken;
 node gProg;
 int mLinha;
 int gFuncId;

//;
 string g2Lang;
 int g2Line;
 BOOL g2NumeraLinha;
//;

void initParse(p1 As String, bMoveTok As Boolean){

  mTexto = p1;
  mIdx = 1;
  mTam = Len(mTexto);
  mLinha = 1;
  g2Line = 1;
  g2NumeraLinha = False;
  gFuncId = 0;
  mCommand(Tag.CBEG, CNOME).s         = SS("BEG");
  mCommand(Tag.CEND, CNOME).s         = SS("END");
  mCommand(Tag.CIF, CNOME).s          = SS("IF");
  mCommand(Tag.CELSE, CNOME).s        = SS("ELSE");
  mCommand(Tag.CWHILE, CNOME).s       = SS("WHILE");
  mCommand(Tag.CCVAR, CNOME).s        = SS("VARIABLE");
  //mCommand(Tag.CFLOAT, CNOME) = "FLOAT";
  mCommand(Tag.CDEF, CNOME).s         = SS("DEF");
  mCommand(Tag.CRETURN, CNOME).s      = SS("RETURN");
  mCommand(Tag.CCBREAK, CNOME).s      = SS("BREAK");
  mCommand(Tag.CCDECLCHAR, CNOME).s   = SS("CHAR");
  mCommand(Tag.CCDECLINT, CNOME).s    = SS("INT");
  mCommand(Tag.CCDECLFLOAT, CNOME).s  = SS("FLOAT");
  mCommand(Tag.CCDECLOBJ, CNOME).s    = SS("OBJECT");
  mCommand(Tag.CCLASS, CNOME).s       = SS("CLASS");
  mCommand(Tag.CNEW, CNOME).s         = SS("NEW");
  mCommand(Tag.CNEWARRAY, CNOME).s    = SS("NEWARRAY");
  mCommand(Tag.CENDCLASS, CNOME).s    = SS("ENDCLASS");
  mCommand(Tag.CENDDEF, CNOME).s      = SS("ENDDEF");
  mCommand(Tag.CENDIF, CNOME).s       = SS("ENDIF");
  mCommand(Tag.CENDWHILE, CNOME).s    = SS("ENDWHILE");
  mCommand(Tag.CDEFNATIVE, CNOME).s   = SS("DEFNATIVE");
  
  mCommand(Tag.CTBDECLTB, CNOME).s    = SS("TABLE");
  mCommand(Tag.CTBDECLWA, CNOME).s    = SS("WORKAREA");
  mCommand(Tag.CTO, CNOME).s          = SS("TO");
  mCommand(Tag.CFROM, CNOME).s        = SS("FROM");
  mCommand(Tag.CIN, CNOME).s          = SS("IN");
  mCommand(Tag.CINTO, CNOME).s        = SS("INTO");
  
  mCommand(Tag.CLOOP, CNOME).s        = SS("LOOP");
  mCommand(Tag.CREAD, CNOME).s        = SS("READ");
  mCommand(Tag.CAPPEND, CNOME).s      = SS("APPEND");
  mCommand(Tag.CMODIFY, CNOME).s      = SS("MODIFY");
  mCommand(Tag.CINSERT, CNOME).s      = SS("INSERT");
  mCommand(Tag.CDELETE, CNOME).s      = SS("DELETE");
  mCommand(Tag.CINDEX, CNOME).s       = SS("INDEX");

  mCommand(Tag.CBEG, CNUMFILHOS).i    = 1;
  mCommand(Tag.CEND, CNUMFILHOS).i    = 0;
  mCommand(Tag.CIF, CNUMFILHOS).i     = 2;
  mCommand(Tag.CELSE, CNUMFILHOS).i   = 3;
  mCommand(Tag.CWHILE, CNUMFILHOS).i  = 2;
  mCommand(Tag.CCVAR, CNUMFILHOS).i   = 0;
  mCommand(Tag.CFLOAT, CNUMFILHOS).i  = 0;
  mCommand(Tag.CDEF, CNUMFILHOS).i    = 3;
  mCommand(Tag.CRETURN, CNUMFILHOS).i = 1;
  mCommand(Tag.CCBREAK, CNUMFILHOS).i = 1;
  mCommand(Tag.CCDECLCHAR, CNUMFILHOS).i = 1;
  mCommand(Tag.CCDECLINT, CNUMFILHOS).i  = 1;
  mCommand(Tag.CCDECLFLOAT, CNUMFILHOS).i = 1;
  mCommand(Tag.CCDECLOBJ, CNUMFILHOS).i   = 1;
     
  if( bMoveTok == TRUE ){
     moveToken();
  }
  
}

  Parse() As String{

   String As s;
   Integer As iId;
  
   putFunc("_globals_", 0, "", False, False);
  
  Set gProg = Class();
  s = emit2Lang2(gProg) //lógica 2;
  
  //s = emit2Lang2(gProg);
  //iId = getId("__main__", CFUNCAO);
  //Call putAssembly(iId, s);
  Parse = s;
  
}

 createNode(p1 As Token) As Node{
   Integer As i;
  Set createNode = New Node;
  i = mCommand(p1.tipo, 2);
  if( i > 0 ){
     createNode.initFilhos(i);
  }
  createNode.valor = p1.valor;
  createNode.tipo = p1.tipo;
  createNode.linha = gToken.linha;
}

 createNode1(p1 As Integer) As Node{
  //p1 - número de filhos;
  Set createNode1 = New Node;
  if( p1 > 0 ){
     createNode1.initFilhos(p1);
  }else{
    createNode1.qtdFilhos = p1;
  }
}

  getToken() As Token{
   
    Integer As i;
    c As String * 1;
    c1 As String * 1;
    c2 As String * 1;
    String As sToken;
    Integer As countPoint;
   
   c = " "     //Caracter atual;
   c2 = " "    //Caracter à frente;
   sToken = "" //Forma palavra;
   
   Set getToken = New Token;
 
   
    while( mIdx <= mTam;
   
     //;
     // Limpa Comentários, sintaxe:;
     //  --comentário 1;
     //  --comentário 3;
     //;
     c = Mid(mTexto, mIdx, 1);
   
     //;
     // Limpa Caracteres Especiais (Enter, Espaço);
     //;
     if( c != " " && Asc(c) != 13 && Asc(c) != 10 ){
       //;
       // Comentários;
       //;
       if( c = "-" ){
         c1 = Mid(mTexto, mIdx + 1, 1);
         if( c1 = "-" ){
           mIdx = mIdx + 1;
            while( Asc(c) != 13 || mIdx = mTam;
             mIdx = mIdx + 1;
             c = Mid(mTexto, mIdx, 1);
           }
         }else{
           break;
         }
       }else{
         break;
       }
     }
     
     if( Asc(c) = 13 ){
       mLinha = mLinha + 1;
     }
     
     mIdx = mIdx + 1;
     
   }
   
   //;
   // Verifica se é Fim de Programa;
   //;
   if( mIdx > mTam ){
     getToken.tipo = Tag.CENDPROGRAM;
     getToken.valor = "ENDOFPROGRAM";
     return({
   }
   
   getToken.linha = mLinha;
   
   //;
   // Pega número: 435 34,45;
   //;
   if( isNumber(c) ){
     countPoint = 0;
      while( mIdx <= mTam;
       sToken = sToken & c;
       mIdx = mIdx + 1;
       c = Mid(mTexto, mIdx, 1);
       if( Not isNumberFloat(c, countPoint) ){
         break;
       }
     }
     getToken.valor = sToken;
     if( countPoint > 0 ){
       getToken.tipo = Tag.CFLOAT;
     }else{
       if( countPoint > 1 ){
         getToken.erro = "E";
       }else{
         getToken.tipo = Tag.CINTEGER;
       }
     }
     return({
   }
   
   //;
   // Pega palavras: if, else, while, var01 ...;
   //;
   if( isLetter(c) ){
      while( mIdx <= mTam;
       sToken = sToken & c;
       mIdx = mIdx + 1;
       c = Mid(mTexto, mIdx, 1);
       if( Not isLetter(c) && Not isNumber(c) ){
         break;
       }
     }
     sToken = UCase(sToken);
     i = isCommand(sToken);
     getToken.valor = sToken;
     if( i > 0 ){
       getToken.tipo = i;
     }else{
        while( mIdx <= mTam;
         c = Mid(mTexto, mIdx, 1);
         if( c != " " ){
           break;
         }
         mIdx = mIdx + 1;
       }
       if( c = "(" ){
         getToken.tipo = Tag.CFUNC;
       } else if( c = "[" ){
         getToken.tipo = Tag.CARRAY;
       }else{
         getToken.tipo = Tag.CCVAR;
       }
     }
     return({
   }
   
   //;
   // Verifica carateres especiais;
   //;
   c1 = Mid(mTexto, mIdx + 1, 1);
   Select Case c;
     Case "<" //Menor igual (<=);
       if( c1 = "=" ){
         mIdx = mIdx + 2;
         getToken.tipo = Tag.CLE;
         getToken.valor = c & c1;
       }else{
         mIdx = mIdx + 1;
         getToken.tipo = Tag.CLT;
         getToken.valor = c;
       }
       return({
     Case ">" //Maior igual (>=);
       if( c1 = "=" ){
         mIdx = mIdx + 2;
         getToken.tipo = Tag.CGE;
         getToken.valor = c & c1;
       }else{
         mIdx = mIdx + 1;
         getToken.tipo = Tag.CGT;
         getToken.valor = c;
       }
       return({
     Case "=" //Igualdade (==);
       if( c1 = "=" ){
         mIdx = mIdx + 2;
         getToken.tipo = Tag.CEQ;
         getToken.valor = c & c1;
         return({
       }
     Case "&" //And (&&);
       if( c1 = "&" ){
         mIdx = mIdx + 2;
         getToken.tipo = Tag.CEQ;
         getToken.valor = c & c1;
         return({
       }
     Case "|" //Or (||);
       if( c1 = "|" ){
         mIdx = mIdx + 2;
         getToken.tipo = Tag.COR;
         getToken.valor = c & c1;
         return({
       }
     Case "(";
       getToken.tipo = Tag.CPAROPEN;
       getToken.valor = c;
       mIdx = mIdx + 1;
       return({
     Case ")";
       getToken.tipo = Tag.CPARCLOS;
       getToken.valor = c;
       mIdx = mIdx + 1;
       return({
     Case Chr(34);
       sToken = "";
       mIdx = mIdx + 1;
       c = Mid(mTexto, mIdx, 1);
        while( c != Chr(13) && c != Chr(34) && mIdx < mTam;
         sToken = sToken & c;
         mIdx = mIdx + 1;
         c = Mid(mTexto, mIdx, 1);
       }
       if( c = Chr(34) ){
         mIdx = mIdx + 1;
       }
       
       getToken.tipo = Tag.CSTRING;
       getToken.valor = sToken;
       return({
   EndSelect;
   
   //;
   // Caracteres Especiais;
   //;
   mIdx = mIdx + 1;
   getToken.tipo = Tag.CCARESP;
   getToken.valor = c;
   
}

//----------- Funcoes Auxiliares ---------------;
  isNumber(c As String) As Boolean{
  isNumber = IsNumeric(c);
}

  isNumberFloat(c As String, ByRef p1 As Integer) As Boolean{
  isNumberFloat = False;
  if( c = "." ){
    isNumberFloat = True;
    p1 = p1 + 1;
  }else{
    isNumberFloat = IsNumeric(c);
  }
}

  isLetter(c As String) As Boolean{
   Integer As i;
  i = Asc(c);
  if( (i >= 65 && i <= 90) || (i >= 97 && i <= 122) ){
    isLetter = True;
  }else{
    isLetter = False;
  }
}

  isCommand(p1 As String) As Integer{
   Integer As i;
  isCommand = 0;
  
  for( i = 1 To CQTDCOMAND;
    if( UCase(p1) = mCommand(i, 1) ){
      isCommand = i;
      return({
    }
  Next;
}

void moveToken(){
  Set gToken = getToken();
}

//------ Funcoes da Linguagem -------------;
 tg(p1 As Integer) As String{
  tg = mCommand(p1, 1) //Retorna string representando um comando da linguage: WHILE IF ...;
}

 matchToken(p1 As String) As Boolean{
   String As sMsg;
  //sNome = gToken.Valor;
  matchToken = False;
  if( gToken.valor = p1 ){
    matchToken = True;
     moveToken;
  }else{
    sMsg = "Anterior a: " & gToken.valor & " - Linha: " & gToken.linha;
     Err.Raise(vbObjectError + 513, "Compilador", sMsg);
  }
}

 matchTokenMsg(p1 As String, pErr As String) As Boolean{
   String As sMsg;
  //sNome = gToken.Valor;
  matchTokenMsg = False;
  if( gToken.valor = p1 ){
    matchTokenMsg = True;
     moveToken;
  }else{
    sMsg = "Err_linha:" & gToken.linha & " - " & pErr;
     Err.Raise(vbObjectError + 513, "Compilador", sMsg);
  }
}

 matchTokenWMoveMsg(p1 As String, pErr As String) As Boolean{
   String As sMsg;
  //sNome = gToken.Valor;
  matchTokenWMoveMsg = False;
  if( gToken.valor = p1 ){
    matchTokenWMoveMsg = True;
  }else{
    sMsg = "Err_linha:" & gToken.linha & " - " & pErr;
     Err.Raise(vbObjectError + 513, "Compilador", sMsg);
  }
}

 matchTokenType(p1 As Integer) As Boolean{
   String As sMsg;
  sNome = gToken.valor;
  matchTokenType = False;
  if( gToken.tipo = p1 ){
    matchTokenType = True;
     moveToken;
  }else{
    sMsg = "Anterior a: " & gToken.valor & " - Linha: " & gToken.linha;
     Err.Raise(vbObjectError + 513, "Compilador", sMsg);
  }
}

 matchTokenTypeMsg(p1 As Integer, pErr As String) As Boolean{
   String As sMsg;
  //sNome = gToken.Valor;
  matchTokenTypeMsg = False;
  if( gToken.tipo = p1 ){
    matchTokenTypeMsg = True;
     moveToken;
  }else{
    sMsg = "Err_linha:" & gToken.linha & " - " & pErr;
     Err.Raise(vbObjectError + 513, "Compilador", sMsg);
  }
}

 matchTokenTypeWMoveMsg(p1 As Integer, pErr As String) As Boolean{
   String As sMsg;
  //sNome = gToken.Valor;
  matchTokenTypeWMoveMsg = False;
  if( gToken.tipo = p1 ){
    matchTokenTypeWMoveMsg = True;
    //Call moveToken;
  }else{
    sMsg = "Err_linha:" & gToken.linha & " - " & pErr;
     Err.Raise(vbObjectError + 513, "Compilador", sMsg);
  }
}

 Class() As Object{
   String As sNome;
   Object As objNode;
  
  Set Class = createNode1(1);
  
   matchTokenMsg("CLASS", "esperado comando CLASS");
  sNome = gToken.valor;
   putNomeClass(sNome);
   putConst(sNome, Tag.CCLASS);
   matchTokenTypeMsg(Tag.CCVAR, "esperado nome da classe");
   matchTokenMsg("BEG", "esperado comando BEG em início de Classe");
  Set objNode = ClassBody();
   Class.putFilho(1, objNode);
  Class.tipo = Tag.CCLASS;
  Class.valor = sNome;
   matchTokenMsg("ENDCLASS", "esperado comando ENDCLASS no fim da definição da Classe");
  
}

 ClassBody() As Object{

    Boolean As bDecl;
    Object As objNode;
   
   Set ClassBody = createNode1(2);
   Set objNode = Decl();
   
   if( Not objNode Is Nothing ){
      ClassBody.putFilho(1, objNode);
     Set objNode = ClassBody()           //Recursão;
      ClassBody.putFilho(2, objNode);
     ClassBody.tipo = Tag.CCLASSBODY;
     ClassBody.valor = "CLASSBODY";
   }else{
            
     if( gToken.tipo = Tag.CDEF ){
       Set objNode = Def(False);
     } else if( gToken.tipo = Tag.CDEFNATIVE ){
       Set objNode = Def(True);
     }else{
       assert gToken.tipo = Tag.CENDCLASS,             "elemento não identificado: " & gToken.valor;
       Set ClassBody = Nothing;
       return({
     }
     
     if( Not objNode Is Nothing ){
        ClassBody.putFilho(1, objNode);
       Set objNode = ClassBody()         //Recursão;
        ClassBody.putFilho(2, objNode);
       ClassBody.tipo = Tag.CCLASSBODY;
       ClassBody.valor = "CLASSBODY";
     }else{
       Set ClassBody = Nothing;
     }
   }
   
}

 Def(pbIsNative As Boolean) As Object{
   Boolean As bHasType;
   Boolean As bIsArray;
   Integer As i;
   Integer As iTipo;
   String As sNomeObj;
   String As Name;
   Object As s;
   Object As b;
  Set Def = Nothing;
  
  bHasType = False;
  bIsArray = False;
  sNomeObj = "";
  iTipo = -1;
  if( gToken.tipo = Tag.CDEF ||      gToken.tipo = Tag.CDEFNATIVE ){
    
     moveToken;
    
    if( gToken.tipo = Tag.CCDECLCHAR ){
      iTipo = Tag.CCHAR1;
      bHasType = True;
      moveToken;
      if( gToken.valor = "[" ){
        moveToken;
         matchTokenMsg("]", "esperado ] para fechar array");
        bIsArray = True;
      }
    } else if( gToken.tipo = Tag.CCDECLINT ){
      iTipo = Tag.CINTEGER;
      bHasType = True;
      moveToken;
      if( gToken.valor = "[" ){
        moveToken;
         matchTokenMsg("]", "esperado ] para fechar array");
        bIsArray = True;
      }
    } else if( gToken.tipo = Tag.CCDECLFLOAT ){
      iTipo = Tag.CFLOAT;
      bHasType = True;
      moveToken;
      if( gToken.valor = "[" ){
        moveToken;
         matchTokenMsg("]", "esperado ] para fechar array");
        bIsArray = True;
      }
    } else if( gToken.tipo = Tag.CCDECLOBJ ){
      iTipo = Tag.COBJ;
      bHasType = True;
      moveToken;
       matchTokenMsg("(", "esperado ( na declaração de objeto");
       matchTokenTypeWMoveMsg(Tag.CCVAR, "esperado o do objeto de referência");
      sNomeObj = gToken.valor;
      moveToken;
       matchTokenMsg(")", "esperado ) na declaração de objeto");
      if( gToken.valor = "[" ){
        moveToken;
         matchTokenMsg("]", "esperado ] para fechar array");
        bIsArray = True;
      }
    }
    
     matchTokenTypeWMoveMsg(Tag.CFUNC, "esperado o Nome na definição da função");
    Name = gToken.valor;
     validFuncMsg2(Name, "não é possível a redeclaração da função: " & Name);
    gFuncId = putFunc(Name, iTipo, sNomeObj, bIsArray, pbIsNative) //número da função;
     putConst(Name, Tag.CFUNC);
     moveToken;
     matchTokenMsg("(", "esperado ( na definicação da função");
    Set s = pegaParDef(True);
     matchTokenMsg(")", "esperado ) na definição da função");
    if( pbIsNative = True ){
      Set b = Nothing;
      Set Def = wordDef(i, Name, s, b);
      Def.tipo = Tag.CDEFNATIVE;
    }else{
       matchTokenMsg(tg(Tag.CBEG), "esperado comando BEG na definição da função " & Name);
      Set b = Stmts() //comandos;
      
       validFuncReturnOk(gFuncId, Name, bHasType, iTipo, sNomeObj, bIsArray);
      
       matchTokenMsg("ENDDEF", "esperado comando ENDDEF na definição da função " & Name);
      
      Set Def = wordDef(i, Name, s, b);
      Def.tipo = Tag.CDEF;
    }
           
    Def.validtipo = iTipo;
    Def.validnomeobj = sNomeObj;
    
    gFuncId = 0 //Zero atua como um boolean;
    
  }
}

 Decl() As Object{
   Integer As i;
  if( gToken.tipo = Tag.CCDECLCHAR ||      gToken.tipo = Tag.CCDECLINT ||      gToken.tipo = Tag.CCDECLFLOAT ||      gToken.tipo = Tag.CCDECLOBJ ){
      i = gToken.linha;
    gFuncId = GLOBALS;
    Set Decl = wordDecl(i);
    Decl.tipo = Tag.CDECLVAR;
    Decl.valor = "DECLVAR";
    Decl.isAttribute = True;
  }else{
    Set Decl = Nothing;
  }
}

 Stmts() As Object{
  //Else é um statement contido em IF;
  if( gToken.tipo = Tag.CENDCLASS ||      gToken.tipo = Tag.CENDDEF ||      gToken.tipo = Tag.CENDIF ||      gToken.tipo = Tag.CENDWHILE ||      gToken.tipo = Tag.CELSE ||      gToken.tipo = Tag.CENDPROGRAM ){
    Set Stmts = Nothing;
  }else{
    Set Stmts = Seq(Stmt(), Stmts())    //Cria deep nodes, como uma escada;
    Stmts.valor = "STMTS";
    Stmts.tipo = Tag.CCOMMAND;
  }
}

 Seq(p1 As Object, p2 As Object) As Object{
  if( p1 Is Nothing && p2 Is Nothing ){
    Set Seq = createNode1(0);
    return({
  }
  if( Not p2 Is Nothing ){
    Set Seq = createNode1(2);
     Seq.putFilho(1, p1);
     Seq.putFilho(2, p2);
  }else{
    Set Seq = createNode1(1);
     Seq.putFilho(1, p1);
  }
  //Seq.Valor = "SEQ";
  //Seq.Tipo = Tag.CSEQ;
  Seq.linha = gToken.linha;
}

 wordIf(p0 As Integer, p1 As Object, p2 As Object) As Object{
  Set wordIf = createNode1(2);
   wordIf.putFilho(1, p1);
   wordIf.putFilho(2, p2);
  wordIf.valor = "IF";
  wordIf.tipo = Tag.CIF;
  wordIf.linha = p0;
}

 wordElse(p0 As Integer, p1 As Object, p2 As Object, p3 As Object) As Object{
  Set wordElse = createNode1(3);
   wordElse.putFilho(1, p1);
   wordElse.putFilho(2, p2);
   wordElse.putFilho(3, p3);
  wordElse.valor = "IFELSE";
  wordElse.tipo = Tag.CELSE;
  wordElse.linha = p0;
}

 wordWhile(p0 As Integer, p1 As Object, p2 As Object) As Object{
  Set wordWhile = createNode1(2);
   wordWhile.putFilho(1, p1);
   wordWhile.putFilho(2, p2);
  wordWhile.valor = "WHILE";
  wordWhile.tipo = Tag.CWHILE;
  wordWhile.linha = p0;
}

 wordFunc(p0 As Integer, p1 As String, p2 As Object) As Object{
  Set wordFunc = createNode1(1);
   wordFunc.putFilho(1, p2);
  wordFunc.valor = p1;
  wordFunc.tipo = Tag.CFUNC;
  wordFunc.linha = p0;
}

 wordDef(p0 As Integer, p1 As String, p2 As Object, p3 As Object) As Object{
  Set wordDef = createNode1(2);
   wordDef.putFilho(1, p2);
   wordDef.putFilho(2, p3);
  wordDef.valor = p1;
  wordDef.tipo = Tag.CDEF;
  wordDef.linha = p0;
}

 wordReturn(p0 As Integer, p1 As Object) As Object{
  Set wordReturn = createNode1(1);
   wordReturn.putFilho(1, p1);
  wordReturn.valor = "RETURN";
  wordReturn.tipo = Tag.CRETURN;
  wordReturn.linha = p0;
}

 wordBreak(p0 As Integer) As Object{
  Set wordBreak = createNode1(0);
  wordBreak.valor = "BREAK";
  wordBreak.tipo = Tag.CCBREAK;
  wordBreak.linha = p0;
}

 wordDecl(p0 As Integer) As Object{
   Boolean As b;
   Boolean As bClass;
   Boolean As bIsArray;
   Integer As i;
   Integer As iTamArray;
   String As sNomeClass;
   String As sValor;
   Node As oNode;
  
  sNomeClass = "";
  bClass = False;
  bIsArray = False;
  Set wordDecl = createNode1(1);
  wordDecl.linha = p0;
  wordDecl.tipo = gToken.tipo;
  
  moveToken;
  
  Set oNode = createNode1(0);
  
  Select Case wordDecl.tipo;
    Case Tag.CCDECLCHAR;
      i = Tag.CCHAR1;
    Case Tag.CCDECLINT;
      i = Tag.CINTEGER;
    Case Tag.CCDECLFLOAT;
      i = Tag.CFLOAT;
    Case Tag.CCDECLOBJ;
      bClass = True;
      i = Tag.COBJ;
       matchTokenMsg("(", "esperado ( em declaração de Objeto");
      sNomeClass = gToken.valor;
      //Carrega a classe;
      b = ReadClass(gToken.valor);
       assert(b = True, "classe não encontrada " & gToken.valor);
       matchTokenTypeMsg(Tag.CCVAR, "esperado nome do objeto na tipificação");
       matchTokenMsg(")", "esperado ) em declaração de Objeto");
    Case Tag.CTBDECLTB || Tag.CTBDECLWA;
      //;
      //colocada esta lógica aqui, pois tabela não pode ser tipo array;
      //;
      if( wordDecl.tipo = Tag.CTBDECLTB ){
        i = Tag.CTBTABLE;
      }else{
        i = Tag.CTBWA;
      }
      
       matchTokenMsg("(", "esperado ( em declaração de tabela ou workarea");
      sNomeClass = gToken.valor;
      b = ReadClass(gToken.valor);
       assert(b = True, "classe de referencia para tabela/workarea não encontrada " & gToken.valor);
       matchTokenTypeMsg(Tag.CCVAR, "esperado nome do objeto na tipificação");
       matchTokenMsg(")", "esperado ) em declaração de Objeto");
      
      oNode.valor = gToken.valor;
      oNode.tipo = i;
       matchTokenTypeMsg(Tag.CCVAR, "Esperado nome do elemento (tabela ou workarea)");
       validVarMsg(oNode.valor, "Não é possível redeclarar variável " + oNode.valor);
       wordDecl.putFilho(1, oNode);
      wordDecl.id = putVarFunc(gFuncId, CTIPOVAR, oNode.valor, oNode.tipo, bIsArray, iTamArray, sNomeClass);
      
      return({
      
  EndSelect;
  
  if( gToken.tipo = Tag.CCVAR ){
    oNode.valor = gToken.valor;
    moveToken;
  } else if( gToken.tipo = Tag.CARRAY ){
    oNode.valor = gToken.valor;
    moveToken;
     matchTokenMsg("[", "esperado [ em declaração de array");
    //sValor = gToken.valor;
    //Call matchTokenTypeMsg(Tag.CINTEGER, "esperado inteiro em quantidade na definição do array");
    //bIsArray = True;
    //iTamArray = CInt(sValor);
     matchTokenMsg("]", "esperado ] em declaração de array");
    bIsArray = True;
    iTamArray = 0;
  }else{
    //;
    // aqui dará erro, somente para emitir a mensagem;
    //;
     assert(gToken.tipo = Tag.CCVAR, "Esperado nome do elemento");
  }
  
   validVarMsg(oNode.valor, "Não é possível redeclarar variável " + oNode.valor);
  
  oNode.tipo = i;
   wordDecl.putFilho(1, oNode);
      
  wordDecl.id = putVarFunc(gFuncId, CTIPOVAR, oNode.valor, oNode.tipo, bIsArray, iTamArray, sNomeClass);
  
}

 Stmt() As Object{
    String As sMsg;
    String As sTokenValor;
    String As sPart1;
    String As sPart2;
    Integer As iTokenTipo;
    Node As b;
    Node As s;
    Node As t;
    Integer As i;
    ElemAssign As tAgn;
   
   sMsg = "";
   i = gToken.linha;
   if( i = 23 ){
     i = 23;
   }
   Select Case gToken.tipo;
     Case Tag.CIF;
        matchToken(tg(Tag.CIF));
        matchTokenMsg("(", "esperado ( no comando IF");
       Set b = Bool(False);
        matchTokenMsg(")", "esperado ) no comando IF");
        matchTokenMsg("BEG", "esperado comando BEG no comando IF");
       Set s = Stmts();
       if( gToken.tipo != Tag.CELSE ){
         Set Stmt = wordIf(i, b, s);
       }else{
          matchToken(tg(Tag.CELSE));
         Set t = Stmts();
         Set Stmt = wordElse(i, b, s, t);
       }
        matchTokenMsg("ENDIF", "esperado comando ENDIF no comando ELSE");
       
     Case Tag.CWHILE;
        matchToken(tg(Tag.CWHILE));
        matchTokenMsg("(", "esperado ( no comando WHILE");
       Set b = Bool(False);
        matchTokenMsg(")", "esperado ) no comando WHILE");
        matchTokenMsg("BEG", "esperado comando BEG no comando ELSE");
       Set s = Stmts();
       Set Stmt = wordWhile(i, b, s);
        matchTokenMsg("ENDWHILE", "esperado comando ENWHILE no comando ELSE");
     Case Tag.CFUNC;
       sTokenValor = gToken.valor      //Pega o nome da função - calc(p1,p2);
       Set Stmt = callFunction(sTokenValor, iTokenTipo) //chama funções locais{
     
     Case Tag.CRETURN;
        moveToken;
        matchTokenMsg("(", "esperado ( em RETURN");
       if( gToken.valor != ")" ){
         Set b = Bool(False);
       }else{
         Set b = Nothing;
       }
        matchTokenMsg(")", "esperado ) em RETURN");
        putReturnOk(gFuncId, b);
       Set Stmt = wordReturn(i, b);
       
     Case Tag.CCBREAK;
       Set Stmt = wordBreak(i);
        moveToken;
       
     Case Tag.CCDECLCHAR, Tag.CCDECLINT,           Tag.CCDECLFLOAT, Tag.CCDECLOBJ,           Tag.CTBDECLTB, Tag.CTBDECLWA;
       Set Stmt = wordDecl(i);
       
     Case Tag.CCVAR, Tag.CARRAY;
       tAgn = assignGetLdEsq();
       
       if( tAgn.funcObj = "" ){
           matchTokenMsg("=", "esperado o carater = de atribuição");
       }
       
       Set Stmt = assignGetLdDir(tAgn);
       
     //Tabelas;
     Case Tag.CTBAPPEND;
       Set Stmt = tbAppend();
       
     Case Tag.CTBINSERT;
       Set Stmt = tbInsert();
       
     Case Tag.CTBDELETE;
       Set Stmt = tbDelete();
       
     Case Tag.CTBMODIFY;
       Set Stmt = tbModify();
       
     Case Tag.CTBREAD;
       Set Stmt = tbRead();
       
     Case Tag.CTBLOOP;
       Set Stmt = tbLoop();
     
     Case }else{
       sMsg = "linha :" & gToken.linha & "-" & "elemento não reconhecido: " & gToken.valor;
        Err.Raise(vbObjectError + 513, "Compilador", sMsg);
  
  EndSelect;

}

//;
// Funções de Tabela;
//;
//append wa to tb;
  tbAppend() As Object{
   Boolean As b;
   Integer As t1;
   Integer As t2;
   String As s1;
   String As s2;
   Node As oNode;
   Node As oNodeTb;
   Node As oNodeWa;
  Set oNode = createNode(2);
  
  oNode.tipo = Tag.CTBAPPEND;
  moveToken;
   matchTokenTypeWMoveMsg(Tag.CCVAR, "Esperado nome do elemento: " & gToken.valor);
  s1 = gToken.valor;
  b = validIsWorkArea(s1, t1);
   assert(b = True, "A variável deve ser do tipo workarea: " & s);
   matchToken("TO");
   matchTokenTypeWMoveMsg(Tag.CCVAR, "Esperado nome do elemento: " & gToken.valor);
  s2 = gToken.valor;
  b = validIsTable(s2, t2);
   assert(b = True, "A variável deve ser do tipo tabela: " & s);
   assert(t1 = t2, "A workarea " & s1 & " deve ser do mesmo tipo da tabela " & s2 & " :" & t1 & " " & t2);
  
  moveToken;
  
  Set oNodeTb = createNode1(0);
  Set oNodeWa = createNode1(0);
  oNodeWa.valor = s1;
  oNodeWa.validnomeobj = t1;
  oNodeTb.valor = s2;
  oNodeTb.validnomeobj = t2;
  
   oNode.putFilho(1, oNodeWa);
   oNode.putFilho(2, oNodeTb);
  
  Set tbAppend = oNode;
  
}

//;
//insert wa in tb index n;
//;
  tbInsert() As Object{
   Boolean As b;
   Integer As t1;
   Integer As t2;
   Integer As iDx;
   String As s1;
   String As s2;
   Node As oNode;
   Node As oNodeTb;
   Node As oNodeWa;
   Node As oNodeIdx;
  
  Set oNode = createNode(3);
  oNode.tipo = Tag.CTBINSERT;
  
  moveToken;
  
   matchTokenTypeWMoveMsg(Tag.CCVAR, "Esperado nome do elemento: " & gToken.valor);
  s1 = gToken.valor;
  b = validIsWorkArea(s1, t1);
   assert(b = True, "A variável deve ser do tipo workarea: " & s);
   matchToken("IN");
   matchTokenTypeWMoveMsg(Tag.CCVAR, "Esperado nome do elemento: " & gToken.valor);
  s2 = gToken.valor;
  b = validIsTable(s2, t2);
   assert(b = True, "A variável deve ser do tipo tabela: " & s);
   assert(t1 = t2, "A workarea " & s1 & " deve ser do mesmo tipo da tabela " & s2 & " :" & t1 & " " & t2);
   matchToken("INDEX");
   matchTokenTypeWMoveMsg(Tag.CINTEGER, "Esperado inteiro para indice");
  
  
  Set oNodeTb = createNode1(0);
  Set oNodeWa = createNode1(0);
  Set oNodeIdx = createNode1(0);
  oNodeWa.valor = s1;
  oNodeWa.validnomeobj = t1;
  oNodeTb.valor = s2;
  oNodeTb.validnomeobj = t2;
  oNodeIdx.valor = gToken.valor;
  
  moveToken;
  
   oNode.putFilho(1, oNodeWa);
   oNode.putFilho(2, oNodeTb);
   oNode.putFilho(3, oNodeIdx);
  
  Set tbInsert = oNode;
}

//;
//delete tb index n;
//;
  tbDelete() As Object{
   Boolean As b;
   Integer As t1;
   Integer As t2;
   Integer As iDx;
   String As s1;
   String As s2;
   Node As oNode;
   Node As oNodeTb;
   Node As oNodeIdx;
  
  Set oNode = createNode(2);
  oNode.tipo = Tag.CTBDELETE;
  
  moveToken;
  
   matchTokenTypeWMoveMsg(Tag.CCVAR, "Esperado nome do elemento: " & gToken.valor);
  s1 = gToken.valor;
  b = validIsTable(s1, t1);
   assert(b = True, "A variável deve ser do tipo workarea: " & s);
   matchToken("INDEX");
   matchTokenTypeWMoveMsg(Tag.CINTEGER, "Esperado inteiro para indice");
  
  Set oNodeTb = createNode1(0);
  Set oNodeIdx = createNode1(0);
  oNodeTb.valor = s1;
  oNodeTb.validnomeobj = t2;
  oNodeIdx.valor = gToken.valor;
  
  moveToken;
  
   oNode.putFilho(2, oNodeTb);
   oNode.putFilho(3, oNodeIdx);
  
  Set tbDelete = oNode;
}

//;
//modify tb from wa index n;
//;
  tbModify() As Object{
   Boolean As b;
   Integer As t1;
   Integer As t2;
   Integer As iDx;
   String As s1;
   String As s2;
   Node As oNode;
   Node As oNodeTb;
   Node As oNodeWa;
   Node As oNodeIdx;
  
  Set oNode = createNode(3);
  oNode.tipo = Tag.CTBMODIFY;
  
  moveToken;
  
   matchTokenTypeWMoveMsg(Tag.CCVAR, "Esperado nome do elemento: " & gToken.valor);
  s1 = gToken.valor;
  b = validIsTable(s1, t1);
   assert(b = True, "A variável deve ser do tipo tabela: " & s1);
   matchToken("FROM");
   matchTokenTypeWMoveMsg(Tag.CCVAR, "Esperado nome do elemento: " & gToken.valor);
  s2 = gToken.valor;
  b = validIsWorkArea(s2, t2);
   assert(b = True, "A variável deve ser do tipo workarea: " & s2);
   assert(t1 = t2, "A workarea " & s2 & " deve ser do mesmo tipo da tabela " & s2 & " :" & t1 & " " & t1);
   matchToken("INDEX");
   matchTokenTypeWMoveMsg(Tag.CINTEGER, "Esperado inteiro para indice");
  
  Set oNodeTb = createNode1(0);
  Set oNodeWa = createNode1(0);
  Set oNodeIdx = createNode1(0);
  oNodeWa.valor = s1;
  oNodeWa.validnomeobj = t1;
  oNodeTb.valor = s2;
  oNodeTb.validnomeobj = t2;
  oNodeIdx.valor = gToken.valor;
  
  moveToken;
  
   oNode.putFilho(1, oNodeWa);
   oNode.putFilho(2, oNodeTb);
   oNode.putFilho(3, oNodeIdx);
  
  Set tbModify = oNode;
}

//;
//read tb to wa index n;
//;
  tbRead() As Object{
   Boolean As b;
   Integer As t1;
   Integer As t2;
   Integer As iDx;
   String As s1;
   String As s2;
   Node As oNode;
   Node As oNodeTb;
   Node As oNodeWa;
   Node As oNodeIdx;
  
  Set oNode = createNode(3);
  oNode.tipo = Tag.CTBREAD;
  
  moveToken;
  
   matchTokenTypeWMoveMsg(Tag.CCVAR, "Esperado nome do elemento: " & gToken.valor);
  s1 = gToken.valor;
  b = validIsTable(s1, t1);
   assert(b = True, "A variável deve ser do tipo tabela: " & s1);
   matchToken("TO");
   matchTokenTypeWMoveMsg(Tag.CCVAR, "Esperado nome do elemento: " & gToken.valor);
  s2 = gToken.valor;
  b = validIsWorkArea(s2, t2);
   assert(b = True, "A variável deve ser do tipo workarea: " & s2);
   assert(t1 = t2, "A workarea " & s2 & " deve ser do mesmo tipo da tabela " & s2 & " :" & t1 & " " & t1);
   matchToken("INDEX");
   matchTokenTypeWMoveMsg(Tag.CINTEGER, "Esperado numero inteiro para indice");
  
  Set oNodeTb = createNode1(0);
  Set oNodeWa = createNode1(0);
  Set oNodeIdx = createNode1(0);
  oNodeWa.valor = s1;
  oNodeWa.validnomeobj = t1;
  oNodeTb.valor = s2;
  oNodeTb.validnomeobj = t2;
  oNodeIdx.valor = gToken.valor;
  
  moveToken;
  
   oNode.putFilho(1, oNodeWa);
   oNode.putFilho(2, oNodeTb);
   oNode.putFilho(3, oNodeIdx);
  
  Set tbRead = oNode;
}
//;
//loop tb into wa;
//  bla bla;
//endloop;
//;
  tbLoop() As Object{
   Boolean As b;
   Integer As t1;
   Integer As t2;
   Integer As iDx;
   String As s1;
   String As s2;
   Node As oNode;
   Node As oNodeTb;
   Node As oNodeWa;
   Node As oNodeSs;
  
  Set oNode = createNode(3);
  oNode.tipo = Tag.CTBLOOP;
  
  moveToken;
  
   matchTokenTypeWMoveMsg(Tag.CCVAR, "Esperado nome do elemento: " & gToken.valor);
  s1 = gToken.valor;
  b = validIsTable(s1, t1);
   assert(b = True, "A variável deve ser do tipo tabela: " & s1);
   matchToken("TO");
   matchTokenTypeWMoveMsg(Tag.CCVAR, "Esperado nome do elemento: " & gToken.valor);
  s2 = gToken.valor;
  b = validIsWorkArea(s2, t2);
   assert(b = True, "A variável deve ser do tipo workarea: " & s2);
   assert(t1 = t2, "A workarea " & s2 & " deve ser do mesmo tipo da tabela " & s2 & " :" & t1 & " " & t1);
  
  Set oNodeSs = Stmts();
  
   matchToken("ENDLOOP");
  
  Set oNodeTb = createNode1(0);
  Set oNodeWa = createNode1(0);
  
  oNodeWa.valor = s1;
  oNodeWa.validnomeobj = t1;
  oNodeTb.valor = s2;
  oNodeTb.validnomeobj = t2;
  oNodeIdx.valor = gToken.valor;
  
   oNode.putFilho(1, oNodeWa);
   oNode.putFilho(2, oNodeTb);
   oNode.putFilho(3, oNodeSs);
  
  Set tbLoop = oNode;
}
  

//;
// Funções assign;
//;
  assignGetLdDir(pAgn As ElemAssign) As Object{
   String As sMsg;
  
  if( gToken.tipo = Tag.CNEW ){ //vv = new obj;
    Set assignGetLdDir = assignNewObj(pAgn);
   
  } else if( gToken.tipo = Tag.CNEWARRAY ){ //vv = newarray(10);
    Set assignGetLdDir = assignNewArray(pAgn);
   
  } else if( pAgn.funcObj != "" ){
    Set assignGetLdDir = callFunctionObj(pAgn.ldEsq1, pAgn.funcObj){
    
  }else{
    Set assignGetLdDir = assignVar(pAgn) //vv = v1 ...;
  
  }
  
}

  assignGetLdEsq() As ElemAssign{
   Boolean As bIsArray;
   Boolean As bGlobal;
   Boolean As bIsNative;
   Integer As iId;
   Integer As iTipo;
   String As sNomeClass;
   String As sNomeTot;
   ElemAssign As tAgn;
  
  tAgn.ldEsq1 = "";
  tAgn.ldEsq1Cls = "";
  tAgn.ldEsq1Gbl = False;
  tAgn.ldEsq1Id = -1;
  tAgn.ldEsq1Tipo = -1;
  tAgn.ldEsq2 = "";
  tAgn.ldEsq2Cls = "";
  tAgn.atribConst = "";
  tAgn.ldEsq2Tipo = -1;
  tAgn.funcObj = "";
  tAgn.funcObjCls = "";
  tAgn.funcObjTipo = -1;
  tAgn.isArray = False;
  Set tAgn.oIdxArray = Nothing;
  
  assignGetLdEsq = tAgn;
  
  if( gToken.tipo != Tag.CCVAR &&        gToken.tipo != Tag.CARRAY ){
     matchTokenTypeWMoveMsg(Tag.CCVAR, "esperado nome do elemento");
  }

  // v1 =;
  tAgn.ldEsq1 = gToken.valor;
  iTipo = pegaTipoVar(gFuncId, tAgn.ldEsq1, "", sNomeClass, iId, bGlobal, bIsArray);
   assert(iTipo > 0, "variável não encontrada: " & tAgn.ldEsq1);
  tAgn.ldEsq1Id = iId;
  tAgn.ldEsq1Gbl = bGlobal;
  tAgn.ldEsq1Tipo = iTipo;
  tAgn.ldEsq1Cls = sNomeClass;
  tAgn.isArray = bIsArray;
  Set tAgn.oIdxArray = Nothing;
  if( gToken.tipo = Tag.CARRAY ){
     assert(bIsArray = True, "variável não é array: " & tAgn.ldEsq1);
    moveToken;
     matchTokenMsg("[", "esperado [ para início de array");
    tAgn.isArray = False //deixou de ser array;
    Set tAgn.oIdxArray = Bool(False);
     matchTokenMsg("]", "esperado ] de final de array");
    assignGetLdEsq = tAgn;
    return({
  }
  
  moveToken;
  if( gToken.valor = "." ){
    moveToken;
    if( gToken.tipo = Tag.CFUNC ){ //obj.func(...;
      tAgn.funcObj = gToken.valor;
      if( sNomeClass != "" ){
        sNomeTot = sNomeClass & "." & tAgn.funcObj;
      }else{
        sNomeTot = tAgn.funcObj;
      }
      //;
      // implementar is array aqui;
      //;
       pegaRetFunc(sNomeTot, iTipo, bIsArray, sNomeClass, bIsNative);
      tAgn.funcObjTipo = iTipo;
      tAgn.funcObjCls = sNomeClass;
      
    }else{  //obj.v1 =;
      sNomeClass = "";
      
      assert gToken.tipo = Tag.CCVAR || gToken.tipo = Tag.CARRAY,             "esperado nome do membro";
      //Call matchTokenTypeWMoveMsg(Tag.CCVAR, "esperado nome do membro");
       
      tAgn.ldEsq2 = gToken.valor;
      iTipo = pegaTipoVar(gFuncId, tAgn.ldEsq2, tAgn.ldEsq1Cls, sNomeClass, iId, bGlobal, bIsArray);
      
      tAgn.ldEsq2Tipo = iTipo;
      tAgn.ldEsq2Cls = sNomeClass;
      tAgn.isArray = bIsArray;
      if( tAgn.ldEsq1Cls != "" ){
        tAgn.atribConst = tAgn.ldEsq1Cls & "." & tAgn.ldEsq2;
      }
      moveToken;
      if( gToken.valor = "[" ){
         assert(bIsArray = True, "variável não encontrada: " & tAgn.ldEsq2);
        tAgn.isArray = False;
        moveToken;
        Set tAgn.oIdxArray = Bool(False);
         matchTokenMsg("]", "esperado ] de final de array");
      }else{
         matchTokenWMoveMsg("=", "esperado = de associação");
      }
    }
  }
  
  assignGetLdEsq = tAgn;
  
}

  assignNewArray(pAgn As ElemAssign) As Object{
   Integer As iTipo;
   Node As b;
   Node As oNode;
   Node As oNode1;
  
   moveToken;
  
   matchTokenMsg("(", "esperado o caracter ( para definir o tamanho do array");
  if( gToken.tipo != Tag.CCDECLCHAR &&      gToken.tipo != Tag.CCDECLINT &&      gToken.tipo != Tag.CCDECLFLOAT &&      gToken.tipo != Tag.CCDECLOBJ ){
      matchTokenTypeMsg(Tag.CCDECLINT, "esperado o tipo: char, int, float ou objeto para declarar array");
  }
  
  iTipo = gToken.tipo;
  Select Case iTipo;
    Case Tag.CCDECLCHAR;
      iTipo = Tag.CCHAR1;
    Case Tag.CCDECLINT;
      iTipo = Tag.CINTEGER;
    Case Tag.CCDECLFLOAT;
      iTipo = Tag.CFLOAT;
    Case Tag.CCDECLOBJ;
      iTipo = Tag.COBJ;
  EndSelect;
  
  moveToken;
  
   matchTokenMsg(",", "esperado o caracter , para finalizar comando array");
  Set b = Bool(False);
   matchTokenMsg(")", "esperado o caracter ) para finalizar comando array");
  
  Set oNode = createNode1(0);
  Set oNode1 = createNode1(1);
  
  if( pAgn.ldEsq2 != "" ){
    oNode.tipo = Tag.CASSIGNATR;
    oNode.valor = pAgn.atribConst;
    oNode.idClass = pAgn.ldEsq1Id;
     assert(pAgn.isArray = True, "a variável deve ser array: " & pAgn.atribConst);
     assert(pAgn.ldEsq2Tipo = iTipo, "tipos diferentes: " & pAgn.atribConst);
  }else{
    oNode.tipo = Tag.CASSIGNLOC //variável da classe local;
    oNode.id = pAgn.ldEsq1Id;
    oNode.isAttribute = pAgn.ldEsq1Gbl;
     assert(pAgn.isArray = True, "a variável deve ser array: " & pAgn.ldEsq1);
     assert(pAgn.ldEsq1Tipo = iTipo, "tipos diferentes no array: " & pAgn.ldEsq1);
  }
  
  oNode1.tipo = Tag.CNEWARRAY;
  oNode1.valor = "NEWARRAY";
  oNode1.validtipo = iTipo;
  
   oNode1.putFilho(1, b);
  
  Set assignNewArray = createNode1(2);
   assignNewArray.putFilho(1, oNode1);
   assignNewArray.putFilho(2, oNode);
  assignNewArray.linha = gToken.linha;
  assignNewArray.tipo = Tag.CASSIGN;
  assignNewArray.valor = "ASSIGN";
  
}

  assignNewObj(pAgn As ElemAssign) As Object{
   Boolean As b;
   Integer As iTipo;
   Node As oNode;
   Node As oNode1;
   String As sVarRef;
  
   moveToken;
   matchTokenTypeWMoveMsg(Tag.CCVAR, "linha " & gToken.linha & "-esperado o nome da tipo do objeto");
  
  iTipo = -1;
  
  //Carrega a classe;
  b = ReadClass(gToken.valor);
   assert(b = True, "classe não encontrada " & gToken.valor);
    
  if( pAgn.ldEsq2Cls != "" ){
    //If gToken.valor != pAgn.ldEsq2Cls ){
    //   Err.Raise(vbObjectError + 513, "Compilador", "linha " & gToken.linha & "-objetos com tipos diferentes: " & gToken.valor & "-" & pAgn.ldEsq2Cls);
    //End if(;
    
     validVarAssignObjNewMsg(gFuncId, pAgn.ldEsq2, pAgn.ldEsq1Cls, gToken.valor);
    
    Set oNode = createNode1(0);
    oNode.tipo = Tag.CASSIGNATR;
    oNode.valor = pAgn.atribConst;
     putConst(pAgn.atribConst, CCONST);
    //Além de validar, ela indica se o objeto foi instanciado;
    
  }else{
    //If gToken.valor != pAgn.ldEsq1Cls ){
    //   Err.Raise(vbObjectError + 513, "Compilador", "linha " & gToken.linha & "-objetos com tipos diferentes: " & gToken.valor & "-" & pAgn.ldEsq2Cls);
    //End if(;
    
     validVarAssignObjNewMsg(gFuncId, pAgn.ldEsq1, "", gToken.valor);
    
    if( pAgn.isArray = True ){
      Set oNode = createNode1(1);
       oNode.putFilho(1, pAgn.oIdxArray);
    }else{
      Set oNode = createNode1(0);
    }
    oNode.tipo = Tag.CASSIGNLOC;
    oNode.id = pAgn.ldEsq1Id;
    oNode.isAttribute = pAgn.ldEsq1Gbl;
  }
  
  Set oNode1 = createNode1(0);
  oNode1.tipo = Tag.CNEWCLASS;
  oNode1.valor = gToken.valor;
   putConst(gToken.valor, CCONST);
  
  Set assignNewObj = createNode1(2);
   assignNewObj.putFilho(1, oNode1);
   assignNewObj.putFilho(2, oNode);
  assignNewObj.linha = gToken.linha;
  assignNewObj.tipo = Tag.CASSIGN;
  assignNewObj.valor = "ASSIGN";
   moveToken;
}

  callFunctionObj(pParte1 As String, pParte2 As String) //, pTokenTipo As Integer) As Object{
   Boolean As bIsArray;
   Boolean As bGlobal;
   Boolean As bIsNative;
   Integer As iId;
   Integer As iIdClass;
   Integer As iTipo;
   String As sNomeTot;
   String As sNomeClass;
   String As sMsg;
   Object As b;
   Node As Node;
  
  iTipo = pegaTipoVar(gFuncId, pParte1, "", sNomeClass, iId, bGlobal, bIsArray);
  iIdClass = iId;
  if( iTipo = -1 ){
    sMsg = "linha " & gToken.linha & "-" & "variável " & pParte1 & " não encontrada";
     Err.Raise(vbObjectError + 513, "Compilador", sMsg);
  }
  //Call validVarAssignMsg(gFuncId, pParte1, sNomeClass)  //valida a variável  objeto;
  
  sNomeTot = sNomeClass & "." & pParte2;
   validFuncMsg(sNomeTot, "função não encontrada: " & sNomeTot);
  
  //sNome = gToken.Valor      //Pega o nome da função - calc(p1,p2);
   putConst(sNomeTot, CCONST);
   moveToken;
   matchTokenMsg("(", "esperado ( em chamada à função: " & sNomeTot);
  Set b = pegaArgs(True)   //Args;
   validFuncChamadaMsg(sNomeTot, b);
   matchTokenMsg(")", "esperado ) em chamada à função: " & sNomeTot);
  
   pegaRetFunc(sNomeTot, iTipo, bIsArray, sNomeClass, bIsNative);
  Set Node = wordFunc(gToken.linha, sNomeTot, b);
  Node.tipo = Tag.CLASSMETHOD;
  Node.valor = sNomeTot;
  Node.validnomeobj = sNomeClass;
  Node.validtipo = iTipo;
  Node.idClass = iIdClass;
  Set callFunctionObj = Node{
  
}

  callFunction(pTokenValor As String, pTokenTipo As Integer) As Object{
   Boolean As bIsNative;
   Boolean As bIsArray;
   Integer As iTipo;
   String As sNome;
   String As sNomeClass;
   Node As oNode;
   Object As b;
  
  sNome = gToken.valor      //Pega o nome da função - calc(p1,p2);
   putConst(sNome, CCONST);
   moveToken;
   matchTokenMsg("(", "esperado ( em chamada à função " & sNome);
  Set b = pegaArgs(True)   //Args;
   validFuncChamadaMsg(sNome, b);
   matchTokenMsg(")", "esperado ) em chamada à função " & sNome);
  Set oNode = wordFunc(gToken.linha, sNome, b);
   pegaRetFunc(sNome, iTipo, bIsArray, sNomeClass, bIsNative);
  //Set callFunction = createNode1(1){
  Set callFunction = oNode{
  callFunction.id = pegaIdFunc2(sNome){
  callFunction.valor = sNome{
  callFunction.tipo = Tag.CALLFUNC{
  callFunction.validnomeobj = sNomeClass{
  callFunction.validtipo = iTipo{
  callFunction.isNative = bIsNative{
  callFunction.linha = gToken.linha{
  callFunction.isArray = bIsArray{
  //Call callFunction.putFilho(1, oNode){
   
}

  assignVar(pAgn As ElemAssign) As Object{
   Boolean As bGlobal;
   Boolean As bIsArray;
   Integer As iId;
   Integer As iTipo;
   String As sVar;
   String As sClass;
   Node As oNode;
   Node As oNode1;
   
  if( Not pAgn.oIdxArray Is Nothing ){
    Set oNode = createNode1(1);
    oNode.isArrayCall = True;
     oNode.putFilho(1, pAgn.oIdxArray);
  }else{
    Set oNode = createNode1(0);
    oNode.isArrayCall = False;
  }
    
  if( pAgn.ldEsq2 != "" ){ //atributo de outra classe;
    oNode.tipo = Tag.CASSIGNATR;
    oNode.valor = pAgn.atribConst;
    oNode.idClass = pAgn.ldEsq1Id;
     putConst(pAgn.atribConst, CCONST);
    iTipo = pAgn.ldEsq2Tipo;
    sClass = pAgn.ldEsq2Cls;
    sVar = pAgn.ldEsq2;
  }else{
    oNode.tipo = Tag.CASSIGNLOC //variável da classe local;
    oNode.id = pAgn.ldEsq1Id;
    oNode.isAttribute = pAgn.ldEsq1Gbl;
    iTipo = pAgn.ldEsq1Tipo;
    sClass = pAgn.ldEsq1Cls;
    sVar = pAgn.ldEsq1;
  }
  
  Set oNode1 = Bool(False);
  
  if( iTipo = Tag.COBJ || oNode1.validtipo = Tag.COBJ ){
     assert(sClass = oNode1.validnomeobj, "atribuição para classes diferentes: " & pAgn.ldEsq1 & "." & pAgn.ldEsq2);
  }
  
   assert(Not ((pAgn.isArray = True || oNode1.isArray = True)                   && (pAgn.isArray != oNode1.isArray)), "variável recebe somente tipo array: " & sVar);
    
  if( pAgn.isArray = True && oNode1.isArray = True ){
     assert(iTipo = oNode1.validtipo, "os tipos devem ser iguais em atribuição com array");
  }
              
  Set assignVar = createNode1(2);
  assignVar.tipo = Tag.CASSIGN;
  assignVar.valor = "ASSIGN";
   assignVar.putFilho(1, oNode1);
   assignVar.putFilho(2, oNode);
  assignVar.linha = gToken.linha;
}

 Bool(pCalledByFunc As Boolean) As Object{
   oNode As New Node;
  Set oNode = RelOr(pCalledByFunc);
  Set Bool = createNode1(1);
   Bool.putFilho(1, oNode);
  Bool.valor = "BOOL";
  Bool.tipo = Tag.CCBOOL;
  Bool.validtipo = oNode.validtipo;
  Bool.validnomeobj = oNode.validnomeobj;
  Bool.isArray = oNode.isArray;
}

 RelOr(pCalledByFunc As Boolean) As Object{
   Node As oNode;
   Node As oNode1;
   Node As oNodeTerm;
  
  Set oNodeTerm = RelCmpEq(pCalledByFunc);
  
  if( gToken.valor != "||" &&      gToken.valor != "&&" ){
    Set RelOr = oNodeTerm;
    return({
  }

   while( gToken.valor = "||" ||            gToken.valor = "&&";
    Set oNode = createNode1(2);
    oNode.tipo = gToken.tipo;
     oNode.putFilho(1, oNodeTerm);
    oNode.valor = gToken.valor;
     moveToken;
    Set oNode1 = RelOr(pCalledByFunc);
     oNode.putFilho(2, oNode1);
    oNode.validtipo = oNode1.validtipo;
    oNode.validnomeobj = oNode1.validnomeobj;
  }
  Set RelOr = oNode;
}

 RelCmpEq(pCalledByFunc As Boolean) As Object{
   Node As oNode;
   Node As oNode1;
   Node As oNodeTerm;
  
  Set oNodeTerm = RelCmp(pCalledByFunc);
  
  if( gToken.valor != ">=" &&      gToken.valor != "<=" ){
    Set RelCmpEq = oNodeTerm;
    return({
  }

   while( gToken.valor = ">=" ||            gToken.valor = "<=";
    Set oNode = createNode1(2);
     oNode.putFilho(1, oNodeTerm);
    oNode.valor = gToken.valor;
    oNode.tipo = gToken.tipo;
     moveToken;
    Set oNode1 = RelCmpEq(pCalledByFunc);
     oNode.putFilho(2, oNode1);
    oNode.validtipo = oNode1.validtipo;
    oNode.validnomeobj = oNode1.validnomeobj;
  }
  Set RelCmpEq = oNode;
}

 RelCmp(pCalledByFunc As Boolean) As Object{
   Node As oNode;
   Node As oNode1;
   Node As oNodeTerm;
  
  Set oNodeTerm = RelEq(pCalledByFunc);
  
  if( gToken.valor != ">" &&      gToken.valor != "<" ){
    Set RelCmp = oNodeTerm;
    return({
  }

   while( gToken.valor = ">" ||            gToken.valor = "<";
    Set oNode = createNode1(2);
     oNode.putFilho(1, oNodeTerm);
    oNode.valor = gToken.valor;
    oNode.tipo = Tag.CCALC;
     moveToken;
    Set oNode1 = RelCmp(pCalledByFunc);
     oNode.putFilho(2, oNode1);
    oNode.validtipo = oNode1.validtipo;
    oNode.validnomeobj = oNode1.validnomeobj;
  }
  Set RelCmp = oNode;
}

 RelEq(pCalledByFunc As Boolean) As Object{
   Node As oNode;
   Node As oNodeEq;
   Node As oNodeTerm;
  
  Set oNodeTerm = CalcMais(pCalledByFunc);
  
  if( gToken.valor != "==" ){
    Set RelEq = oNodeTerm;
    return({
  }

   while( gToken.valor = "==";
    Set oNode = createNode1(2);
    oNode.tipo = gToken.tipo;
     oNode.putFilho(1, oNodeTerm);
    oNode.valor = gToken.valor;
    oNode.tipo = Tag.CEQ;
     moveToken;
    Set oNodeEq = RelEq(pCalledByFunc);
     oNode.putFilho(2, oNodeEq);
    oNode.validtipo = oNodeEq.validtipo;
    oNode.validnomeobj = oNodeEq.validnomeobj;
  }
  Set RelEq = oNode;
}

 CalcMais(pCalledByFunc As Boolean) As Object{
   Node As oNode;
   Node As oNodeMais;
   Node As oNodeTerm;
  
  Set oNodeTerm = CalcVezes(pCalledByFunc);
  
  if( gToken.valor != "+" &&      gToken.valor != "-" ){
    Set CalcMais = oNodeTerm;
    return({
  }
  
   while( gToken.valor = "+" ||            gToken.valor = "-";
    Set oNode = createNode1(2);
    oNode.tipo = Tag.CCALC;
     oNode.putFilho(1, oNodeTerm);
    oNode.valor = gToken.valor;
     moveToken;
    Set oNodeMais = CalcMais(pCalledByFunc);
     oNode.putFilho(2, oNodeMais);
    oNode.tipo = Tag.CCALC;
    oNode.validtipo = oNodeMais.validtipo;
    oNode.validnomeobj = oNodeMais.validnomeobj;
     validAssignTipoCalcMsg(oNodeTerm.validtipo, oNodeMais.validtipo);
  }
  Set CalcMais = oNode;
}

 CalcVezes(pCalledByFunc As Boolean) As Object{
   Node As oNode;
   Node As oNode1;
   Node As oNodeTerm;
  
  Set oNodeTerm = CalcFator(pCalledByFunc);
  
  if( gToken.valor != "*" &&      gToken.valor != "/" ){
    Set CalcVezes = oNodeTerm;
    return({
  }
  
   while( gToken.valor = "*" ||            gToken.valor = "/";
    Set oNode = createNode1(2);
    oNode.tipo = Tag.CCALC;
     oNode.putFilho(1, oNodeTerm);
    oNode.valor = gToken.valor;
     moveToken;
    Set oNode1 = CalcVezes(pCalledByFunc);
     oNode.putFilho(2, oNode1);
    oNode.tipo = Tag.CCALC;
    oNode.validtipo = oNode1.validtipo;
    oNode.validnomeobj = oNode1.validnomeobj;
     validAssignTipoCalcMsg(oNodeTerm.validtipo, oNode1.validtipo);
  }
  Set CalcVezes = oNode;
}

 CalcFator(pCalledByFunc As Boolean) As Object{
   Node As oNode;
   Node As oNodeTerm;
  
  //Set oNodeTerm = getTerm(pCalledByFunc);
  
  if( gToken.valor != "(" ){
     Set oNodeTerm = getTerm(pCalledByFunc);
     Set CalcFator = oNodeTerm;
    return({
  }
  
   matchToken("(");
  
  Set oNode = Bool(pCalledByFunc);
  oNode.tipo = Tag.CPAROPEN;
  oNode.valor = "PARENTESES";
  oNode.validtipo = oNode.validtipo;
  oNode.validnomeobj = oNode.validnomeobj;
  
   matchToken(")");
  
  Set CalcFator = oNode;
}

 getTerm(pCalledByFunc As Boolean) As Object{
   Boolean As bIsArray;
   Boolean As bGlobal;
   Integer As i;
   Integer As iId;
   Integer As iIdClass;
   Integer As iTipo;
   Integer As iTipo1;
   Integer As idFunc;
   String As sNome;
   String As sTipo;
   String As sNomeClass;
   String As sNomeClassBase;
   String As sParte1;
   String As sParte2;
   Object As oFunc;
   Funcao As tfunc;
   Node As oNode;
   Node As oNode1;
   Object As b;
  
  bGlobal = False;
  
  if( gToken.tipo = Tag.CCVAR ||      gToken.tipo = Tag.CARRAY ||      gToken.tipo = Tag.CCHAR1 ||      gToken.tipo = Tag.CINTEGER ||      gToken.tipo = Tag.CFLOAT ||      gToken.tipo = Tag.CSTRING ||      gToken.tipo = Tag.COBJ ){
    
    //;
    // Coloca constante na tabela de simbolos;
    //;
    if( gToken.tipo != Tag.CCVAR &&        gToken.tipo != Tag.CARRAY ){
      iTipo = putConst(gToken.valor, gToken.tipo);
      Set getTerm = createNode1(0);
      getTerm.valor = gToken.valor;
      getTerm.tipo = gToken.tipo;
      getTerm.idConst = iTipo;
      getTerm.validnomeobj = "";
      getTerm.validtipo = gToken.tipo;
      if( gToken.tipo = Tag.CSTRING ){
        getTerm.isArray = True;
        getTerm.tipo = Tag.CCHAR1;
        getTerm.validtipo = Tag.CCHAR1;
        //oNode.;
      }
                
      moveToken;
    }else{
      sParte1 = gToken.valor;
      iTipo1 = gToken.tipo;
      moveToken;
      if( gToken.valor = "." ){
        moveToken;
        if( gToken.tipo = Tag.CCVAR ||            gToken.tipo = Tag.CARRAY ){
          sParte2 = gToken.valor;
          iTipo = pegaTipoVar(gFuncId, sParte1, "", sNomeClassBase, iId, bGlobal, bIsArray);
          iIdClass = iId;
           validObjIsInstanceadMsg(gFuncId, sParte1);
          iTipo = pegaTipoVar(gFuncId, sParte2, sNomeClassBase, sNomeClass, iId, bGlobal, bIsArray);
           
          //Verifica Array;
          moveToken;
          if( gToken.valor = "[" ){
             assert(bIsArray = True, "variável não é array: " & sParte2);
            moveToken;
            Set b = Bool(False);
             matchTokenMsg("]", "esperado o caracter ] para fechar array");
            Set getTerm = createNode1(1);
             getTerm.putFilho(1, b);
            getTerm.isArrayCall = True;
            getTerm.isArray = False;
            getTerm.tipo = Tag.CLASSATTRIBARRAY;
          }else{
            Set getTerm = createNode1(0);
            getTerm.isArrayCall = False;
            getTerm.tipo = Tag.CLASSATTRIB;
            getTerm.isArray = bIsArray;
          }
          
          getTerm.idClass = iIdClass;
          getTerm.valor = sNomeClassBase & "." & sParte2;
          //getTerm.tipo = Tag.CLASSATTRIB;
          getTerm.validnomeobj = sNomeClass;
          getTerm.validtipo = iTipo;
          
        } else if( gToken.tipo = Tag.CFUNC ){
          sParte2 = gToken.valor;
           validObjIsInstanceadMsg(gFuncId, sParte1);
          Set getTerm = callFunctionObj(sParte1, sParte2){
        }
      }else{
        if( pCalledByFunc = False ){ //Evita que entre aqui quando for chamado por função;
          iTipo = pegaTipoVar(gFuncId, sParte1, "", sNomeClass, iId, bGlobal, bIsArray);
          if( iTipo < 0 ){
             Err.Raise(vbObjectError + 513, "Compilador", "linha " & gToken.linha & "-variável não encontrada: " & sParte1);
          }
        }
        
        //Verifica Array;
        //moveToken;
          
        if( gToken.valor = "[" ){
          moveToken;
          if( pCalledByFunc = False ){
             assert(bIsArray = True, "variável não é array: " & sParte1);
            Set b = Bool(False);
          }
           matchTokenMsg("]", "esperado o caracter ] para fechar array");
          if( pCalledByFunc = False ){
            Set getTerm = createNode1(1);
             getTerm.putFilho(1, b);
            getTerm.isArrayCall = True;
            getTerm.isArray = False;
            getTerm.tipo = Tag.CCVARARRAY;
          }else{
            Set getTerm = createNode1(0);
            getTerm.isArrayCall = False;
            getTerm.isArray = True;
            getTerm.tipo = Tag.CCVAR;
          }
        }else{
          Set getTerm = createNode1(0);
          getTerm.isArrayCall = False;
          getTerm.isArray = bIsArray;
          getTerm.tipo = Tag.CCVAR //indica que é uma variável;
        }
          
        getTerm.id = iId;
        getTerm.isAttribute = bGlobal;
        getTerm.valor = sParte1;
        getTerm.validnomeobj = sNomeClass;
        getTerm.validtipo = iTipo;
        //Call moveToken;
      }
      
    }
    
  } else if( gToken.tipo = Tag.CFUNC ){ //tratamento de função;
    sNome = gToken.valor      //Pega o nome da função - calc(p1,p2);
    iTipo = gToken.tipo;
    Set getTerm = callFunction(sNome, iTipo){
  }else{
     Err.Raise(vbObjectError + 513, "Compilador", "linha " & gToken.linha & "-erro sintaxe, elemento não esperado na expressão: " & gToken.valor);
  }
}

//-------------- Pega Argumentos --------------;
 pegaArgs(pFirst As Boolean) As Object{
  
  //;
  // Se pFirst = true, significa que foi passado pela raiz;
  // pegaArgs pode ter 0, 1 ou 2 nós:;
  //  0 - não foi passado parâmetros;
  //  1 - foi passado somente um parâmetro ou chegou-se ao final;
  //      da cadeia de parâmetros;
  //  2 - possui mais de 1 parâmetro e monta um encadeamento de nód args;
  //;
   Node As oNode;
   Node As oNode1;
  
  if( gToken.valor = ")" &&      pFirst = True ){
    Set pegaArgs = createNode1(0) //Nao foi passado argumentos;
    pegaArgs.valor = "ARGS";
    pegaArgs.tipo = Tag.CCARGS;
    return({
  }
  
  //Set onode = getTerm(True);
  Set oNode = Bool(False);
  
  if( gToken.valor = ")" ){
    Set pegaArgs = createNode1(1);
    pegaArgs.tipo = Tag.CCARGS;
    pegaArgs.valor = "ARGS";
     pegaArgs.putFilho(1, oNode);
    return({
  }
  
   while( gToken.valor = ",";
    Set pegaArgs = createNode1(2);
    pegaArgs.tipo = Tag.CCARGS;
    pegaArgs.valor = "ARGS";
     pegaArgs.putFilho(1, oNode);
     moveToken;
     pegaArgs.putFilho(2, pegaArgs(False));
  }
  
   matchTokenWMoveMsg(")", "esperado ) para fechar a expressão");
  
}

//-------------- Pega Argumentos --------------;
 pegaParDef(pFirst As Boolean) As Object{
  
   String As sNomeClass;
   Node As oNode;
   Node As oNode1;
   Node As oNode2;
   Token As lToken;
  
  sNomeClass = "";
  Set pegaParDef = Nothing;
    
  if( gToken.valor = ")" ){
    return({
  }
  
   while( gToken.valor != ")";
    if( pFirst = False ){
       matchTokenMsg(",", "esperado o carater ,") //pula virgula;
    }
    Set lToken = gToken;
    
//   Início tratamento do objeto;
    if( lToken.tipo = Tag.CCDECLOBJ ){
       matchTokenMsg("OBJECT", "esperada a declaração Object");
       matchTokenMsg("(", "esperado ( em declaração de Objeto");
      sNomeClass = gToken.valor;
       matchTokenTypeMsg(Tag.CCVAR, "esperado nome do objeto na tipificação");
       matchTokenWMoveMsg(")", "esperado ) em declaração de Objeto");
    }
//   Fim tratamento objeto;

     moveToken;
    
    Set oNode1 = getTerm(True);
    
    if( lToken.tipo = Tag.CCDECLCHAR ){
      oNode1.tipo = Tag.CCHAR1;
    } else if( lToken.tipo = Tag.CCDECLINT ){
      oNode1.tipo = Tag.CINTEGER;
    } else if( Tag.CCDECLOBJ ){
      oNode1.tipo = Tag.COBJ;
    }else{
      oNode1.tipo = Tag.CFLOAT;
    }
    Set oNode2 = pegaParDef(False);
    if( oNode2 Is Nothing ){
      Set oNode = createNode1(1);
    }else{
      Set oNode = createNode1(2);
       oNode.putFilho(2, oNode2);
    }
    oNode.tipo = Tag.CCARGS;
    oNode.valor = "ARGS";
    
    oNode1.id = putVarFunc(gFuncId, CTIPOPARIN, oNode1.valor, oNode1.tipo, oNode1.isArray, 0, sNomeClass);
    
     oNode.putFilho(1, oNode1);
    
    Set pegaParDef = oNode;
    
  }
  
}

//------------------ 2a. linguagem ---------------------;
  list2Lang(p1 As Node) As Node{

   Integer As i;
   Integer As t;
  
  if( p1 Is Nothing ){
    Set list2Lang = Nothing;
    return({
  }
  
  g2Lang = g2Lang & p1.valor & vbCrLf;
  
  t = p1.qtdFilhos;
  for( i = 1 To t;
     list2Lang(p1.getFilho(i));
  Next;
  
}

  emit2Lang2(p1 As Node) As String{
   Integer As i;
   Integer As t;
   Integer As iId;
   String As s;
   String As sNome;
   String As sPrg;
   Node As n1;
   Node As n2;
  
  s = "";
  t = p1.qtdFilhos;
  
  for( i = 1 To t;
    Set n1 = p1.getFilho(i);
    if( Not n1 Is Nothing ){
      if( n1.tipo = Tag.CDEF ){
        sNome = n1.valor;
        gFuncId = getId(sNome, CFUNCAO);
        Set n2 = n1.getFilho(2);
        if( Not n2 Is Nothing ){ //Função sem corpo;
          g2Line = 1;
          sPrg = emit2Lang(n2);
          if( sPrg != "" ){
            sPrg = sPrg & mMaqCommands(tag2.OEND, 1);
          }
          s = s & sNome & ":" & vbCrLf & sPrg & vbCrLf;
          //MsgBox sPrg;
           putAssembly(gFuncId, sPrg);
        }
      }else{
        s = s & emit2Lang2(n1);
      }
    }
  Next;
  
  emit2Lang2 = s & emit2Lang2;
  
}


  emit2Lang(p1 As Node) As String{
   String As s = createString();
   String As t;
   String As u;
   String As y;
   String As z;
   Integer As id = createInteger();;
   Integer As idClass;
   
  Select Case p1.tipo;
    Case Tag.CIF;
      s = emit2Lang(p1.getFilho(1));
      t = putC(getOpNome(tag2.OIFFALSE), False);
      u = emit2Lang(p1.getFilho(2));
      t = t & g2Line & vbCrLf;
      s = s & t & u;
    
    Case Tag.CELSE;
      s = emit2Lang(p1.getFilho(1));
      t = putC(getOpNome(tag2.OIFFALSE), False);
      u = emit2Lang(p1.getFilho(2));
      y = putC(getOpNome(tag2.OGOTO), False);
      t = t & g2Line & vbCrLf;
      z = emit2Lang(p1.getFilho(3));
      y = y & g2Line & vbCrLf;
      s = s & t & u & y & z;
      
    Case Tag.CWHILE;
      t = g2Line;
      s = emit2Lang(p1.getFilho(1));
      u = putC(getOpNome(tag2.OIFFALSE), False);
      y = emit2Lang(p1.getFilho(2));
      t = putC(getOpNome(tag2.OGOTO) & t, True);
      y = Replace(y, "@@BR", g2Line);
      u = u & g2Line & vbCrLf;
      s = s & u & y & t;

    Case Tag.CCBREAK;
      s = putC(getOpNome(tag2.OGOTO) & "@@BR", True);
   
    Case Tag.CALLFUNC;
      if( p1.isNative = True ){
        id = getIdS(p1.valor, CCONST);
        id = id - 1;
        u = emit2Lang(p1.getFilho(1));
        s = putC(getOpNome(tag2.OCALLNATV) & id, True);
      }else{
        id = getIDF(p1.valor);
        id = id - 2 //porque a global não conta???;
        u = emit2Lang(p1.getFilho(1));
        s = putC(getOpNome(tag2.OCALLF) & id, True);
      }
      s = u & s;
      
    Case Tag.CRETURN;
      u = "";
      if( Not p1.getFilho(1) Is Nothing ){
        u = emit2Lang(p1.getFilho(1));
        s = putC(getOpNome(tag2.ORET), True);
      }else{
        s = putC(getOpNome(tag2.ORETNULL), True);
      }
      s = u & s;
      
    Case Tag.CCARGS;
      if( p1.qtdFilhos > 0 ){
        t = emit2Lang(p1.getFilho(1));
      }
      if( p1.qtdFilhos > 1 ){
        s = emit2Lang(p1.getFilho(2));
      }
      s = t & s;
      
    Case Tag.CCOMMAND;
      if( p1.qtdFilhos > 0 ){
        s = emit2Lang(p1.getFilho(1));
      }
      if( p1.qtdFilhos > 1 ){
        t = emit2Lang(p1.getFilho(2));
      }
      s = s & t;
     
    Case Tag.CCOMMANDS;
      s = emit2Lang(p1.getFilho(1));
      if( p1.qtdFilhos > 1 ){
        t = emit2Lang(p1.getFilho(2));
      }
      s = s & t;
       
    Case Tag.CCBOOL;
      s = emit2Lang(p1.getFilho(1));
    
    Case Tag.CCALC;
      s = emit2Lang(p1.getFilho(1));
      t = emit2Lang(p1.getFilho(2));
      u = putC(calcSimbol(p1.valor), True);
      s = s & t & u;
    
    Case Tag.CPAROPEN;
      s = emit2Lang(p1.getFilho(1));
      
    Case Tag.CEQ;
      s = emit2Lang(p1.getFilho(2));
      t = emit2Lang(p1.getFilho(1));
      u = putC(calcSimbol(p1.valor), True);
      s = s & t & u;
    
    Case Tag.CDEF;
      gFuncId = getId(p1.valor, CFUNCAO);
      s = emit2Lang(p1.getFilho(2));
       putAssembly(gFuncId, s);
      gFuncId = 0;
      s = "";
      
    Case Tag.CASSIGN;
      s = emit2Lang(p1.getFilho(1));
      t = emit2Lang(p1.getFilho(2));
      s = s & t;
 
    Case Tag.CINTEGER, Tag.CFLOAT, Tag.CCHAR1;
       assert(p1.idConst != 0, "");
      id = p1.idConst;
      id = id - 1;
      s = putC(getOpNome(tag2.OLOADC) & id, True);
      
    Case Tag.CCVAR;
      id = p1.id;
      id = id - 1;
      if( p1.isAttribute = True ){
        s = putC(getOpNome(tag2.OGLOADV) & id, True);
      }else{
        s = putC(getOpNome(tag2.OLOADV) & id, True);
      }
      
    Case Tag.CCVARARRAY;
      id = p1.id;
      id = id - 1;
      u = emit2Lang(p1.getFilho(1));
      if( p1.isAttribute = True ){
        s = putC(getOpNome(tag2.OGLOADVY) & id, True);
      }else{
        s = putC(getOpNome(tag2.OLOADVY) & id, True);
      }
      s = u & s;
      
    Case Tag.CASSIGNATR;
      idClass = p1.idClass;
      idClass = idClass - 1;
      //idClass = idClass;
      u = putC(getOpNome(tag2.OLOADV) & idClass, True);
      id = getIdS(p1.valor, CCONST);
      id = id - 1;
      if( p1.isArrayCall = True ){
        t = emit2Lang(p1.getFilho(1));
        s = putC(getOpNome(tag2.OOSTORVY) & id, True);
        s = t & u & s;
      }else{
        s = putC(getOpNome(tag2.OOSTORV) & id, True);
        s = u & s;
      }
      
    Case Tag.CASSIGNLOC;
      id = p1.id;
      id = id - 1;
      if( p1.isArrayCall = True ){
        t = emit2Lang(p1.getFilho(1));
        if( p1.isAttribute = True ){
          s = putC(getOpNome(tag2.OGSTORVY) & id, True);
        }else{
          s = putC(getOpNome(tag2.OSTORVY) & id, True);
        }
        s = t & s;
      }else{
        if( p1.isAttribute = True ){
          s = putC(getOpNome(tag2.OGSTORV) & id, True);
        }else{
          s = putC(getOpNome(tag2.OSTORV) & id, True);
        }
      }
      
    Case Tag.CLASSATTRIB;
      idClass = p1.idClass;
      idClass = idClass - 1;
      id = getIdS(p1.valor, CCONST);
      id = id - 1;
      u = putC(getOpNome(tag2.OLOADV) & idClass, True);
      s = putC(getOpNome(tag2.OOLOADV) & id, True);
      s = u & s;
      
    Case Tag.CLASSATTRIBARRAY;
      id = getIdS(p1.valor, CCONST);
      id = id - 1;
      idClass = p1.idClass;
      idClass = idClass - 1;
      //idClass = idClass;
      t = emit2Lang(p1.getFilho(1));
      u = putC(getOpNome(tag2.OLOADV) & idClass, True);
      s = putC(getOpNome(tag2.OOLOADVY) & id, True) //executa pop na pilha para pegar o idx do array;
      s = t & u & s;
    
    Case Tag.CLASSMETHOD //opcode de carregamento do objeto;
      idClass = p1.idClass;
      idClass = idClass - 1;
      id = getIdS(p1.valor, CCONST);
      id = id - 1;
      t = emit2Lang(p1.getFilho(1));
      u = putC(getOpNome(tag2.OLOADV) & idClass, True);
      s = putC(getOpNome(tag2.OOCALLF) & id, True);
      s = t & u & s;
      
    Case Tag.CNEWARRAY //falta o nome de objeto;
      id = p1.validtipo //indica o tipo de variável;
      //id = id - 1;
//      Select Case id;
//        Case Tag.CCDECLCHAR;
//          id = Tag.CCHAR1;
//        Case Tag.CCDECLINT;
//          id = Tag.CINTEGER;
//        Case Tag.CCDECLFLOAT;
//          id = Tag.CFLOAT;
//        Case Tag.CCDECLOBJ;
//          id = Tag.COBJ;
//      EndSelect;
      t = emit2Lang(p1.getFilho(1));
      s = putC(getOpNome(tag2.ONEWY) & id, True);
      s = t & s;
     
    Case Tag.CNEWCLASS;
      id = getIdS(p1.valor, CCONST);
      id = id - 1;
      s = putC(getOpNome(tag2.ONEW) & id, True);
   
   EndSelect;
   
   emit2Lang = s;
   
}

  putC(p1 As String, bEnter As Boolean) As String{
   String As sEnt;
  if( bEnter = True ){
    sEnt = vbCrLf;
  }else{
    sEnt = "";
  }
  if( g2NumeraLinha = True ){
    putC = "L" & g2Line & ": " & p1 & sEnt;
  }else{
    putC = p1 & sEnt;
  }
  g2Line = g2Line + 1;
}

  calcSimbol(p1 As String) As String{
  Select Case p1;
    Case "+";
      calcSimbol = "add";
    Case "-";
      calcSimbol = "sub";
    Case "*";
      calcSimbol = "mul";
    Case "/";
      calcSimbol = "div";
    Case "<";
      calcSimbol = "lt";
    Case ">";
      calcSimbol = "gt";
    Case "==";
      calcSimbol = "eq";
  EndSelect;
}

//---- Funcao que pega id de simbolo -----;
  getIdS(p0 As String, ptipo As Byte) As Integer{

  if( gFuncId > 0 && ptipo = CVARIABLE ){
    getIdS = getIdVarFunc(gFuncId, p0);
  }else{
    getIdS = getIdElem(p0, ptipo);
  }
  
  if( getIdS = -1 ){
    //Trata erro;
  }
  
}

//---- verifica variável ----;
 void validVarMsg(pvar As String, pmsg As String){
  if( validVarBase(gFuncId, pvar) = False ){
     Err.Raise(vbObjectError + 513, "Compilador", "linha " & gToken.linha & "-" & pmsg);
  }
}

//---- verifica função local;
 void validFuncMsg(pNomeFunc As String, pmsg As String){
  if( validFuncBase(pNomeFunc) = False ){
     Err.Raise(vbObjectError + 513, "Compilador", "linha " & gToken.linha & "-" & pmsg);
  }
}

//---- verifica função local;
 void validFuncMsg2(pNomeFunc As String, pmsg As String){
  if( validFuncBase(pNomeFunc) = True ){ //achou a função;
     Err.Raise(vbObjectError + 513, "Compilador", "linha " & gToken.linha & "-" & pmsg);
  }
}

//---- verifica parâmetros da função na chamada;
 void validFuncChamadaMsg(pNomeFunc As String, b As Node){
   String As sMsg;
  sMsg = validFuncLocalParBase(gFuncId, pNomeFunc, b);
  if( sMsg != "0" ){
    sMsg = "linha " & gToken.linha & "-" & sMsg;
     Err.Raise(vbObjectError + 513, "Compilador", sMsg);
  }
}

 void validVarAssignMsg(pidFunc As Integer, pNomeVar As String, pNomeClass As String){
   Boolean As b;
   String As sMsg;
  b = validVarAssignBase(pidFunc, pNomeVar, pNomeClass);
  if( b = False ){
    sMsg = "linha " & gToken.linha & "-" & "variável " & pNomeVar & " não encontrada";
     Err.Raise(vbObjectError + 513, "Compilador", sMsg);
  }
}

 void validVarAssignObjMsg(pidFunc As Integer, pNomeVarE As String, pNomeVarD As String){
   Integer As i;
   String As sMsg;
  sMsg = "";
  i = validVarAssignObjBase(pidFunc, pNomeVarE, pNomeVarD);
  Select Case i;
  Case 1;
     sMsg = "linha " & gToken.linha & "-" & "erro em identificação de variável";
  Case 2;
     sMsg = "linha " & gToken.linha & "-" & "variável não encontrada: " & pNomeVarE;
  Case 3;
     sMsg = "linha " & gToken.linha & "-" & "variável não encontrada: " & pNomeVarD;
  Case 4;
     sMsg = "linha " & gToken.linha & "-" & "variável não é objeto: " & pNomeVarE;
  Case 5;
     sMsg = "linha " & gToken.linha & "-" & "variável não é objeto: " & pNomeVarD;
  Case 6;
     sMsg = "linha " & gToken.linha & "-" & "tipos diferentes das variáveis: " & pNomeVarE & "-" & pNomeVarD;
  EndSelect;
  if( sMsg != "" ){
     Err.Raise(vbObjectError + 513, "Compilador", sMsg);
  }
}

 void validVarAssignObjNewMsg(pidFunc As Integer, pNomeVarE As String, pNomeVarEClass As String, pNomeClass As String){
   Integer As i;
   String As sMsg;
  i = validVarAssignObjNewBase(pidFunc, pNomeVarE, pNomeVarEClass, pNomeClass);
  sMsg = "";
  Select Case i;
  Case 1;
     sMsg = "linha " & gToken.linha & "-" & "erro em identificação de variável";
  Case 2;
     sMsg = "linha " & gToken.linha & "-" & "variável não encontrada: " & pNomeVarE;
  Case 3;
     sMsg = "linha " & gToken.linha & "-" & "variável não é objeto: " & pNomeVarE;
  Case 4;
     sMsg = "linha " & gToken.linha & "-" & "tipo de objeto diferente do associado: " & pNomeVarE & "->" & pNomeClass;
  EndSelect;
  if( sMsg != "" ){
     Err.Raise(vbObjectError + 513, "Compilador", sMsg);
  }
}

 void validAssignTipoCalcMsg(pTipoE As Integer, pTipoD As Integer){
   String As sMsg;
  sMsg = "linha " & gToken.linha & "-" & "cálculos devem ser efetuados com tipos INT ou LONG";
  if( pTipoE != Tag.CINTEGER &&      pTipoE != Tag.CFLOAT ){
      Err.Raise(vbObjectError + 513, "Compilador", sMsg);
  }
  if( pTipoD != Tag.CINTEGER &&      pTipoD != Tag.CFLOAT ){
      Err.Raise(vbObjectError + 513, "Compilador", sMsg);
  }
}

 void validObjIsInstanceadMsg(pidFunc As Integer, pNomeVarE As String){
   Integer As i;
   String As sMsg;
  sMsg = "";
  i = validObjIsInstanceadBase(pidFunc, pNomeVarE);
  Select Case i;
  Case 1;
     sMsg = "linha " & gToken.linha & "-" & "erro em identificação de variável";
  Case 2;
     sMsg = "linha " & gToken.linha & "-" & "variável não encontrada: " & pNomeVarE;
  Case 3;
     sMsg = "linha " & gToken.linha & "-" & "variável não é objeto: " & pNomeVarE;
  Case 4;
     sMsg = "linha " & gToken.linha & "-" & "objeto não instanciado: " & pNomeVarE;
  EndSelect;
  if( sMsg != "" ){
     Err.Raise(vbObjectError + 513, "Compilador", sMsg);
  }
}

 void validFuncReturnOk(pCtxFuncId As Integer,                              pnomef As String,                              pcheckret As Boolean,                              ptipo As Integer,                              pclass As String,                              parray As Boolean){
   Integer As i;
   String As sMsg;
  sMsg = "";
  i = validFuncReturnOkBase(pCtxFuncId, pcheckret, ptipo, pclass, parray);
  Select Case i;
  Case 1;
     sMsg = "linha " & gToken.linha & "-" & "falta comando return na função: " & pnomef;
  Case 2;
     sMsg = "linha " & gToken.linha & "-" & "a função deve retornar valor: " & pnomef;
  Case 3;
     sMsg = "linha " & gToken.linha & "-" & "tipo de retorno diferente do tipo esperado na função: " & pnomef;
  Case 4;
     sMsg = "linha " & gToken.linha & "-" & "objeto de retorno diferente do esperado na função: " & pnomef;
  Case 5;
     sMsg = "linha " & gToken.linha & "-" & "erro de tipos com array no retorno da função: " & pnomef;
  Case 6;
     sMsg = "linha " & gToken.linha & "-" & "a função não retorna valores: " & pnomef;
  Case 7;
     sMsg = "linha " & gToken.linha & "-" & "tipo de retorno no array está incorreto, função: " & pnomef;
   EndSelect;
  
  if( sMsg != "" ){
     Err.Raise(vbObjectError + 513, "Compilador", sMsg);
  }
  
}

 void assert(pbol As Boolean, pmsg As String){
  if( pbol = False ){
     Err.Raise(vbObjectError + 513, "Compilador", "linha " & gToken.linha & "-" & pmsg);
  }
}


  pegaTipoVar(pidFunc As Integer,                             pNomeVar As String,                             pNomeClass As String,                             ByRef pclass As String,                             ByRef pId As Integer,                             ByRef pbGlobal As Boolean,                             ByRef pisArray As Boolean) As Integer{
   Boolean As b;
   String As sMsg;
   Variable As tvar;
  pegaTipoVar = -1;
  b = pegaVarFuncClass(pidFunc, pNomeVar, pNomeClass, tvar, False, pId, pbGlobal, pisArray);
  if( b = True ){
    pegaTipoVar = tvar.tipo;
    pclass = tvar.nomeobj;
  }
}

