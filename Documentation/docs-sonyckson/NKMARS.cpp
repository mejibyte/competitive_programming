// INTERSECCIÖN DE AREAS DE RECTÄNGULOS CON SEGMENT TREES :D
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
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>

#define REP(i, n) for(int i=0;i<int(n);i++)
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
struct node{
	int on,area;
	node(){}
	node(int x, int y){on=x,area=y;}
};
struct segmentTree{
	vector<node> vec;
	int off;
	segmentTree(int x){off=1;while(off<x)off*=2;vec.resize(off*2,node(0,0));}
	int superficie(){return vec[1].area;}
	void add(int node, int begin, int end, int a, int b){
		if( begin > b || end < a ) return; 
		if( begin <= a && b <= end ){
			if( !vec[node].on ){
				vec[node].area = b-a+1;
			}vec[node].on++;
		}else{
			add(node*2,begin,end,a,(a+b)/2);
			add(node*2+1,begin,end,(a+b)/2+1,b);
			if(!vec[node].on)vec[node].area = vec[2*node].area+vec[2*node+1].area;
		}
	}
	void take(int node,int begin,int end,int a, int b){
		if( begin > b || end < a ) return;
		if( begin <= a && b <= end ){
			vec[node].on--;
			if( !vec[node].on ){
				if(a!=b)vec[node].area = vec[node*2].area + vec[node*2+1].area;
				else vec[node].area = 0;
			}
		}else{
			take(node*2,begin,end,a,(a+b)/2);
			take(node*2+1,begin,end,(a+b)/2+1,b);
			if(!vec[node].on)vec[node].area = vec[node*2].area + vec[node*2+1].area;
		}
	}
};
#define PII pair<int,int>
int main(){
	int i,j ,k;
	segmentTree sTree(30001);
	int N;scanf("%i", &N);
	int x1, y1, x2, y2;
	vector< pair<int,PII> > abre, cierra;
	int lastx=INT_MAX;
	for(i=0;i<N;i++){
		scanf("%i %i %i %i", &x1, &y1, &x2, &y2);
		y2--;
		abre.PB(MP(x1,MP(y1,y2)));
		cierra.PB(MP(x2,MP(y1,y2)));
		lastx = min(x1,min(x2,lastx));
	}
	sort(ALL(abre)); sort(ALL(cierra));
	abre.PB(MP(INT_MAX,PII(0,0)));
	int ind1, ind2;
	ind1 = ind2 = 0;
	int res = 0;
	for(k=0;k<2*N;k++){
		if( abre[ind1].first < cierra[ind2].first ){
			res += sTree.superficie() * (abre[ind1].first-lastx);
			lastx = abre[ind1].first;
			sTree.add(1,abre[ind1].second.first, abre[ind1].second.second,0,sTree.off-1);
			ind1++;
		}else{
			res += sTree.superficie()*(cierra[ind2].first-lastx);
			lastx = cierra[ind2].first;
			sTree.take(1,cierra[ind2].second.first, cierra[ind2].second.second,0,sTree.off-1);
			ind2++;
		}
	}
	printf("%i\n", res);
}
