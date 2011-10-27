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

#define D(x) cout << #x " is " << x << endl


/*
  Returns true if point (x, y) lies inside (or in the border)
  of box defined by points (x0, y0) and (x1, y1).
*/
bool point_in_box(double x, double y,
                  double x0, double y0,    double x1, double y1){
  return min(x0, x1) <= x && x <= max(x0, x1) && min(y0, y1) <= y && y <= max(y0, y1);
}

/*
  Finds the intersection between two segments (Not infinite lines!)
  Segment 1 goes from point (x0, y0) to (x1, y1).
  Segment 2 goes from point (x2, y2) to (x3, y3).

  Handles the case when the 2 segments are:
  *Parallel but don't lie on the same line (No intersection)
  *Parallel and both lie on the same line (Infinite intersections or no intersections)
  *Not parallel (One intersection or no intersections)

  Returns true if the segments do intersect in any case.
*/
bool segment_segment_intersection(double x0, double y0,   double x1, double y1,
                                  double x2, double y2,   double x3, double y3){
#ifndef EPS
#define EPS 1e-9
#endif

  double t0 = (y3-y2)*(x0-x2)-(x3-x2)*(y0-y2);
  double t1 = (x1-x0)*(y2-y0)-(y1-y0)*(x2-x0);
  double det = (y1-y0)*(x3-x2)-(y3-y2)*(x1-x0);
  if (fabs(det) < EPS){
    //parallel
    if (fabs(t0) < EPS || fabs(t1) < EPS){
      //they lie on same line, but they may or may not intersect.
      return (point_in_box(x0, y0,   x2, y2, x3, y3) ||
              point_in_box(x1, y1,   x2, y2, x3, y3) ||
              point_in_box(x2, y2,   x0, y0, x1, y1) ||
              point_in_box(x3, y3,   x0, y0, x1, y1));
    }else{
      //just parallel, no intersection
      return false;
    }
  }else{
    t0 /= det;
    t1 /= det;
    /*
      0 <= t0 <= 1 if the intersection point lies in segment 1.
      0 <= t1 <= 1 if the intersection point lies in segment 2.
    */
    if (0.0 <= t0 && t0 <= 1.0 && 0.0 <= t1 && t1 <= 1.0){
      double x = x0 + t0*(x1-x0);
      double y = y0 + t0*(y1-y0);
      //intersection is point (x, y)
      return true;
    }
    //the intersection points doesn't lie on both segments.
    return false;
  }
}

typedef pair<double, double> point;
typedef pair<point, point> segment;

bool point_in_box(point x, point a, point b){
  return point_in_box(x.first, x.second, a.first, a.second, b.first, b.second);
}

bool segment_segment_intersection(segment a, segment b){
  return segment_segment_intersection(a.first.first, a.first.second,
                                      a.second.first, a.second.second,
                                      b.first.first, b.first.second,
                                      b.second.first, b.second.second);
}


int main(){
  int n;
  scanf("%d", &n);
  while (n--){
    double x0, y0, x1, y1, x2, y2, x3, y3;
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf",
          &x0, &y0, &x1, &y1, &x2, &y2, &x3, &y3);
    bool boom =
      point_in_box(x0, y0, x2, y2, x3, y3) ||
      point_in_box(x1, y1, x2, y2, x3, y3);

    point a, b, c, d;
    a = point(x2, y2);
    b = point(x2, y3);
    c = point(x3, y2);
    d = point(x3, y3);

    segment line = segment(point(x0, y0), point(x1, y1));
    boom |=
      segment_segment_intersection(line, segment(a, b)) ||
      segment_segment_intersection(line, segment(a, c)) ||
      segment_segment_intersection(line, segment(b, d)) ||
      segment_segment_intersection(line, segment(c, d));

    printf("%s\n", (boom ? "T" : "F"));

  }
  return 0;
}
