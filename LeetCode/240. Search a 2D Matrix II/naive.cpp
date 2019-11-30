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
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (m[i][j] == target) return true;
      }
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