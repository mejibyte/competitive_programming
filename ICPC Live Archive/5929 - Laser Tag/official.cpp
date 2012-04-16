/* Laser Tag, MCPC 2011 Problem B, C++ solution by Michael Goldwasser */
/*
  Basic strategy is the following. If we could guess the precise
  sequence of mirrors against which a shot will reflect, then we can
  compute the precise firing angle to hit the origin.  This can be
  done by reflecting the goal across the last mirror, then across the
  second-to-last, and so on.  After doing this for all mirrors, the
  direct angle between the start and the modified goal is the proper
  firing angle.

  So we can generate all possible such mirror sequences (avoiding
  hitting the same mirror twice in a row); there are approximately 7^7
  of these.  For each, we calculate the ideal firing angle.  Then we
  have to retrace the actual path to ensure that it does hit the
  expected sequence of mirrors, and that it is not obstructed by any
  other mirrors along the way.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAX_MIRRORS 7
#define MAX_REFLECT 7


struct Point {
  double x,y;
  Point() : x(0.0), y(0.0) {};  // for convenience with arrays
  Point(double x, double y) : x(x), y(y) {};
};

struct Segment {
  Point end[2];
  Segment() {};
  Segment(double x1, double y1, double x2, double y2) {
    end[0] = Point(x1,y1);
    end[1] = Point(x2,y2);
  }

  Point perpendicular() const {
    return Point(end[1].y - end[0].y, end[0].x - end[1].x);  // 
  }

  // Returns the point at which a perpendicular from p to the
  // idealized infinite mirror intersects that line.
  Point snapTo(const Point& p) const {
    Point v = perpendicular();
    double t = (end[0].x * v.x + end[0].y * v.y - v.x*p.x - v.y*p.y) / (v.x*v.x + v.y*v.y);
    return Point(p.x + t*v.x, p.y + t*v.y);
  }

};


int n;
Segment mirror[MAX_MIRRORS];
int reflections[MAX_REFLECT];       // mirror indices
vector<double> solutions;           // approximate theta values for known solutions


// signed area of triangle ABC
double signedArea(Point a, Point b, Point c) {
  return ( (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y) ) / 2.0;
}

// does line(a,b) intersect segment(c,d)?
bool lineIntersectsSegment(const Point& a, const Point& b, const Point& c, const Point& d) {
  return ( (signedArea(a,b,c) > 0)  != (signedArea(a,b,d) > 0) );
}

bool segmentIntersectsSegment(const Point& a, const Point& b, const Point& c, const Point& d) {
  return lineIntersectsSegment(a,b,c,d) && lineIntersectsSegment(c,d,a,b);
}

Point computeIntersection(const Point& a, const Point& b, const Point& c, const Point& d) {
  Segment temp(a.x, a.y, b.x, b.y);
  Point perp = temp.perpendicular();
  double constant = perp.x * a.x + perp.y * a.y;
  double t = (constant - perp.x*c.x - perp.y*c.y) / (perp.x*(d.x-c.x) + perp.y*(d.y-c.y));
  return Point(c.x + t*(d.x-c.x), c.y + t*(d.y-c.y));
}

// Return point p, reflected across the (infinite) lined defined by mirror m
Point reflect(const Point& p, const Segment& m) {
  Point intersect = m.snapTo(p);
  Point delta(intersect.x-p.x, intersect.y-p.y);
  return Point(p.x + 2*delta.x, p.y + 2*delta.y);
}

// Assuming that we are shooting from origin to origin, while
// reflecting precisely off the first numReflect mirrors indicated
// in current reflections[] array, what is the initial firing angle?
double computeIdealAngle(int numReflect) {
  Point target(0,0);
  for (int k=numReflect-1; k >= 0; k--) {
    target = reflect(target, mirror[reflections[k]]);
  }

  // now we just need straight line from origin to target.
  double radians = atan2(target.y, target.x);  // note parameter order
  double degrees = radians * 180.0 / M_PI;
  if (degrees < -0.5) degrees += 360.0;      // should be between -0.5 and 359.49999
  return degrees;
}

// Is "ideal" firing angle legitimate, in that it really intersects
// expected mirrors, and avoids unexpected mirrors?
bool verify(double theta, int numReflect) {
  Point p(0,0);
  double radian = theta * M_PI / 180;
  Point dir(cos(radian), sin(radian));  // initial direction

  vector<Point> hops;
  hops.push_back(p);

  for (int k=0; k < numReflect; k++) {
    Segment& m(mirror[reflections[k]]);    // notational convenience
    Point forward(p.x+dir.x, p.y+dir.y);
    if (!lineIntersectsSegment(p, forward, m.end[0], m.end[1]))
      return false;    // Projected path missed the expected mirror

    Point pRefl = reflect(p,m);   // do this before changing p
    Point oldP = p;
    p = computeIntersection(p, forward, m.end[0], m.end[1]);

    if (dir.x*oldP.x + dir.y*oldP.y > dir.x*p.x + dir.y*p.y)
      return false;    // Cannot walk through a mirror
    hops.push_back(p);

    dir = Point(p.x - pRefl.x, p.y - pRefl.y);   // new direction after reflection
  }

  if (dir.x*p.x + dir.y*p.y > 0)
    return false;   // Cannot walk through last mirror to return to origin
  hops.push_back(Point(0,0));

  for (int k=0; k < numReflect + 1; k++)
    for (int j=0; j < n; j++)
      // check for interfering mirrors
      if (j != reflections[k] && (k == 0 || j != reflections[k-1]))
        if (segmentIntersectsSegment(hops[k], hops[k+1], mirror[j].end[0], mirror[j].end[1]))
          return false;  // obstacle interferes

  return true;    // must be valid!
}


void fillAndSolve(int numReflect=0) {
  if (numReflect < MAX_REFLECT) {
    for (int m=0; m < n; m++) {                                  // add every possible reflection
      if (numReflect == 0 || m != reflections[numReflect-1]) {   // avoiding immediately preceding choice
        reflections[numReflect] = m;

        // look for immediate solution
        double theta = computeIdealAngle(numReflect + 1);
        if (verify(theta, numReflect + 1))
          solutions.push_back(theta);

        // continue to look for recursive solutions with more reflections
        fillAndSolve(numReflect+1);
      }
    }
  }
}

int main() {
  while (true) {
    cin >> n;
    if (n == 0) break;

    for (int k=0; k<n; k++) {
      cin >> mirror[k].end[0].x >> mirror[k].end[0].y;
      cin >> mirror[k].end[1].x >> mirror[k].end[1].y;
    }

    // time for the real work
    solutions.clear();
    fillAndSolve();

    // consolidate results and output accordingly
    if (solutions.size() == 0)
      cout << "no danger" << endl;
    else {
      vector<int> clean;
      for (int k=0; k < solutions.size(); k++)
        clean.push_back((int) (solutions[k] + 0.5));

      sort(clean.begin(), clean.end());
      vector<int> uniq(clean.begin(), unique(clean.begin(), clean.end()));
      cout << uniq[0];
      for (int k=1; k < uniq.size(); k++)
        cout << " " << uniq[k];
      cout << endl;
    }
  }
}
