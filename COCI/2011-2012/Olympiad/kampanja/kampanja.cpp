#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <cassert>

using namespace std;

const int MAXN = 1005;

bool g[MAXN][MAXN];

int p[MAXN][MAXN];
int d[MAXN][MAXN];

struct State {
	int u, v, w;
	bool operator < (const State &that) const {
		return w > that.w;
	}

	State(int u, int v, int w) : u(u), v(v), w(w) {}
};

priority_queue<State> q;

void enqueue(int u, int v, int weight) {
	if (weight < d[u][v]) {
		d[u][v] = weight;
		q.push(State(u, v, weight));
	}
}

int main() {
	int n, m, run = 1;
	while (cin >> n >> m and n > 0 and m > 0) {
		memset(g, false, sizeof g);

		for (int i = 0; i < m; ++i) {
			int u, v; cin >> u >> v;
			u--, v--;
			g[u][v] = true;	
		}


		const int infinite = 1 << 29;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				d[i][j] = infinite;
				p[i][j] = g[i][j] ? 1 : infinite;
			}
			p[i][i] = 0;
		}


		for (int k = 0; k < n; ++k)
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					p[i][j] = min(p[i][j], p[i][k] + p[k][j]);

		d[0][0] = 1;
		while (q.size() > 0) q.pop();

		q.push(State(0, 0, 1));	

		while (q.size() > 0) {
			State cur = q.top(); q.pop();
			if (cur.u == 1 and cur.v == 1) break;

			if (cur.w > d[cur.u][cur.v]) continue;
			
			int u = cur.u, v = cur.v;
			if (u != v) {
				assert(p[u][v] >= 1);
				enqueue(v, u, cur.w + p[u][v] - 1);
			}
			for (int k = 0; k < n; ++k) {
				if (g[u][k]) enqueue(k, v, cur.w + (k == v ? 0 : 1));
				if (g[k][v]) enqueue(u, k, cur.w + (k == u ? 0 : 1));
			}
				
		}

		int ans = d[1][1];
        assert(ans <= n);
        cout << ans << endl;
	}
	return 0;
}
