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

namespace LCA {
    vector<int> g[MAXN];
    int number[MAXN], parent[MAXN], leader[MAXN], subtree[MAXN], original[MAXN], I[MAXN], A[MAXN];
    int clock;
    
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // Counts trailing zeros in binary. For example: ctz(1010) = 1, ctz(1001) = 0, ctz(1100) = 2.
    // The result is undefined if u is zero.
    #define ctz(u) __builtin_ctz(u)

    // Returns one plus the index of the least significant 1-bit of x, or if x is zero, returns zero.
    // This is the same as ctz(u) + 1.
    // Example: h(1001) = 1, h(1010) = 2, h(1100) = 3.
    #define h(u) __builtin_ffs(u)

    // Compute number, original, subtree, I and leader
    void dfs1(int u) {
        number[u] = clock++;
        original[number[u]] = u;
        subtree[u] = 1;
        I[number[u]] = number[u];
        
        for (int k = 0; k < g[u].size(); ++k) {
            int v = g[u][k];
            if (number[v] != -1) {
                parent[u] = v;
            } else {
                dfs1(v);
                subtree[u] += subtree[v];
                if ( h(I[number[v]]) > h(I[number[u]]) ) {
                    I[number[u]] = I[number[v]];
                }
            }
        }
        leader[I[number[u]]] = number[u];
    }

    void dfs2(int u) {
        A[number[u]] = 0;
        if (parent[u] != -1) {
            A[number[u]] = A[number[parent[u]]];
        }
        A[number[u]] |= 1 << ctz(I[number[u]]);
        
        for (int k = 0; k < g[u].size(); ++k) {
            int v = g[u][k];
            if (parent[u] == v) continue;
            dfs2(v);
        }
    }
    
    void preprocess(int root, int n) {
        assert(n > 1 and n + 1 < MAXN);
        for (int i = 0; i <= n; ++i) {
            number[i] = parent[i] = I[i] = leader[i] = -1;
        }
        clock = 1;
        dfs1(root);
        dfs2(root);
    }

    int binaryLCA(int u, int v) {
        if (u == v) return u;
        // Special case: One node is an ancestor of the other
        int subtree = (u & -u) - 1;
        if (u - subtree <= v and v <= u + subtree) return u;
        
        subtree = (v & -v) - 1;
        if (v - subtree <= u and u <= v + subtree) return v;
        
        int ans = u | v;
        int x = (u ^ v) >> 1;
        while (x > 0) {
            ans &= ~x;
            x >>= 1;
        }
        return ans;
    }
    
    int closest(int u, int j) {
        int l = h(A[u]);
        if (l == j) return u;
        // assert(l < j); // commented out for efficiency
        int k = j - 1;
        while ((A[u] & 1 << k - 1) == 0) k--;
        int iw = (I[u] >> k - 1 | 1) << k - 1;
        int w = leader[iw];
        return number[parent[original[w]]];
    }
    
    int lca(int u, int v) {
        // Special case: One node is an ancestor of the other
        if (number[u] <= number[v] and number[u] + subtree[u] > number[v]) return u;
        if (number[v] <= number[u] and number[v] + subtree[v] > number[u]) return v;
        
        u = number[u];
        v = number[v];

        int b = binaryLCA(I[u], I[v]);

        int j = h( (A[u] & A[v]) >> ctz(b) ) + ctz(b);
        
        int x = closest(u, j);
        int y = closest(v, j);
        return x < y ? original[x] : original[y];
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
            LCA::g[i].clear();
            dist[i] = -1;
            g[i].clear();
        }
        
        for (int i = 1; i < n; ++i) {
            int v, w;
            scanf("%d %d", &v, &w);
            LCA::add_edge(i, v);
            
            g[i].push_back( make_pair(v, w) );
            g[v].push_back( make_pair(i, w) );
        }
        
        LCA::preprocess(0, n);

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