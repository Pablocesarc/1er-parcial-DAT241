import multiprocessing as np
from multiprocessing import Pool
import math

def fibo(inicial, final):

  v=[]
  i=0
  for i in range (inicial+1, final+1):
    a1=i*2
    v.append(a1)
  return v


if __name__=="__main__":
    
  nm=int(input("Ingrese M"))
  if (nm%np.cpu_count()==0):
    limite=int(nm/np.cpu_count())
    param=[((i*limite), (limite*(i+1))) for i in range (np.cpu_count())]
    print(param)
  else:
    nm=nm-1
    limite=int(nm/np.cpu_count())
    param=[((i*limite), (limite*(i+1))) for i in range (np.cpu_count()-1)]
    param.append(((limite*(np.cpu_count()-1)),nm+1))

    
  pool=Pool()
  resultado=pool.starmap(fibo,param)
  for i in resultado:
    print(i)
