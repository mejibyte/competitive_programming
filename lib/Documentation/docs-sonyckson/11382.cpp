// CALCULAR EL MINIMO ANGULO PARA EL ARMA QUE CON HASTA K TIROS MATA A TODOS
// LOS SEGMENTOS; ( FANTASMITAS :P ES COMO GHOSTBUSTERS :P )
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
typedef struct{
	double x, y;
}point;
typedef struct{
	point p1, p2;
}segment;
int n;
segment seg[101];
double M = 2*acos(-1);
double PI = acos(-1);
#define EPS 1e-7
double angulo(point p){
	double d = sqrt(p.x*p.x+p.y*p.y);
	p.x /= d;
	p.y /= d;
	double angle = acos(p.x);
	if( p.y + EPS< 0.0 ) angle = 2.0*PI-angle;
	return angle;
}
pair<double,double> inter(segment seg){
	return make_pair(angulo(seg.p1), angulo(seg.p2));
}
int borrar(vector<pair<double,double> > &vec){
	if( vec.size() == 1 ) return 0;
	for(int i=0;i<vec.size();i++){
		if( fabs(vec[i].first-vec[i].second) < EPS ){
			vec.erase(vec.begin()+i);
			return 1;
		}
		int next = (i+1)%vec.size();
		if( next ){
			if(  vec[next].first < vec[i].second ){
				vec[i].second = max(vec[i].second, vec[next].second);
				vec.erase(vec.begin()+next);
				return 1;
			}
		}else{
			pair<double, double> par = vec[next];
			par.first+=2.0*PI, par.second+=2.0*PI;
			if( par.first < vec[i].second ){
				vec[i].second = max(vec[i].second, par.second);
				vec.erase(vec.begin()+next);
				return 1;
			}
		}
	}
	return 0;
}
int tratar(vector<pair<double, double> >  vec, int ind, double dist){
	int i,j ,k;
	double last = vec[ind].first;
	int listo = 0;
	i = ind;int first=0;
	int res = 0;
	while(!listo){
		if( i == ind ){
			if(first)break;
			else first=1;
		}
		if( i == 0 && last > M ){
			while(last > M )last -= M;
		}else if( i == 0 ) last = 0.0;
		double pri, sec;
		pri = max(vec[i].first, last);
		sec = vec[i].second;
		if( pri < sec ){
			double len = ((sec-pri)/dist);
			int ca;
			if( fabs(len-floor(len+EPS)) < EPS ) ca = (int)(len+EPS);
			else ca = (int)(len+EPS)+1;
			res+=ca;
			last = pri+dist*(double)ca;
		}
		i = (i+1)%vec.size();
	}
	return res;
}
int cantidad(double dist, vector<pair<double, double> > vec){
	int i,j ,k;
	int res = 100000;
	for(i=0;i<vec.size();i++)  res = min(tratar(vec, i, dist), res);
	return res;
}
int main(){
	int i,j ,k;
	int casos;scanf("%i", &casos);
	double R;
	int K;
	for(int h = 0 ; h < casos;h++){
		scanf("%i %i", &n, &K);
		double x, y;
		scanf("%lf %lf", &x, &y);
		for(i=0;i<n;i++)scanf("%lf %lf %lf %lf", &seg[i].p1.x, &seg[i].p1.y, &seg[i].p2.x, &seg[i].p2.y);
		for(i=0;i<n;i++){
			seg[i].p1.x -= x;
			seg[i].p2.x -= x;
			seg[i].p1.y -= y;
			seg[i].p2.y -= y;
		}
		vector<pair<double,double> > intervalo;
		for(i=0;i<n;i++) intervalo.push_back(inter(seg[i]));
		for(i=0;i<intervalo.size();i++){
			if( intervalo[i].first < intervalo[i].second){
				if( intervalo[i].second-intervalo[i].first  > PI)
					swap(intervalo[i].first, intervalo[i].second);
			}else{
				if( intervalo[i].first-intervalo[i].second  < PI ) 
					swap(intervalo[i].first, intervalo[i].second);
			}
		}
		for(i=0;i<intervalo.size();i++) if( intervalo[i].first > EPS+intervalo[i].second){
			intervalo[i].second += 2.0*PI;
		}
		sort(intervalo.begin(), intervalo.end());
		while(borrar(intervalo));
		double tot = 0.0;
		for(i=0;i<intervalo.size();i++)
			tot+=intervalo[i].second-intervalo[i].first;
		tot = min(M, tot);
		double res;
		if( fabs(tot-M) < EPS ){
			if( K == 1 ) res = -1.0;
			else res = M / (double) K ;
		}else{
			double b, e;
			b = (1.0/180.0)*PI;
			e = PI;
			if( cantidad(e, intervalo) > K ) res = -1.0;
			else if( cantidad(b,intervalo) <= K )res = b;
			else {
				while( fabs( b-e ) > EPS/2.0 ){
					double med = (b+e)/2.0;
					if( cantidad(med, intervalo) <= K ){
						e = med;
					}else b = med;
				}
				res = e;
			}
		}
		if( res > -0.01 ){
			res = (res/PI)*180.0;
			res = max(res, 1.0);
		}
		printf("%.4lf\n", res);
	}return 0;
}
