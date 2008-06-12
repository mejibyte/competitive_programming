#include <iostream>

using namespace std;

unsigned long long dp[1000001];

inline unsigned long long cuantosNuevos(unsigned long long n){
  if (n == 3) return 1;
  if (n == 4) return 2;
  if (n % 2 == 0) return (n*(n-2))/4;
  return cuantosNuevos(n-1) + (n-1)/2;
}

int main(){
  int n;
  dp[3] = 0;
  dp[4] = 1;
  for (int i=5; i<=1000000; ++i){
    dp[i] = dp[i-1] + cuantosNuevos(i-1);
  }
  while (scanf("%d", &n) == 1 && n > 2){
    printf("%llu\n", dp[n]);
  }
  return 0;
}
