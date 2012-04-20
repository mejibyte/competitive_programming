#include <cstdio>
using namespace std;

#define MAXN 30005

long long dp[MAXN];
int m[] = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};

int main(){
  dp[0] = 1;
  for (int i = 0; i < 11; ++i)
      for (int s = m[i]; s < MAXN; ++s)
        dp[s] += dp[s - m[i]];

  int d, c;
  while (scanf("%d.%d", &d, &c) == 2 && (d+c)){
    int amount = d*100 + c;
    printf("%3d.%.2d%17lld\n", d, c, dp[amount]);
  }
  return 0;
}

