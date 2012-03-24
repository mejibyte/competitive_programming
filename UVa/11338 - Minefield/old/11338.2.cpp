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
    if (vecinos.count(a)) return;
    nodos.push_back(a);
    if (vecinos.size() == 0){
      vector<point> v;
      vecinos.insert(make_pair(a, v));
    }

    //printf("vecinos.begin() apunta a (%f,%f)\n", (*vecinos.begin()).first.x, (*vecinos.begin()).first.y);

    map< point, vector<point> >::iterator lower, upper;
    lower = vecinos.lower_bound(point(a.x-1.5, a.y-1.5));
    //if (lower == vecinos.begin()) printf("Lower == vecinos.begin() que apunta a (%f,%f)\n", (*vecinos.begin()).first.x, (*vecinos.begin()).first.y);
    //if (lower == vecinos.end()) printf("Lower == vecinos.end()\n");

    if (lower != vecinos.begin()) --lower;
    upper = vecinos.upper_bound(point(a.x+1.5, a.y+1.5));

    printf("Todos los vecinos de (%f,%f) deben estar entre: (%f,%f) y (%f,%f)\n", a.x, a.y,
	   (*lower).first.x, (*lower).first.y, (*upper).first.x, (*upper).first.y);

    
    
    map< point, vector<point> >::iterator it;
    for (it=lower; it != upper; ++it){
      //Insertarlo como vecino en los nodos diferentes a el mismo
      if ((*it).first != a){
	vector<point> adj = vecinos[(*it).first];
	//Asegurarse de no insertar un vecino repetido
	if (distancia(a, (*it).first) <= 1.5){
	  //printf("Insertando (%f,%f) como vecino de (%f,%f).\n", a.x, a.y, nodos[i].x, nodos[i].y);
	  vecinos[(*it).first].push_back(a);
	  vecinos[a].push_back((*it).first);
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
    

    priority_queue<point, vector<point>, heapCompare > q;
    q.push(point(0.0, 0.0));

    while (!q.empty()){

      point u = q.top();
      q.pop();

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
    }
  }

  void printMap(){
    printf("Voy a imprimir los elementos del mapa en orden.\n");
    map< point, vector<point> >::iterator i;// = vecinos.begin();
    for (i = vecinos.begin(); i != vecinos.end(); ++i){
      printf("  (%f,%f)\n", (*i).first.x, (*i).first.y);
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
    g.insert(point(0.00, 0.00));
    g.insert(point((double)w, (double)h));
    int noPuntos;
    cin >> noPuntos;
    for (int i=0; i<noPuntos; ++i){
      double x,y;
      cin >> x >> y;
      g.insert(point(x,y));
    }

  
    cout << "Termine de insertar todos los nodos.\n";

    g.printMap();


    double maximoCamino;
    cin >> maximoCamino;

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
