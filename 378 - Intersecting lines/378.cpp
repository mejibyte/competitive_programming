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
#include <map>
#include <set>

#define D(x) cout << #x " is " << x << endl

/*
  Finds the intersection between two lines (Not segments! Infinite lines)
  Line 1 passes through points (x0, y0) and (x1, y1).
  Line 2 passes through points (x2, y2) and (x3, y3).

  Handles the case when the 2 lines are the same (infinite intersections),
  parallel (no intersection) or only one intersection.
*/
void line_line_intersection(double x0, double y0,   double x1, double y1,
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
      //same line
      printf("LINE\n");
    }else{
      //just parallel
      printf("NONE\n");
    }
  }else{
    t0 /= det;
    t1 /= det;
    double x = x0 + t0*(x1-x0);
    double y = y0 + t0*(y1-y0);
    //intersection is point (x, y)
    printf("POINT %.2lf %.2lf\n", x, y);
  }
}

int main(){
  int n;
  scanf("%d", &n);
  printf("INTERSECTING LINES OUTPUT\n");
  while (n--){
    double x0,y0, x1,y1,    x2,y2, x3,y3;
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf",
          &x0, &y0, &x1, &y1, &x2, &y2, &x3, &y3);
    line_line_intersection(x0,y0, x1,y1,    x2,y2,  x3,y3);
  }
  printf("END OF OUTPUT\n");
  return 0;
}
