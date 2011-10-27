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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

const int MAXN = 100001;
vector<int> g[MAXN];
int memo[MAXN][2];

int f(int node, bool edge, int parent = -1) {
    assert(g[node].size() > 0);
    if (g[node].size() == 1 and g[node][0] == parent) { // Base case
        return edge ? 0 : 1;
    }
    
    if (memo[node][edge] > -1) return memo[node][edge];
    
    // take this node
    int ans = 1;
    for (int k = 0; k < g[node].size(); ++k) {
        int v = g[node][k];
        if (v == parent) continue;
        ans += f(v, true, node);
    }
    
    if (edge) {
        // do not take this node
        int option = 0;
        for (int k = 0; k < g[node].size(); ++k) {
            int v = g[node][k];
            if (v == parent) continue;
            option += f(v, false, node);
        }
        ans = min(ans, option);
    }
    
    return memo[node][edge] = ans;
}

int main(){
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
         g[i].clear();
         memo[i][0] = memo[i][1] = -1;
     }
    for (int i = 0; i < n - 1; ++i) {
        int u, v; scanf("%d %d", &u, &v);
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    if (n == 1) {
        printf("0\n");
    } else {
        printf("%d\n", min(f(0, false), f(0, true)));
    }
    return 0;
}