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
    int maxProduct(vector<int>& nums) {
      if (nums.size() == 1) return nums[0];
      int best = 0;
      int from = 0;

      nums.push_back(0);
      for (int to = 0; to < nums.size(); ++to) {
        if (nums[to] == 0) {
          best = max(best, find_best(nums, from, to - 1));
          from = to + 1;
        }
      }
      return best;
    }

    // Find the max subarray asumming there are no zeroes.
    int find_best(const vector<int> &nums, int l, int r) {
      if (l > r) return 0;
      if (l == r) return nums[l];
      for (int i = l; i <= r; ++i) assert(nums[i] != 0);
      int negatives = 0;
      for (int i = l; i <= r; ++i) negatives += (nums[i] < 0);

      if (negatives % 2 == 0) {
        // The best is to take everything.
        int answer = 1;
        for (int i = l; i <= r; ++i) answer *= nums[i];
        return answer;
      } else {
        // The best is to take everything before the last negative or everything after the first negative.
        int to = r;
        while (nums[to] > 0) to--;
        int best1 = 1;
        for (int i = l; i < to; ++i) best1 *= nums[i];

        int from = l;
        while (nums[from] > 0) from++;
        int best2 = 1;
        for (int i = from + 1; i <= r; ++i) best2 *= nums[i];

        return max(best1, best2);
      }
    }
};

int main(){
    Solution s;
    //vector<int> a = {-1, -1, -3, 0, 0, 0, -2, 1, 2, -1, -3};
    vector<int> a = {-2, 0, -1};
    cout << s.maxProduct(a) << endl;
    return 0;
}
