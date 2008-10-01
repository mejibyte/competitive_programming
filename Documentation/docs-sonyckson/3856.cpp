#include <algorithm>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>
#include <queue>

#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>

#define forn(i, n) for(int i=0;i<int(n);i++)
#define FOR(i, a, b) for(int i=(a);i<int(b);i++)
#define RFOR(i, b, a) for(int i=(b);i>int(a);i--)
#define foreach(it, c)  for(__typeof((c).begin()) it = (c).begin();it!=(c).end();++it)
#define ALL(x)   (x).begin(),(x).end()
#define SIZE(x)   (int)(x).size()
#define SORT(x) sort(ALL(x))
using namespace std;
#define VI vector<int>
#define VS vector<string>
#define PB push_back
#define ISS istringstream
#define OSS ostringstream
typedef long long ll;
// NUNCA DEFINIR int max....
#define M 100000
class point{
	public:
		double x, y;
		point(){};
		point(double xx, double yy){x=xx,y=yy;}
};
class object{
	public:
		string tipo;
		point p1, p2;
		object(){};
};
object objects[110];
bool mark[110];
#define D double
#define EPS 1e-9
#define SQ(a)  (a*a)
int N;
D X, Y;
bool inRange(double x, double mx, double Mx){
	if( x+EPS > mx && x < Mx+EPS ) return true;
	return false;
}
void print(point p){
// 	printf("%lf %lf\n", p.x, p.y);
}
bool intersect(point p1, point p2, int ind){
	D A1, B1, C1, A2, B2, C2;
	A1 = p2.y - p1.y, B1 = p1.x - p2.x;C1 = A1 * p1.x + B1 * p1.y;
	object O = objects[ind];
	A2 = O.p2.y - O.p1.y, B2 = O.p1.x - O.p2.x; C2 = A2 * O.p1.x + B2 * O.p1.y;
	print(p1) , print(p2), print(O.p1), print(O.p2);
	D det = A1 * B2 - B1 * A2;
	X =  ( C1 * B2 - C2 * B1 ) / det;
	Y =  ( A1 * C2 - A2 * C1 ) / det;
	print(point(X,Y));
	if( inRange(X, min(O.p1.x, O.p2.x) , max(O.p2.x, O.p1.x)) ){
		if( inRange(Y,min(O.p1.y,O.p2.y), max(O.p1.y,O.p2.y)) )
			return true;
	}
// 	printf("y no..\n");
	return false;
}

bool EQ(double a, double b){if( fabs(a-b) < EPS ) return true; return false;}
double dist(point p1, point p2){
	double x = p2.x-p1.x, y = p2.y - p1.y;
	return sqrt(x*x+y*y);
}
int cruz(point p1, point p2, point p3){
	double x1, y1, x2, y2;
	x1 = p2.x-p1.x, y1 = p2.y - p1.y;
	x2 = p3.x-p1.x, y2 = p3.y - p1.y;
	double det = x1*y2-x2*y1;
	if( det >0. ) return 1;
	return -1;
}
void back(D x1, D y1, D x2, D y2, int last){
// 	printf("%lf %lf %lf %lf %i\n", x1, y1, x2, y2, last);
	int i,j ,k;
	point p;
	int have = 0;
	int ind;
	point aux(x1+(y2-y1), y1+(x2-x1));
	int sign = cruz(point(x1,y1), aux, point(x2,y2));
	for(i=0;i<N;i++){
		if( i == last ) continue;
		if(intersect(point(x1,y1), point(x2,y2), i) ){
			double d1, d2;
			d1 = dist(point(X,Y), point(x1,y1)), d2 = dist(point(x1,y1),point(x2,y2));
// 			if( EQ(d1+d2, dist(point(X,Y), point(x2,y2))) ) continue;
			if( cruz(point(x1,y1),aux,point(X,Y)) != sign ) continue;
			if( have ){
				if( dist(point(x1,y1),point(X,Y)) < dist(point(x1,y1),p) ) p = point(X,Y), ind = i;
			}else{
				have = 1;
				p = point(X,Y);
				ind = i;
			}
		}
	}
	if( !have ) return;
	object O = objects[ind];
	if ( O.tipo == "D" ){
		mark[ind] = true;
		return;
	}if( O.tipo == "M" ){
		D A1, B1, C1, A2, B2, C2;
		A1 = O.p2.y - O.p1.y, B1 = O.p1.x-O.p2.x; C1 = A1 * O.p1.x + B1 * O.p1.y ;
		swap(A1, B1);
		A1 *= -1.;
		C1 = A1 * p.x + B1 * p.y ;
		A2 = O.p2.y - O.p1.y, B2 = O.p1.x-O.p2.x; C2 = A2 * x1 + B2 * y1 ;
		D det = A1 * B2 - B1 * A2;
		X =  ( C1 * B2 - C2 * B1 ) / det;
		Y =  ( A1 * C2 - A2 * C1 ) / det;
		point P;
		P.x = X + X-x1;
		P.y = Y + Y-y1;
		back(p.x,p.y,P.x, P.y,ind);
		return;
	}
	// SI TENEMOS UN SPLITTER:
	// buscamos la perpendicular al segmento del objeto y lo ponemos en A1, B1, C1...
	D A1, B1, C1, A2, B2, C2;
	A1 = O.p2.y - O.p1.y, B1 = O.p1.x-O.p2.x; C1 = A1 * O.p1.x + B1 * O.p1.y ;
	swap(A1, B1);
	A1 *= -1.;
	C1 = A1 * p.x + B1 * p.y ;
	A2 = O.p2.y - O.p1.y, B2 = O.p1.x-O.p2.x; C2 = A2 * x1 + B2 * y1 ;
	
	D det = A1 * B2 - B1 * A2;
	X =  ( C1 * B2 - C2 * B1 ) / det;
	Y =  ( A1 * C2 - A2 * C1 ) / det;

	point P;
	P.x = X + X-x1;
	P.y = Y + Y-y1;
	back(p.x,p.y,P.x, P.y,ind);
	back(p.x, p.y, p.x+(x2-x1), p.y + (y2-y1) ,ind);
}
int main(){
	int i,j ,k;
	int casos;scanf("%i", &casos);
	char arr[4];
	
	for(int h =0  ; h < casos; h ++ ){
		double x1, y1, x2, y2;
		scanf("%lf,%lf %lf,%lf", &x1, &y1, &x2, &y2);
		scanf("%i", &N);
		for(i=0;i<N;i++){
			string s; double x1, y1, x2, y2;
			char c;
			scanf("%s", arr);
			s += arr[0];
			scanf("%lf,%lf %lf,%lf", &x1, &y1, &x2, &y2);
			objects[i].tipo = s;
			objects[i].p1 = point(x1,y1);
			objects[i].p2 = point(x2,y2);
		}
		memset(mark, false, sizeof(mark));
		back(x1,y1,x2+x1,y2+y1, -1);
		vector<int> res;
		for(i=0;i<N;i++) if( mark[i]  && objects[i].tipo == "D" ) res.push_back(i);
		printf("DATA SET #%i\n", h+1);
		if( res.size()){
			for(i=0;i<res.size();i++) printf("%i\n", 1+res[i]);
		}else printf("NO BEAMS DETECTED\n");
	}return 0;
}
