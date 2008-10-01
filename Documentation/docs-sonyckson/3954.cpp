#include <cstdio>
#include <vector>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
int N;double R;
#define D double
#define EPS 1e-9
#define PB push_back
vector<pair<D,D> > point;
int res;
double hypot(double x, double y){
	return sqrt(x*x+y*y);
}
double cruz(pair<D,D> p1, pair<D,D> p2, pair<D,D> p3){
	double x1, x2, y1, y2;
	x1 = p2.first - p1.first, x2 = p3.first - p1.first;
	y1 = p2.second - p1.second, y2 = p3.second - p1.second;
	return acos( (x1*x2+y1*y2)/(hypot(x1,y1)*hypot(x2,y2)));
}
double dist(pair<D,D> p1, pair<D,D> p2){
	double dx, dy;
	dx = p2.first -p1.first, dy = p2.second - p1.second;
	return hypot(dx,dy);
}
#define Y second
#define X first
pair<D,D> P;
bool menor(pair<pair<D,D>,int> p1, pair<pair<D,D>,int> p2){
	double c = cruz(P, p1.first,p2.first);
	if( fabs(c) < EPS ) return false;
	return c < 0.;
}
void PROVE(vector<pair<D,D> > &vec, pair<D,D> p){
	vector<pair<double,int> > interval;
	int i,j ,k;
	int cant = 0;
	for(k=0;k<vec.size();k++){
		D xmed, ymed;
		xmed = (p.first+vec[k].first)/2., ymed = (p.second+vec[k].second)/2.;
		// calculamos la alturita del triángulo...
		D d = dist(make_pair(xmed,ymed),p);
		D altura = sqrt(max(R*R-d*d,0.));
		D xch, ych;
		xch = vec[k].second-ymed;
		ych = xmed-vec[k].first;
		xch /= d, ych/=d;
		xch *= altura, ych *= altura;

		pair<D,D> p1, p2;
		p1.first = xmed+xch; //min(p.first,xmed + xch);
		p2.first = xmed-xch; //min(p.first,xmed - xch);
		p1.second = ymed + ych;
		p2.second = ymed - ych;
		double c1, c2;
		c1 = cruz(p,p1,make_pair(p.X,10000000000000.));
		c2 = cruz(p,p2,make_pair(p.X,10000000000000.));
		double V = acos(-1);
		if( p1.first > p.first ) c1 = 2.*V-c1;
		if( p2.first > p.first ) c2 = 2.*V-c2;
		if( p1.first > p.first && p2.first < p.first ){
			if( vec[k].second > p.second ) cant++;
			
		}
		interval.push_back(make_pair(c1,-1));
		interval.push_back(make_pair(c2,1));
	}
	sort(interval.begin(), interval.end());
	int c = cant;
	for(i=(int)interval.size()-1;i>=0;i--){
		res = max ( res, abs(c) );
		c += interval[i].second;
	}
}
int main(){
	int i,j ,k;
	while(1){
		scanf("%i %lf", &N, &R);
		if(!N) return 0;
		point.clear();
		for(i=0;i<N;i++){D x, y; scanf("%lf %lf", &x, &y); point.push_back(make_pair(x,y));}
		
		sort(point.begin(), point.end());

		res = 0;
		
		R+= 0.001;
		for(i=0;i<point.size();i++){
			vector<pair<D,D> > AUX;
			for(j=0;j<point.size();j++){
				if( j == i ) continue;
				if( dist(point[i], point[j]) > 2.* R ) continue;
				AUX.push_back(point[j]);
			}
			PROVE(AUX, point[i]);
		}
		printf("It is possible to cover %i points.\n", res+1);
	}return 0;
}
