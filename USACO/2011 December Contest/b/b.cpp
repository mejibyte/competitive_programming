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

const int MAXNODES = 40005;

int p[MAXNODES], rank[MAXNODES];
void make_set(int x){ p[x] = x, rank[x] = 0; }
void link(int x, int y){
  if (rank[x] > rank[y]) p[y] = x;
  else{ p[x] = y; if (rank[x] == rank[y]) rank[y]++; }
}
int find_set(int x){
  return x != p[x] ? p[x] = find_set(p[x]) : p[x];
}
void merge(int x, int y){ link(find_set(x), find_set(y)); }

const long long mod = 1000000007;

struct Edge {
    int u, v, w;
    bool operator < (const Edge &t) const {
        return w < t.w;
    }
};

vector< Edge > edges;


bool dfs(int u, int parent, map<int, vector<int> > &g, set<int> &visited) {
    if (visited.count(u)) return false;
    visited.insert(u);
    const vector<int> &out = g[u];
    int parentCount = 0;
    for (int k = 0; k < out.size(); ++k) {
        int v = out[k];
        if (v == parent) {
            parentCount++;
            if (parentCount == 1) continue;
            else return false;
        }
        if (!dfs(v, u, g, visited)) return false;
    }
    return true;
}

bool isSpanningTree(map<int, vector<int> > &g) {
    set<int> visited;
    for (map<int, vector<int> >::iterator i = g.begin(); i != g.end(); i++  ) {
        if (i->second.size() == 0) return false;
        if (visited.count(i->first)) continue;
        if (!dfs(i->first, -1, g, visited)) return false;
    }
    return visited.size() == g.size();
}

long long ways(int first, int last) {
    //printf("first = %d, last = %d\n", first, last);
    int size = last - first;
    if (size == 1) return 1;
    int ans = 0;
    for (int set = 1; set < 1 << size; ++set) {
        map<int, vector<int> > g;
        for (int k = 0; k < size; ++k) {
            const Edge &e = edges[first + k];
            if (set & (1 << k)) {                
                g[ find_set(e.u) ].push_back( find_set(e.v) );
                g[ find_set(e.v) ].push_back( find_set(e.u) );
            }
            g[ find_set(e.u) ];
            g[ find_set(e.v) ];
        }
        // printf("Set = %d. Graph is:\n", set);
        // foreach(p, g) {
        //     printf("g[%d] = ", p->first);
        //     foreach(v, p->second) printf("%d ", *v); puts("");
        // }
        if (isSpanningTree(g)) {
            // //printf("These edges form a spanning tree (set = %d):\n", set);
            // for (int k = 0; k < size; ++k) {
            //     if (set & (1 << k)) {
            //         printf("(%d, %d, %d)\n", edges[k + first].u, edges[k + first].v, edges[k + first].w);
            //     }
            // }
            ans++;
        }
    }
    return ans % mod;
}

int countTrees(int n) {
    long long ans = 1;
    for (int i = 0; i < n; ++i) make_set(i);
    for (int k = 0; k < edges.size(); ++k) {
        int same = k;
        while (same < edges.size() and edges[k].w == edges[same].w) same++;
        int size = same - k;
        assert(1 <= size and size <= 3);
        ans *= ways(k, same);
        ans %= mod;
        
        for (int j = k; j < same; ++j) {
            if (find_set(edges[j].u) == find_set(edges[j].v)) continue;
            merge(edges[j].u, edges[j].v);
        }
        
        k = same - 1;
    }
    return ans % mod;
}

int main(){
    #ifndef LOCAL
    freopen("simplify.in", "r", stdin);
    freopen("simplify.out", "w", stdout);
    #endif
    
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) make_set(i);
    for (int k = 0; k < m; ++k) {
        Edge e; scanf("%d %d %d", &e.u, &e.v, &e.w);
        e.u--, e.v--;
        edges.push_back(e);
    }
    assert(edges.size() == m);
    sort(edges.begin(), edges.end());
    long long weight = 0;
    for (int k = 0; k < m; ++k) {
        if (find_set(edges[k].u) == find_set(edges[k].v)) continue;
        weight += edges[k].w;
        merge(edges[k].u, edges[k].v);
    }
    int trees = countTrees(n);
    printf("%lld %d\n", weight, trees);
    return 0;
}