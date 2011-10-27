// PROBLEMA DE GEOMETIRA, 2 cortes en una torta, y calcula el volumen de cada pedazo :D

#include <algorithm>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <stack>
#include <sstream>
#include <queue>

#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>

#define REP(i, n) for(int i=0;i<int(n);i++)
#define foreach(it, c)  for(typeof((c).begin()) it = (c).begin();it!=(c).end();++it)
#define ALL(x)   (x).begin(),(x).end()
#define SORT(x) sort(ALL(x))
using namespace std;
#define VI vector<int>
#define VS vector<string>
#define PB push_back
typedef struct{
	double x, y;
}point;
typedef struct{
	double a, b, c;
}line;
#define EPS 1e-7
int signo(double a){
	if( a >= 0.0 ) return 1; 
	return -1;
}
double prodcruz(point p1, point p2, point p3){
	double x1, x2, y1, y2;
	x1 = p2.x-p1.x; x2 = p3.x-p1.x;
	y1 = p2.y-p1.y; y2 = p3.y-p1.y;
	return fabs(x1*y2-x2*y1)/2.0;
}
double prodcruz2(point p1, point p2, point p3){
	double x1, x2, y1, y2;
	x1 = p2.x-p1.x; x2 = p3.x-p1.x;
	y1 = p2.y-p1.y; y2 = p3.y-p1.y;
	return (x1*y2-x2*y1)/2.0;
}
int equal(double a, double b){if( fabs(a-b) < EPS) return 1; return 0;}
void points_to_line(point p1, point p2, line & l){
	if(equal(p1.x, p2.x)){
		l.a = 1;
		l.b = 0;
		l.c = -p1.x;
	}else{
		l.b = 1;
		l.a = -(p1.y-p2.y)/(p1.x-p2.x);
		l.c = -(l.a*p1.x)-(l.b*p1.y);
	}
}
double R;
double dist(point p1, point p2){
	double ax, ay;
	ax = p1.x-p2.x;
	ay = p1.y-p2.y;
	return sqrt(ax*ax+ay*ay);
}
double area(point p1, point p2, point p3){
	double a, b, c;
	point p;
	p.x = 0.0; p.y = 0.0;
	a = dist(p2,p1);
	b = dist(p2,p);
	c = dist(p1,p);
	double aux = a*a-b*b-c*c;
	aux /= (-2.0*b*c);
	double angle = acos(aux);
	double prop = angle/(acos(-1)*2.0);
	if( signo(prodcruz2(p1,p2,p3)) == signo(prodcruz2(p1,p2,p))){
		prop *= (acos(-1)*R*R);
		prop -= prodcruz(p1,p2,p);
		prop += prodcruz(p1,p2,p3);
	}else{
		prop =  1.0-prop;
		prop *= (acos(-1)*R*R);
		prop += prodcruz(p1,p2,p);
		prop += prodcruz(p1,p2,p3);
	}
	return prop;
}
void intersection_point(line l1, line l2, point &p){
	p.x = (l2.b*l1.c-l1.b*l2.c) / (l2.a*l1.b-l1.a*l2.b);
	if( fabs(l1.b) > EPS )
		p.y = -(l1.a*p.x+l1.c)/l1.b;
	else
		p.y = -(l2.a*p.x+l2.c)/l2.b;
}
double cuad(double a) { return a*a;}
double complementox(double x, line l){
	double y =  sqrt(cuad(R)-cuad(x));
	if( !equal(l.a*x+l.b*y+l.c, 0.0) ) return -y;
	return y;
}
double complementoy(double y, line l){
	double x =  sqrt(cuad(R)-cuad(y));
	if( !equal(l.a*x+l.b*y+l.c, 0.0) ) return -x;
	return x;
}
void line_to_points(line l, point &p1, point &p2){
	if(equal(l.b, 0.0)){
		double a , b, c;
		a = cuad(l.b)/cuad(l.a)+1.0;
		b = (2.0*l.c*l.b)/cuad(l.a);
		c = cuad(l.c)/cuad(l.a)-cuad(R);
		p1.y = (-b+sqrt(b*b-4.0*a*c))/(2.0*a);
		p2.y = (-b-sqrt(b*b-4.0*a*c))/(2.0*a);
		p1.x = complementoy(p1.y, l);
		p2.x = complementoy(p2.y, l);
	}else{
		double a, b, c;
		a = cuad(l.a)/cuad(l.b)+1.0;
		b = (2.0*l.c*l.a)/cuad(l.b);
		c = cuad(l.c)/cuad(l.b)-cuad(R);
		p1.x = (-b+sqrt(b*b-4.0*a*c))/(2.0*a);
		p2.x = (-b-sqrt(b*b-4.0*a*c))/(2.0*a);
		p1.y = complementox(p1.x, l);
		p2.y = complementox(p2.x, l);
	}
}
int main(){
	int i , j, k;
	int radio, h;
	while(scanf("%i %i", &radio, &h) != EOF){
		R = (double)radio;
		double x[4], y[4];
		REP(i, 4)scanf("%lf %lf", &x[i], &y[i]);
		point p[4];
		REP(i, 4)p[i].x = x[i], p[i].y = y[i];
		line l1, l2;
		points_to_line(p[0], p[1], l1);
		points_to_line(p[2], p[3], l2);
		line_to_points(l1, p[0], p[1]);
		line_to_points(l2, p[2], p[3]);
		point P;
		intersection_point(l1, l2, P);
		double areas[4];
		areas[0] = area(p[0], p[2], P);
		areas[1] = area(p[0], p[3], P);
		areas[2] = area(p[1], p[2], P);
		areas[3] = area(p[1], p[3], P);
		sort(areas, areas+4);
		printf("%.2lf %.2lf\n", (areas[3])*(double)h, (areas[0])*(double)h);
	}
	return 0;
}
