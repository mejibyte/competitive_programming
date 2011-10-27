/*
  10310 - SuperSale
  UVa Online Judge

  Andrés Mejía-Posada
  Accepted
 */

#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define MAXC 30
#define MAXN 1000

int dp[MAXN][MAXC+1];

int main(){
  int T, n, i, j;
  scanf("%d", &T);
  while (T--){
    scanf("%d", &n);
    int w[n], v[n];
    for (i=0; i<n; ++i){
      scanf("%d %d", &v[i], &w[i]);
    }

    for (j=0; j<=MAXC; ++j){
      dp[0][j] = (j < w[0] ? 0 : v[0]);
    }

    for (i=1; i<n; ++i){
      dp[i][0] = 0;
      for (j=1; j<=MAXC; ++j){
        dp[i][j] = dp[i-1][j];
        if (j - w[i] >= 0){
          dp[i][j] = MAX(dp[i][j], dp[i-1][j-w[i]] + v[i]);
        }
      }
    }

    int g, c, answer = 0;
    scanf("%d", &g);
    while (g--){
      scanf("%d", &c);
      answer += dp[n-1][c];
    }
    printf("%d\n", answer);
  }
  return 0;
}
