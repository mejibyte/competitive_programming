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

class Solution {
public:
    int jump(const vector<int>& nums) {
      int n = nums.size();
      vector<int> dp(n);
      dp[n - 1] = 0;
      for (int i = n - 2; i >= 0; --i) {
        dp[i] = INT_MAX / 2;
        for (int j = i + 1; j <= i + nums[i] and j < n; ++j) {
          dp[i] = min(dp[i], 1 + dp[j]);
        }
      }
      return dp[0];
    }
};

int main(){
    Solution s;

    auto m = s.jump({2,3,1,1,4});
    D(m);
    return 0;
}
