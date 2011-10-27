casillas_por_diag_por_m = lambda m:\
                   (lambda k:k+1 if k < m else 2*m-k-1)

def alfiles(n,k):
    filas_negras = range(0,2*n-1,2) #son filas si giramos el tablero 45 grados
    filas_blancas = range(1,2*n-1,2)
    casillas_por_diag = casillas_por_diag_por_m(n)
    filas_negras.sort(cmp=lambda x,y: -1 if casillas_por_diag(x) < casillas_por_diag(y) else \
                      1 if casillas_por_diag(x) > casillas_por_diag(y) else 0)
    filas_blancas.sort(cmp=lambda x,y: -1 if casillas_por_diag(x) < casillas_por_diag(y) else \
                      1 if casillas_por_diag(x) > casillas_por_diag(y) else 0)
    # Memorizacion de resultados
    mem_negras=[[None for t in xrange(k+1)] for y in xrange(n+1)]
    mem_blancas=[[None for t in xrange(k+1)] for y in xrange(n+1)]
    
    #inicializamos las tables
    for i in xrange(n+1):
        mem_blancas[i][0]=1
        mem_negras[i][0]=1
        
    for j in xrange(1,k+1):
        mem_blancas[0][j]=0
        mem_negras[0][j]=0
    
    acum = 0
    
    if n%2==1:
        for t in xrange(k+1):
            acum += contar(n,t,filas_negras,mem_negras,casillas_por_diag)*contar(n-1,k-t,filas_blancas,mem_blancas,casillas_por_diag)
    else:
        for t in xrange(k+1):
            acum += contar(n,t,filas_negras,mem_negras,casillas_por_diag)*contar(n,k-t,filas_negras,mem_negras,casillas_por_diag)
    print acum
    
def contar(i,j,fs,mem,map):
    if mem[i][j] == None:
        aux = contar(i-1,j-1,fs,mem,map)
        aux2 =map(fs[i-1])-(j-1)
        mem[i][j] = aux*aux2
        mem[i][j] += contar(i-1,j,fs,mem,map)
    return mem[i][j]
    
        
alfiles(8,7)
alfiles(4,6)
alfiles(6,7)
alfiles(5,10)
alfiles(5,8)
alfiles(5,2)
alfiles(500,300)
    
