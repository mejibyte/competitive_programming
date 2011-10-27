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
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

template <class T> string toStr(const T &x){ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x){ stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl

struct point{
  double x, y;
  point(){} point(double x, double y) : x(x), y(y) {}
  const point perp() const{
    return point(-y, x);
  }
  point operator - (const point &t) const{
    return point(x - t.x, y - t.y);
  }
  point operator + (const point &t) const{
    return point(x + t.x, y + t.y);
  }
  point operator / (double t) const{
    return point(x / t, y / t);
  }
};

point circle3points(const point &a, const point &b, const point &c){
  
}

int main(){
  double x0, y0, x1, y1, x2, y2;
  while (scanf("%lf%lf%lf%lf%lf%lf", &x0, &y0, &x1, &y1, &x2, &y2)==6){
    point a(x0, y0), b(x1, y1), c(x2, y2);

  }
  return 0;
}
