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
    int minPatches(const vector<int>& nums, long long n) {
      long long reach = 0;
      int extra = 0;
      int next = 0;
      while (reach < n) {
        // Check if we need to buy one.
        while (reach < n and (next >= nums.size() || reach + 1 < nums[next])) {
          reach += reach + 1;
          extra++;
        }
        // Grab all the free ones.
        while (reach < n and next < nums.size() and reach + 1 >= nums[next]) {
          reach += nums[next];
          next++;
        }
      }
      return extra;
    }
};

int main(){
    Solution s;

    D(s.minPatches({1, 3}, 6));

    D(s.minPatches({1, 5, 10}, 20));

    D(s.minPatches({1, 2, 2}, 5));
    return 0;
}
