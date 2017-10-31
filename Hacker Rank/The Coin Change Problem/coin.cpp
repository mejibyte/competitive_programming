// Andrés Mejía
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <bitset>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>
using namespace std;

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cerr << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////


const int MAXC = 55;
const int MAXM = 255;

long long dp[MAXC][MAXN];

int main(){
  int want;
  int coins;
  cin >> want >> coins;
  vector<long> c(coins);
  for(int c_i = 0; c_i < coins; c_i++){
     cin >> c[c_i];
  }
  memset(dp, 0, sizeof dp);
  dp[0][0] = 1;
  for (int i = 0; i < c.size(); ++i) {
    for (int m = 0; m <= want; ++m) {
      if (i - 1 >= 0) dp[i][m] += dp[i - 1][m];
      if (m - c[i] >= 0) dp[i][m] += dp[i][m - c[i]];
    }
  }
  cout << dp[coins - 1][want] << endl;

  return 0;
}
