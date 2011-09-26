//Complejidad: O(V*E)

const int oo = 1000000000;
struct edge{
  int v, w; edge(){} edge(int v, int w) : v(v), w(w) {}
};
vector<edge> g[MAXNODES];

int d[MAXNODES];
int p[MAXNODES];
// Retorna falso si hay un ciclo de costo negativo alcanzable
// desde s.  Si retorna verdadero, entonces d[i] contiene la
// distancia más corta para ir de s a i.  Si se quiere
// determinar la existencia de un costo negativo que no
// necesariamente sea alcanzable desde s, se crea un nuevo
// nodo A y nuevo nodo B. Para todo nodo original u se crean
// las aristas dirigidas (A, u) con peso 1 y (u, B) con peso
// 1. Luego se corre el algoritmo de Bellman-Ford iniciando en
// A.
bool bellman(int s, int n){
  for (int i=0; i<n; ++i){
    d[i] = oo;
    p[i] = -1;
  }

  d[s] = 0;
  for (int i=0, changed = true; i<n-1 && changed; ++i){
    changed = false;
    for (int u=0; u<n; ++u){
      for (int k=0; k<g[u].size(); ++k){
        int v = g[u][k].v, w = g[u][k].w;
        if (d[u] + w < d[v]){
          d[v] = d[u] + w;
          p[v] = u;
          changed = true;
        }
      }
    }
  }

  for (int u=0; u<n; ++u){
    for (int k=0; k<g[u].size(); ++k){
      int v = g[u][k].v, w = g[u][k].w;
      if (d[u] + w < d[v]){
        //Negative weight cycle!

        //Finding the actual negative cycle. If not needed
        //return false immediately.
        vector<bool> seen(n, false);
        deque<int> cycle;
        int cur = v;
        for (; !seen[cur]; cur = p[cur]){
          seen[cur] = true;
          cycle.push_front(cur);
        }
        cycle.push_front(cur);
        //there's a negative cycle that goes from
        //cycle.front() until it reaches itself again
        printf("Negative weight cycle reachable from s:\n");
        int i = 0;
        do{
          printf("%d ", cycle[i]);
          i++;
        }while(cycle[i] != cycle[0]);
        printf("\n");
        // Negative weight cycle found

        return false;
      }
    }
  }
  return true;
}
