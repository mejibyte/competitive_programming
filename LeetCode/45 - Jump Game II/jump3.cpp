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
    int jump(vector<int>& nums) {
      int n = nums.size();
      for (int i = 1; i < n; ++i) {
        nums[i] = max(nums[i - 1], i + nums[i]);
      }
      int jumps = 0;
      for (int at = 0; at < n - 1; at = nums[at]) {
        jumps++;
      }
      return jumps;
    }
};

int main(){
    Solution s;
    vector<int> a = {2,3,1,1,4};
    auto m = s.jump(a);
    D(m);
    return 0;
}
