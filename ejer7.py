from multiprocessing import Pool
import multiprocessing as np
import math
def calcular_pi(inicial, final):

  v=[]

  for i in range (inicial, final):
    if i==0:
      continue
    term=(1/i**2)
    v.append(term)

  return v
if __name__=="__main__":
  limite=9999
  param=[((i*limite), (limite*(i+1))) for i in range (np.cpu_count())]
  pool=Pool()
  resultado=pool.starmap(calcular_pi,param)
  pi=math.sqrt(6*sum(sum(resultado,[])))
  print (pi)
