#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Algoritmo de Kruskal, para encontrar el árbol de recubrimiento de mínima suma.
*/

struct edge{
  int start, end, weight;
  bool operator < (const edge &that) const {
    //Si se desea encontrar el árbol de recubrimiento de máxima suma, cambiar el < por un >
    return weight < that.weight;
  }
};



/* Union find */
int p[10001], rank[10001];
void make_set(int x){ p[x] = x, rank[x] = 0; }
void link(int x, int y){ rank[x] > rank[y] ? p[y] = x : p[x] = y, rank[x] == rank[y] ? rank[y]++: 0; }
int find_set(int x){ return x != p[x] ? p[x] = find_set(p[x]) : p[x]; }
void merge(int x, int y){ link(find_set(x), find_set(y)); }
/* End union find */


int main(){
  int c;
  cin >> c;
  while (c--){
    int n, m;
    cin >> n >> m;
    vector<edge> e;
    long long total = 0;
    while (m--){
      edge t;
      cin >> t.start >> t.end >> t.weight;
      e.push_back(t);
      total += t.weight;
    }
    sort(e.begin(), e.end());
    for (int i=0; i<=n; ++i){
      make_set(i);
    }
    for (int i=0; i<e.size(); ++i){
      int u = e[i].start, v = e[i].end, w = e[i].weight;
      if (find_set(u) != find_set(v)){
        //xprintf("Joining %d with %d using weight %d\n", u, v, w);
        total -= w;
        merge(u, v);
      }
    }
    cout << total << endl;

  }
  return 0;
}
