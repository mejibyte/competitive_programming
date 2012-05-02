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
int d[MAXN][MAXN];

void enqueue(int u, int v, int previous_cost, int edge_cost, deque< pair<int, int> > &q) {
    printf("   trying to push (%d, %d) with cost %d (current cost is %d)\n", u + 1, v + 1, previous_cost + edge_cost, d[u][v]);
    if (d[u][v] == -1 or previous_cost + edge_cost < d[u][v]) {
        d[u][v] = previous_cost + edge_cost;
        assert(edge_cost == 0 or edge_cost == 1);
        if (edge_cost == 0) q.push_front(make_pair(u, v));
        else q.push_back(make_pair(u, v));
        
        printf("     pushed (%d, %d) with cost %d\n", u + 1, v + 1, d[u][v]);
    }
}

int main(){
    int n, m, run = 1;
    while (scanf("%d %d", &n, &m) == 2) {
        if (n == 0 and m == 0) break;
        printf("Network %d\n", run++);

        static bool closure[MAXN][MAXN];
        
        memset(g, 0, sizeof g);
        memset(closure, 0, sizeof closure);

        while (m--) {
            int u, v;
            scanf("%d %d", &u, &v);
            u--, v--;
            g[u][v] = true;
            closure[u][v] = true;
        }
        
        for (int i = 0; i < n; ++i) closure[i][i] = true;
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    closure[i][j] |= closure[i][k] and closure[k][j];
        
        if (!closure[0][1] or !closure[1][0]) {
            puts("Impossible");
            puts("");
            continue;
        }
        
        memset(d, -1, sizeof d);
        d[0][0] = 1;
        
        deque< pair<int, int> > q;
        
        q.push_front(make_pair(0, 0));
        while (q.size() > 0) {
            int u = q.front().first, v = q.front().second;
            printf("popped (%d, %d) with cost %d\n", u + 1, v + 1, d[u][v]);
            q.pop_front();
                        
            for (int k = 0; k < n; ++k) {
                                
                if (g[u][k]) {
                    enqueue(k, v, d[u][v], 1, q);
                }
                if (g[k][v]) {
                    enqueue(u, k, d[u][v], u == k ? 0 : 1, q);
                }
            }
        }
        
        assert(d[1][1] != -1);
        printf("Minimum number of nodes = %d\n", d[1][1]);
        puts("");
    }
    return 0;
}