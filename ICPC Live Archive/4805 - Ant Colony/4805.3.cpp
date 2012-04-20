// Andrés Mejía
// Live Archive - 4805 - Ant Colony
//    Accepted. Uses Schieber-Vishkin algorithm for LCA as explained in
//              "Algorithms on Strings, Trees and Sequences" by Dan Gusfield.

// This is just a cleaner version of the same code.
using namespace std;
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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

const int MAXN = 100005;

// Usage:
// Preprocessing in O(n log n):
//   - LCA::clear(number_of_nodes);
//   - LCA::add_edge(u, v) for every edge
//   - LCA::preprocess(number_of_nodes, root)
// Queries in O(log n):
//   - LCA::lca(u, v)

namespace LCA {
    int tin[MAXN], tout[MAXN];
    vector<int> up[MAXN];
    vector<int> g[MAXN]; // alternatively, you can use a global graph
                         // if you have one to save space (it's only used
                         // inside LCA::dfs below).
    int L, timer;

    void clear(int n) {
        for (int i = 0; i < n; ++i) g[i].clear();
    }
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void dfs(int v, int p = 0) {
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
        dfs(root);
    }
};



vector< pair<int, int> > g[MAXN];
long long dist[MAXN];

void dfs(int u) {
    assert(dist[u] != -1);
    for (int k = 0; k < g[u].size(); ++k) {
        int v = g[u][k].first;
        long long w = g[u][k].second;
        if (dist[v] != -1) continue;
        dist[v] = dist[u] + w;
        dfs(v);
    }
}

int main(){
    int n;
    while (scanf("%d", &n) == 1) {
        if (n == 0) break;
        for (int i = 0; i < n; ++i) {
            dist[i] = -1;
            g[i].clear();
        }

        LCA::clear(n);
        
        for (int i = 1; i < n; ++i) {
            int v, w;
            scanf("%d %d", &v, &w);
            LCA::add_edge(i, v);
            
            g[i].push_back( make_pair(v, w) );
            g[v].push_back( make_pair(i, w) );
        }
        
        LCA::preprocess(n, 0);

        dist[0] = 0;
        dfs(0);

        int Q; scanf("%d", &Q);
        for (int q = 0; q < Q; ++q) {
            if (q > 0) printf(" ");
            int u, v;
            scanf("%d %d", &u, &v);
            int a = LCA::lca(u, v);
            long long ans = dist[u] + dist[v] - 2 * dist[a];
            printf("%lld", ans);
        }
        puts("");
    }
    return 0;
}