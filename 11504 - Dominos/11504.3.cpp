/*
  Problem: 11504 - Dominos
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

  Accepted
 */

using namespace std;
#include <iostream>
#include <deque>
#include <vector>
#include <cassert>
#include <set>

const int N = 100005;

vector<int> g[N], gt[N];
int visited[N], scc[N], in_degree[N];

void dfs(int u, int mark, deque<int> *in_order, int visited[], vector<int> g[]){
  visited[u] = mark;

  vector<int> &out = g[u];
  for (int k=0, m=out.size(); k<m; ++k){
    int v = out[k];
    if (!visited[v]) dfs(v, mark, in_order, visited, g);
  }
  if (in_order) in_order->push_front(u);
}

int main(){
  int t;
  for(cin >> t; t--;){
    int n, m; cin >> n >> m;

    for (int i=0; i<=n; ++i) g[i].clear(), gt[i].clear(), visited[i] = scc[i] = in_degree[i] = 0;

    for (int u, v, i=0; i<m && cin >> u >> v; ++i) g[u].push_back(v), gt[v].push_back(u);

    deque<int> in_order;

    for (int i=1; i<=n; ++i)
      if (!visited[i])
	dfs(i, 1, &in_order, visited, g);


    int id = 1;
    for (deque<int>::iterator i=in_order.begin(); i!=in_order.end(); ++i)
      if (!scc[*i])
	dfs(*i, id++, NULL, scc, gt);


    /*    
    for (int i=0; i<=n; ++i){
      printf("ssc[%d] = %d\n", i, scc[i]);
    }
    cout << endl;
    */


    for (int i=1; i<=n; ++i){
      vector<int> &out = g[i];
      for (int k=0, m=out.size(); k<m; ++k){
	int j = out[k];
	if (scc[i] != scc[j]) in_degree[scc[j]]++;
      }
    }

    int ans = 0;
    for (int i=1; i<id; ++i){
      //printf("in_degree[%d] = %d\n", i, in_degree[i]);
      ans += !in_degree[i];
    }

    cout << ans << endl;
  }
  return 0;
}


/*
  Explicación del algoritmo:

  Lo primero es ver que cada componente fuertemente conexa del grafo puede
  tumbarse completamente usando solo una ficha. Entonces primero reducimos
  el grafo a un DAG donde cada nodo representa una componente fuertemente
  conexa del grafo original.

  La respuesta es el número de nodos en el nuevo grafo que tienen in-degree == 0.
 */
