// ALGORITMO, QUE USA GEMETIA; PARA VER EN UN POLIGONO CONVEXO 
//Q PUNTOS ESTAN EN Q TRIANGULO Q CONTENGA PUNTOS ADJACENTES
// FRONTIER, TIMUS :), costo un ojo de la cara! :P :D

#include <algorithm>
#include <cassert>
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
#include <cassert>
#define forn(i, n) for(int i=0;i<int(n);i++)
#define foreach(it, c)  for(typeof((c).begin()) it = (c).begin();it!=(c).end();++it)
#define ALL(x)   (x).begin(),(x).end()
#define SORT(x) sort(ALL(x))
using namespace std;
#define VI vector<int>
#define VS vector<string>
#define PB push_back
#define ll long long
int N, M;
int tow[51][2];
int p[1001][2];
double m[1001][2];
bool fijo[51][51][51];
double cruz(int h, int i, int j){
	int x1, x2, y1, y2;
	x1 = tow[i][0]-p[h][0], x2 = tow[j][0] - p[h][0];
	y1 = tow[i][1]-p[h][1], y2 = tow[j][1] - p[h][1];
	return fabs((double)x1*y2-x2*y1)/2.0;
}
double cruz2(int h, int i, int j){
	int x1, x2, y1, y2;	
	x1 = tow[i][0]-tow[h][0], x2 = tow[j][0] - tow[h][0];
	y1 = tow[i][1]-tow[h][1], y2 = tow[j][1] - tow[h][1];
	return fabs((double)x1*y2-x2*y1)/2.0;
}
bool adentro(int pi, int i, int j, int k){
	double a1 = cruz(pi,i,j), a2 = cruz(pi,i,k), a3 = cruz(pi,j,k);
	if( fabs(a1+a2+a3 - cruz2(i,j,k)) < 1e-7 ) return true;
	return false;
}
double cruz3(double x1, double y1, double x2, double y2, double x3, double y3){
	double xx1, xx2, yy1, yy2;
	xx1 = x2-x1, xx2 = x3-x1;
	yy1 = y2-y1, yy2 = y3-y1;
	return fabs(xx1*yy2-xx2*yy1);
}
double dist(double x1, double y1, double x2, double y2){
	double dx, dy;
	dx = x1-x2;
	dy = y1-y2;
	return sqrt(dx*dx+dy*dy);
}
void f(int ind){
	vector<pair<double, int> > vec;
	int i ,j ,k;
	int ant = (ind+N-1)%N;
	for(i=0;i<M;i++){
		double x, y;
		x = (m[i][0]-(double)tow[ind][0]) / dist(tow[ind][0], tow[ind][1], m[i][0], m[i][1]);
		y = (m[i][1]-(double)tow[ind][1]) / dist(tow[ind][0], tow[ind][1], m[i][0], m[i][1]);
		double xa, ya;
		xa = (tow[ant][0]-(double)tow[ind][0]) / (dist(tow[ant][0], tow[ant][1], tow[ind][0], tow[ind][1]));
		ya = (tow[ant][1]-(double)tow[ind][1]) / (dist(tow[ant][0], tow[ant][1], tow[ind][0], tow[ind][1]));
		double d1, d2, d3;
		d1 = dist( xa, ya, x, y);
		d2 = dist(0.0, 0.0, x, y);
		d3 = dist(0.0, 0.0, xa, ya);
		double area = cruz3(x, y, 0.0, 0.0, xa, ya);
		double alt = area / d3;
		double len = sqrt(d2*d2-alt*alt);
		if( d1*d1 + 1e-7 > d2*d2+d3*d3 ){
			vec.PB(make_pair(len+d3, i));
		}else{
			vec.PB(make_pair(d3-len, i));
		}
	}
	sort(vec.begin(), vec.end());
	reverse(vec.begin(), vec.end());
	int v = 0;
	int tri = (ind+1)%N;
	while(v != M && tri != ant){
		int w = vec[v].second;
		int aux  = (tri+1)%N;
		if( adentro(w, ind, tri, aux) ){
			fijo[ind][tri][aux] = fijo[ind][aux][tri] = true;
			fijo[tri][ind][aux] = fijo[tri][aux][ind] = true;
			fijo[aux][ind][tri] = fijo[aux][tri][ind] = true;
			if( aux != ant && adentro(w, ind, aux, (aux+1)%N) ) tri = aux;
			else v++;
		}else tri = aux;
	}
}
bool visited[51][51][51];
double b[51][51][51];
double back(int last, int tamos, int vamos){
	if( tamos == vamos ) return dist(tow[last][0], tow[last][1], tow[tamos][0], tow[tamos][1]);
	if( visited[last][tamos][vamos] ) return b[last][tamos][vamos];
	visited[last][tamos][vamos] = true;
	double & res = b[last][tamos][vamos];
	res = back(tamos, (tamos+1)%N, vamos) + dist(tow[last][0], tow[last][1], tow[tamos][0], tow[tamos][1]);
	if(!fijo[last][tamos][(tamos+1)%N]){
		res = min( res, back(last, (tamos+1)%N, vamos));
	}
	return res;
}
int main(){
	int i,j ,k;
	scanf("%i %i", &N, &M);
	for(i=0;i<N;i++)scanf("%i %i",&tow[i][0], &tow[i][1]);
	for(i=0;i<M;i++)scanf("%i %i",&p[i][0], &p[i][1]);
	memset(fijo, false, sizeof(fijo));
	for(i=0;i<M;i++) for(j=0;j<2;j++) m[i][j] = (double) p[i][j];
	for(i=0;i<N;i++) f( i );
	double res = 1000000000000.0;
	memset(visited, false, sizeof(visited));
	for(i=0;i<N;i++)for(j=i+1;j<N;j++)for(k=j+1;k<N;k++){
		if( cruz3(tow[i][0], tow[i][1], tow[j][0], tow[j][1], tow[k][0], tow[k][1])/ 2.0 < 1e-7 ) continue;
		double aux = back(i, (i+1)%N, j) + back(j, (j+1)%N, k) + back(k, (k+1)%N, i);
		res = min( res, aux );
	}
	if( res > 10000000000.0 ) while(1);
	printf("%.2lf\n", res);
	return 0;
}
