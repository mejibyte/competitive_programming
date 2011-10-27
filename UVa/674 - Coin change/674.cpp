//647 - Coin change [UVa Online Judge]
//Andrés Mejía-Posada [http://blogaritmo.factorcomun.org]
#include <stdio.h>

#define MAX 7489

unsigned long long dp[2][MAX+1];
//dp[i][j] = numero de maneras en que puedo formar j pesos usando las primeras i monedas
//(Tiene un truco: solo necesitamos la fila anterior así que no es necesario construir toda
//la tabla si no sólo dos filas)
int m[] = {1, 5, 10, 25, 50};
int const coins = 5;

int main(){
  dp[0][0] = dp[1][0] = 1LL;
  for (int i=0; i<coins; ++i){
    for (int a=1; a<=MAX; ++a){
      dp[i%2][a] = 0;
      if (i > 0){
        dp[i%2][a] += dp[(i+1)%2][a];
      }
      if (a - m[i] >= 0){
        dp[i%2][a] += dp[i%2][a - m[i]];
      }
    }
  }

  int d;
  while (scanf("%d", &d) == 1){
    printf("%llu\n", dp[(coins-1)%2][d]);
  }
  return 0;
}

