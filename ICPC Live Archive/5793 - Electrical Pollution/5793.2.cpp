// Andrés Mejía
// Wrong Answer
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

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

#include <bitset>

struct Edge {
    int to, weight;
    Edge(int t, int w) : to(t), weight(w) {}
    Edge(){}
};

const int MAXN = 20005;

vector<Edge> g[MAXN];

int d[MAXN];
bitset<MAXN> hasExact;
long long s[MAXN];
long long exact[MAXN];
int component[MAXN];


void setExact(int u, long long what) {
    if (hasExact[u]) {
        if (what != exact[u]) {
            printf("u = %d, exact[u] = %lld but what = %lld\n", u, exact[u], what);
        }
        assert(what == exact[u]);
        return;
    }
    hasExact[u] = true;
    exact[u] = what;
    
    foreach(out, g[u]) {
        setExact(out->to, out->weight - exact[u]);
    }
}

void dfs(int x, int comp, int parent = -1) {
    //printf("dfs(x = %d, comp = %d, parent = %d), d[x] = %d\n", x, comp, parent, d[x]);
    component[x] = comp;
    assert(d[x] >= 0);
    foreach(out, g[x]) {
        if (out->to == parent) continue;
        
        if (d[out->to] == -1) {
            d[out->to] = d[x] + 1;
            s[out->to] = s[x] + (d[x] % 2 == 0 ? out->weight : -out->weight);
            dfs(out->to, comp, x);
        } else  {
            long long v = s[x] - s[out->to];
            if (d[out->to] % 2 == 1) v = -v;
            assert((v + out->weight) % 2 == 0);
        
            if ((d[x] - d[out->to] + 1) % 2 == 1) {
                setExact(out->to, (v + out->weight) / 2);
            } else {

            }

        }
    }
}


namespace LCA {
    vector<int> tin, tout;
    int timer, n, l;
    vector < vector<int> > up;

    void init(int _n) {
        timer = 0;
        n = _n;
        tin.assign(n, -1),  tout.resize(n),  up.resize(n);
        l = 1;
        while ((1<<l) <= n)  ++l;
        for (int i=0; i<n; ++i)  up[i].resize (l+1);
    }
    
    void dfs(int v, int p) {
        tin[v] = ++timer;
        up[v][0] = p;
        for (int i = 1; i <= l; ++i)
            up[v][i] = up[ up[v][i-1] ][i-1];
        foreach(out, g[v]) {
            if (out->to != p and tin[out->to] == -1)
                dfs(out->to, v);
        }
        tout[v] = ++timer;
    }

    bool upper(int a, int b) {
        return tin[a] <= tin[b] && tout[a] >= tout[b];
    }

    int lca(int a, int b) {
        if (upper (a, b))  return a;
        if (upper (b, a))  return b;
        for (int i = l; i >= 0; --i)
            if (!upper(up[a][i], b))
            a = up[a][i];
        return up[a][0];
    }
}

void precompute(int n) {
    for (int i = 0, nextComponent = 0; i < n; ++i) {
        if (component[i] == -1) {
            d[i] = 0;
            dfs(i, nextComponent++);
            LCA::dfs(i, i);
        }
    }
}

int getId(int u, map<int, int> &id, int &nextId) {
    if (id.count(u) > 0) return id[u];
    g[nextId].clear();
    s[nextId] = 0;
    d[nextId] = -1;
    component[nextId] = -1;
    id[u] = nextId++;
    //printf("id[u=%d] = %d\n", u, id[u]);
    return id[u];
}

long long calculate(int u, int v, int lca) {
    long long ans = 0;
    int du = d[u] - d[lca];
    int dv = d[v] - d[lca];
    assert(du % 2 == 1 or dv % 2 == 1);
    
    ans += du % 2 == 0 ? -(s[u] - s[lca]) : (s[u] - s[lca]);
    ans += dv % 2 == 0 ? -(s[v] - s[lca]) : (s[v] - s[lca]);
    
    if (d[lca] % 2 == 1) ans = -ans;
    return ans;
}

int main(){
    int M, Q;
    while (scanf("%d %d", &M, &Q) == 2) {
        if (M == 0 and Q == 0) break;
        
        hasExact.reset();
        
        map<int, int> id;
        int nextId = 0;
        
        set< pair<int, int> > seen;
        set< int > alone;
        for (int i = 0; i < M; ++i) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            if (u > v) swap(u, v);
            if (seen.count(make_pair(u, v))) continue;
            seen.insert(make_pair(u, v));
            u = getId(u, id, nextId);
            v = getId(v, id, nextId);
            if (u == v) {
                alone.insert(u);
                exact[u] = w;
            } else {
                g[u].push_back(Edge(v, w));
                g[v].push_back(Edge(u, w));
            }
        }
        foreach(u, alone) setExact(*u, exact[*u]);
        
        LCA::init(nextId);
        precompute(nextId);
        
        for (int i = 0; i < Q; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            u = id.count(u) ? id[u] : -1;
            v = id.count(v) ? id[v] : -1;
            if (u == -1 or v == -1) {
                printf("*\n");
            } else if (u == v) {
                if (hasExact[u]) printf("%lld\n", exact[u]);
                else printf("*\n");
            } else {
               if (hasExact[u] and hasExact[v]) {
                   printf("%lld\n", exact[u] + exact[v]);
               } else if (component[u] != component[v]) {
                   printf("*\n");
               } else {
                   
                   int ancestor = LCA::lca(u, v);
                   assert(d[u] >= d[ancestor] and d[v] >= d[ancestor]);
                   // printf("lca(u=%d, v=%d) = %d\n", u, v, ancestor);
                   // printf("d[u] = %d, d[v] = %d, d[lca] = %d\n", d[u], d[v], d[ancestor]);
                   if ((d[u] - d[ancestor] + d[v] - d[ancestor]) % 2 == 0) {
                       printf("*\n");
                   } else {
                       long long ans = calculate(u, v, ancestor);
                       //printf("pending\n");
                       printf("%lld\n", ans);
                   }
               }
            }
        }
        puts("-");
    }
    
    return 0;
}