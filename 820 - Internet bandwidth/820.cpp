#include <iostream>
#include <iterator>
#include <queue>
#include <stdio.h>

using namespace std;

const int MAXN = 101;

int cap[MAXN+1][MAXN+1], flow[MAXN+1][MAXN+1], prev[MAXN+1];

int fordFulkerson(int n, int s, int t){
  int ans = 0;
  for (int i=0; i<n; ++i) fill(flow[i], flow[i]+n, 0);
  while (true){
    fill(prev, prev+n, -1);
    queue<int> q;
    q.push(s);
    while (q.size() && prev[t] == -1){
      int u = q.front();
      q.pop();
      for (int v = 0; v<n; ++v)
        if (v != s && prev[v] == -1 && cap[u][v] > 0 && cap[u][v] - flow[u][v] > 0)
          prev[v] = u, q.push(v);
    }

    if (prev[t] == -1) break;

    int bottleneck = INT_MAX;
    for (int v = t, u = prev[v]; u != -1; v = u, u = prev[v]){
      bottleneck = min(bottleneck, cap[u][v] - flow[u][v]);
    }
    for (int v = t, u = prev[v]; u != -1; v = u, u = prev[v]){
      flow[u][v] += bottleneck;
      flow[v][u] = -flow[u][v];
    }
    ans += bottleneck;
  }
  return ans;
}

int main(){
  int n, runs = 1;
  while (scanf("%d", &n) == 1 && n){
    for (int i=0; i<n; ++i){
      fill(cap[i], cap[i]+n, 0);
    }
    int s, t, C;
    scanf("%d %d %d", &s, &t, &C);
    --s, --t;
    while (C--){
      int i, j, k;
      scanf("%d %d %d", &i, &j, &k);
      cap[--i][--j] += k, cap[j][i] += k;
    }

    printf("Network %d\nThe bandwidth is %d.\n\n", runs++, fordFulkerson(n, s, t));
  }
  return 0;
}
