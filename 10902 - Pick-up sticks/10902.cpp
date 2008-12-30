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
int main(){
  int n;
  while (scanf("%d", &n) && n){
    vector<segment> sticks;
    list<int> top;
    for (int i=0; i<n; ++i){
      double x0, y0, x1, y1;
      scanf("%lf %lf %lf %lf", &x0, &y0, &x1, &y1);
      sticks.push_back(segment(point(x0, y0), point(x1, y1)));
      for (list<int>::iterator j = top.begin(); j != top.end(); ++j){
        const segment &s = sticks[*j];
        bool b = segment_segment_intersection(s.first.first, s.first.second,
                                              s.second.first, s.second.second,
                                              x0, y0, x1, y1);
        /*
        printf("Intersection between <(%.2lf, %.2lf) - (%.2lf, %.2lf)> and "
               "<(%.2lf, %.2lf) - (%.2lf, %.2lf)> = %s\n", x0, y0, x1, y1,
               s.first.first, s.first.second, s.second.first, s.second.second,
               (b ? "true" : "false"));
        */

        if (b) j = top.erase(j), --j;
      }
      top.push_back(i);
    }
    printf("Top sticks:");
    int k = 0;
    for (list<int>::iterator i = top.begin(); k < top.size(); ++i, ++k){
      printf(" %d%c", *i + 1, (k < top.size()-1 ? ',' : '.'));
    }
    printf("\n");
  }
  return 0;
}
