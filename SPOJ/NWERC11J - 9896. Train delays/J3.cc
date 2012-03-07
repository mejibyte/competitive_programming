// Author: Adrian Kuegel
// Date: August 26th, 2011
// Algorithm: Dijkstra

#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <queue>
using namespace std;

const double eps = 1e-9;

char name[21];
map<string, int> by_name;

int getIndex(char *n) {
	if (by_name.find(n) == by_name.end()) {
		int ret = by_name.size();
		return by_name[n] = ret;
	}
	return by_name[n];
}

struct connection {
	int m, t, p, d, dest;
}c;

struct qelem {
	int cur_city, minute;
	double time;
}qe, nq;

bool operator<(const qelem &a, const qelem &b) {
	return a.time > b.time;
}

typedef vector<connection> VC;
VC adj[2000];

double mintime[2000][60];

int main() {
	int tc;
	scanf("%d", &tc);
	while(tc--) {
		int n;
		by_name.clear();
		scanf("%s", name);
		int start = getIndex(name);
		scanf("%s", name);
		int end = getIndex(name);
		scanf("%d", &n);
		for (int i=0; i<2*n; ++i)
			adj[i].clear();
		for (int i=0; i<n; ++i) {
			scanf("%s", name);
			c.dest = getIndex(name);
			scanf("%s", name);
			int e = getIndex(name);
			scanf("%d %d %d %d", &c.m, &c.t, &c.p, &c.d);
			adj[e].push_back(c);
		}
		priority_queue<qelem> Q;
		qe.cur_city = end;
		qe.time = 0;
		for (int i=0; i<60; ++i) {
			mintime[end][i] = 0;
			qe.minute = i;
			Q.push(qe);
		}
		for (int i=0; i<2*n; ++i)
			if (i != end)
				for (int j=0; j<60; ++j)
					mintime[i][j] = 1e9;
		while(!Q.empty()) {
			qe = Q.top();
			Q.pop();
			if (qe.time > mintime[qe.cur_city][qe.minute] + eps)
				continue;
			// see if we can update times at the same location
			for (int i=1; i<60; ++i) {
				if (qe.time+i < mintime[qe.cur_city][(qe.minute+60-i)%60] - eps) {
					nq.cur_city = qe.cur_city;
					nq.minute = (qe.minute+60-i)%60;
					nq.time = mintime[qe.cur_city][nq.minute] = qe.time + i;
					Q.push(nq);
				}
			}
			for (VC::iterator it=adj[qe.cur_city].begin(); it!=adj[qe.cur_city].end(); ++it) {
				double p = it->p * 0.01;
				double res = 0;
				for (int i=1; i<=it->d; ++i)
					res += mintime[qe.cur_city][(it->m+it->t+i)%60] + it->t + i;
				res *= p / it->d;
				res += (mintime[qe.cur_city][(it->m+it->t)%60] + it->t) * (1-p);
				if (res < mintime[it->dest][it->m] - eps) {
					nq.time = mintime[it->dest][it->m] = res;
					nq.cur_city = it->dest;
					nq.minute = it->m;
					Q.push(nq);
				}
			}
		}
		double res = 1e9;
		for (int i=0; i<60; ++i)
			if (mintime[start][i] < res)
				res = mintime[start][i];
		if (res < 1e9)
			printf("%.10lf\n", res);
		else
			puts("IMPOSSIBLE");
	}
	return 0;
}
