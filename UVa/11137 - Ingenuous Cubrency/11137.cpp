/*
  11137 - Ingenuous Cubrency [UVa Online Judge]
  Andrés Mejía-Posada [http://blogaritmo.factorcomun.org]

  Programación dinámica, coin change

  Aceptado por el juez.
 */
#include <iostream>

using namespace std;

const int COINS = 21, MONEY = 9999;

int coins[COINS];

/*
  dp[i][j] = Utilizando las primeras i monedas, de cuantas maneras puedo fomar exactamente j cubos?
 */
unsigned long long dp[COINS][MONEY+1];

int main(){
  for (int i=1; i<=COINS; ++i){
    coins[i-1] = i*i*i;
  }

  for (int i=0; i<COINS; ++i){
    dp[i][0] = 1ULL; //Cero cubos los puedo formar de una única manera: coger ninguna moneda.
    for (int j=1; j<=MONEY; ++j){
      dp[i][j] = 0ULL;
      if (i > 0) dp[i][j] += dp[i-1][j];
      if (j - coins[i] >= 0) dp[i][j] += dp[i][j - coins[i]];
    }
  }

  int n;
  while (cin >> n) cout << dp[COINS-1][n] << endl;


  return 0;
}
