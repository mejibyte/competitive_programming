using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
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
#include <map>
#include <set>

#define For (i, a, b) for (int i = (a); i < (b); i++)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); x++)
#define D(x) cout << #x " = " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS){
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

const int MAXN = 1005;

int cap[MAXN][MAXN], prev[MAXN], resid[MAXN][MAXN];


vector< int > g[MAXN];
vector< pair<int, int> > g2[MAXN];

void link(int u, int v, int c) {
    if (cap[u][v] == 0) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cap[u][v] += c;
}

int maxFlow(int n, int s, int t) {
    memcpy(resid, cap, sizeof cap);
    
    int ans = 0;
    while (true) {
        fill(prev, prev + n, -1);
        queue<int> q;
        q.push(s);
        while (q.size() and prev[t] == -1) {
            int u = q.front();
            q.pop();
            vector<int> &out = g[u];
            for (int k = 0, m = out.size(); k < m; ++k) {
                int v = out[k];
                if (v != s and prev[v] == -1 and resid[u][v] > 0) {
                    prev[v] = u; q.push(v);
                }
            }
        }
        
        if (prev[t] == -1) break;
        
        int bottleneck = (1 << 30);
        for (int v = t, u = prev[v]; u != -1; v = u, u = prev[v]) {
            bottleneck = min(bottleneck, resid[u][v]);
        }
        for (int v = t, u = prev[v]; u != -1; v = u, u = prev[v]) {
           resid[u][v] -= bottleneck;
           resid[v][u] += bottleneck;
        }        
        ans += bottleneck;
    }
    return ans;
}

void init(int n) {
    for (int i = 0; i <= n; ++i) {
        g[i].clear();
        g2[i].clear();
        for (int j = 0; j <= n; ++j) cap[i][j] = 0;
    }
}

#include<bitset>

bitset<MAXN> been;
void dfs(int u, int c) {
    if (been[u]) return;
    been[u] = true;
    foreach(out, g2[u]) {
        int v = out->first, w = out->second;
        if (w < c) continue;
        dfs(v, c);
    }
}

bool works(int c, int a, int b) {
    // usa aristas >= c
    been.reset();
    dfs(a, c);
    return been[b];
}

int main() {
    int casos; cin >> casos;
    while (casos--) {
        int id, n, e, a, b; 
        cin >> id >> n >> e >> a >> b;

        init(n);

        int maxCap = -1;
        for (int k = 0; k < e; ++k) {
            int u, v, w;
            cin >> u >> v >> w;
            link(u, v, w);
            
            g2[u].push_back( make_pair(v, w) );

            maxCap = max(maxCap, w);
        }

        int f = maxFlow(n, a, b);
        
        int low = 0, high = maxCap + 1;
        
        
        while (low < high) {
            int mid = (low + high + 1) / 2;
            if (works(mid, a, b)) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        assert(low > 0);

        printf("%d %.3lf\n", id, 1.0 * f / low);
        
    }

    return 0;
}
