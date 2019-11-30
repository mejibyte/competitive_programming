// Memory limit exceeded
#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

#define DEBUG false
#define dprintf DEBUG&& printf

struct State {
  int r0, r1, c0, c1;
};

class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& m, int target) {
    int rows = m.size();
    if (rows == 0) return false;
    int cols = m[0].size();
    if (cols == 0) return false;
    int bound = cols;
    for (int i = 0; i < rows && bound > 0; ++i) {
      bound = upper_bound(m[i].begin(), m[i].begin() + bound, target) - m[i].begin();
      if (bound - 1 >= 0 and m[i][bound-1] == target) return true;
    }
    return false;
  }
};

#ifdef LOCAL
int main() {
  Solution s;

  return 0;
}
#endif