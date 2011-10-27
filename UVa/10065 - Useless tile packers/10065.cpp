#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>

using namespace std;



struct point{
  int x,y;
  point(int X, int Y) : x(X), y(Y) {}
};

point pivot(10000, 10000);

ostream& operator<< (ostream& out, const point& c)
{
  out << "(" << c.x << "," << c.y << ")";
  return out;
}

double area(const vector<point> &p){
  double r = 0.0;
  for (int i=0; i<p.size(); ++i){
    int j = (i+1) % p.size();
    r += p[i].x*p[j].y - p[j].x*p[i].y;
  }
  return r/2.0;
}

//retorna si c esta a la izquierda de el segmento AB
int cross(const point &a, const point &b, const point &c){
  return (b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y);
}

bool angleCmp(const point &self, const point &that){
  return( cross(pivot, that, self) < 0 );
}

int distsqr(point a,  point b){
  return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

//vector p tiene los puntos ordenados anticlockwise
vector<point> graham(vector<point> p){
  pivot = p[0];
  sort(p.begin(), p.end(), angleCmp);
  for (int i=1; i<p.size()-1; ++i){    
    if (cross(p[0], p[i], p[i+1]) == 0){
      if (distsqr(p[0], p[i]) < distsqr(p[0], p[i+1])){
	p.erase(p.begin() + i);
      }else{
	p.erase(p.begin() + i + 1);
      }
      i--;
    }
  }
  
  /*cout << "Candidatos para el Convex Hull: " << endl;
  for (int i=0; i<p.size(); ++i) cout << p[i] << " ";
  cout << endl;*/

  vector<point> chull(p.begin(), p.begin()+3);

  //Ahora sí!!!
  for (int i=3; i<p.size(); ++i){
    while ( chull.size() >= 2 && cross(chull[chull.size()-2], chull[chull.size()-1], p[i]) < 0){
      chull.erase(chull.end() - 1);
    }
    chull.push_back(p[i]);
  }

  /*  cout << "Nuestro Chull es: " << endl;
  for (int i=0; i<chull.size(); ++i) cout << chull[i] << " ";
  cout << endl;*/
  
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

    /*cout << cross(p[0], p[1], p[2]) << endl;
      cout << "El punto " << p[2] << " esta a la " << (cross(p[0], p[1], p[2]) < 0 ? "derecha":"izquierda") << " del segmento " << p[0] << p[1] << endl;*/


    double tileArea = area(p);
    vector<point> sortedP;

    if (tileArea > 0){
      for (int j=minPos,cuenta=1; cuenta<=p.size(); ++cuenta, j = (j+1)%p.size()){
	sortedP.push_back(p[j]);
      }
    }else{
      for (int j=minPos, cuenta=1; cuenta<=p.size(); ++cuenta, j = (j-1 < 0?j-1+p.size():j-1)){
	sortedP.push_back(p[j]);
      }
    }
    //cout << "Area es: " << area(p) << endl;
    /*for (int i=0; i<sortedP.size(); ++i) cout << sortedP[i] << " ";
      cout << endl;*/
    tileArea = fabs(tileArea);
    double chullArea = fabs(area(graham(sortedP)));
    
    cout << "Tile #"<<tileNo++<<endl;
    printf("Wasted Space = %.2f \%\n\n",  (chullArea - tileArea) * 100.0 / chullArea);
   
  }
  return 0;
}
