// Accepted
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

#define EPS 1e-9

typedef pair<int, int> point;
typedef vector< point > polygon;

vector< polygon > polygons;

const int MAXN = 50;
int p[MAXN];

int find(int u) {
    return p[u] == u ? u : p[u] = find(p[u]);
}

void link(int u, int v) {
    if (find(u) != find(v)) {
        p[find(u)] = find(v);
    }
}

// Polar angle
// Returns an angle in the range [0, 2*Pi) of a given Cartesian point.
// If the point is (0,0), -1.0 is returned.
// REQUIRES:
// include math.h
// define EPS 0.000000001, or your choice
// P has members x and y.
double polarAngle( point p ) {  
    double x = p.first, y = p.second;
    if(fabs(x) <= EPS && fabs(y) <= EPS) return -1.0;
    if(fabs(x) <= EPS) return (y > EPS ? 1.0 : 3.0) * acos(0);
    double theta = atan(1.0 * y / x);
    if(x > EPS)
      return (y >= -EPS ? theta : (4*acos(0) + theta));
    else
      return(2 * acos( 0 ) + theta);
}

//Point inside polygon
// Returns true iff p is inside poly.
// PRE: The vertices of poly are ordered (either clockwise or
//      counter-clockwise.
// POST: Modify code inside to handle the special case of "on
// an edge".
// REQUIRES:
// polarAngle()
// include math.h
// include vector
// define EPS 0.000000001, or your choice
bool pointInPoly( point p, const polygon &poly ) {
  int n = poly.size();
  double ang = 0.0;
  for(int i = n - 1, j = 0; j < n; i = j++){
    point v( poly[i].first - p.first, poly[i].second - p.second );
    point w( poly[j].first - p.first, poly[j].second - p.second );
    double va = polarAngle(v);
    double wa = polarAngle(w);
    double xx = wa - va;
    if(va < -0.5 || wa < -0.5 || fabs(fabs(xx)-2*acos(0)) < EPS){
        // POINT IS ON THE EDGE
        return true;
        assert( false );
        ang += 2 * acos( 0 );
        continue;
      }
    if( xx < -2 * acos( 0 ) ) ang += xx + 4 * acos( 0 );
    else if( xx > 2 * acos( 0 ) ) ang += xx - 4 * acos( 0 );
    else ang += xx;
  }
  return( ang * ang > 1.0 );
}


/*
  Returns true if point (x, y) lies inside (or in the border)
  of box defined by points (x0, y0) and (x1, y1).
*/
bool point_in_box(double x, double y,
                  double x0, double y0,
                  double x1, double y1){
  return
    min(x0, x1) <= x && x <= max(x0, x1) &&
    min(y0, y1) <= y && y <= max(y0, y1);
}


/*
  Finds the intersection between two segments (Not infinite
  lines!)
  Segment 1 goes from point (x0, y0) to (x1, y1).
  Segment 2 goes from point (x2, y2) to (x3, y3).

  (Can be modified to find the intersection between a segment
  and a line)

  Handles the case when the 2 segments are:
  *Parallel but don't lie on the same line (No intersection)
  *Parallel and both lie on the same line (Infinite
  *intersections or no intersections)
  *Not parallel (One intersection or no intersections)

  Returns true if the segments do intersect in any case.
*/
bool segment_segment_intersection(int x1, int y1,
                                  int x2, int y2,
                                  
                                  int x3, int y3,
                                  int x4, int y4){

    int d1 = (x1 - x3) * (y4 - y3) - (y1 - y3) * (x4 - x3);
    int d2 = (x2 - x3) * (y4 - y3) - (y2 - y3) * (x4 - x3);
    int d3 = (x3 - x1) * (y2 - y1) - (y3 - y1) * (x2 - x1);
    int d4 = (x4 - x1) * (y2 - y1) - (y4 - y1) * (x2 - x1);    
    
    bool b1 = d1 > 0 and d2 < 0 or d1 < 0 and d2 > 0;
    bool b2 = d3 > 0 and d4 < 0 or d3 < 0 and d4 > 0;
    if (b1 and b2) return true;
    if (d1 == 0 and point_in_box(x1, y1,   x3, y3, x4, y4)) return true;
    if (d2 == 0 and point_in_box(x2, y2,   x3, y3, x4, y4)) return true;
    if (d3 == 0 and point_in_box(x3, y3,   x1, y1, x2, y2)) return true;
    if (d4 == 0 and point_in_box(x4, y4,   x1, y1, x2, y2)) return true;
    return false;        
}

bool polygonsIntersect(const polygon &a, const polygon &b) {
    int na = a.size(), nb = b.size();
    for (int i = 0; i < na; ++i) {
        if (pointInPoly(a[i], b)) return true;
    }
    for (int i = 0; i < nb; ++i) {
        if (pointInPoly(b[i], a)) return true;
    }
    
    for (int i = 0; i < na; ++i) {
        for (int j = 0; j < nb; ++j) {
            int xa1 = a[i].first, ya1 = a[i].second;
            int xa2 = a[(i + 1) % na].first, ya2 = a[(i + 1) % na].second;
            int xb1 = b[j].first, yb1 = b[j].second;
            int xb2 = b[(j + 1) % nb].first, yb2 = b[(j + 1) % nb].second;
            if (segment_segment_intersection(xa1, ya1,    xa2, ya2,               xb1, yb1, xb2, yb2)) {
                return true;
            }
        }
    }
    
    
    return false;
}


void solve() {
    int n = polygons.size();
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (polygonsIntersect(polygons[i], polygons[j])) {
                link(i, j);
            }
        }
    }
    set<int> ans;
    for (int i = 0; i < n; ++i) {
        ans.insert(find(i));
    }
    cout << ans.size() << endl;
}


int main(){
    int n;
    while (cin >> n) {
        if (n == 0) break;
        string s; getline(cin, s);
        polygons.clear();
        for (int i = 0; i < n; ++i){
            polygons.push_back(polygon());
            getline(cin, s);
            stringstream sin(s);
            int x, y;
            while (sin >> x >> y) {
                polygons.back().push_back(point(x, y));
            }
            assert(polygons.back().size() >= 3);
        }
        assert(polygons.size() == n);
        
        solve();
    }
    return 0;
}