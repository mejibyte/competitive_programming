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

const int MAXN = 100005;

///////////////// Union find ////////////////////////
int p[MAXN], rank[MAXN];
void make_set(int x){ p[x] = x, rank[x] = 0; }
void link(int x, int y){
  if (rank[x] > rank[y]) p[y] = x;
  else{ p[x] = y; if (rank[x] == rank[y]) rank[y]++; }
}
int find_set(int x){
  return x != p[x] ? p[x] = find_set(p[x]) : p[x];
}
void merge(int x, int y){ link(find_set(x), find_set(y)); }
///////////////// Union find ////////////////////////


struct Edge {
    int u, v, w;
    int index;
    bool operator < (const Edge &t) const {
        return w < t.w;
    }
};

enum { Pending, None, Any, One };

int ans[MAXN];


const int WHITE = 0, GRAY = 1, BLACK = 2;
int colors[MAXN], d[MAXN], low[MAXN];
int timeCount;

void dfs(int u, int pid, const vector< vector<pair<int, int> > > &g) {
	d[u] = low[u] = ++timeCount;
	colors[u] = GRAY;
	for (vector<pair<int, int> >::const_iterator e = g[u].begin(); e != g[u].end(); ++e) {
		int t = e->first, id = e->second;
		if (id == pid)
			continue;
		if (colors[t] == WHITE) {
			dfs(t, id, g);
			low[u] = min(low[u], low[t]);
		} else {
			low[u] = min(low[u], d[t]);
		}
	}
	if (pid != -1) {
		if (low[u] == d[u]) {
            assert(ans[pid] == Pending);
			ans[pid] = Any;
		}
	}
    colors[u] = BLACK;
}

void markBridges(const vector< vector<pair<int, int> > > &g) {
    timeCount = 0;
    int n = g.size();
    for (int i = 0; i < n; ++i) {
        colors[i] = WHITE;
    }
    for (int i = 0; i < n; ++i) {
        if (colors[i] == WHITE) {
            dfs(i, -1, g);
        }
    }
}

int main(){
    int n, M;
    cin >> n >> M;
    vector<Edge> e(M);
    for (int i = 0; i < M; ++i) {
        e[i].index = i;
        cin >> e[i].u >> e[i].v >> e[i].w;
        e[i].u--, e[i].v--;
    }
    sort(e.begin(), e.end());
    for (int i = 0; i < n; ++i) make_set(i);

    int components = n;
    
    for (int i = 0; i < M; ++i){
        int j = i;
        while (j < M and e[j].w == e[i].w) j++;
        
        map<int, int> pos; int nextPos = 0;
        vector< vector<pair<int, int> > > g(components);
        
        // group is [i, j)
        for (int k = i; k < j; ++k) {
            const Edge &edge = e[k];
            int left = find_set(edge.u), right = find_set(edge.v);

            assert(ans[edge.index] == Pending);
            if (left == right) {
                ans[edge.index] = None;
            } else {
                int leftPos = pos.count(left) ? pos[left] : (pos[left] = nextPos++);
                int rightPos = pos.count(right) ? pos[right] : (pos[right] = nextPos++);
                assert(leftPos < components and rightPos < components);
                g[leftPos].push_back( make_pair(rightPos, edge.index) );
                g[rightPos].push_back( make_pair(leftPos, edge.index) );
            }
        }
        
        markBridges(g);
        for (int k = i; k < j; ++k) {
            const Edge &edge = e[k];
            if (ans[edge.index] == Pending) ans[edge.index] = One;
            int left = find_set(edge.u), right = find_set(edge.v);
            if (left != right) merge(left, right), components--;
        }
        
        i = j - 1;
    }
    for (int i = 0; i < M; ++i) {
        int k = ans[i];
        assert(k != Pending);
        if (k == None) {
            puts("none");
        } else if (k == One) {
            puts("at least one");
        } else {
            puts("any");
        }
    }
    
    return 0;
}