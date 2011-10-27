/*
  Problem: 10081 - Tight words
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

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

#define D(x) cout << #x " is " << x << endl

 double dp[101][10];

int main(){

  for (int k, n; scanf("%d %d", &k, &n)==2; ){

    for (int last=0; last<=9; ++last) dp[1][last] = 1.0/(k+1);

    for (int len=2; len<=n; ++len){
      for (int last=0; last<=k; ++last){
        dp[len][last] = dp[len-1][last];
        if (last > 0) dp[len][last] += dp[len-1][last-1];
        if (last < k) dp[len][last] += dp[len-1][last+1];
        dp[len][last] /= k+1;
      }
    }

    double ans = 0;
    for (int last=0; last<=k; ++last) ans += dp[n][last];
    printf("%.5lf\n", 100.0 * ans);
  }


  return 0;
}
