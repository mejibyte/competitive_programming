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

const int MAXN = 110;
const int oo = 1e9;

int flow[MAXN][MAXN];
int cap[MAXN][MAXN];
int least[MAXN][MAXN];

int prev[MAXN];

bool find_path(int n, int from, int to) {
    for (int i = 0; i < n; ++i) prev[i] = -1;
    prev[from] = -2;
    queue<int> q;
    q.push(from);
    while (q.size() > 0) {
        int u = q.front(); q.pop();
        for (int v = 0; v < n; ++v) {
            int capacity = flow[v][u] - least[v][u] + cap[u][v] - flow[u][v];
            if (capacity <= 0) continue;
            if (prev[v] != -1) continue;
            prev[v] = u;
            q.push(v);
        }
    }
    if (prev[to] == -1) return false;
    
    int neck = oo;
    for (int v = to; prev[v] >= 0; v = prev[v]) {
        int u = prev[v];
        int capacity = flow[v][u] - least[v][u] + cap[u][v] - flow[u][v];
        assert(capacity > 0);
        neck = min(neck, capacity);
    }

    for (int v = to; prev[v] >= 0; v = prev[v]) {
        int u = prev[v];
        flow[u][v] += neck;
    }
    return true;
}

void goDown(int cur, int n, int sink) {
    if (cur != sink) printf("%d ", cur + 1);
    for (int v = 0; v < n; ++v) {
        if (flow[cur][v] - flow[v][cur] > 0) {
            flow[cur][v]--;
            goDown(v, n, sink);
            break;
        }
    }
}

int main(){
    int n; scanf("%d", &n);
    int source = n, sink = n + 1;
    for (int i = 0; i < n; ++i) {
        cap[source][i] = oo;
        cap[i][sink] = oo;
    }
    
    for (int i = 0; i < n; ++i) {
        int m; scanf("%d", &m);
        for (int j = 0; j < m; ++j) {
            int to; scanf("%d", &to);
            to--;
            
            cap[i][to] = oo;
            least[i][to] = 1;
            
            flow[source][i]++;
            flow[i][to]++;
            flow[to][sink]++;
        }
    }
    
    while (find_path(n + 2, sink, source));
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += flow[source][i] - flow[i][source];
    }
    printf("%d\n", ans);

    for (int i = 0; i < n; ++i) {
        while (flow[source][i] - flow[i][source] > 0) {
            flow[source][i]--;
            goDown(i, n + 2, sink);
            printf("\n");
        }
    }
    return 0;
}