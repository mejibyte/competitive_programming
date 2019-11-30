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

class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int t) {
    m = matrix;
    rows = m.size();
    if (rows == 0) return false;
    cols = m[0].size();
    target = t;
    return search(0, rows - 1, 0, cols - 1);
  }

  bool search(int r0, int r1, int c0, int c1) {
    if (r0 > r1) return false;
    if (c0 > c1) return false;

    int rmid = (r0 + r1) / 2;
    int cmid = (c0 + c1) / 2;

    if (m[rmid][cmid] == target) {
      return true;
    } else if (m[rmid][cmid] < target) {
      return search(r0, rmid, cmid + 1, c1) ||
             search(rmid + 1, r1, c0, cmid) ||
             search(rmid + 1, r1, cmid + 1, c1);
    } else if (m[rmid][cmid] > target) {
      return search(rmid, r1, c0, cmid - 1) ||
             search(r0, rmid - 1, cmid, c1) ||
             search(r0, rmid - 1, c0, cmid - 1);
    } else {
      assert(false);
    }
  }

  vector<vector<int>> m;
  int rows, cols, target;
};

#ifdef LOCAL
int main() {
  Solution s;

  return 0;
}
#endif