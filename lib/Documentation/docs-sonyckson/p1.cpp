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
#define UNIQUE(a) SORT(a),(a).resize(unique(ALL(a))-a.begin())
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
vector<pair<int,int> > POL;
#define X first
#define Y second
bool inRange(double x, double x1, double x2){
	if( x > x1 && x < x2 ) return true;
	return false;
}
void print(pair<int,int> p){
// 	printf("  %i %i\n", p.first, p.second);
}
bool back(double x, double y){
	// primero contamos los q intersecan horizontales...
	int res = 0;
	int i,j ,k;
	int arriba, abajo, izq, der;
	arriba = abajo = izq = der = 0;
	for(i=0;i<POL.size();i++){
		int i1 = i, i2 = (i+1)%POL.size();
		if((double) POL[i1].second > y && POL[i1].second == POL[i2].second ){
			if( inRange(x, min(POL[i1].X,POL[i2].X),max(POL[i1].X,POL[i2].X)) ){
				arriba++;
			}
		}else if( (double) POL[i1].second < y && POL[i1].second == POL[i2].second ){
			print(POL[i1]),print(POL[i2]);
			if( inRange(x, min(POL[i1].X,POL[i2].X),max(POL[i1].X,POL[i2].X)) ){
				abajo++;
			}
		}else if((double)POL[i1].X < x && POL[i1].X == POL[i2].X){
			if(inRange(y,min(POL[i1].Y,POL[i2].Y), max(POL[i1].Y,POL[i2].Y))){
				izq++;
			}
		}else if((double)POL[i1].X > x && POL[i1].X == POL[i2].X){
			if(inRange(y,min(POL[i1].Y,POL[i2].Y), max(POL[i1].Y,POL[i2].Y))){
				der++;
			}
		}
	}
	if(arriba && abajo &&  (arriba%2==0) && (abajo%2==0) ) return true;
	if(izq && der && (izq%2==0) && (der%2==0)) return true;
	return false;
}
bool vale(int x1, int x2, int y1, int y2 ){
	return back((double)(x1) + 0.5, (double)(y1+0.5) );
}

int main(){
	int i, j, k;int casos;
	cin >> casos;
	for(int h = 0 ;h < casos; h ++ ){
		int n;scanf("%i", &n);
		POL.clear();
		string s, t;
		for(i=0;i<n;i++){
			cin >> t >> k;
			for(j=0;j<k;j++) s += t ;
		}
		int x, y; x = y = 0;
		int dx[4] ={0, 1, 0, -1};
		int dy[4] ={1, 0, -1, 0};
		
		int ind =  0;
		POL.push_back(make_pair(0,0));
		for(i=0;i<s.size();i++){
// 			printf("%i %i %i   %c\n", x, y, ind, s[i]);
			if( s[i] == 'F' ){
				
				x += dx[ind], y+= dy[ind];
			}if( s[i] == 'R' ){
				POL.PB(make_pair(x,y));
				ind = (ind+1)%4;
			}if( s[i] == 'L' ){
				POL.PB(make_pair(x,y));
				ind = (ind+3)%4;
			}
		}
// 		for(i=0;i<POL.size();i++) printf("%i %i\n", POL[i].X, POL[i].Y);
		vector<int> X, Y;
		X.PB(4000);Y.PB(4000);
		for(i=0;i<POL.size();i++){
			X.PB(POL[i].first); Y.PB(POL[i].second);
		}
		UNIQUE(X), UNIQUE(Y);
		sort(ALL(X));sort(ALL(Y));
		int res = 0;
// 		for(i=0;i<X.size();i++) printf("%i ", X[i]);printf("\n");
// 		for(i=0;i<Y.size();i++) printf("%i  ", Y[i]);printf("\n");
// 		printf("%i %i\n", X.size(), Y.size());
		for(i=0;i<(int)X.size()-1;i++)for(j=0;j<(int)Y.size()-1;j++){

			if( vale(X[i], X[i+1], Y[i], Y[i+1]) ){
				res += ( X[i+1]-X[i] ) * (Y[i+1]-Y[i]) ;
			}
		}
		printf("Case #%i: %i\n", h+1, res);
	}return 0;
}







