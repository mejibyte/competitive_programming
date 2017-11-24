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
      long long sum = 0;
      for (int x : nums) {
        sum += x;
      }
      long long low = 0, high = sum;
      while (low < high) {
        long long mid = low + (high - low) / 2;
        if (works(nums, m, mid)) {
          high = mid;
        } else {
          low = mid + 1;
        }
      }
      assert(low == high);
      return low;
    }

    bool works(const vector<int>& a, int m, long long max_sum) {
      int n = a.size();

      int i = 0;
      while (i < n) {
        if (m == 0) return false;

        long long sum = 0;
        int grabbed = 0;
        // Add as many as I can to this slice without exceeding the sum and leaving enough parts for m.
        m--;
        // Next to add is i. While I can add another one, add it.
        while (i < n and sum + a[i] <= max_sum) {
          sum += a[i];
          i++;
          grabbed++;
        }
        if (grabbed == 0) return false;
      }
      assert(m >= 0);
      return true;
    }
};

int main(){
    Solution s;
    auto ans = s.splitArray({7,2,5,10,8}, 2);
    D(ans);
    return 0;
}
