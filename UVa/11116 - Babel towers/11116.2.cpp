/*
 Problem: 11116 - Babel towers
 (From the UVa Online Judge)

 Author: Andrés Mejía-Posada
 Date: April 20/2008
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

const double EPS = 10E-9;

struct disc{
  double x, y, r;
  disc(){}
  disc(double X, double Y, double R) : x(X), y(Y), r(R){}
};

//Represents a mass "m" centered at point ("x", "y")
struct center{
  double x, y, m;
  center(){}
  center(double X, double Y, double M) : x(X), y(Y), m(M){}
  center &operator = (const center &b){
    x = b.x;
    y = b.y;
    m = b.m;
    return *this;
  }
};


//Returns the new mass formed by combining both masses "a" and "b" into a puntual mass.
center operator | (const center &a, const center &b){
  center r;
  r.x = (a.x * a.m + b.x * b.m) / (a.m + b.m);
  r.y = (a.y * a.m + b.y * b.m) / (a.m + b.m);
  r.m = a.m + b.m;
  return r;
}

//For debugging
ostream& operator<<( ostream& out, const center &c) {
  out << setprecision(2) << "(" << c.x << ", " << c.y << ", " << c.m << ")";
  return out;
}

//For debugging
ostream& operator<<( ostream& out, const disc &c) {
  out << setprecision(2) << "(" << c.x << ", " << c.y << ", " << c.r << ")";
  return out;
}


//True if the center of mass "C" is outside of the base of disc "D"
inline bool outside(const center &c, const disc &d){
  return fabs((c.x-d.x)*(c.x-d.x) + (c.y-d.y)*(c.y-d.y)) >  d.r*d.r - EPS;
}

int main(){
  int n;
  while (cin >> n && n){

    vector<disc> d(n);
    for (int i=0; i<n; ++i){
      double x, y, r;
      cin >> x >> y >> r;
      d[i] = disc(x, y, r);
      
    }

    int k;
    bool ok = true;
    for (int j=1; j < n && ok; ++j){
      center c(d[j].x, d[j].y, d[j].r * d[j].r);

      for (int i=j-1; i >= 0 && ok; --i){
	if (outside(c, d[i])){
	  ok = false;
	  k = j;
	}
	c = c | center(d[i].x, d[i].y, d[i].r*d[i].r);
      }
    }
    
    cout << (ok?"F":"Unf") << "easible";
    if (!ok) cout << " " << k;
    cout << endl;
    
  }
  return 0;
}
