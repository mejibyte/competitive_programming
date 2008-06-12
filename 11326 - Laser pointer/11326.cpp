#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

int main(){
  int casos;
  cin >> casos;
  while (casos--){
    int L, W, angleGrad;
    cin >> L >> W >> angleGrad;
    //Pasarlo a radianes (2*acos(0) == PI)
    double angle = 2*acos(0)*angleGrad/180.0;
    if (angle == 0) printf("1.000\n");
    else{
      double x = W / tan(angle);
      int k = 1;
      while (x*k <= L) ++k;
      double y = L - (k-1)*x;
      double h;
      if (k % 2 == 0) h = W - y*tan(angle);
      else h = y*tan(angle);
      double s = y / cos(angle);
      double resultado = W/sin(angle)*(k-1);
      resultado += s;
      resultado /= sqrt(h*h + L*L);
      
      printf("%.3f\n", resultado);
    }
  }
  return 0;
}
