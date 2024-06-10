import multiprocessing as np
from multiprocessing import Pool
import math

def fibo(inicial, final):

  v=[]
  i=0
  for i in range (inicial, final):
    p1=(1/math.sqrt(5))*(((1+math.sqrt(5))/2)**i)
    p2=(1/math.sqrt(5))*(((1-math.sqrt(5))/2)**i)
    pt=p1-p2
    v.append(round(pt))


  return v


if __name__=="__main__":
    
  nm=1051
  if (nm%np.cpu_count()==0):
    limite=int(nm/np.cpu_count())
    param=[((i*limite), (limite*(i+1))) for i in range (np.cpu_count())]
    print(param)
  else:
    nm=nm-1
    limite=int(nm/np.cpu_count())
    param=[((i*limite), (limite*(i+1))) for i in range (np.cpu_count()-1)]
    param.append(((limite*(np.cpu_count()-1)),nm+1))
    print(param)

    
  pool=Pool()
  resultado=pool.starmap(fibo,param)
  for i in resultado:
    print(i)
