#include <iostream>
#include <math.h>
using namespace std;

int dameFila(unsigned int n){
    return int(ceil(sqrt(n+1)));
}

int dameColumna(unsigned int n){
    int miFila = dameFila(n);
    int centro = miFila*(miFila-1);
    return n - centro;
}

const double altura = sqrt(3)/2.0;

double dameY(unsigned int a){
       double ay;
       int fila_a, columna_a;
       columna_a = dameColumna(a);
       fila_a = dameFila(a);
       if (fila_a & 1){
          ay = (fila_a-1)*altura;
          if (columna_a & 1) ay -= altura/3.0;
       }else{
          ay = altura*((fila_a-2) + 2.0/3.0);
          if (columna_a & 1) ay += altura/3.0;
       }
       return ay;
}

int main(){
    unsigned int a, b;
    double ax, ay, bx, by;
    while (cin >> a >> b){
          //cout << "fila de a es " << dameFila(a) << endl;
          //cout << "columna de a es " << dameColumna(a) << endl;
          ax = 0.5 * dameColumna(a);
          ay = dameY(a);
          
          bx = 0.5 * dameColumna(b);
          by = dameY(b);
          
          //cout << ax << ", " << ay << endl;
          printf("%.3f\n", hypot(ax-bx, ay-by));
    }
    return 0;
}
