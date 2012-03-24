#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include <sstream>
#include <functional>

using namespace std;

const double infinity = 1E20;

struct point{
  double x, y;
  point(double X, double Y){ x = X; y = Y;}
};

map< point, double > dist;

bool operator ==(const point &a, const point &b){ return (a.x == b.x && a.y == b.y);}
bool operator !=(const point &a, const point &b){ return !(a == b);}
bool operator <(const point &a, const point &b){ return (a.x < b.x || (a.x == b.x && a.y < b.y));}
//bool operator <(point a, point b){ return (a.dist > b.dist);}
double distancia(point a, point b){return hypot(a.y-b.y, a.x-b.x);}



bool heapCmp(const point &a,const point &b){
  return (dist[a] > dist[b]);
}


struct heapCompare : public binary_function<point, point, bool>
{
  bool operator()(const point &x, const point &y) const
  { return dist[x] > dist[y]; }
};


struct grafo{
  //contiene todos los nodos sueltos
  vector<point> nodos;
  //contiene un vector con todos los vecinos para el punto point
  map< point, vector<point> > vecinos;

  void insert(point a){
    if (vecinos.count(a) == 1) return; //Ya insertamos este nodo
    nodos.push_back(a);
    vector<point> v;
    vecinos.insert(make_pair(a, v));
    //printf("Insertando (%f,%f).\n", a.x, a.y);
  }

  void make_vecinos(double maxPath){
    for (map< point, vector<point> >::iterator it=vecinos.begin(); it!=vecinos.end(); ++it){
      if (distancia((*it).first, point(0.00, 0.00)) > maxPath){
	//printf("El punto (%f,%f) es un desastre.\n", (*it).first.x, (*it).first.y);
	continue;
      }
      for (map< point, vector<point> >::iterator jt = it; jt!=vecinos.end(); ++jt){
	//Insertarlo como vecino en los nodos diferentes a el mismo
	//printf("  Ensayando (*it).first = (%f,%f)\n", (*it).first.x, (*it).first.y);
	if ((*it).first != (*jt).first){
	  if ((*jt).first.x - (*it).first.x > 1.5){
	    //printf("Rompiendo con a = (%f,%f) y nodos[i] = (%f,%f)\n", a.x, a.y, (*it).first.x, (*it).first.y);
	    break;
	  }
	  vector<point> adj = vecinos[(*it).first];
	  //Asegurarse de no insertar un vecino repetido
	  //	if (find(adj.begin(), adj.end(), a) == adj.end()){
	  if (distancia((*jt).first, (*it).first) <= 1.5){
	    //printf("Insertando (%f,%f) como vecino de (%f,%f).\n", a.x, a.y, (*it).first.x, (*it).first.y);
	    vecinos[(*it).first].push_back((*jt).first);
	    vecinos[(*jt).first].push_back((*it).first);
	  }
	  //	}
	}
      }
    }
  }
  
  void initialize(){
    dist.clear();
    for (int i=0; i<nodos.size(); ++i){
      dist[nodos[i]] = infinity;
      if (nodos[i].x == 0.00 && nodos[i].y == 0.00){
	dist[nodos[i]] = 0.00;
      }
    }
  }

  /*void relax(point u, point v){
    if (dist[v] > dist[u] + distancia(u, v)){
      dist[v] = dist[u] + distancia(u, v);
    }
    }*/

  void dijkstra(const double &maxPath, const point &finalPoint){
    initialize();
    
    //priority_queue<point, vector<point>, heapCompare > q(nodos.begin(), nodos.end());
    priority_queue<point, vector<point>, heapCompare > q;
    q.push(point(0.0, 0.0));
    //vector<point> q(nodos.begin(), nodos.end());
    //make_heap(q.begin(), q.end(), heapCmp);
    while (!q.empty()){
      //point u = q.front();
      //pop_heap(q.begin(), q.end(), heapCmp); q.pop_back();
      point u = q.top();
      q.pop();
      //printf("Saque (%f,%f) cuya distancia es %f\n", u.x, u.y, dist[u]);
      if (distancia(point(0.00, 0.00), u) + distancia(u, finalPoint) <= maxPath){
	for (int i=0; i<vecinos[u].size(); ++i){
	  point v = vecinos[u][i];
	  //printf("  Comparando (%f,%f) con (%f,%f) que estan a %f\n", u.x, u.y, v.x, v.y, distancia(u,v));
	  //printf(" dist[u] es %f, dist[v] es %f\n", dist[u], dist[v]);
	  if (dist[vecinos[u][i]] > (dist[u] + distancia(u,v))){
	    //printf("  Actualizando la distancia de v = (%f,%f)\n", v.x, v.y);
	    dist[vecinos[u][i]] = dist[u] + distancia(u, v);
	    //printf("  Nueva distancia de v: %f\n", dist[v]);
	    q.push(v);
	  }
	}
      }
      //make_heap(q.begin(), q.end(), heapCmp);
    }
  }

};



int main(){
  while (true){

    string s;
    for (s = ""; s == ""; getline(cin, s));
    if (s == "*") break;


    grafo g;

    stringstream line;
    line << s;

    int w,h;
    line >> w >> h;
    g.insert(point((double)w, (double)h));
    g.insert(point(0.00, 0.00));
    int noPuntos;
    cin >> noPuntos;
    for (int i=0; i<noPuntos; ++i){
      double x,y;
      cin >> x >> y;
      g.insert(point(x,y));
    }

  
    double maximoCamino;
    cin >> maximoCamino;

    g.make_vecinos(maximoCamino);
    //cout << "Termine de insertar todos los nodos.\n";

    /*printf("Voy a imprimir el grafo de %d nodos:\n", g.nodos.size());
    for (int i=0; i<g.nodos.size(); ++i){
      printf("Estos son los vecinos de (%f,%f):\n", g.nodos[i].x, g.nodos[i].y);
      for (int j=0; j<g.vecinos[g.nodos[i]].size(); ++j){
	printf("  (%f,%f)\n", g.vecinos[g.nodos[i]][j].x, g.vecinos[g.nodos[i]][j].y);
      }
      }*/

    g.dijkstra(maximoCamino, point((double)w, (double)h));
    //printf("La distancia minima hasta (%d,%d) es %f.\n", w,h,dist[point((double)w, (double)h)]);
    if (dist[point((double)w, (double)h)] <= maximoCamino){
      printf("I am lucky!\n");
    }else{
      printf("Boom!\n");
    }
   
  }
  return 0;
}
