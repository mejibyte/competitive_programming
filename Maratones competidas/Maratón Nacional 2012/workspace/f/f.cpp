using namespace std;
# include <algorithm>
# include <iostream>
# include <iterator>
# include <sstream>
# include <fstream>
# include <cassert>
# include <cstdlib>
# include <string>
# include <cstring>
# include <cstdio>
# include <vector>
# include <cmath>
# include <queue>
# include <stack>
# include <map>
# include <set>

#define For(i, a, b) for (int i = (a); i < (b); i++)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != v.end(); x++)
#define D(x) cout << #x  " = " << (x) << endl

const double EPS = 1e-9;
int cmp (double x, double y = 0, double tol = EPS){
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

const int oo = (int)1e9;

struct Edge {
    int v, w;
    Edge(){}
    Edge(int vv, int ww) : v(vv), w(ww){}
};

const int MAXN = 200;
vector<Edge> g[MAXN];

void add_edge(int u, int v, int w) {
    g[u].push_back( Edge(v, w) );
    g[v].push_back( Edge(u, -w) );
}

int d[MAXN];

bool bellman(int s, int n) {
    for (int i = 0; i < n; ++i) {
        d[i] = oo;
    }
    d[s] = 0;
    for (int i = 0, changed = true; i < n and changed; ++i) {
        changed = false;
        for (int u = 0; u < n; ++u) {
            for (int k = 0; k < g[u].size(); ++k) {
                int v = g[u][k].v, w = g[u][k].w;
                if (d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                }
            }
        }
    }
    
      for (int u = 0; u < n; ++u) {
        for (int k = 0; k < g[u].size(); ++k) {
            int v = g[u][k].v, w = g[u][k].w;
            if (d[u] + w < d[v]) {
                return false;
            }
        }
    }
    return true;
}

int main () {
    freopen("parabox.in", "r", stdin);
    int n, b;
    while (cin >> n >> b) {
        if (n == 0 and b == 0) break;
        for (int i = 0; i < n; ++i) g[i].clear();
        for (int i = 0; i < b; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            u--, v--;
            add_edge(u, v, w);
        }
        bool ans = bellman(0, n);
        if (!ans) puts("Y");
        else puts("N");
    }
    return 0;
}
