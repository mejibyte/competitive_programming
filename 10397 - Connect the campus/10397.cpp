/*
  Problem 10397 - Connect the campus

Hallar un árbol de recubrimiento mínimo (Algoritmo de Prim)

Autor: Andrés Mejía P.
Fecha: Marzo 25/2008
 */
#include <set>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

typedef pair<int, int> point;
typedef pair<double, int> edge; //Edge incidente en second con longitud first
typedef vector<int> * graph;


double euclidean(const point &a, const point &b){ return hypot(a.first-b.first, a.second-b.second); }

int main(){
  int n;
  while (cin >> n){
    vector<point>  p(n+1); //p[i] contiene las coordenadas del punto etiquetado con i
    graph g = new vector<int>[n+1]; //g[i] contiene el set de vecinos "gratuitos" del nodo i (ya existentes en el grafo)
    vector<bool> visited(n+1, false);
    for (int i=0; i<n; ++i){
      int x,y;
      scanf("%d%d", &x, &y);
      p[i] = make_pair(x, y);
    }

    priority_queue<edge, vector<edge>, greater<edge> > q;
    
    int m;
    cin >> m;
    for (int i=0; i<m; ++i){
      int x, y;
      scanf("%d%d", &x, &y);
      g[x-1].push_back(y-1);
      g[y-1].push_back(x-1);
    }

    q.push( edge(0.0, 0) ); //empiezo arbitrariamente en el primer nodo

    
    double totalDistance = 0.0;
    
    while (!q.empty()){
      edge nearest = q.top(); q.pop();

      int actualNode = nearest.second;

      if (!visited[actualNode]){
	//cout << "Visitando " << actualNode << " (" << p[actualNode].first << ", " << p[actualNode].second << ")" << " en " << nearest.first << endl;
	visited[actualNode] = true;
	totalDistance += nearest.first;
	vector<int> neighbors = g[actualNode];
	for (int i = 0; i < neighbors.size(); ++i){
	  if (!visited[neighbors[i]]){
	    q.push( edge(0.0, neighbors[i]) );
	  }
	}
	
	for (int i = 0; i < n; ++i){
	  if (!visited[i]){
	    q.push( edge(euclidean(p[actualNode], p[i]), i) );
	  }
	}
      }
    }
    printf("%.2f\n", totalDistance);
    delete [] g;
  }
  return 0;
}
