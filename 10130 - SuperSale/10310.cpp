/*
  10310 - SuperSale
  UVa Online Judge

  Andrés Mejía-Posada
  Accepted
 */
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

const int MAXC = 30, MAXN = 1000;

/*
  Classical 0-1 knapsack.
  dp[i][j] = Using first i objects, maximum value that can be selected not exceeding weight j.
 */

int dp[MAXN][MAXC+1];

int main(){
  int T;
  cin >> T;
  while (T--){
    int n;
    cin >> n;
    int w[n], v[n];
    for (int i=0; i<n; ++i){
      cin >> v[i] >> w[i];
      assert(1 <= v[i] && v[i] <= 100);
      assert(1 <= w[i] && w[i] <= 30);
    }

    for (int j=0; j<=MAXC; ++j){
      dp[0][j] = (j < w[0] ? 0 : v[0]);
    }

    for (int i=1; i<n; ++i){
      dp[i][0] = 0;
      for (int j=1; j<=MAXC; ++j){
        dp[i][j] = dp[i-1][j];
        if (j - w[i] >= 0){
          dp[i][j] = max(dp[i][j], dp[i-1][j-w[i]] + v[i]);
        }
      }
    }

    int g, c, answer = 0;
    cin >> g;
    while (g--){
      cin >> c;
      assert(1 <= c && c <= 30);
      answer += dp[n-1][c];
    }
    assert(answer > 0);
    cout << answer << endl;
  }
  return 0;
}
