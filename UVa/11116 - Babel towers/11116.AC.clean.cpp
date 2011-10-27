/*
 Problem: 11116 - Babel towers
 (From the UVa Online Judge)

 Author: Andrés Mejía-Posada
 Date: April 20/2008
*/

#include <iostream>
#include <vector>

using namespace std;

const double EPS = 10E-9;

struct disc{
  double x, y, r;
};

//Represents a mass "m" with center of mass at point ("x", "y")
struct mass{
  double x, y, m;
  mass(){}
  mass(double X, double Y, double M) : x(X), y(Y), m(M){}
};


//Returns the new mass formed by combining both masses "a" and "b" into a punctual mass.
mass operator | (const mass &a, const mass &b){
  mass r;
  r.x = (a.x * a.m + b.x * b.m) / (a.m + b.m);
  r.y = (a.y * a.m + b.y * b.m) / (a.m + b.m);
  r.m = a.m + b.m;
  return r;
}

//True if the center of mass of "C" is outside the base of disc "D"
inline bool outside(const mass &c, const disc &d){
  return (c.x-d.x)*(c.x-d.x) + (c.y-d.y)*(c.y-d.y) >  d.r*d.r - EPS;
}

int main(){
  int n;
  while (cin >> n && n){

    vector<disc> d(n);
    for (int i=0; i<n; ++i){
      cin >> d[i].x >> d[i].y >> d[i].r;
    }

    int k;
    bool ok = true;
    for (int j=1; j < n && ok; ++j){
      mass c(d[j].x, d[j].y, d[j].r * d[j].r);

      for (int i=j-1; i >= 0 && ok; --i){
	if (outside(c, d[i])){
	  ok = false;
	  k = j;
	}
	c = c | mass(d[i].x, d[i].y, d[i].r*d[i].r);
      }
    }
    
    cout << (ok?"F":"Unf") << "easible";
    if (!ok) cout << " " << k;
    cout << endl;
    
  }
  return 0;
}
 
