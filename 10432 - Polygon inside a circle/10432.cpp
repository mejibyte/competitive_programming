#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cassert>

using namespace std;

const double pi = 2*acos(0);

int main(){
  double r;
  int n;
  while (cin >> r >> n){
    assert(r > 0);
    assert(n > 2);
    double anguloInterno = (pi - (2*pi / n)); // 180 - (360/n)
    anguloInterno /= 2;
    //cout << anguloInterno * 180.0 / pi << endl;
    double anguloFaltante = pi - 2*anguloInterno;
    //cout << anguloFaltante * 180.0 / pi << endl;
    double b = r * sin(anguloFaltante) / sin(anguloInterno); 
    //cout << b << endl;
    double h = r*r - b*b/4;
    h = sqrt(h);
    double resultado = b*h/2 * n;
    printf("%.3f\n", resultado);
  }
  return 0;
}
