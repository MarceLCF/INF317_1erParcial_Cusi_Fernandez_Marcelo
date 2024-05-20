import multiprocessing as mp
import math as m

#2 4 6 8 10 12 ...

def serie(ini, fin): 
  v = []
  for i in range(ini, fin):
    v.append(i*2+2)
  return v

if __name__=="__main__":
  N = int(input("Introduzca cantidad de terminos N: "))
  M = mp.cpu_count() #M procesadores
  print("Cantidad de procesadores:",M)
  N //= M #---
  params = [(i*N,N*(i+1)) for i in range(M)]

  pool = mp.Pool()
  resultado = pool.starmap(serie, params)
  for i in range(len(resultado)):
    print("Proceso",i,"-->",resultado[i])

