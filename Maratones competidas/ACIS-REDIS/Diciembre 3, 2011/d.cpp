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
int indegree[MAXN];
bool visited[MAXN];

void knock(int u) {
    assert( !visited[u] );
    visited[u] = true;
    for (int k = 0; k < g[u].size(); ++k) {
        int v = g[u][k];
        if (!visited[v]) knock(v);
    }
}

void solve(){
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i <= n; ++i) {
        g[i].clear();
        indegree[i] = 0;
        visited[i] = false;
    }
    for (int i = 0; i < m; i++) {
        int u, v; scanf("%d %d", &u, &v);
        u--, v--;
        g[u].push_back(v);
        indegree[v]++;
    }
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) {
            assert( !visited[i] );
            knock(i);
            ans++;
        }
    }
    
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            knock(i);
            ans++;
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
