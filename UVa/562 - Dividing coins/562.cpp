/*
/*
  Solution to problem: 562 - Dividing coins
  (From the UVa Online Judge
  http://icpcres.ecs.baylor.edu/onlinejudge/
  )

  Author: Andres Mejia-Posada
  http://blogaritmo.factorcomun.org

  Accepted.
 */
#include <stdio.h>
#include <stdlib.h>

int main(){
  int n, s, c;
  scanf("%d", &n);
  while (n--){
    scanf("%d", &c);
    int m[c];
    s = 0;
    for (int i=0; i<c; ++i){
      scanf("%d", &m[i]);
      s += m[i];
    }

    bool dp[c][s+1];
    for (int d=0; d<=s; ++d)
      dp[0][d] = false;

    if (c == 0)
      printf("0\n");
    else {
      dp[0][m[0]] = true;
      for (int i=1; i<c; ++i)
        for (int d=0; d<=s; ++d){
          dp[i][d] = dp[i-1][abs(d - m[i])];
          if (d + m[i] <= s)
            dp[i][d] |= dp[i-1][d + m[i]];
        }

      for (int d=0; d<=s; ++d)
        if (dp[c-1][d]){
          printf("%d\n", d);
          break;
        }
    }
  }
  return 0;
}
