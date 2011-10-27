/*
  Accepted

  This is a cleaner version of 10897.cpp
 */
using namespace std;
#include <iostream>
#include <cmath>

const long double rho = 6371.01;//km
const long double pi = 2*acos(0.0);

struct Vector{
  //A geometrical vector
  long double x, y, z;
  long double dot(const Vector &t) const{
    return x*t.x + y*t.y + z*t.z;
  }
  long double mag() const{
    return sqrt(x*x + y*y + z*z);
  }
};

struct point{
  //A point in spherical coordinates
  //assuming rho = 1
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

  p.phi *= pi/180.0, p.theta *= pi/180.0; //"radianize"
  return in;
}

long double dist(point &a, point &b){
  //Convert shperical coordinates to rectangular coordinates...
  Vector va = a.toVector(), vb = b.toVector();
  //find angle between the two vectors...
  long double angle = acos(va.dot(vb) / (va.mag()*vb.mag()) );
  //calculate length of circle arc... (rho is the radius)
  return rho * angle;
}

int main(){
  int n;
  for (scanf("%d", &n); n--; ){
    point a, b;
    cin >> a >> b;
    cout.precision(2);
    cout << fixed << dist(a, b) << endl;
  }
  return 0;
}
