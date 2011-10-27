//Complejidad: O(E log V)
//¡El grafo debe ser no digirido!
typedef string node;
typedef pair<double, node> edge;
//edge.first = peso de la arista, edge.second = nodo al que se
//dirige
typedef map<node, vector<edge> > graph;

double prim(const graph &g){
  double total = 0.0;
  priority_queue<edge, vector<edge>, greater<edge> > q;
  q.push(edge(0.0, g.begin()->first));
  set<node> visited;
  while (q.size()){
    node u = q.top().second;
    double w = q.top().first;
    q.pop(); //!!
    if (visited.count(u)) continue;
    visited.insert(u);
    total += w;
    vector<edge> &vecinos = g[u];
    for (int i=0; i<vecinos.size(); ++i){
      node v = vecinos[i].second;
      double w_extra = vecinos[i].first;
      if (visited.count(v) == 0){
        q.push(edge(w_extra, v));
      }
    }
  }
  return total; //suma de todas las aristas del MST
}
