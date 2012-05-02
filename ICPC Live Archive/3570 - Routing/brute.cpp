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
#include <bitset>
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
bool g[MAXN][MAXN];

bool works(int mask, int n){
    static bool seen[MAXN];
    for (int i = 0; i < n; ++i) seen[i] = false;
    queue<int> q;
    
    if ((mask & 3) == 0) return false;
    
    seen[0] = true;
    q.push(0);
    while (q.size() > 0) {
        int u = q.front(); q.pop();
        if (u == 1) break;
        for (int v = 0; v < n; ++v) {
            if (mask & (1 << v)) {
                if (g[u][v] and !seen[v]) {
                    seen[v] = true;
                    q.push(v);
                }
            }
        }
    }
    if (!seen[1]) return false;


    for (int i = 0; i < n; ++i) seen[i] = false;
    while (q.size() > 0) q.pop();
    
    seen[1] = true;
    q.push(1);
    while (q.size() > 0) {
        int u = q.front(); q.pop();
        if (u == 0) break;
        for (int v = 0; v < n; ++v) {
            if (mask & (1 << v)) {
                if (g[u][v] and !seen[v]) {
                    seen[v] = true;
                    q.push(v);
                }
            }
        }
    }
    if (!seen[0]) return false;
    return true;
    
}

int main(){
    int n, m, run = 1;
    while (scanf("%d %d", &n, &m) == 2) {
        if (n == 0 and m == 0) break;

        memset(g, 0, sizeof g);
        while (m--) {
            int u, v;
            scanf("%d %d", &u, &v);
            u--, v--;
            g[u][v] = true;
        }

        int best = n + 1;
        for (int mask = 0; mask < (1 << n); ++mask) {
            if (works(mask, n)) best = min(best, __builtin_popcount(mask));
        }


        printf("Network %d\n", run++);
        if (best == n + 1) {
            puts("Impossible");
        } else {
            printf("Minimum number of nodes = %d\n", best);
        }
        puts("");
    }
    return 0;
}