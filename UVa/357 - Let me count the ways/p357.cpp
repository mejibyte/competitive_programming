#include <iostream>

using namespace std;

#define M 3
int m[] = {1,2, 5};//, 10, 25, 50};

long long f(const int &n, const int &i){
  if (n < 0){
    printf("f(%d,%d) retornando 0\n", n, i);
    return 0;
  }
  if (n <= 1 || i == 1){
    printf("f(%d,%d) retornando 1\n", n, i);
    return 1;
  }
  long long r=0;
  for (int j=1; j<=M; ++j)
    r += f(n-m[j-1], j);
  printf("f(%d,%d) retornando %lld\n", n, i, r);
  return r;
}

long long f(const int &n){
  //printf("n es: %d\n", n);
  if (n < 0) return 0;
  if (n <= 1) return 1;

 
  int pisoMonetario = 9999;
  for (int i=M-1; n < pisoMonetario; --i)
    pisoMonetario = m[i];
  //pisoMonetario tiene la moneda más proxima hacia abajo

  //printf("pisoMonetario es: %d\n", pisoMonetario);

 long long r=0;
  for (int i=0; i<M; ++i){
    //printf("i es: %d\n", i);
    //printf("m[i] es: %d\n", m[i]);
    if (n - m[i] > pisoMonetario)
      r += f(n - m[i]);
  }
  return r;
  
}

int main(){
  int n;
  while (scanf("%d", &n) == 1){
    cout << f(n, M) << endl; 
  }
  return 0;
}
