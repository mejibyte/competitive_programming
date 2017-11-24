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

// Accepted.
class Solution {
public:
    int minPatches(const vector<int>& nums, long long n) {
      const int MAXK = 64;
      vector<vector<long long> > dp(nums.size() + 1, vector<long long>(MAXK, 0));
      // dp[i][k] = The maximum range I can cover if I have used
      // the first i nums and have added exactly k new nums.
      //
      // Examples:
      //    dp[0][0] = 0 (if I haven't used any numbers and I haven't added even a single
      //                  one, I can't even form 1)
      //    dp[0][1] = 1 (I haven't used any numbers but I "bought" 1, the maximum range I can cover
      //                  is therefore [0, 1])
      //    dp[0][2] = 3 (I have bought two numbers - 1 and 2. With those, I can represent all
      //                  the entire range [0,3])
      //    dp[0][3] = 7 (I have bought 1, 2, 4 and can form all numbers in [0..7]).
      for (int k = 1; k < MAXK; ++k) {
        dp[0][k] = 2 * dp[0][k - 1] + 1;
      }

      for (int i = 1; i <= nums.size(); ++i) {
        int num = nums[i - 1];
        for (int k = 0; k < MAXK; ++k) {
          dp[i][k] = dp[i - 1][k]; // I can just ignore this number and have the same results.
          if (dp[i - 1][k] >= num - 1) {
            dp[i][k] = dp[i - 1][k] + num; // I'm going to use this number and combine it with every number in the best range I could already form without this number.
          }
          if (k - 1 >= 0) {
            dp[i][k] = max(dp[i][k], 2 * dp[i][k - 1] + 1); // I am going to buy the next number in the range.
          }
        }
      }

      for (int k = 0; k < MAXK; ++k) {
        D(k);
        D(dp[nums.size()][k]);
        if (dp[nums.size()][k] >= n) return k;
      }
      assert(false);
      return -1;
    }
};

int main(){
    Solution s;

    D(s.minPatches({1, 3}, 6));

    D(s.minPatches({1, 5, 10}, 20));

    D(s.minPatches({1, 2, 2}, 5));
    return 0;
}
