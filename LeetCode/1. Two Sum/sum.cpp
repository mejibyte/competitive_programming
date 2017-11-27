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
    vector<int> twoSum(const vector<int>& nums, int target) {
      unordered_map<int, int> where;
      for (int i = 0; i < nums.size(); ++i) {
        int need = target - nums[i];
        if (where.count(need) > 0) {
          return {i, where[need]};
        }
        where[nums[i]] = i;
      }
      return {};
    }
};

int main() {
  Solution s;
  auto v = s.twoSum({2, 7, 11, 15}, 9);
  for (auto k : v) D(k);

  v = s.twoSum({3, 3}, 6);
  for (auto k : v) D(k);


  return 0;
}
