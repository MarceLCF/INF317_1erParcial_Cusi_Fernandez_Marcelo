import multiprocessing as mp
import math as m


def fibo(ini, fin): 
  fb= []
  a, b = 0, 1
  for _ in range(ini):
  	a, b = b, a + b
  for _ in range(fin-ini):
  	fb.append(a)
  	a, b = b, a + b
  return fb

if __name__=="__main__":
  N = 1000
  M = mp.cpu_count() #cantidad de procesadores
  print("Cantidad de procesadores:",M)
  N //= M #---
  params = [(i*N,N*(i+1)) for i in range(M)]

  pool = mp.Pool()
  resultado = pool.starmap(fibo, params)
  
  print("Mostrando los primeros 10 terminos de cada proceso")
  for i in range(len(resultado)):
    print("Proceso",i,"-->",resultado[i][:10],"....")
