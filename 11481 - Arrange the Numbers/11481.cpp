/*
  Problem: 11481 - Arrange the Numbers
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

  Algorithm: Inclusion-exclusion principle

  Accepted.
 */

using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>

const int N = 1000, mod = 1000000007;

long long choose[N+1][N+1], fact[N+1];

void prepare(){
  /* Factorials */
  fact[0] = fact[1] = 1;
  for (int i=2; i<=N; ++i) fact[i] = (fact[i-1]*i)%mod;

  /* Binomial coefficients */
  for (int i=0; i<=N; ++i) choose[i][0] = choose[i][i] = 1;
  for (int i=1; i<=N; ++i)
    for (int j=1; j<i; ++j)
      choose[i][j] = (choose[i-1][j-1] + choose[i-1][j])%mod;
}

int main(){
  prepare();

  int C, pizza = 1;
  scanf("%d", &C);
  while (C--){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    long long ans = 0;
    for (int i=0; i<=m-k; ++i){
      ans += (i & 1 ? -1 : 1) * (choose[m-k][i] * fact[n-k-i]) % mod;
      ans %= mod;
    }

    ans =  ((ans * choose[m][k]) % mod + mod) % mod;

    printf("Case %d: %lld\n", pizza++, ans);
  }
  return 0;
}
