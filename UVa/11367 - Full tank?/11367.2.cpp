/*
  Time limit exceeded + Wrong answer!
 */
#include <iostream>
#include <vector>
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


int p[MAXN], //Prices
  d[MAXN][MAXC+1],
  n,
  mind[MAXN][MAXN]; //mind[i][j] = Min distance from node i to j

vector<edge> g[MAXN];

int min_distance(const int &start, const int &end){
  if (mind[start][end] == -1){
    vector<int> d(n, INT_MAX);
    d[start] = 0;
    priority_queue<edge> q;
    q.push(edge(start, 0, 0));
    while (q.size()){
      edge u = q.top();
      q.pop();
      if (u.i == end){
        mind[start][end] = u.w;
        break;
      }
      if (d[u.i] < u.w) continue;
      vector<edge> &v = g[u.i];
      for (int j=0; j<v.size(); ++j){
        int distance = v[j].w;
        int neighbor = v[j].i;
        if (u.w + distance < d[neighbor]){
          d[neighbor] = u.w + distance;
          q.push(edge(neighbor, 0, d[neighbor]));
        }
      }
    }
  }
  return mind[start][end];
}



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

    vector<edge> &v = g[u.i];
    for (int j=0; j<v.size(); ++j){
      int distance = v[j].w;
      int neighbor = v[j].i;

      //no comprar nada
      if (u.g >= distance){
        int new_gas = u.g - distance;
        if (u.w < d[neighbor][new_gas]){
          d[neighbor][new_gas] = u.w;
          q.push(edge(neighbor, new_gas, u.w));
        }
      }

      //comprar lo justito para llegar allá
      if (u.g < distance){
        int k = distance - u.g;
        if ( u.g + k <= c ){ //No puedo exceder el tanque
          int w_extra = k*p[u.i];
          if (u.w + w_extra < d[neighbor][0]){
            d[neighbor][0] = u.w + w_extra;
            q.push(edge(neighbor, 0, u.w + w_extra));
          }
        }
      }

      //llenar el tanque
      if ( distance <= c ){
        int k = std::min(c, min_distance(neighbor, end)) - u.g;
        if (0 <= k && u.g + k <= c){ //no tengo más gasolina de la que necesito
          int w_extra = k*p[u.i];
          int new_gas = u.g - distance + k;
          if (u.w + w_extra < d[neighbor][new_gas]){
            d[neighbor][new_gas] = u.w + w_extra;
            q.push(edge(neighbor, new_gas, u.w + w_extra));
          }
        }
      }


      /*      for (int k = distance - u.g; k <= c + distance - u.g; ++k){
        int new_gas = u.g - distance + k;
        if (k >= 0 && 0 <= new_gas && u.g + k <= c ){
          int w_extra = k*p[u.i];
          //assert(w_extra >= 0);
          if (u.w + w_extra < d[neighbor][new_gas]){
            d[neighbor][new_gas] = u.w + w_extra;
            q.push(edge(neighbor, new_gas, u.w + w_extra));
            //printf("  pushed <%d, %d, %d>\n", neighbor, new_gas, u.w + w_extra);
          }
        }
        }*/

    }
  }
  return INT_MAX;

}

int main(){
  int m;
  scanf("%d %d", &n, &m);
  for (int i=0; i<n; ++i){
    scanf("%d", &p[i]);
    for (int j=0; j<n; ++j){
      mind[i][j] = -1;
    }
    mind[i][i] = 0;
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
