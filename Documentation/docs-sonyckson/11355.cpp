// PORCENTAJE VISIBLE DESDE EL CENTRO DE UN CIRCULO; ANTE VARIOS SEGMENTOS :)
// ACLARACIÖN: MISTERIOSAMENTE NO FUNCIONO EL PRODUCTO CRUZ....
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
#define EPS 1e-9
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
int main(){
	int i,j ,k;
	int casos;scanf("%i", &casos);
	double R;
	for(int h = 0 ; h < casos;h++){
		scanf("%i %lf", &n, &R);
		for(i=0;i<n;i++)scanf("%lf %lf %lf %lf", &seg[i].p1.x, &seg[i].p1.y, &seg[i].p2.x, &seg[i].p2.y);
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
		printf("Case %i: %.2lf%%\n", h+1, 100.0*(1.0-tot/M));
	}return 0;
}
