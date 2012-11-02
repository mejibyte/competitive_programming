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

struct Edge {
    int u, v;
    bool erased;
};

const int MAXN = 2505;
int N;
vector<Edge> edges;
vector<int> g[MAXN];
int dist[MAXN];
int from[MAXN];

void bfs(int start) {
    for (int i = 0; i < N; ++i) dist[i] = from[i] = -1;
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (q.size() > 0) {
        int u = q.front(); q.pop();
        for (int k = 0; k < g[u].size(); ++k) {
            const Edge &out = edges[g[u][k]];
            assert(out.u == u or out.v == u);
            if (out.erased) continue;
            int v = out.u == u ? out.v : out.u;
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                from[v] = u;
                q.push(v);
            }
        }
    }
}

// Returns the diameter of the tree that contains u.
// The first value is the diameter, the second value
// is the "inflection vertex", the vertex that if taken
// as the root of the tree minimizes the tree's height.
pair<int, int> get_diameter(int u) {
    bfs(u);
    int to = -1, best = -1;
    for (int i = 0; i < N; ++i) {
        if (dist[i] > best) {
            best = dist[i];
            to = i;
        }
    }
    assert(0 <= to and to < N);
    bfs(to);
    to = -1, best = -1;
    for (int i = 0; i < N; ++i) {
        if (dist[i] > best) {
            best = dist[i];
            to = i;
        }
    }
    assert(0 <= to and to < N);
    vector<int> path;
    for (int at = to; at != -1; at = from[at]) {
        path.push_back(at);
    }
    return make_pair(path.size() - 1, path[path.size() / 2]);
}

int new_diameter(int a, int b, int c, int d) {
    int ans = max(a + b, c + d);
    ans = max(ans, b + d + 1);
    return ans;
}

int main(){
    #ifndef LOCAL
        int runs; cin >> runs;
    #else
        int runs = 1;
    #endif
    while (runs--) {
        cin >> N;
        for (int i = 0; i < N; ++i) {
            g[i].clear();
        }
        edges.clear();
        for (int i = 0; i < N - 1; ++i) {
            Edge e;
            e.erased = false;
            cin >> e.u >> e.v;
            e.u--;
            e.v--;
            edges.push_back(e);
            g[e.u].push_back(edges.size() - 1);
            g[e.v].push_back(edges.size() - 1);
        }
        
        int best = N;
        pair<int, int> deleted, added;
        for (int i = 0; i < edges.size(); ++i) {
            edges[i].erased = true;
            pair<int, int> left = get_diameter(edges[i].u);
            pair<int, int> right = get_diameter(edges[i].v);
                        
            int a = left.first / 2, b = (left.first + 1) / 2;
            int c = right.first / 2, d = (right.first + 1) / 2;
            assert(a <= b and c <= d);
            
            int m = new_diameter(a, b, c, d);
            
            if (m < best) {
                best = m;
                deleted = make_pair(edges[i].u, edges[i].v);
                added = make_pair(left.second, right.second);
            }
            edges[i].erased = false;
        }
        cout << best << endl;
        cout << deleted.first + 1 << " " << deleted.second + 1<< endl;
        cout << added.first + 1 << " " << added.second + 1 << endl;
    }
    return 0;
}