#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <iterator>
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
#include <numeric>
#include <list>
#include <map>
#include <set>
using namespace std;

#ifdef LOCAL
#define DEBUG true
#else
#define DEBUG false
#endif
#define dprintf DEBUG && printf


class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
      const int oo = numeric_limits<int>::max();
      int n = graph.size();
      vector<vector<int>> d(1 << n, vector<int>(n, oo));

      queue<pair<int, int>> q; // <mask, at>
      for (int i = 0; i < n; ++i) {
        d[1 << i][i] = 0;
        q.push({1 << i, i});
      }

      while (q.size() > 0) {
        int seen = q.front().first;
        int at = q.front().second;
        if (seen == (1 << n) - 1) {
          return d[seen][at];
        }
        q.pop();
        for (int to : graph[at]) {
          int newSeen = seen | (1 << to);
          if (d[seen][at] + 1 < d[newSeen][to]) {
            d[newSeen][to] = d[seen][at] + 1;
            q.push({newSeen, to});
          }
        }
      }
      assert(false);
    }
};

#ifdef LOCAL
int main() {
  Solution s;

  return 0;
}
#endif