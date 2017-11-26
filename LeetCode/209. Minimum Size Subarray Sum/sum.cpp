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
    int minSubArrayLen(int s, const vector<int>& nums) {
      int sum = 0;
      int n = nums.size();
      int i = 0;
      int best = n + 1;
      for (int j = 0; j < n; ++j) {
        sum += nums[j];
        while (sum >= s and i <= j) {
          best = min(best, j - i + 1);
          sum -= nums[i++];
        }
      }
      if (best == n + 1) best = 0;
      return best;
    }
};

int main(){
    Solution s;
    auto ans = s.minSubArrayLen(7, {2,3,1,2,4,3});
    D(ans);
    ans = s.minSubArrayLen(100, {2,3,1,2,4,3});
    D(ans);

    //for (auto k : ans) D(k);
    return 0;
}
