// PROBLEMITA EN O ( N * SQRT ( N ) ) :) ASPERITO...

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
#define MP make_pair
typedef long long ll;
int N;
int res[100010], RES;
int arr[100010];
int pos[100010];

struct par{
	int first, second;
	par(){};
	par(int _x, int _y) {first=_x,second=_y;}
};

struct par B2[100010];
struct par B[100010];
int indiceB;
bool in(par p, int s){
	if( p.first <= s && s <= p.second ) return true;
	if( p.first >= s && s >= p.second ) return true;
	return false;
}
void change(int F, int SS){
	int i,j ,k;
	int S;
	int indiceB2=0;
	int R = F;
	int FI = 0;
	while( F > abs(B[FI].first-B[FI].second) ){
		F -= 1+abs(B[FI].first-B[FI].second);
		B2[indiceB2++] = par(B[FI].first, B[FI].second);
		FI++;
	}
	if( F ){
		if( B[FI].first < B[FI].second ){
			B2[indiceB2++] = par(B[FI].first, B[FI].first+F-1);
			B[FI].first = B[FI].first+F;
		}else{
			B2[indiceB2++] = par(B[FI].first, B[FI].first-F+1);
			B[FI].first = B[FI].first-F;
		}
		F  = 0;
	}
	int ind = FI;
	while(1){
		if( in(B[ind],SS) )break;
		R += 1+abs(B[ind].first-B[ind].second);
		ind++;
	}
	R--;
	if( B[ind].first < B[ind].second ) R += (SS-B[ind].first+1);
	else R += B[ind].first-SS+1;
	pair<int,int> agregar(-1,-1);
	if( B[ind].first < B[ind].second  && SS != B[ind].second ){
		agregar.first = SS+1;agregar.second = B[ind].second;
		B[ind].second = SS;
	}else if( B[ind].second < B[ind].first && SS != B[ind].second ){
		agregar.first = SS-1; agregar.second = B[ind].second;
		B[ind].second = SS;
	}
	for(i=0;i<(1+ind-FI)/2;i++)swap(B[i+FI],B[ind-i]);
	for(i=0;i<ind-FI+1;i++) B2[indiceB2++] = par(B[i+FI].second,B[i+FI].first);
	if( agregar.first != -1 ) B2[indiceB2++] = par(agregar.first, agregar.second);
	for(i=ind+1;i<indiceB;i++) B2[indiceB2++] = par(B[i].first, B[i].second);
// 	for(i=0;i<indiceB2;i++) B[i].first = B2[i].first, B[i].second = B2[i].second;
	memcpy(B,B2,sizeof(B[0])*indiceB2);
	indiceB = indiceB2;
	res[RES++] = R;
}
#define M 100010
int arr1[M], pos1[M];
void stable(){
	int i,j ,k;
	for(i=0;i<N;i++) arr1[i] = arr[i], pos1[i] = pos[i];
	int ind = 0;
	for(i=0;i<indiceB;i++){
		if( B[i].first < B[i].second ){
			for(j=B[i].first ; j <= B[i].second;j++)arr[ind] = arr1[j], pos[ind++] = pos1[j];
		}else{
			for(j=B[i].first ; j >= B[i].second;j--)arr[ind] = arr1[j], pos[ind++] = pos1[j];
		}
	}
}
int  main(){
	int i,j, k;
	while(1){
		scanf("%i", &N); if(!N) return 0;
		RES=0;
		for(i=0;i<N;i++) scanf("%i", &arr[i]);
		vector<pair<int,int> > fin;
		for(i=0;i<N;i++) fin.PB(MP(arr[i],i));
		sort(ALL(fin));
		for(i=0;i<fin.size();i++)pos[fin[i].second] = i;
		int sq = (int)sqrt((double)N+0.001);
		int search[1000];
		B[0].first = 0, B[0].second = N-1; indiceB = 1;
		int first = 2;
		for(int ind = 0; ind < N ; ind += sq){
			for(i=0;i<N;i++) if(pos[i] >= ind && pos[i]-ind < sq ) search[pos[i]-ind] = i;	
			for(k=0;k<sq&&k+ind<N;k++){
				change(ind+k,search[k]);
			}
			stable();

			B[0].first = 0, B[0].second = N-1; indiceB = 1;
		}
		for(i=0;i<RES;i++){if(i)printf(" ");printf("%i", res[i]+1);}printf("\n");
	}return 0;
}
