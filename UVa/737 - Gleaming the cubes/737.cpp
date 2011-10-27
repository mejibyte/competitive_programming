#include <iostream>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

using namespace std;

//Describe el segmento de recta que es >= a min y <= a max
struct recta{
  int min, max;
  //recta(int mn, int mx){min = mn; max = mx;}
};

recta make_recta(int mn, int mx){  recta r;  r.min = mn;  r.max = mx;  return r; }

//Describe un cubo en términos de sus regiones en cada plano
struct cubo{
  recta x,y,z;
  cubo(recta X, recta Y, recta Z){x = X; y = Y; z = Z;}
};


//Retorna verdadero si puede calcular la interseccion de dos rectas
//Almacena el resultado en c
bool interseccion(recta a, recta b, recta &c){
  if (a.min > b.max || b.min > a.max) return false;
  c.min = MAX(a.min,b.min);
  c.max = MIN(a.max,b.max);
  return true;
}

bool interseccion(cubo a, cubo b, cubo &c){
  if (!interseccion(a.x, b.x, c.x)) return false;
  if (!interseccion(a.y, b.y, c.y)) return false;
  if (!interseccion(a.z, b.z, c.z)) return false;
  return true;
}


int main(){
  int noCubos;
  cin >> noCubos;
  while (noCubos > 0){
    bool vacio = false;
    int x,y,z,r;
    cin >> x >> y >> z >> r;
    cubo resultado(make_recta(x, x+r), make_recta(y, y+r), make_recta(z, z+r));  

    for (int i=1; i<noCubos; ++i){
      cin >> x >> y >> z >> r;
      cubo temp(make_recta(x, x+r), make_recta(y, y+r), make_recta(z, z+r));  
      if (!interseccion(resultado, temp, resultado)){
	cout << "0\n";
	vacio = true;
      }
    }

    if (!vacio){
      cout << (resultado.x.max - resultado.x.min)*(resultado.y.max - resultado.y.min)*(resultado.z.max - resultado.z.min) << endl;
    }
    cin >> noCubos;
  }
  return 0;
}
