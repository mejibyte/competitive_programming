//10373 - The brick stops here
#include <iostream>
using namespace std;

const int MAXM = 20, MAXN = 200, MAXSUM = MAXM * 1000;

unsigned int dp[MAXM+1][MAXSUM+1];
int w[MAXN], p[MAXN];

void check(bool b){
  while (!b);
}

int main(){
  int runs;
  scanf("%d", &runs);
  for (int run=0; run<runs; ++run){
    if (run) printf("\n");

    int n, sum = 0;
    scanf("%d", &n);
    for (int i=0; i<n; ++i){
      scanf("%d %d", &w[i], &p[i]);
      check(1 <= w[i] && w[i] <= 999);
      sum += w[i];
    }

    sum = std::min(sum, MAXSUM);
    for (int i=0; i<=MAXM; ++i)
      for (int j=0; j<=sum; ++j)
        dp[i][j] = INT_MAX;

    dp[0][0] = 0;
    dp[1][w[0]] = p[0];
    for (int k=1; k<n; ++k){
      //en este momento, dp[i][j] = minimo precio en que puedo escoger i ladrillos entre los ladrillos [0..k]
      //tal que la suma neta de cobre sea j.
      for (int i=MAXM; i>=1; --i){ //i va descendiendo para no ir a usar el mismo ladrillo dos veces.
        for (int j=0; j <=sum; ++j){
          if (j - w[k] >= 0){
            dp[i][j] = std::min(dp[i][j], dp[i-1][j-w[k]] + p[k]);
          }
        }
      }
    }

    int c;
    scanf("%d", &c);
    while (c--){
      int m, cmin, cmax;
      scanf("%d %d %d", &m, &cmin, &cmax);
      check(0 <= m && m <= 20);
      check(1 <= cmin && cmin <= 999);
      check(1 <= cmax && cmax <= 999);

      unsigned int answer = INT_MAX;
      for (int j=m*cmin; j<=m*cmax && j <=sum; ++j){
        //if (answer > dp[m][j]) printf("better answer: dp[%d][%d] = %u\n", m, j, dp[m][j]);
        answer = std::min(answer, dp[m][j]);
      }
      if (answer < INT_MAX){
        printf("%u\n", answer);
      }else{
        printf("impossible\n");
      }
    }
  }
  return 0;
}
