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

// Minmimum cost max flow, as implemented by Ivan Krasilnikov

// in https://github.com/infnty/acm/blob/master/lib/notebook.tex
struct MCMF {
	typedef long long ctype;
	enum { MAXN = 35, INF = LONG_LONG_MAX };
	struct Edge { int x, y; ctype cap, cost; };
	vector<Edge> E;      vector<int> adj[MAXN];
	int N, prev[MAXN];   ctype dist[MAXN], phi[MAXN];

	MCMF(int NN) : N(NN) {}
	
	void add(int x, int y, ctype cap, ctype cost) {  // cost >= 0
		Edge e1={x,y,cap,cost}, e2={y,x,0,-cost};
		adj[e1.x].push_back(E.size()); E.push_back(e1);
		adj[e2.x].push_back(E.size()); E.push_back(e2);
	}

	void mcmf(int s, int t, ctype &flowVal, ctype &flowCost) {
		int x;
		flowVal = flowCost = 0;  memset(phi, 0, sizeof(phi));
		while (true) {
			for (x = 0; x < N; x++) prev[x] = -1;
			for (x = 0; x < N; x++) dist[x] = INF;
			dist[s] = prev[s] = 0;

			set< pair<ctype, int> > Q;
			Q.insert(make_pair(dist[s], s));
			while (!Q.empty()) {
				x = Q.begin()->second; Q.erase(Q.begin());
				foreach(it, adj[x]) {
					const Edge &e = E[*it];
					if (e.cap <= 0) continue;
					ctype cc = e.cost + phi[x] - phi[e.y];                    // ***
                    assert(cc >= 0);
					if (dist[x] + cc < dist[e.y]) {
						Q.erase(make_pair(dist[e.y], e.y));
						dist[e.y] = dist[x] + cc;
						prev[e.y] = *it;
						Q.insert(make_pair(dist[e.y], e.y));
					}
				}
			}
			if (prev[t] == -1) break;

			ctype z = INF;
			for (x = t; x != s; x = E[prev[x]].x) z = min(z, E[prev[x]].cap);
			for (x = t; x != s; x = E[prev[x]].x)
				{ E[prev[x]].cap -= z; E[prev[x]^1].cap += z; }
			flowVal += z;
			flowCost += z * (dist[t] - phi[s] + phi[t]);
			for (x = 0; x < N; x++) if (prev[x] != -1) phi[x] += dist[x];     // ***
		}
	}
};

long long knight_distance(long long x1, long long y1, long long x2, long long y2) {
    long long x = abs(x2 - x1), y = abs(y2 - y1);
    // if (y > x) swap(y, x);
    // assert(y <= x);
    // if (y == 0 and x == 1) return 3;
    // if (y == 2 and x == 2) return 4;
    // 
    // long long d = x - y;
    // if (y > d) {
    //     return 2 * ((y - d) / 3) + d;
    // } else {
    //     return d - 2 * ((d - y) / 4);
    // }
    
    if (x > y) swap(x, y);
    assert(x <= y);
    if (x == 0 and y == 1) return 3;
    if (x == 2 and y == 2) return 4;
    long long d = max((y + 1) / 2, (x + y + 1) / 3);
    if (d % 2 != (x + y) % 2) d++;
    return d;
}

int main(){
    int run = 1;
    int n; while (cin >> n) {
        if (n == 0) break;
        vector< pair<long long, long long> > knights(n);
        vector< pair<long long, long long> > homes(n);
        for (int i = 0; i < n; ++i) cin >> knights[i].first >> knights[i].second;
        for (int i = 0; i < n; ++i) cin >> homes[i].first >> homes[i].second;
        
        MCMF flow(2*n + 2);
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                long long dist = knight_distance(knights[i].first, knights[i].second, homes[j].first, homes[j].second);
                
                //printf("distance from (%d, %d) to (%d, %d) = %lld\n", knights[i].first, knights[i].second, homes[j].first, homes[j].second, dist);
                
                flow.add(i, n + j, 1, dist);
            }
        }
        int src = 2*n, snk = 2*n+1;
        for (int i = 0; i < n; ++i) {
            flow.add(src, i, 1, 0);
            flow.add(n + i, snk, 1, 0);            
        }
        
        long long flow_units, min_cost;
        flow.mcmf(src, snk, flow_units, min_cost);
        assert(flow_units == n);
        cout << run++ << ". " << min_cost << endl;
    }
    return 0;
}