// Andrés Mejía

// Accepted

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
const int oo = 1 << 30;

vector<Edge> g[MAXN]; // Normal graph
vector<int> distance_to, distance_from, previous;

void dijkstra(int start, vector<int> &d, vector<int> &p) {
    d.assign(N, oo);
    p.assign(N, -1);
    priority_queue<Edge> q;
    d[start] = 0;
    q.push(Edge(start, 0));
    while (q.size() > 0) {
        int u = q.top().to, w = q.top().weight;
        q.pop();
        if (w > d[u]) continue;
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

void print(int ans){
    if (ans == oo) cout << "Infinity" << endl;
    else cout << ans << endl;
}

void precompute(int source, int sink, map< pair<int, int>, int > &ans){
    if (distance_to[sink] == oo) return;
    
    vector<int> path;
    for (int cur = sink; cur != -1; cur = previous[cur]) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());
    assert(path[0] == source and path.back() == sink);
    
    vector<bool> visited(N, false);
    priority_queue<Edge> heap;

    ans.clear();
    
    for (int p = 0; p + 1 < path.size(); ++p) {
        int start = path[p];
        int avoid = path[p + 1];
        
        assert(!visited[start] and !visited[avoid]);
        
        vector<int> seen;
        queue<int> q;
        visited[start] = true;
        q.push(start);
        seen.push_back(start);
        
        while (q.size() > 0) {
            int u = q.front(); q.pop();
            for (int k = 0; k < g[u].size(); ++k) {
                const Edge &e = g[u][k];
                
                if (u == start and e.to == avoid) continue;
                
                if (previous[e.to] != u) continue;
                visited[e.to] = true;
                q.push(e.to);
                seen.push_back(e.to);
            }
        }
        
        for (int k = 0; k < seen.size(); ++k) {
            int u = seen[k];
            for (int e = 0; e < g[u].size(); ++e) {
                int v = g[u][e].to, w_extra = g[u][e].weight;
                if (visited[v]) continue;
                if (u == start and v == avoid) continue;
                heap.push( Edge(v, distance_to[u] + w_extra + distance_from[v]) );
            }
        }
        
        while (heap.size() > 0 and visited[heap.top().to]) heap.pop();
        
        int cost = heap.size() > 0 ? heap.top().weight : oo;
        int u = min(avoid, start), v = max(avoid, start);
        assert(u <= v);
        ans[make_pair(u, v)] = cost;
    }
    
}

int main(){
    cin >> N >> M;

    long long total_weight = 0;
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back(Edge(v, w));
        g[v].push_back(Edge(u, w));
        assert(w <= 1000);
        total_weight += w;
    }

    assert(total_weight < (1LL << 31) - 1);
    
    

    int source, sink;
    cin >> source >> sink;
    
    dijkstra(sink, distance_from, previous);
    dijkstra(source, distance_to, previous);
    
    // distance_from[u] = Distance from u to sink
    // distance_to[u] = Distance form source to u
    // previous[u] = previous of node u in shortest path from source to u
    

    map< pair<int, int>, int > cost_without;
    precompute(source, sink, cost_without);
        
    int Q;
    cin >> Q;
    for (int q = 0; q < Q; ++q) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        assert(u <= v);
        
        if (distance_to[sink] == oo) {
            print(oo);
            continue;
        }
        // output shortest path when edge u, v is blocked.
        if (cost_without.count(make_pair(u, v)) > 0) {
        int ans = cost_without[make_pair(u, v)];
        assert(ans != -1);
        print(ans);
        } else { // edge doesn't belong to the shortest path, so blocking it changes nothing.
            print(distance_to[sink]);
        }
    }
    
    return 0;
}