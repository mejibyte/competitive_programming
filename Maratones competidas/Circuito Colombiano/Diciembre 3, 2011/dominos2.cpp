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
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

template <class T> string toStr(const T &x)
{ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x)
{ stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); \
                           x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS){
    return( x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

#define INPUT_FILE "dominos"

const int MAXN = 100010;

vector<int> g[MAXN];
int d[MAXN], low[MAXN], scc[MAXN];
bool stacked[MAXN];
stack<int> s;
int ticks, current_scc;

void tarjan(int u) {
    d[u] = low[u] = ticks++;
    s.push(u);
    stacked[u] = true;
    const vector<int> &out = g[u];
    for (int k = 0, m = out.size(); k < m; ++k) {
        int v = out[k];
        if (d[v] == -1) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (stacked[v]) {
            low[u] = min(low[u], low[v]);
        }
    }
    if (d[u] == low[u]){
        int v;
        do {
            v = s.top();
            s.pop();
            stacked[v] = false;
            scc[v] = current_scc;
        } while (u != v);
        current_scc++;
    }
}

bool knocked[MAXN];

void solve(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    // init
    ticks = 0; current_scc = 0;
    while (s.size()) s.pop();
    for (int i = 0; i <= n; ++i) {
        g[i].clear();
        d[i] = -1;
        stacked[i] = false;
        knocked[i] = false;
    }
    for (int i = 0; i < m; i++) {
        int u, v; scanf("%d %d", &u, &v);
        u--, v--;
        g[u].push_back(v);

    }
    
    for (int i = 0; i < n; ++i) {
        if (d[i] == -1) tarjan(i);
    }
    
    //for (int i = 0; i < n; ++i) D(scc[i]);
    
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < g[i].size(); ++k) {
            int comp1 = scc[ i ];
            int v = g[i][k];
            int comp2 = scc[ v ];
            if (comp1 == comp2) continue;
            knocked[ comp2 ] = true;
        }
    }
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int comp = scc[ i ];
        if (!knocked[ comp ]) {
            ans++;
            knocked[ comp ] = true;
        }
    }
    printf("%d\n", ans);
}


int main(){
    freopen(INPUT_FILE ".in", "r", stdin); // Read from file
    int Cases; cin >> Cases;
    while (Cases--) solve();
    return 0;
}
