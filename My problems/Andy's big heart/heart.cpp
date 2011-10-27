#include <math.h>
#include <iostream>
#include <algorithm>
#include <cassert>

#define EPSILON 0.000001

using namespace std;

struct Point{
  double x, y;
  bool operator < (const Point &p) const {
    return (x < p.x || (x == p.x && y < p.y));
  }
  
  double dist(const Point &p) const {
    return hypot(p.x-x, p.y-y);
  }

  void print(){
    cout << "("<<x<<","<<y<<")\n";
  }
};

struct Line{
  double a;
  double b;
  double c;
  void makePointSlopeLine(Point p, double m){
    a = -m;
    b = 1;
    c = -((a*p.x) + (b*p.y));
  }
  bool parallel(const Line &l) const {
    return ((fabs(a - l.a) <= EPSILON) && (fabs(b - l.b) <= EPSILON));
  }
  
  bool equals (const Line &l) const {
    return (parallel(l) && (fabs(c-l.c) <= EPSILON));
  }
  
  Point intersection(const Line &l) const {
    assert( !(equals(l)) );
    assert( !(parallel(l)));
    Point r;
    r.x = (l.b*c - b*l.c) / (l.a*b - a*l.b);
    if (fabs(b) > EPSILON){
      r.y = - (a * r.x + c) / b;
    }else{
      r.y = - (l.a * r.x + l.c) / l.b;
    }
    return r;
  }
};

int main(){
  Point p[3];
  for (int i=0; i<3; ++i){
    int x, y;
    cin >> x >> y;
    p[i].x = x;
    p[i].y = y;
  }
  while (p[0].x != 0 || p[0].y != 0 || p[1].x != 0 || p[1].y != 0 || p[2].x != 0 || p[2].y != 0){
    //Procesar caso aquí
    sort(p, p+3);

    // for (int i=0; i<3; ++i){
//       p[i].print();
//     }


    Point pm1, pm2;
    pm1.x = (p[0].x + p[1].x) / 2.0;
    pm1.y = (p[0].y + p[1].y) / 2.0;

    pm2.x = (p[1].x + p[2].x) / 2.0;
    pm2.y = (p[1].y + p[2].y) / 2.0;


    double m1, m2;
    m1 = (p[0].y - p[1].y)/(p[0].x - p[1].x);
    m2 = (p[1].y - p[2].y)/(p[1].x - p[2].x);

    double pmm1 = -1/m1;
    double pmm2 = -1/m2;
    //cout << pmm1<<" "<<pmm2<<endl;

    Line s1, s2;
    s1.makePointSlopeLine(pm1, pmm1);
    s2.makePointSlopeLine(pm2, pmm2);

    //if (s1.parallel(s2)){
    if (fabs(p[0].x*(p[1].y - p[2].y) +
 	     p[1].x*(p[2].y - p[0].y) +
	     p[2].x*(p[0].y - p[1].y)) < EPSILON){
      cout << "Andy's big heart will break.\n";
    }else{
      Point intersection = s1.intersection(s2);
      assert(intersection.dist(p[0]) - intersection.dist(p[1]) <= EPSILON);
      assert(intersection.dist(p[1]) - intersection.dist(p[2]) <= EPSILON);
      assert(intersection.dist(p[2]) - intersection.dist(p[0]) <= EPSILON);
	     //cout << intersection.dist(p[0])<<endl;
	     //cout << intersection.dist(p[1])<<endl;
	     //cout << intersection.dist(p[2])<<endl;
      
      printf("Andy should move to the house at point (%.3f, %.3f).\n", intersection.x, intersection.y);
    }




    //leer puntos
    for (int i=0; i<3; ++i){
      int x, y;
      cin >> x >> y;
      p[i].x = x;
      p[i].y = y;
    }
  }
  return 0;
}
