/*
  Problem: Gopher II
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

  Algorithm: Maximum bipartite matching, using Ford-Fulkerson method.
 */

using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
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
#include <map>
#include <set>

#define D(x) cout << #x " is " << x << endl

struct point{
  double x, y;
};

double d(const point &a, const point &b){
  return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
}

int cap[202][202];
int prev[202];

int fordFulkerson(int n, int s, int t){
  int ans = 0;
  while (true){
    fill(prev, prev+n, -1);
    queue<int> q;
    q.push(s);
    while (q.size() && prev[t] == -1){
      int u = q.front();
      q.pop();
      for (int v=0; v<n; ++v){
        if (v != s && prev[v] == -1 && cap[u][v] > 0)
          prev[v] = u, q.push(v);
      }
    }

    if (prev[t] == -1) break;

    int bottleneck = INT_MAX;
    for (int v = t, u = prev[v]; u != -1; v = u, u = prev[v]){
      bottleneck = min(bottleneck, cap[u][v]);
    }
    for (int v = t, u = prev[v]; u != -1; v = u, u = prev[v]){
      cap[u][v] -= bottleneck;
      cap[v][u] += bottleneck;
    }
    ans += bottleneck;
  }
  return ans;
}



int main(){
  int n, m, s, v;
  while (scanf("%d %d %d %d", &n, &m, &s, &v) == 4){
    vector<point> gophers(n);
    vector<point> holes(m);

    for (int i=0; i<n; ++i) scanf("%lf %lf", &gophers[i].x, &gophers[i].y);
    for (int i=0; i<m; ++i) scanf("%lf %lf", &holes[i].x, &holes[i].y);

    memset(cap, 0, sizeof cap);
    const int source = n + m, sink = n + m + 1;

    for (int i=0; i<n; ++i){
      for (int j=0; j<m; ++j){
        if (d(gophers[i], holes[j]) <= s*v - 1e-9){
          cap[i][n+j] = 1;
        }
      }
    }

    for (int i=0; i<n; ++i) cap[source][i] = 1;
    for (int j=0; j<m; ++j) cap[n+j][sink] = 1;


    int lucky = fordFulkerson(n + m + 2, source, sink);

    printf("%d\n", n - lucky);
  }
  return 0;
}
