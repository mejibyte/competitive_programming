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

struct Edge {
    int to, weight;
    Edge(){}
    Edge(int v, int w) : to(v), weight(w) {}
    bool operator < (const Edge &t) const {
        return weight > t.weight;
    }
};

const int MAXN = 100005;

vector<Edge> g[MAXN];

int cost[20][20]; // from important places

int d[MAXN];

void dijkstra(int start, int n) {
    for (int i = 0; i < n; ++i) d[i] = 1 << 30;
    priority_queue<Edge> q;
    d[start] = 0;
    q.push(Edge(start, 0));
    while (q.size() > 0) {
        int u = q.top().to;
        int w = q.top().weight;
        q.pop();
        if (w > d[u]) continue;
        foreach(out, g[u]) {
            int w_extra = out->weight;
            int v = out->to;
            if (w + w_extra < d[v]) {
                d[v] = w + w_extra;
                q.push(Edge(v, d[v]));
            }
        }
    }
}

void solve() {
    int n, m; scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) g[i].clear();
    for (int i = 0; i < m; ++i) {
        int u, v, w; scanf("%d %d %d", &u, &v, &w);
        g[u].push_back(Edge(v, w));
        g[v].push_back(Edge(u, w));
    }
    vector<int> important(1, 0);
    int s; scanf("%d", &s);
    while (s--) {
        int u; scanf("%d", &u);
        important.push_back(u);
    }
    sort(important.begin(), important.end());
    important.resize(unique(important.begin(), important.end()) - important.begin());
    for (int k = 0; k < important.size(); ++k) {
        dijkstra(important[k], n);
        for (int next = 0; next < important.size(); ++next) {
            cost[k][next] = d[ important[next] ];
        }
    }
    assert(important[0] == 0);
    
    for (int i = 1; i < important.size(); ++i) important[i] = i;
    
    int best = 1 << 30;
    do {
        int option = 0;
        for (int i = 0; i < important.size(); ++i){
            int j = (i + 1) % important.size();
            option += cost[ important[i] ][ important[j] ];
        }
        best = min(best, option);
    } while (next_permutation(important.begin() + 1, important.end()));

    cout << best << endl;
}

int main(){
    int runs; scanf("%d", &runs);
    while (runs--) {
        solve();
    }
    return 0;
}