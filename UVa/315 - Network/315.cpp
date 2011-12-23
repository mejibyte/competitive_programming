// Andrés Mejía
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

const int MAXN = 105;

int discovery[MAXN], reach[MAXN], ans, ticks, n;
bool g[MAXN][MAXN];

void dfs(int u, int parent = -1) {
    discovery[u] = reach[u] = ticks++;
    int children = 0;
    bool is = false; // true if this node is an articulation point
    for (int v = 0; v < n; ++v) {
        if (v == parent or !g[u][v]) continue;
        if (discovery[v] == -1) {
            dfs(v, u);
            children++;
            reach[u] = min(reach[u], reach[v]);
            if (reach[v] >= discovery[u]) {
                is = true;
            }
        } else {
            reach[u] = min(reach[u], discovery[v]);
        }
    }
    assert(reach[u] <= discovery[u]);
    if (parent == -1 and children > 1 || parent != -1 and is) {
        ans++;
    }
}

int main(){
    string s; while (getline(cin, s) and s != "0") {
        stringstream sin(s);
        sin >> n;
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                g[i][j] = false;
            }
            discovery[i] = -1;
        }
        
        while (getline(cin, s) and s != "0") {
            sin.clear(); sin.str(s);
            int first; sin >> first;
            first--;
            for (int next; sin >> next; ) {
                next--;
                g[first][next] = g[next][first] = true;
                //printf("%d %d\n", first, next);
            }
        }
        ticks = 0;
        ans = 0;
        dfs(0);
        cout << ans << endl;
    }
    return 0;
}