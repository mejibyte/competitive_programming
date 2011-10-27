struct edge{
  int u, v, w;
};

edge * e; //e = Arreglo de todas las aristas
long long d[300]; //Distancias
int n; //Cantidad de nodos
int m; //Cantidad de aristas

/*
  Retorna falso si hay un ciclo de costo negativo.

  Si retorna verdadero, entonces d[i] contiene la distancia más corta entre el s y el nodo i.
 */
bool bellman(int &s){
  //Llenar e
  e = new edge[n];
  //...

  for (int i=0; i<n; ++i) d[i] = INT_MAX;
  d[s] = 0LL;

  for (int i=0; i<n-1; ++i){
    bool cambio = false;
    for (int j=0; j<m; ++j){
      int u = e[j].u, v = e[j].v;
      long long w = e[j].w;
      if (d[u] + w < d[v]){
        d[v] = d[u] + w;
        cambio = true;
      }
    }
    if (!cambio) break; //Early-exit
  }

  for (int j=0; j<m; ++j){
    int u = e[j].u, v = e[j].v;
    long long w = e[j].w;
    if (d[u] + w < d[v]) return false;
  }

  delete [] e;
  return true;
}
