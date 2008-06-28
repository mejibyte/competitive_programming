/*
  Problem: 910 - TV Game

  Author: Andrés Mejía-Posada

  Method: Dynamic programming

  Accepted.
 */
#include <iostream>
#include <set>

using namespace std;

int main(){
  int N;
  while (cin >> N){
    int g[N][2]; //g[i][j] = A donde me lleva el nodo i con la entrada j
    set<int> special;
    for (int i=0; i<N; ++i){
      char a, b, c, d;
      cin >> a >> b >> c >> d;
      a -= 'A', b -= 'A', c -= 'A';
      g[a][0] = b;
      g[a][1] = c;
      if (d == 'x'){
        special.insert(a);
      }
    }
    int m;
    cin >> m;

    unsigned long long dp[m+1][N]; //dp[i][j] = cantidad de caminos de longitud i que terminan en el nodo j
    memset(dp, 0ULL, sizeof dp);
    dp[0][0] = 1ULL; //Para llegar al nodo A hay un solo camino
    for (int i=0; i<m; ++i){
      for (int j=0; j<N; ++j){
        dp[i+1][g[j][0]] += dp[i][j];
        dp[i+1][g[j][1]] += dp[i][j];
      }
    }

    unsigned long long answer = 0;
    for (int i=0; i<N; ++i){
      if (special.count(i)){
        answer += dp[m][i];
      }
    }
    cout << answer << endl;
  }
  return 0;
}
