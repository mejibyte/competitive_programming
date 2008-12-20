/*
  Accepted
 */
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>

#define D(x) cout << #x " is " << x << endl

const long double rho = 6371.01;//km
const long double pi = 2*acos(0.0);

struct Vector{
  long double x, y, z;
  long double dot(const Vector &t) const {
    return x*t.x + y*t.y + z*t.z;
  }
  long double mag() const{
    return sqrt(x*x + y*y + z*z);
  }
};

ostream& operator << (ostream &out, Vector &v){
  out << "<" << v.x << ", " << v.y << ", " << v.z << ">";
}

struct point{
  long double phi, theta;
  Vector toVector() const{
    Vector v;
    v.x = sin(phi)*cos(theta);
    v.y = sin(phi)*sin(theta);
    v.z = cos(phi);
    return v;
  }
};

istream& operator >> (istream &in, point &p){
  long double a, b, c, d, e, f;
  char X, Y;
  in >> a >> b >> c >> X >> d >> e >> f >> Y;

  long double latitude, longitude;
  latitude = (a + b/60.0 + c/3600.0);
  longitude = (d + e/60.0 + f/3600.0);

  p.phi = 90 + latitude * (X == 'N' ? -1.0 : 1.0);
  p.theta = longitude * (Y == 'E' ? -1.0 : 1.0);

  /*
  D(p.phi), D(p.theta);
  cout << endl;
  */

  p.phi *= pi/180.0, p.theta *= pi/180.0; //"radianize"

  return in;
}

long double dist(point &a, point &b){
  Vector va = a.toVector(), vb = b.toVector();

  /*
  cout << "Point A as a vector = " << va << endl;
  cout << "Point B as a vector = " << vb << endl;
  cout << endl;

  cout << "|A| = " << va.mag() << endl;
  cout << "|B| = " << vb.mag() << endl;
  */

  long double angle = acos(va.dot(vb));
  return rho * angle;
}

int main(){
  int n;
  for (scanf("%d", &n); n--; ){
    point a, b;
    cin >> a >> b;
    printf("%.2llf\n", dist(a, b));
  }

  return 0;
}
