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
    int trap(const vector<int>& height) {
      int n = height.size();
      if (n == 0) return 0;

      vector<int> max_left(n), max_right(n);
      max_left[0] = height[0];
      for (int i = 1; i < n; ++i) {
        max_left[i] = max(height[i], max_left[i - 1]);
      }
      max_right[n - 1] = height[n - 1];
      for (int i = n - 2; i >= 0; --i) {
        max_right[i] = max(height[i], max_right[i + 1]);
      }

      int ans = 0;
      for (int i = 0; i < n; ++i) {
        int boundary = min(max_left[i], max_right[i]);
        assert(boundary >= height[i]);
        ans += boundary - height[i];
      }
      return ans;
    }
};

int main(){
    Solution s;
    auto ans = s.trap({0,1,0,2,1,0,1,3,2,1,2,1});
    D(ans);

    //for (auto k : ans) D(k);
    return 0;
}
