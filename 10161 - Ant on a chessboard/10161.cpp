/*
  Problem: 10161 - Ant on a chessboard
  Andrés Mejía-Posada (andmej@gmail.com)
 */
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

int main(){
  int n;
  while (scanf("%d", &n) && n){
    int cascara = 1;
    while (n > cascara*cascara) cascara++;
    int empieza = (cascara-1)*(cascara-1)+1;
    int termina = cascara*cascara;
    int longitud = termina - empieza + 1;
    int posicion = n - empieza + 1;
    if (cascara & 1) posicion = longitud - posicion + 1;
    int fila, columna;
    int mitad = longitud / 2;
    if (posicion == mitad + 1) fila = columna = cascara;
    else if (posicion <= mitad){
      fila = cascara, columna = posicion;
    }else{
      columna = cascara, fila = longitud - posicion + 1;
    }
    printf("%d %d\n", columna, fila);
  }
  return 0;
}
