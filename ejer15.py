
import multiprocessing as np



if __name__=="__main__":

  param=["Hola mundo" for i in range (np.cpu_count())]
  print(param)
