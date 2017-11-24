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

// Memory exceeded since n can be huge.
class Solution {
public:
    int minPatches(const vector<int>& nums, int n) {
      vector<bool> can(n + 1, false);
      can[0] = true;
      for (int i = 0; i < nums.size(); ++i) {
        for (int k = n; k >= nums[i]; --k) {
          can[k] = can[k] || can[k - nums[i]];
        }
      }

      int answer = 0;
      for (int i = 1; i <= n; ++i) {
        if (can[i]) continue;
        answer++;

        for (int k = n; k >= i; --k) {
          can[k] = can[k] || can[k - i];
        }
      }
      return answer;
    }
};

int main(){
    Solution s;
    cout << s.minPatches({1, 5, 10}, 20) << endl;
    return 0;
}
