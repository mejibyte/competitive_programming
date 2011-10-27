#include <iostream>
using namespace std;

long f(long x){
  if (x == 0) return 0;
  long raiz = 1;
  while (raiz*raiz <= x) ++raiz;
  --raiz;
  long suma = raiz * raiz;
  long terminos = 2*raiz-1;
  long diferencia = x - suma;
  long i = raiz;
  while (diferencia > 0){
    if (diferencia - i >=0){
      diferencia -= i;
      ++terminos;
    }else --i;
  }
  return terminos;

}

int main(){
  int n;
  cin >> n;
  while (n-- > 0){
    long x, y;
    cin >> x >> y;
    cout << f(y-x) << endl;
  }
  return 0;
}
