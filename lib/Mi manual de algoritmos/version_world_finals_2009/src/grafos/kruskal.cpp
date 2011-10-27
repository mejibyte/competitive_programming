//Complejidad: O(E log V)
struct edge{
  int start, end, weight;
  bool operator < (const edge &that) const {
    //Si se desea encontrar el árbol de recubrimiento de
    //máxima suma, cambiar el < por un >
    return weight < that.weight;
  }
};


///////////////// Empieza Union find ////////////////////////
//Complejidad: O(m log n), donde m es el número de operaciones
//y n es el número de objetos. En la práctica la complejidad
//es casi que O(m).
int p[MAXNODES], rank[MAXNODES];
void make_set(int x){ p[x] = x, rank[x] = 0; }
void link(int x, int y){
  if (rank[x] > rank[y]) p[y] = x;
  else{ p[x] = y; if (rank[x] == rank[y]) rank[y]++; }
}
int find_set(int x){
  return x != p[x] ? p[x] = find_set(p[x]) : p[x];
}
void merge(int x, int y){ link(find_set(x), find_set(y)); }
///////////////// Termina Union find ////////////////////////

//e es un vector con todas las aristas del grafo ¡El grafo
//debe ser no digirido!
long long kruskal(const vector<edge> &e){
  long long total = 0;
  sort(e.begin(), e.end());
  for (int i=0; i<=n; ++i){
    make_set(i);
  }
  for (int i=0; i<e.size(); ++i){
    int u = e[i].start, v = e[i].end, w = e[i].weight;
    if (find_set(u) != find_set(v)){
      total += w;
      merge(u, v);
    }
  }
  return total;
}
