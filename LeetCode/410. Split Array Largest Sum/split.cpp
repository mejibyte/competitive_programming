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

const long long oo = LLONG_MAX / 2;

class Solution {
public:
    int splitArray(const vector<int>& nums, int m) {
      int n = nums.size();
      vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, oo));
      dp[0][0] = 0;
      for (int i = 1; i <= n; ++i) {
        long long num = nums[i - 1];
        for (int k = 1; k <= m; ++k) {
          long long sum = 0;
          for (int from = i; from >= 1; --from) {
            sum += nums[from - 1];

            long long option = max(dp[from - 1][k - 1], sum);
            dp[i][k] = min(dp[i][k], option);
          }
        }
      }

      return dp[n][m];
    }
};

int main(){
    Solution s;
    auto ans = s.splitArray({7,2,5,10,8}, 2);
    D(ans);
    return 0;
}
