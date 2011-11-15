/*
  Accepted
 */
#include <iostream>
#include <climits>
#include <vector>
#include <cstdio>
#include <queue>
//#include <cassert>

using namespace std;

const int MAXN = 1000, MAXC = 100;

struct edge{
  int i, g, w;
  edge(){}
  edge(int I, int G, int W) : i(I), g(G), w(W) {}
  bool operator < (const edge &that) const {
    return w > that.w;
  }
};

int p[MAXN], d[MAXN][MAXC+1], n;
vector<edge> g[MAXN];


int dijkstra(const int &start, const int &end, const int &c){
  for (int i=0; i<n; ++i)
    for (int j=0; j<=c; ++j)
      d[i][j] = INT_MAX;

  priority_queue<edge> q;
  q.push(edge(start, 0, 0));
  d[start][0] = 0;

  while (q.size()){
    edge u = q.top();
    q.pop();

    //printf("popped <%d, %d, %d>\n", u.i, u.g, u.w);
    if (u.i == end){
      return u.w;
    }
    if (d[u.i][u.g] < u.w) continue;

    //I can buy another gallon and stay where I am
    if (u.g < c && u.w + p[u.i] < d[u.i][u.g+1]){
      d[u.i][u.g+1] = u.w + p[u.i];
      q.push(edge(u.i, u.g+1, u.w + p[u.i]));
    }

    //Now try to reach each other node as long as I have enough gas
    vector<edge> &v = g[u.i];
    for (int j=0; j<v.size(); ++j){
      int distance = v[j].w;
      int neighbor = v[j].i;
      if (u.g >= distance){
        int new_gas = u.g - distance;
        if (u.w < d[neighbor][new_gas]){
          d[neighbor][new_gas] = u.w;
          q.push(edge(neighbor, new_gas, u.w));
        }
      }
    }
  }
  return INT_MAX;

}

int main(){
  int m;
  scanf("%d %d", &n, &m);
  for (int i=0; i<n; ++i){
    scanf("%d", &p[i]);
  }

  while (m--){
    int u, v, d;
    scanf("%d %d %d", &u, &v, &d);
    g[u].push_back(edge(v, 0, d));
    g[v].push_back(edge(u, 0, d));
  }

  int q;
  scanf("%d", &q);
  while (q--){
    int c, s, e;
    scanf("%d %d %d", &c, &s, &e);
    int t = dijkstra(s, e, c);
    if (t < INT_MAX){
      printf("%d\n", t);
    }else{
      printf("impossible\n");
    }
  }
  return 0;
}
