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

const int oo = int(1e6);

class Solution {
public:
    string minWindow(string s, string t) {
      int n = s.size();
      int m = t.size();
      vector<vector<int>> dp(n + 1, vector<int>(m + 1, oo));

      dp[n][m] = 0;
      for (int i = n - 1; i >= 0; --i) {
        dp[i][m] = 0;
        for (int j = m - 1; j >= 0; --j) {
          dp[i][j] = dp[i+1][j] + 1;
          if (s[i] == t[j]) {
            int option = dp[i+1][j+1] + 1;
            if (option <= dp[i][j]) {
              dp[i][j] = option;
            }
          }
        }
      }
      int best = 0;
      for (int i = 1; i < n; ++i) {
        if (dp[i][0] < dp[best][0]) {
          best = i;
        }
      }
      if (dp[best][0] >= oo) return "";
      return s.substr(best, dp[best][0]);
    }
};
int main(){
    Solution s;
    auto ans = s.minWindow("abcdebdde", "bde");
    D(ans);
    ans = s.minWindow("x", "y");
    D(ans);
    ans = s.minWindow("xazxbz", "xz");
    D(ans);
    //for (auto k : ans) D(k);
    return 0;
}
