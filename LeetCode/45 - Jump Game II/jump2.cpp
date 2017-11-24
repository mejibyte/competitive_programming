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
      vector< vector<bool> > dp(2, vector<int>(n));
      // dp[i][j] == true

      int n = nums.size();
      int last = 0;
      int reach = 0;
      int jumps = 0;
      while (reach < n - 1) {
        int next_reach = 0;
        for (int i = last; i <= reach; ++i) {
          next_reach = max(next_reach, i + nums[i]);
        }
        assert(next_reach >= 1);
        last = reach + 1;
        reach = next_reach;
        jumps++;
      }
      return jumps;
    }
};

int main(){
    Solution s;

    auto m = s.jump({2,3,1,1,4});
    D(m);
    return 0;
}
