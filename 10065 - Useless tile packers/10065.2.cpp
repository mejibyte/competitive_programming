#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>

using namespace std;

struct point{
  int x,y;
  point() {}
  point(int X, int Y) : x(X), y(Y) {}
};

point pivot;

ostream& operator<< (ostream& out, const point& c)
{
  out << "(" << c.x << "," << c.y << ")";
  return out;
}

//P es un polígono ordenado anticlockwise.
//Si es clockwise, retorna el area negativa.
//Si no esta ordenado retorna pura mierda.
//P[0] != P[n-1]
double area(const vector<point> &p){
  double r = 0.0;
  for (int i=0; i<p.size(); ++i){
    int j = (i+1) % p.size();
    r += p[i].x*p[j].y - p[j].x*p[i].y;
  }
  return r/2.0;
}

//retorna si c esta a la izquierda de el segmento AB
inline int cross(const point &a, const point &b, const point &c){
  return (b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y);
}

//Self < that si esta a la derecha del segmento Pivot-That
bool angleCmp(const point &self, const point &that){
  return( cross(pivot, that, self) < 0 );
}

inline int distsqr(const point &a, const point &b){
  return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

//vector p tiene los puntos ordenados anticlockwise
vector<point> graham(vector<point> p){
  pivot = p[0];
  sort(p.begin(), p.end(), angleCmp);
  //Ordenar por ángulo y eliminar repetidos.
  //Si varios puntos tienen el mismo angulo se borran todos excepto el que esté más lejos
  for (int i=1; i<p.size()-1; ++i){    
    if (cross(p[0], p[i], p[i+1]) == 0){ //Si son colineales...
      if (distsqr(p[0], p[i]) < distsqr(p[0], p[i+1])){ //Borrar el mas cercano
	p.erase(p.begin() + i);
      }else{
	p.erase(p.begin() + i + 1);
      }
      i--;
    }
  }
  
  vector<point> chull(p.begin(), p.begin()+3);

  //Ahora sí!!!
  for (int i=3; i<p.size(); ++i){
    while ( chull.size() >= 2 && cross(chull[chull.size()-2], chull[chull.size()-1], p[i]) < 0){
      chull.erase(chull.end() - 1);
    }
    chull.push_back(p[i]);
  }

  return chull;
}

int main(){
  int n;
  int tileNo = 1;
  while (cin >> n && n){
    vector<point> p;
    point min(10000, 10000);
    int minPos;
    for (int i=0; i<n; ++i){
      int x, y;
      cin >> x >> y;
      p.push_back(point(x,y));      
      if (y < min.y || (y == min.y && x < min.x )){
	min = point(x,y);
	minPos = i;
      }
    }
    double tileArea = fabs(area(p));

    //Destruye el orden cw|ccw poligono, pero hay que hacerlo por que Graham necesita el pivote en p[0]
    swap(p[0], p[minPos]);
    pivot = p[0];
    double chullArea = fabs(area(graham(p)));
    
    printf("Tile #%d\n", tileNo++);
    printf("Wasted Space = %.2f \%\n\n",  (chullArea - tileArea) * 100.0 / chullArea);
   
  }
  return 0;
}
