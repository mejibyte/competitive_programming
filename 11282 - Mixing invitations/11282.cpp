/*
  Problem: 11282 - Mixing invitations
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

  Algoritm: Combinatorics formula
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

const int N = 20;

long long choose[N+1][N+1], d[N+1]; //d[i] = Number of derangements if i elements.

int main(){
    /* Binomial coefficients */
  for (int i=0; i<=N; ++i) choose[i][0] = choose[i][i] = 1;
  for (int i=1; i<=N; ++i)
    for (int j=1; j<i; ++j)
      choose[i][j] = choose[i-1][j-1] + choose[i-1][j];

  /* Derangements */
  d[0] = 1, d[1] = 0;
  for (int i=2; i<=N; ++i) d[i] = (i-1)*(d[i-2] + d[i-1]);

  int n, m;
  while (cin >> n >> m){
    long long ans = 0;
    for (int k=0; k<=m; ++k) ans += choose[n][k] * d[n-k];
    cout << ans << endl;
  }
  return 0;
}

/*
  Explanation: Let f(n, k) = Number of permutations of n elements
  such that exactly k of them are in their correct position. For
  example, f(3, 1) = 3 which are {1,3,2}, {3,2,1} and {2,1,3}.
  Then the answer is sum for every 0 <= k <= m of f(n, k).

  Let D(n) = Numbers of derangenents of n elements. Note that for
  every n we have f(n, 0) = D(n). And in general, 

  f(n, k) = choose(n, k) * D(n - k)

  The idea behind this is that we "nail" k elements from the whole
  sequence of n elements in choose(n, k) ways and for each possi-
  bility we disorder completely the missing n - k elements in
  D(n - k) ways.

  D(i) is computed using a recurrent function, although could also
  be found using inclusion-exclusion principle.
 */
