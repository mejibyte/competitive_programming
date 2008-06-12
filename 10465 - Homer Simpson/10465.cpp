#include <iostream>

#define MAX(a,b) ((a)>(b)?(a):(b))

using namespace std;

//Este problema se puede modelar como una mochila de capacidad t.
//Tengo objetos de tamaño m y n.
//Encontrar cuál es la capacidad máxima que puedo usar de la mochila.
//(O en otras palabras, minimizar el espacio desperdiciado de la mochila)
//Encontrar la mayor cantidad posible de objetos que me permitan usar la
//capacidad máxima posible de la mochila.


//x[i] : Maxima capacidad que puedo gastar con los objetos m y n que no exceda i
//y[i] : Maxima cantidad de objetos que puedo utilizar para gastar una capacidad x[i]
int x[10001], y[10001];

int main(){
  int m, n, t;
  while (cin >> m >> n >> t){
    x[0] = 0; //La maxima capacidad que puedo utilizar que no exceda 0 es 0, porque 1 < m,n 
    y[0] = 0; //Para lograrlo utilizo 0 objetos
    for (int i=1; i<=t; ++i){
      x[i] = x[i-1]; //Puedo usar al menos la misma capacidad que podía antes...
      y[i] = y[i-1]; //Utilizando la misma cantidad de objetos que podía antes...

      if (i-m >= 0 && x[i-m] + m <= i){
	if (x[i-m] + m > x[i]){ //Si la capacidad que gasto usando el objeto m es mayor que la actual...
	  x[i] = x[i-m] + m;
	  y[i] = y[i-m] + 1;
	}
      }
      if (i-n >= 0 && x[i-n] + n <= i){
	if (x[i-n] + n > x[i]){ ////Si la capacidad que gasto usando el objeto n es mayor que la actual..
	  x[i] = x[i-n] + n;
	  y[i] = y[i-n] + 1;
	}
      }

      if (i-n >= 0 && i - m >= 0 &&
	  x[i-n] + n == x[i-m] + m){ //Si gasto la misma capacidad escogiendo como ultimo objeto m o n...
	y[i] = MAX(y[i-m] + 1, y[i-n] + 1); //entonces la cantidad de objetos debe ser la máxima de las dos posibles
      }
    }
    //cout << "La maxima capacidad que puedo usar es: " << x[t] << endl;
    //cout << "Utilizo " << y[t] << " objetos" << endl;
    cout << y[t];
    if (x[t] < t){
      cout << " " << t - x[t] << endl;
    }else
    cout << endl;
  }
  return 0;
}
