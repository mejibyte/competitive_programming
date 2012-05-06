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

int N, M;

struct Edge {
    int to, weight; 
    Edge(int v, int w) : to(v), weight(w) {}
    
    bool operator < (const Edge &that) const {
        return weight > that.weight;
    }
};

const int MAXN = 200005;

vector<Edge> g[MAXN]; // Normal graph
vector<int> distance_to, distance_from, previous;
const int oo = 1 << 30;

void dijkstra(int start, vector<int> &d, pair<int, int> blocked) {
    d.assign(N, oo);
    priority_queue<Edge> q;
    d[start] = 0;
    q.push(Edge(start, 0));
    while (q.size() > 0) {
        int u = q.top().to, w = q.top().weight;
        q.pop();
        if (w > d[u]) continue;
        for (int k = 0; k < g[u].size(); ++k) {
            int v = g[u][k].to, w_extra = g[u][k].weight;
            if (u == blocked.first and v == blocked.second) continue;
            if (u == blocked.second and v == blocked.first) continue;
            if (w + w_extra < d[v]) {
                d[v] = w + w_extra;
                q.push(Edge(v, d[v]));
            }
        }
    }
}

int main(){
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back(Edge(v, w));
        g[v].push_back(Edge(u, w));
        assert(w <= 1000);
    }
    
    int source, sink;
    cin >> source >> sink;

    int Q;
    cin >> Q;
    for (int q = 0; q < Q; ++q) {
        int u, v;
        cin >> u >> v;
        // output shortest path when edge u, v is blocked.
        dijkstra(source, distance_to, make_pair(u, v));
        int ans = distance_to[sink];

        if (ans == oo) cout << "Infinity" << endl;
        else cout << distance_to[sink] << endl;
    }
    
    return 0;
}