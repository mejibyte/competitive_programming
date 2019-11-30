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

    stack<State> q;
    q.push({0, rows-1, 0, cols-1});
    while (q.size() > 0) {
      int r0 = q.top().r0, r1 = q.top().r1, c0 = q.top().c0, c1 = q.top().c1;
      q.pop();

      if (r0 > r1) continue;
      if (c0 > c1) continue;

      if (m[r0][c0] > target) continue;
      if (m[r1][c1] < target) continue;

      int rmid = (r0 + r1) / 2;
      int cmid = (c0 + c1) / 2;

      if (m[rmid][cmid] == target) {
        return true;
      } else if (m[rmid][cmid] < target) {
        q.push({r0, rmid, cmid + 1, c1});
        q.push({rmid + 1, r1, c0, cmid});
        q.push({rmid + 1, r1, cmid + 1, c1});
      } else if (m[rmid][cmid] > target) {
        q.push({rmid, r1, c0, cmid - 1});
        q.push({r0, rmid - 1, cmid, c1});
        q.push({r0, rmid - 1, c0, cmid - 1});
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