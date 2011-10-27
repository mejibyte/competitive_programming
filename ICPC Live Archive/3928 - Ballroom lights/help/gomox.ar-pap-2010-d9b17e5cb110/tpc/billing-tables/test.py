#!/usr/bin/python
import random
import os

MAXLEN = 4

def ranp(n):
  return ''.join([random.choice('0123456789') for i in range(n)])

def ranincr(n):
  return random.randint(0, 10**(n / 2))

def rango(n):
  while True:
    s1 = ranp(n)
    s2 = str(int(s1) + ranincr(n))
    if len(s2) != len(s1): continue
    i = 0
    while i < len(s1) and s1[i] == s2[i]:
      i += 1
    while i > 0 and random.choice([0, 1, 1, 1]) == 0:
      i -= 1
    s1, s2 = s1[:i] + s1[i:], s2[i:]
    if s2 == '':
      return s1, s1
    else:
      return s1, s2

def plan():
  return random.choice(['nenuco', 'roque', 'moniche', 'mifus', 'invalid'])

def gentabla():
  tabla = []
  for i in range(random.randint(1, 20)):
    s1, s2 = rango(random.randint(1, MAXLEN))
    p = plan()
    tabla.append((s1, s2, p))
  return tabla

def pad(num, P='0'):
  return num + (10 - len(num)) * P

def genstrs(l):
  if l == 0:
    yield ''
    return
  for r in genstrs(l - 1):
    for dig in range(10):
      yield r + str(dig)

def enumerar(fr, to, pref):
  pot = 1
  while fr + pot <= to:
    while fr + pot <= to and fr % (pot * 10) != 0:
      yield decor(fr / pot, pref)
      fr += pot
    pot *= 10
    pref -= 1
  while fr + pot > to:
    pot /= 10
    pref += 1
  while pot > 0: # and fr + pot <= to:
    while fr + pot <= to and to % (pot * 10) != 0:
      yield decor(fr / pot, pref)
      fr += pot
    pot /= 10
    pref += 1

def readtabla(a):
  f = file(a, 'r')
  ls = f.readlines()
  tabla = []
  for x in map(lambda l: l.strip(' \t\r\n').split(' '), ls[1:]):
    tabla.append((x[0], x[2], x[3]))
  f.close()
  return tabla

def decor(x, k):
  if k == 0:
    #return '...'
    return ''
  else:
    xx = str(x)
    assert len(xx) <= k
    return (k - len(xx)) * '0' + xx #+ '...'

def resultado_referencia1(tabla):
  #tabla = tabla[::-1]
  tabla1 = []
  for start, end, plan in tabla:
    tabla1.append((pad(start), pad(start[:-len(end)] + end, '9'), plan))
  tabla = tabla1
  
  tabla2 = {}
  def cuanto_da(n):
    n = pad(n)
    if n in tabla2:
      return tabla2[n]
    for start, end, plan in tabla:
      if start <= n and n <= end:
        tabla2[n] = plan
        return plan
    tabla2[n] = 'invalid'
    return 'invalid'

  for n in genstrs(MAXLEN):
    cdn = cuanto_da(n)
    #print n, cdn
    yield n, cdn

def resultado_referencia(tabla):
  res = []
  l = list(resultado_referencia1(tabla))
  l.append((int(l[-1][0]) + 1, 'invalid'))
  i0 = None
  v0 = None
  for i, v in l:
    if v != v0:
      if v0 not in [None, 'invalid']:
        ###print int(i0), int(i), v0
        for j in enumerar(int(i0), int(i), len(i0)):
          res.append((j, v0))
      v0 = v
      i0 = i
  g = file('tmp.referencia', 'w')
  g.write('%i\n' % (len(res),))
  for x, y in res:
    g.write('%s %s\n' % (x, y,))
  g.close()
  return res

def resultado_implementacion(tabla):
  f = file('tmp.in', 'w')
  f.write('%i\n' % (len(tabla),))
  for start, end, plan in tabla:
    f.write('%s - %s %s\n' % (start, end, plan))
  f.close()
  os.system('cat tmp.in | ./main > tmp.implementacion')
  f = file('tmp.implementacion', 'r')
  ls = map(lambda x: tuple(x.strip(' \t\r\n').split(' ')), f.readlines()[1:])
  f.close()
  return ls

def main():
  tabla = gentabla()
  #tabla = readtabla('tmp.in')
  ###print tabla
  l1 = resultado_referencia(tabla)
  l2 = resultado_implementacion(tabla)
  print l1
  print l2
  if l1 != l2:
    print 'falla'
    assert False

while True:
  main()

