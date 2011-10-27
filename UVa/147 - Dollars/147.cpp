//147 - Dollars [UVa Online Judge]
//Andrés Mejía-Posada [http://blogaritmo.factorcomun.org]
#include <stdio.h>

#define MAX 30000

unsigned long long dp[2][MAX+1];
//dp[i][j] = numero de maneras en que puedo formar j pesos usando las primeras i monedas
//(Tiene un truco: solo necesitamos la fila anterior así que no es necesario construir toda
//la tabla si no sólo dos filas)
int m[] = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};

int main(){
  dp[0][0] = dp[1][0] = 1LL;
  for (int i=0; i<11; ++i){
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

  int c, d, amount;
  while (scanf("%d.%d", &d, &c) == 2 && (d+c)){
    amount = d*100 + c;
    printf("%3d.%.2d%17llu\n", d, c, dp[10%2][amount]);
  }
  return 0;
}

