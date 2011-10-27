#include <iostream>
#include<stdio.h>
#include<math.h>
using namespace std;
struct point{
  double x;
  double y;
  point(double X,double Y){
    x=X;
    y=Y;
  }
};

double operator |(point &a,point &b){
  //return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
  return hypot(a.x-b.x, a.y-b.y);
}

const double pi = 2*acos(0);
int main(){
  

  double x1,x2,x3,y1,y2,y3;
  
  while(cin>>x1>>y1>>x2>>y2>>x3>>y3){
    point p(x1,y1);
    point q(x2,y2);
    point r(x3,y3);
    printf("%.2f\n",fabs(pi*(q|r)*(p|q)*(p|r)/((q.x-p.x)*(r.y-p.y)-(q.y-p.y)*(r.x-p.x))));
  }

  return 0;
}
