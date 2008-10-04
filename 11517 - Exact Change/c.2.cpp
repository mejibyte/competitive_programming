/*
  Problem: 11517 - Exact Change
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

  Accepted
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

const int S = 10005, N = 105, oo = INT_MAX / 4;

int dp[2][S*N+1], c[N];

/*
dp[i][j] = Mínima cantidad de monedas para formar j pesos
utilizando las primeras i monedas. (0 <= i <= n)
*/

int main(){

  int C;
  cin >> C;
  while (C--){

    int price;
    cin >> price;

    int n;
    cin >> n;

    int sum = 0;
    c[0] = oo; // Don't fuck

    int cota = S*N;

    for (int i=1; i<=n; ++i){
      cin >> c[i];
      sum += c[i];

      if (c[i] >= price) cota = min(cota, c[i]);
    }

    cota = min(cota, sum);
    //sum = min(sum, price);

    dp[0][0] = 0;
    for (int j=1; j <= cota; ++j) dp[0][j] = oo;

    for (int i=1; i<=n; ++i){
      for (int j=0; j<=cota; ++j){
	dp[i%2][j] = dp[(i+1)%2][j];
	if (j - c[i] >= 0){
	  dp[i%2][j] = min(dp[i%2][j], dp[(i+1)%2][j-c[i]] + 1);
	}
      }
    }

    /*
    for (int i=0; i<=n; ++i){
      for (int j=0; j<=sum; ++j){
	printf("%10d ", dp[i][j]);
      }
      puts("");
    }    
    */

    for (int j=price; /*j <= sum*/; ++j){
      if (dp[n%2][j] < oo){
	cout << j << " " << dp[n%2][j] << endl;
	break;
      }
    }

  }

  return 0;
}
