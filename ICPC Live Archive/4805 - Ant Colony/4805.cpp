// Andrés Mejía
// Live Archive - 4805 - Ant Colony
//    Accepted. Uses Schieber-Vishkin algorithm for LCA as explained in
//              "Algorithms on Strings, Trees and Sequences" by Dan Gusfield.
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

void binary(int u) {
    string s = "";
    while (u > 0) {
        s += char('0' + (u & 1));
        u >>= 1;
    }
    reverse(s.begin(), s.end());
    printf("%s", s.c_str());
}

namespace LCA {
    vector<int> g[MAXN];
    int number[MAXN], parent[MAXN], leader[MAXN], subtree[MAXN], original[MAXN], I[MAXN], A[MAXN];
    int clock;
    
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    int h(const int u) {
        assert(u > 0);
        return __builtin_ctz(u) + 1;
    }
    
    void dfs1(int u) {
        number[u] = clock++;
        original[number[u]] = u;
        subtree[u] = 1;
        for (int k = 0; k < g[u].size(); ++k) {
            int v = g[u][k];
            if (number[v] != -1) {
                parent[u] = v;
            } else {
                dfs1(v);
                subtree[u] += subtree[v];
            }
        }
    }
    
    // Compute I and leader
    void dfs2(int u) {
        I[number[u]] = number[u];
        for (int k = 0; k < g[u].size(); ++k) {
            int v = g[u][k];
            if (I[number[v]] != -1) continue;
            dfs2(v);
            if ( h(I[number[v]]) > h(I[number[u]]) ) {
                I[number[u]] = I[number[v]];
            }
        }
        leader[I[number[u]]] = number[u];
    }
    
    void dfs3(int u) {
        if (parent[u] != -1) {
            A[number[u]] = A[number[parent[u]]];
        } else {
            A[number[u]] = 0;
        }
        A[number[u]] |= ( 1 << (h(I[number[u]]) - 1) );
        
        for (int k = 0; k < g[u].size(); ++k) {
            int v = g[u][k];
            if (parent[u] == v) continue;
            dfs3(v);
        }
    }
    
    void preprocess(int root, int n) {
        assert(n > 1 and n + 1 < MAXN);
        for (int i = 0; i <= n; ++i) {
            number[i] = parent[i] = I[i] = leader[i] = -1;
        }
        clock = 1;
        dfs1(root);
        assert(clock == n + 1);
        
        // printf("After dfs1:\n");
        // For(i, 0, n) {
        //     printf("number[%d] = %d\nparent[%d] = %d\nsubtree[%d] = %d\n***\n", i, number[i], i, parent[i], i, subtree[i]);
        // }
        
        dfs2(root);
        // printf("After dfs2:\n");
        // For(i, 0, n) {
        //     printf("number[%d] = %d\n", i, number[i]);
        //     printf("h(%d) = %d\n", number[i], h(number[i]));
        //     printf("I[%d] = ", number[i]); binary(I[number[i]]); printf("\n");
        //     printf("h(I[%d]) = %d\n", number[i], h(I[number[i]]));
        //     printf("leader[I[%d]] = %d\n", I[number[i]], leader[I[number[i]]]);
        //     printf("***\n");
        // }

        dfs3(root);
        // printf("After dfs3:\n");
        // For(i, 0, n) {
        //     printf("number[%d] = %d\n", i, number[i]);
        //     printf("A[%d] = ", number[i]); binary(A[number[i]]); printf("\n");
        //     printf("***\n");
        // }
    }
    
    int binaryLCA(int u, int v) {
        if (u == v) return u;
        // Special case: One node is an ancestor of the other
        int subtree = (u & -u) - 1;
        if (u - subtree <= v and v <= u + subtree) return u;
        
        subtree = (v & -v) - 1;
        if (v - subtree <= u and u <= v + subtree) return v;
        
        int x = u ^ v;
        int ans = u | v;
        x >>= 1;
        while (x > 0) {
            ans &= ~x;
            x >>= 1;
        }
        return ans;
    }
    
    int lca(int u, int v) {
        //printf("Called lca(%d, %d)\n", u, v);
        // Special case: One node is an ancestor of the other
        if (number[u] <= number[v] and number[u] + subtree[u] > number[v]) return u;
        if (number[v] <= number[u] and number[v] + subtree[v] > number[u]) return v;
        
        u = number[u];
        v = number[v];
        //printf("Now u = %d and v = %d\n", u, v);
        
        int b = binaryLCA(I[u], I[v]);
        
        // printf("I[u=%d] = ", u); binary(I[u]); printf(" (%d)\n", I[u]);
        // printf("I[v=%d] = ", v); binary(I[v]); printf(" (%d)\n", I[v]);
        // printf("b = "); binary(b); printf(" (%d)\n", b);
        //printf("h(b) = %d\n", h(b));
        // 
        // printf("A[u] = "); binary(A[u]); printf("\n");
        // printf("A[v] = "); binary(A[v]); printf("\n");
        
        int j = h((A[u] & A[v]) >> (h(b) - 1)) + h(b) - 1;
        //printf("j = %d\n", j);
        
        int x, y, l;
        
        //printf("finding x'\n");
        // Find x
        l = h(A[u]);
        //printf("l = %d\n", l);
        if (l == j) {
            x = u;
        } else {
            assert(l < j);
            int k = j - 1;
            //printf("Originally, k is %d\n", k);
            while ((A[u] & (1 << (k - 1))) == 0) k--;
            //printf("k = %d, A[u] = ", k);  binary(A[u]); printf("\n");
            
            int iw = ((I[u] >> (k - 1)) | 1) << (k - 1);
            //printf("I[u] = "); binary(I[u]); printf(", iw = "); binary(iw); printf("\n");
            int w = leader[iw];
            //printf("w via x is = %d\n", w);
            x = number[parent[original[w]]];
            //printf("x = parent[w] = %d\n", x);
        }
        
        l = h(A[v]);
        if (l == j) {
            y = v;
        } else {
            assert(l < j);
            int k = j - 1;
            while ((A[v] & (1 << (k - 1))) == 0) k--;
           // printf("j = %d, k = %d, A[v] = ", j, k);  binary(A[v]); printf("\n");
            
            int iw = ((I[v] >> (k - 1)) | 1) << (k - 1);
            int w = leader[iw];
            //printf("w via y is = %d\n", w);
            y = number[parent[original[w]]];
        }
        return x < y ? original[x] : original[y];
    }
    
    void printBinaryLCA(int u, int v, int expected) {
        printf("u = "); binary(u); printf("\n");
        printf("v = "); binary(v); printf("\n");
        int a = binaryLCA(u, v);
        printf("LCA(u=%d, v=%d) = ", u, v); binary(a); printf(" (%d)\n", a);
        assert(a == expected);
        assert(a == binaryLCA(v, u));
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
            cout << ans;
            //printf("LCA(u=%d, v=%d) = %d\n", u, v, a);
        }
        puts("");
        //printf("-----------------------End of case.\n");
        
        // LCA::printBinaryLCA(8, 8,  8);
        // LCA::printBinaryLCA(8, 4,  8);
        // LCA::printBinaryLCA(4, 6,  4);
        // LCA::printBinaryLCA(6, 4,  4);
        // LCA::printBinaryLCA(1, 8,  8);
        // LCA::printBinaryLCA(1, 3,  2);
        // LCA::printBinaryLCA(1, 15,  8);
        // LCA::printBinaryLCA(9, 13,  12);
        // LCA::printBinaryLCA(9, 14,  12);
        // LCA::printBinaryLCA(8, 25,  16);
        // LCA::printBinaryLCA(1, 31,  16);
        // LCA::printBinaryLCA(1, 63,  32);
        // LCA::printBinaryLCA(1, 63,  32);
        // LCA::printBinaryLCA(18, 28,  24);
        // LCA::printBinaryLCA(18, 12,  16);
        // LCA::printBinaryLCA(1, 1024, 1024);
        // LCA::printBinaryLCA(1, 1023234234, 536870912);
        //
    }
    return 0;
}