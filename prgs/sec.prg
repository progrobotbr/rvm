class sec
beg
  int res
  int aa[]

  --****************************
  --Defini��o de fun��o nativa
  --****************************
  defnative int calc5(int p1, int p2)

  --
  --Retorno e par�metro com arrays
  --
  def int[] calc3(int o1[]) beg
    int o2
    o2 = 1
    o2 = 10
    aa = newarray(int,10)
    aa[ o2 ] = 10 + 3
    res = aa[o2]
    --CALC5(O2,1)
    return(aa)
  enddef
 
  def int calc2(int p1, int p2) beg
    object(prim) obj
    int a
    int a1[]
    int b[]
    a1=newarray(int,2)
    obj = new prim
    b = a1

    if (p1 > a1[1]) beg
      p2 = 3
    else
      p2 = a1[1]
    endif

    a=1
    while(a<10) beg
      a=a+1
      if(a<5) beg
        break
      endif
      a=a-2
    endwhile

    calc3(b)
    obj.res = calc2(obj.res,obj.calc(obj.calc(a,a),a))
    a1[1] = 2
    obj.calc(P1,2)
    return(10)

  enddef

  def object(prim) teste() beg
    int rr[]
    object(prim) tt
    tt = new prim
    return(tt)
  enddef


  def int calc6(int a, int b) beg
    int aa
    aa = a+b
    return(aa)
  enddef

  --
  --Main
  --
  def main() beg
    --int i
    --int z
    --int u
    --int t
    --object(prim) obj
    
    --obj  = new prim
    --i=100
    --z=10+i
    --u=15
    --t=12
    --i=calc6(z,u)
    --z=obj.calc(z,u)
    --obj.res = t
    --t = obj.res + t

    int i
    int z
    int t
    z = 10
    t = 11
    i = calc5(z,t)

  enddef

endclass
