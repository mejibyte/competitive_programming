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

void dijkstra(int start, vector<int> &d, vector<int> &p) {
    const int oo = 1 << 30;
    d.assign(N, oo);
    p.assign(N, -1);
    priority_queue<Edge> q;
    d[start] = 0;
    q.push(Edge(start, 0));
    while (q.size() > 0) {
        int u = q.top().to, w = q.top().weight;
        q.pop();
        if (w > d[w]) continue;
        for (int k = 0; k < g[u].size(); ++k) {
            int v = g[u][k].to, w_extra = g[u][k].weight;
            if (w + w_extra < d[v]) {
                p[v] = u;
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
    
    dijkstra(sink, distance_from, previous);
    dijkstra(source, distance_to, previous);
    
    // distance_from[u] = Distance from u to sink
    // distance_to[u] = Distance form source to u
    // previous[u] = previous of node u in shortest path from source to u
    
    int Q;
    cin >> Q;
    for (int q = 0; q < Q; ++q) {
        int u, v;
        cin >> u >> v;
        // output shortest path when edge u, v is blocked.
        if (previous[v] != u) { // edge doesn't belong to the shortest path, so blocking it changes nothing.
            cout << distance_to[sink] << endl;
        } else {
            cout << "hold on" << endl;
        }
    }
    
    return 0;
}