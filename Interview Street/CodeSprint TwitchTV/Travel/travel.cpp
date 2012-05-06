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

int city[MAXN];

struct Edge {
    int to, weight;
    bool operator < (const Edge &that) const {
        return weight < that.weight;
    }
    Edge(int a, int b) : to(a), weight(b){}
};

vector<Edge> g[MAXN];

int main(){
    int n, m, initial_gold;
    cin >> n >> m >> initial_gold;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].push_back(Edge(v, w));
        g[v].push_back(Edge(u, w));
    }
    
    for (int i = 0; i < n; ++i) {
        cin >> city[i];
    }
    
    static int d[MAXN];
    for (int i = 0; i < n; ++i) {
        d[i] = 0;
    }
    d[0] = initial_gold;
    priority_queue<Edge> q;
    q.push(Edge(0, initial_gold));
    
    while (q.size() > 0) {
        int u = q.top().to, gold = q.top().weight;
        q.pop();
        
        if (gold < d[u]) continue;
        
        for (int t = 0; t < g[u].size(); ++t) {
            
            const Edge &e = g[u][t];
            int v = e.to;
            int toll = e.weight;
            
            int new_gold = (gold - toll + city[v]) / 2;
            if (new_gold > d[v]) {
                d[v] = new_gold;
                q.push(Edge(v, new_gold));
            }
        }
    }
    cout << d[n - 1] << endl;
    return 0;
}