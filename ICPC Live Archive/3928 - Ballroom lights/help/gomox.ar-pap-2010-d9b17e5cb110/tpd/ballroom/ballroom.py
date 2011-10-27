#!/usr/bin/python
# -*- coding: utf8 -*-

from __future__ import division

import psyco
psyco.full()

import math


###########
# Helpers #
###########

def mod2pi(x):
    '''Devuelve un valor de angulo equivalente en [0, 2*pi).
    
    >>> import math
    >>> mod2pi(0.0)
    0.0
    >>> mod2pi(4 * math.pi)
    0.0
    >>> mod2pi(-math.pi)
    3.1415926535897931
    '''
    while x < 0:
         x += 2 * math.pi
    while x >= 2 * math.pi:
        x -= 2 * math.pi
    return x


def mod360(x):
    '''Devuelve un valor de angulo equivalente en [0, 360).
    
    >>> import math
    >>> mod360(0.0)
    0.0
    >>> mod360(360+180)
    180.0
    >>> mod360(-180)
    180.0
    '''
    while x < 0:
         x += 360.0
    while x >= 360.0 :
        x -= 360.0
    return x


##########
# Vector #
##########

class Vector:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, otro):
        return Vector(self.x + otro.x, self.y + otro.y)

    def __sub__(self, otro):
        return Vector(self.x - otro.x, self.y - otro.y)

    def __mul__(self, f):
        return Vector(self.x * f, self.y * f)

    def __rmul__(self, f):
        return self * f

    def __div__(self, f):
        return Vector(self.x / f, self.y / f)
    
    def __neg__(self):
        return Vector(self.x *-1 , self.y * -1)

    def __eq__(self, otro):
        return self.x == otro.x and self.y == otro.y

    def __repr__(self):
        return '''<Vector %s,%s>''' % (self.x, self.y)

    def __iter__(self):
        yield self.x
        yield self.y
    
    def __hash__(self):
        return hash((self.x,self.y))

    def dotP(self, otro):
        '''Computa el producto escalar de 2 vectores.
        
        >>> Vector(1,0).dotP(Vector(0,1))
        0.0
        >>> Vector(1,1).dotP(Vector(1,1))
        2.0
        '''

        return self.x * otro.x + self.y * otro.y

    def boundNorm(self, norma):
        '''Devuelve un vector idéntico a este pero con la norma
        acotada al rango [0, norma]

        >>> Vector(2,0).boundNorm(1)
        <Vector 1.0,0.0>
        >>> Vector(1,1).boundNorm(4)
        <Vector 1.0,1.0>
        >>> Vector(2,2).boundNorm(math.sqrt(2))
        <Vector 1.0,1.0>
        '''

        assert norma > 0
        norma_efectiva = min(norma, self.norma())
        factor = norma_efectiva / self.norma()
        return self * factor

    def flipY(self):
        '''Devuelve un vector idéntico a este con la coordenada
        Y invertida (útil para dibujar en la pantalla, que tiene el
        sistema de coordenadas con esta particularidad).
        '''
        return Vector(self.x, -self.y)

    def norma(self):
        '''Computa la norma cartesiana del vector.
        
        >>> Vector(1,1).norma()
        1.4142135623730951
        >>> Vector(1,0).norma()
        1.0
        >>> Vector(0,1).norma()
        1.0
        '''
        return math.sqrt(self.x**2 + self.y**2)

    def angulo(self):
        '''Computa el ángulo polar del vector (en radianes desde la recta y=0).

        >>> Vector(1,0).angulo()
        0.0
        >>> Vector(0,1).angulo()
        1.5707963267948966
        >>> Vector(0,-1).angulo()
        -1.5707963267948966
        '''
        if self.x == 0 and self.y == 0:
            return 0
        elif self.x >= 0:
            return math.asin(self.y/self.norma())
        else:
            return -math.asin(self.y/self.norma()) + math.pi
        
    def grados(self):
        '''Computa el ángulo polar del vector (en grados desde la recta y=0).

        >>> Vector(1,0).grados()
        0.0
        >>> Vector(0,1).grados()
        90.0
        >>> Vector(0,-1).grados()
        -90.0
        '''
        return math.degrees(self.angulo())

    def viento(self):
        '''Devuelve el viento correspondiente a este vector.

        >>> viento = Vector(10,10).viento()
        >>> viento
        <Viento 225.0º de 14.1kt>
        >>> Vector(1, 0).viento()
        <Viento 270.0º de 1.0kt>
        >>> Vector(-10, 0).viento()
        <Viento 90.0º de 10.0kt>
        '''
        return Viento(mod360(270 - self.grados()), self.norma())


##########
# Viento #
##########

class Viento:
    def __init__(self, direccion, intensidad):
        '''Construye un viento soplando desde la direccion indicada,
        con la intensidad indicada.

        >>> viento = Viento(0, 15)
        >>> viento.angulo
        4.7123889803846897
        >>> viento.x
        -2.7553642961003488e-15
        >>> viento.y
        -15.0
        '''

        assert 0 <= intensidad
        direccion = mod360(direccion)
        self.direccion = direccion
        self.intensidad = intensidad
        
        # Precalculo algunas cosas
        self.angulo = mod2pi(-math.radians(direccion) - math.pi/2)
        self.x = math.cos(self.angulo) * intensidad
        self.y = math.sin(self.angulo) * intensidad

    def vector(self):
        '''Devuelve el vector asociado a este viento.
        
        >>> vector = Viento(90,10).vector()
        >>> vector.x
        -10.0
        >>> vector.y
        1.2246063538223773e-15
        >>> vector.viento()
        <Viento 90.0º de 10.0kt>
        '''
        return Vector(self.x, self.y)

    def anguloIncidencia(self, vector_navegacion):
        '''Devuelve el ángulo de incidencia del viento sobre un
        barco que navega sobre vector_navegacion.
        
        >>> Viento(0, 10).anguloIncidencia(Vector(-1,1))
        0.78539816339744828
        >>> Viento(0, 10).anguloIncidencia(Vector(1,1))
        5.497787143782138
        '''
        return mod2pi(vector_navegacion.angulo() - (-self.vector()).angulo())
        
    def __repr__(self):
        return "<Viento %.1fº de %.1fkt>" % (self.direccion, self.intensidad)





inf = float('inf')

def intersect_lines(l1, l2):

    p1 = l1[0]
    p2 = l1[1]
    p3 = l2[0]
    p4 = l2[1]

    den = (p4.y-p3.y)*(p2.x-p1.x) - (p4.x-p3.x)*(p2.y-p1.y)

    ua_num = (p4.x-p3.x)*(p1.y-p3.y) - (p4.y-p3.y)*(p1.x-p3.x)
    ub_num = (p2.x-p1.x)*(p1.y-p3.y) - (p2.y-p1.y)*(p1.x-p3.x)

    if abs(den) == 0:
        if abs(ua_num - ub_num) == 0 and \
           abs(ub_num) == 0:
            return max(p1, p2, key=lambda v: v.norma())

        return None
    
    ua = ua_num/den
    ub = ub_num/den

    if ub >= 0:
        return ua
    
    return None



def rango_oscurecido(inicio, fin, src, centro, radio):
    '''
    Devuelve el rango (en distancia de 0 a ||$inicio-$fin||)
    que se encuentra a la sombra de una columna de radio $radio,
    ubicada en $centro e iluminada por una fuente de luz puntual en $src.
    '''

    bisectriz = centro - src
    p = math.asin(radio/bisectriz.norma())
    alpha = bisectriz.angulo()
    
    d1 = Vector(math.cos(alpha + p), math.sin(alpha + p))
    d2 = Vector(math.cos(alpha - p), math.sin(alpha - p))

    p1 = intersect_lines((inicio, fin), (src, src + d1))
    p2 = intersect_lines((inicio, fin), (src, src + d2))

    unidad = (fin - inicio).norma()

    # Se sabe que los puntos de interseccion estan ordenados correctamente
    # porque el angulo de diferencia entre las semirectas es menor a 180,
    # entonces no es necesario chequearlo.
    if p1 is None:
        if p2 is None:
            return (0.0, 0.0)
        else:
            res = (0.0, p2)
    else:
        if p2 is None:
            res = (p1, 1.0)
        else:
            res = (p1, p2)

    res_bounded = interseccion_intervalos(res, (0.0, 1.0))
    p = (res_bounded[0] * unidad, res_bounded[1] * unidad)
    return p


def interseccion_intervalos(i1, i2):
    '''Devuelve los extremos del intervalo interseccion entre i1 y i2.
    
    >>> interseccion_intervalos((1,3),(2,8))
    (2, 3)
    >>> interseccion_intervalos((1,2), (5,6))
    (5, 5)
    >>> interseccion_intervalos((-inf, 8), (6, inf))
    (6, 8)
    '''

    p1, p2 = i1
    p3, p4 = i2

    d = (max(p1, p3), min(p2, p4))
    if d[1] < d[0]:
        return (d[0], d[0])
    else:
        return d


def reduce_interseccion(l):
    cand = (-inf, inf)
    for e in l:
        cand = interseccion_intervalos(cand, e)
    return cand


def reduce_union(l):
    '''Devuelve la union de la lista de intervalos l
    
    >>> reduce_union([(1,3), (2,5)])
    [(1, 5)]
    >>> reduce_union([(1,3), (4, 6)])
    [(1, 3), (4, 6)]
    >>> reduce_union([(1,3), (4, 6), (5, 6)])
    [(1, 3), (4, 6)]
    >>> reduce_union([(1,3), (4, 6), (5, 7)])
    [(1, 3), (4, 7)]
    '''

    ordenados = l[:]
    ordenados.sort(key=lambda x: x[0])
    
    if len(l) == 0:
        return []
    
    res = []
    cand = ordenados[0]
    for i in range(1, len(l)):
        otro = ordenados[i]
        if otro[0] > cand[1] and otro[0] != otro[1]:
            res.append(cand)
            cand = otro
        else:
            if otro[1] > cand[1]:
                cand = (cand[0], otro[1])

    res.append(cand)
    return res
      

# Asume que los intervalos estan ordenados por punto de comienzo
def invertir_rango(ints, fin):
    '''
    Invierte el conjunto de segmentos (minimo y ordenado) para 
    tomar su complemento.

    >>> invertir_rango([(3,4)], 8)
    [(0, 3), (4, 8)]
    >>> invertir_rango([(3,4),(6,8)], 8)
    [(0, 3), (4, 6)]
    >>> invertir_rango([(0,2), (5,6)], 10)
    [(2, 5), (6, 10)]
    '''

    if len(ints) == 0:
        return [(0, fin)]

    invertido = []
    if ints[0][0] > 0:
        invertido.append((0, ints[0][0]))

    for i in range(1, len(ints)):
        invertido.append((ints[i-1][1], ints[i][0]))
    
    if ints[-1][1] < fin:
        invertido.append((ints[-1][1], fin))

    return invertido





def resolver(lamparas, columnas, max_x, max_y):
    
    paredes = ((Vector(0,0), Vector(0,max_y)),
               (Vector(0, max_y), Vector(max_x, max_y)),
               (Vector(max_x, max_y), Vector(max_x, 0)),
               (Vector(max_x, 0), Vector(0,0)))


    total = 0
    for p in paredes:
        luces_pared = []
        for l in lamparas:
            zonas_tapadas = []
            for c in columnas:
                r = rango_oscurecido(p[0], p[1], l, c[0], c[1])
                zonas_tapadas.append(r)
            zona_iluminada = invertir_rango(reduce_union(zonas_tapadas), (p[1]-p[0]).norma())
            luces_pared += zona_iluminada
        luces_pared = reduce_union(luces_pared)

        s = sum(map(lambda x: x[1] - x[0], luces_pared))
        total += s

    print "%.4f" % total



def main():
    import sys

    while True:
        nl, nc, max_x, max_y = map(int, sys.stdin.readline().strip().split())
        
        if nl == nc == max_x == max_y == 0:
            break
        
        lamparas = []
        for i in range(nl):
            lampara = Vector(*(map(float, sys.stdin.readline().strip().split())))
            lamparas.append(lampara)
    
        columnas = []
        for i in range(nc):
            x, y, r = map(float, sys.stdin.readline().strip().split())
            columnas.append((Vector(x,y), r))
       
        resolver(lamparas, columnas, max_x, max_y)



if __name__ == '__main__':
    #import doctest
    #doctest.testmod()

    main()
