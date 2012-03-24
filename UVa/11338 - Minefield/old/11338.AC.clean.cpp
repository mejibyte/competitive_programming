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
double distancia(point a, point b){return hypot(a.y-b.y, a.x-b.x);}


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
  }

  void make_vecinos(double maxPath){
    for (map< point, vector<point> >::iterator it=vecinos.begin(); it!=vecinos.end(); ++it){
      if (distancia((*it).first, point(0.00, 0.00)) > maxPath){
	continue;
      }
      for (map< point, vector<point> >::iterator jt = it; jt!=vecinos.end(); ++jt){
	if ((*it).first != (*jt).first){
	  if ((*jt).first.x - (*it).first.x > 1.5){
	    break;
	  }
	  vector<point> adj = vecinos[(*it).first];
	  if (distancia((*jt).first, (*it).first) <= 1.5){
	    vecinos[(*it).first].push_back((*jt).first);
	    vecinos[(*jt).first].push_back((*it).first);
	  }
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

  void dijkstra(const double &maxPath, const point &finalPoint){
    initialize();
    
    priority_queue<point, vector<point>, heapCompare > q;
    q.push(point(0.0, 0.0));
    while (!q.empty()){
      point u = q.top();
      q.pop();
      if (distancia(point(0.00, 0.00), u) + distancia(u, finalPoint) <= maxPath){
	for (int i=0; i<vecinos[u].size(); ++i){
	  point v = vecinos[u][i];
	  if (dist[vecinos[u][i]] > (dist[u] + distancia(u,v))){
	    dist[vecinos[u][i]] = dist[u] + distancia(u, v);
	    q.push(v);
	  }
	}
      }
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

    g.dijkstra(maximoCamino, point((double)w, (double)h));
    if (dist[point((double)w, (double)h)] <= maximoCamino){
      printf("I am lucky!\n");
    }else{
      printf("Boom!\n");
    }
   
  }
  return 0;
}
