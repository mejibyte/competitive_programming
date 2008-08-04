/*
Problem: 10986 - Sending email (UVa Online Judge)
Andrés Mejía-Posada (http://github.com/andmej/acm)

Verdict: Accepted
Algorithm: Dijkstra

*/
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct edge{
  int to, weight;
  edge() {}
  edge(int t, int w) : to(t), weight(w) {}
  bool operator < (const edge &that) const {
    return weight > that.weight;
  }
};

int main(){
  int N, C=0;
  scanf("%d", &N);
  while (N-- && ++C){
    int n, m, s, t;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    vector<edge> g[n];
    while (m--){
      int u, v, w;
      scanf("%d %d %d", &u, &v, &w);
      g[u].push_back(edge(v, w));
      g[v].push_back(edge(u, w));
    }

    int d[n];
    for (int i=0; i<n; ++i) d[i] = INT_MAX;
    d[s] = 0;
    priority_queue<edge> q;
    q.push(edge(s, 0));
    while (q.empty() == false){
      int node = q.top().to;
      int dist = q.top().weight;
      q.pop();

      if (dist > d[node]) continue;
      if (node == t) break;

      for (int i=0; i<g[node].size(); ++i){
        int to = g[node][i].to;
        int w_extra = g[node][i].weight;

        if (dist + w_extra < d[to]){
          d[to] = dist + w_extra;
          q.push(edge(to, d[to]));
        }
      }
    }
    printf("Case #%d: ", C);
    if (d[t] < INT_MAX) printf("%d\n", d[t]);
    else printf("unreachable\n");
  }
  return 0;
}
