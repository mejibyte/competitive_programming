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
set<int> gc[N];
int visited[N], scc[N], color[N];

void dfs(int u, int mark, deque<int> *in_order, int visited[], vector<int> g[]){
  visited[u] = mark;

  vector<int> &out = g[u];
  for (int k=0, m=out.size(); k<m; ++k){
    int v = out[k];
    if (!visited[v]) dfs(v, mark, in_order, visited, g);
  }
  if (in_order) in_order->push_front(u);
}

enum { standing, tiled, handed };
void shoot(int u, int root, set<int> g[]){
  if (u == root) color[u] = handed;
  else color[u] = tiled;

  set<int> &out = g[u];
  for (set<int>::iterator k=out.begin(); k!=out.end(); ++k){
    if (color[*k] == handed && *k != root) color[*k] = tiled;
    else if (color[*k] == standing) shoot(*k, root, g);
  }
}


int main(){
  int t;
  for(cin >> t; t--;){
    int n, m; cin >> n >> m;

    for (int i=0; i<=n; ++i) g[i].clear(), gt[i].clear(), gc[i].clear(), visited[i] = scc[i] = color[i] = 0;

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

    /*
      Build strongly connected components graph in gc.
     */
    for (int i=1; i<=n; ++i){
      vector<int> &out = g[i];
      for (int k=0, m=out.size(); k<m; ++k){
	gc[scc[i]].insert(scc[out[k]]);
      }
    }

    for(int i=1; i<id; ++i){
      if (!color[i])
	  shoot(i, i, gc);
    }

    int ans = 0;

    for (int i=1; i<id; ++i){
      ans += (color[i] == handed);
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

  Para encontrar la respuesta utilizamos el siguiente algoritmo:
  Tumbamos cada ficha a mano y seguimos el efecto dominó. Si alcanzamos
  otra ficha que había sido tumbada a mano, entonces esta segunda no necesita
  ser tumbada a mano.
 */
