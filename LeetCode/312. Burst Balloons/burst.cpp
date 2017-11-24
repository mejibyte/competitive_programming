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

const int MAXN = 500 + 2;
int memo[MAXN][MAXN];


class Solution {
public:
    int maxCoins(vector<int>& nums) {
      nums.insert(nums.begin(), 1);
      nums.push_back(1);
      int n = nums.size();
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          memo[i][j] = -1;
        }
      }
      return solve(nums, 1, n - 2);
    }

    int solve(vector<int>& a, int i, int j) {
      if (i > j) return 0;
      int n = a.size();
      assert(1 <= i and i <= n - 2);
      assert(1 <= j and j <= n - 2);

      if (memo[i][j] != -1) return memo[i][j];
      int best = 0;
      for (int k = i; k <= j; ++k) {
        // k is the last balloon we'll pop.
        int option = solve(a, i, k - 1) + solve(a, k + 1, j) + a[i - 1] * a[k] * a[j + 1];
        best = max(best, option);
      }
      return memo[i][j] = best;
    }

};

int main(){
    Solution s;
    vector<int> v = {3, 1, 5, 8};
    auto ans = s.maxCoins(v);
    D(ans);
    //for (auto k : ans) D(k);
    return 0;
}
