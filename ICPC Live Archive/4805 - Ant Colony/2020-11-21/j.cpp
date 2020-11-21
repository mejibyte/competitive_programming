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
#include <unordered_set>
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

const int MAXN = 100005;
// Usage:
// Preprocessing in O(n log n):
//   - LCA::clear(number_of_nodes);
//   - LCA::add_edge(u, v) for every edge
//   - LCA::preprocess(number_of_nodes, root);
// Queries in O(log n):
//   - LCA::lca(u, v);

// Assumes the tree is connected. If it's not,
// you might want to run the algorithm on every
//  component (but remember to check if the two
// nodes of a query are on the same component,
// otherwise there's no LCA).

namespace LCA {
    int tin[MAXN], tout[MAXN];
    vector<int> up[MAXN];
    vector<int> g[MAXN];
    // alternatively, you can use a global graph to save space.
    // This graph is only used inside LCA::dfs below.

    int L, timer;

    void clear(int n) {
        for (int i = 0; i < n; ++i) g[i].clear();
    }
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void dfs(int v, int p) {
        tin[v] = ++timer;
        up[v][0] = p;
        for (int i = 1; i <= L; ++i)
            up[v][i] = up[up[v][i-1]][i-1];
        for (int i = 0; i < g[v].size(); ++i) {
            int to = g[v][i];
            if (to != p) dfs(to, v);
        }
        tout[v] = ++timer;
    }
    inline bool upper(int a, int b) {
        return tin[a] <= tin[b] && tout[b] <= tout[a];
    }
    int lca(int a, int b) {
        if (upper(a, b)) return a;
        if (upper(b, a)) return b;
        for (int i = L; i >= 0; --i)
            if (!upper(up[a][i], b))
                a = up[a][i];
        return up[a][0];
    }
    void preprocess(int n, int root) {
        L = 1;
        while ((1 << L) <= n) ++L;
        for (int i = 0; i < n; ++i) up[i].resize(L + 1);
        timer = 0;
        dfs(root, root);
    }
};

long long depth[MAXN];
bool v[MAXN];
vector<pair<int, long long>> g[MAXN];

void dfs(int u) {
  for (const auto &out : g[u]) {
    int to = out.first;
    long long w = out.second;
    if (v[to]) continue;
    v[to] = true;
    depth[to] = depth[u] + w;
    dfs(to);
  }
}

int main(){
  // ios::sync_with_stdio(0);
  // cin.tie(0);

  int N;
  while (cin >> N) {
    if (N == 0) break;
    LCA::clear(N);

    for (int i = 0; i < N; ++i) {
      depth[i] = 0;
      v[i] = false;
      g[i].clear();
    }


    for (int i = 1; i <= N - 1; ++i) {
      int j; long long length;
      cin >> j >> length;

      LCA::add_edge(i, j);

      g[i].push_back(make_pair(j, length));
      g[j].push_back(make_pair(i, length));
    }
    LCA::preprocess(N, 0);

    v[0] = true;
    dfs(0);

    int Q;
    cin >> Q;
    bool first = true;
    while (Q--) {
      int S, T;
      cin >> S >> T;

      int lca = LCA::lca(S, T);

      long long answer = depth[S] - depth[lca] + depth[T] - depth[lca];

      // D(S); D(T); D(lca);
      // D(depth[S]);
      // D(depth[T]);
      // D(depth[lca]);
      // D(answer);

      if (!first) {
        cout << " ";
      }
      cout << answer;
      first = false;
    }
    cout << endl;
  }
  return 0;
}