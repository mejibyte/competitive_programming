#include <stdio.h>
#include <algorithm>

using namespace std;

#define MAXN 19

int n, base;
long long cache[MAXN+1][MAXN+1];

long long a(const int &i, const int &j){
  if (i == n && j == 0) return 0;
  if (i == n && j == 1) return base;

  if (cache[i][j] == -1){
    long long &r = cache[i][j] = 0;

    if (i < j){
      for (int k=i; k<j; ++k){
        r = max(r, a(i, k) + a(k+1, j));
      }
    }else{ //i >= j
      long long x = 0, y = 0;
      if (i < n){
        for (int k=i+1; k<=n; ++k){
          x = max(x, a(k, 1) + a(k, j));
        }
      }

      if (j > 0){
        for (int k=1; k<j; ++k){
          y = max(y, a(i, k) + a(n, k));
        }
      }
      r = x + y;
    }
  }
  return cache[i][j];
}

int main(){
  while (scanf("%d %d", &n, &base) == 2){
    memset(cache, -1, sizeof cache);
    printf("%lld\n", a(1, n));
  }
  return 0;
}
