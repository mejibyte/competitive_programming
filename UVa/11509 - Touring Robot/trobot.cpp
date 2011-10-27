/*
Accepted
*/
#include<iostream>
#include<stdio.h>
#include<math.h>
#include<vector>
using namespace std;
#define D(x) cout<<__LINE__ <<": " <<#x<<" es "<<x<<endl

const double pi = acos(-1.0);

inline double toGrad(double a){ return 180*a / pi; }

struct point{
  double x, y;
  point(){} point(double x, double y) : x(x), y(y) {}
  const point operator-(const point &that) const{
    return point(this->x - that.x, this->y - that.y);
  }
  void print() const{printf("%lf %lf, inclination = %lf\n", x, y, toGrad(atan2(y, x)));}
};

/*
Retorna el ángulo de inclinación del vector p, barrido
en sentido antihorario a partir del eje X positivo.
0 <= angulo <= 2*pi
*/
double ccw(point p){
  double r = atan2(p.y, p.x);
  if (r < 0.0) r += 2*pi;
  return r;
}

double rotation(point a, point b, point c){
  //D(  asin(((b.x-a.x)*(c.y-b.y)-(b.y-a.y)*(c.x-b.x))/(hypot(b.x-a.x,b.y-a.y)*hypot(c.x-b.x,c.y-b.y)))*180.0/pi);
  double antes = ccw(b-a), despues = ccw(c-b);
  double giro = 0.0;
  if (despues > antes) giro = despues - antes;
  else if (antes > despues) giro = 2*pi - (antes - despues);
  //  a.print(),b.print(),c.print(), D(giro);
  return giro;    
}



int main(){
  //assert(freopen("trobot.in", "r", stdin) != NULL);
  int n;
  while (cin >> n && n){
    vector<point> p(n);
    for(int i=0;i<n && scanf("%lf%lf",&p[i].x,&p[i].y)!=EOF;++i);
    double ans=0.0;
    for(int i=0; i<n ;++i)ans+=rotation(p[i],p[(i+1)%n],p[(i+2)%n]);//, D(ans);
    printf("%.0lf\n",ans/(2*pi));
  }
  return 0;
}
