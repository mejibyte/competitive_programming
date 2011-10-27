/*
  Accepted
 */
#include <stdio.h>

const int MAXN = 10000, MAXK = 100;

bool dp[MAXN][MAXK];

int main(){
  int cases;
  scanf("%d", &cases);
  while (cases--){
    int n, k;
    scanf("%d %d", &n, &k);
    int a[n];
    for (int i=0; i<n; ++i){
      for (int j=0; j<k; ++j){
        dp[i][j] = false;
      }
      scanf("%d", &a[i]);
    }

    if (a[0] < 0) a[0] *= -1;
    dp[0][a[0]%k] = true;
    for (int i=0; i<n-1; ++i){
      for (int j=0; j<k; ++j){
        if (dp[i][j]){
          int t = j + a[i+1];
          if (t < 0) t *= -1;
          dp[i+1][t%k] = true;

          t = j - a[i+1];
          if (t < 0) t *= -1;
          dp[i+1][t%k] = true;
        }
      }
    }

    printf((dp[n-1][0]?"D":"Not d"));
    puts("ivisible");
  }
  return 0;
}
