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

struct State {
  int at, flights, w;
  bool operator < (const State& other) const {
    return w > other.w;
  }
};


class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>> flights, int src, int dst, int K) {
      const int oo = numeric_limits<int>::max();
      vector<vector<int>> d(n, vector<int>(n, oo));
      d[src][0] = 0;
      priority_queue<State> q;
      q.push({src, 0, 0});

      vector<vector<pair<int,int>>> g(n);
      for (const auto& edge : flights) {
        g[edge[0]].push_back({edge[1], edge[2]}); // to, weight
      }

      int best = oo;
      while (q.size() > 0) {
        State s = q.top();
        q.pop();

        dprintf("popped at=%d, flights=%d, w=%d, k+1=%d, n=%d\n", s.at, s.flights, s.w, K+1, n);

        if (s.at == dst) {
          assert(s.flights <= K + 1);
          best = min(best, s.w);
        }

        if (s.flights >= K + 1 or s.flights >= n - 1) continue;
        if (s.w > d[s.at][s.flights]) continue;

        for (const auto& edge : g[s.at]) {
          int to = edge.first;
          int w = edge.second;
          if (s.w + w < d[to][s.flights + 1]) {
            d[to][s.flights + 1] = s.w + w;
            q.push({to, s.flights + 1, s.w + w});
          }
        }

      }
      if (best == oo) best = -1;
      return best;
    }
};

#ifdef LOCAL
int main() {
  Solution s;

  s.findCheapestPrice(3,
    {{0,1,100},{1,2,100},{0,2,500}},
    0,
    2,
    1);


s.findCheapestPrice(8,
{ {3,4,7},{6,2,2},{0,2,7},{0,1,2},{1,7,8},{4,5,2},{0,3,2},{7,0,6},{3,2,7},{1,3,10},{1,5,1},{4,1,6},{4,7,5},{5,7,10}},
4,
3,
7);

  return 0;
}
#endif