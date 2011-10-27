// SEGMENT TREES! :D...
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
#define MAXN 100010
vector<int> edges[MAXN];
int N, Q;
struct node{
	int first, val, begin, end;
};
struct STREE{
	int size;
	vector<node> vec;
	void create(int node, int begin, int end){
		vec[node].begin = begin; vec[node].end = end;
		vec[node].first = -1, vec[node].val = 0;
		if( begin == end )return;
		create(2*node,begin,(end+begin)/2);
		create(2*node+1,(end+begin)/2+1,end);
	}
	STREE(int x){
		size = x;
		int pot = 1;
		while( pot < x ) pot *=2;
		pot *= 2;
		vec.resize(pot+1);
		create(1,0,x-1);
	}
	// indexado en 0...
	void change(int node, int pos){
		if( vec[node].begin != vec[node].end ){
			if( pos <= (vec[node].begin+vec[node].end)/2 )change(2*node,pos);
			else change(2*node+1,pos);
			if( vec[2*node].first !=-1 ) vec[node].first = vec[2*node].first;
			else if( vec[2*node+1].first != -1 ) vec[node].first = vec[2*node+1].first;
			else vec[node].first = -1;	
			return;
		}
		assert( vec[node].begin == pos);
		vec[node].val = 1 - vec[node].val;
		if( vec[node].val ) vec[node].first = vec[node].begin;
		else vec[node].first = -1;
		
	}
	bool inrange(int pos, int node){
		if( pos >= vec[node].begin && pos <= vec[node].end) return true;
		return false;
	}
	int query(int node, int end){
		if( vec[node].end <= end )return vec[node].first;
		if( vec[node].begin > end )return -1;
		if( vec[node].begin == vec[node].end ) return -1;
		int a;
		if( inrange(end,2*node)){a= query(2*node,end);if(a>=0) return a;}
		if( inrange(end,2*node+1)){a = query(2*node+1,end); if( a>=0) return a;}
		return -1;
	}
};
int ind;
vector<STREE> streeVec;
vector<vector<int> > nodosVec;
int depth[MAXN],chain[MAXN], prev[MAXN];
int prevStree[MAXN], homeStree[MAXN], homeIndex[MAXN];
int dep(int node){if( node < 0 ) return -1; return depth[node];}
vector<int> nodos;

void constructStree(){
	if(nodos.size() == 0 ) return;
	int i,j ,k;
	for(i=0;i<nodos.size();i++){
		prevStree[nodos[i]] = prev[nodos[0]];
		homeStree[nodos[i]] = ind;
		homeIndex[nodos[i]] = i;
	}
	ind++;
	streeVec.PB(STREE(nodos.size()));
	nodosVec.PB(nodos);
}
void go(int node, int father){
	nodos.push_back(node);
	if( edges[node].size() == 1 && edges[node][0] == father ) constructStree();
	int i,j ,k;
	int larger = -1;
	for(i=0;i<edges[node].size();i++){
		if( edges[node][i] == father ) continue;
		if( dep(edges[node][i]) > dep(larger) ) larger = edges[node][i];
	}
	if( larger >= 0 )go(larger,node);
	for(i=0;i<edges[node].size();i++){
		if( edges[node][i] == father ) continue;
		if( edges[node][i] != larger ){
			nodos.clear(); go(edges[node][i],node);
		}
	}
}
void dfs(int node, int father){
	prev[node] = father;
	int i,j ,k;
	for(i=0;i<edges[node].size();i++){
		if( edges[node][i] == father ) continue;
		dfs(edges[node][i], node);
	}
	depth[node] = 0;
	for(i=0;i<edges[node].size();i++){
		if( edges[node][i] == father ) continue;
		depth[node] = max( depth[node], depth[edges[node][i]]+1);
	}
}
void query(int node){
	int stree = homeStree[node];
	int f = streeVec[stree].query( 1,  homeIndex[node] );
	int nod = -1;
	if( f >= 0 ) nod = nodosVec[stree][f];
	int last = prevStree[node];
	while( last != -1 ){
		stree = homeStree[last];
		int aux = streeVec[stree].query( 1,  homeIndex[last] );
		if( aux >= 0 ){
			f = aux;
			nod = nodosVec[stree][f];
		}
		last = prevStree[last];
	}
	if(nod == -1 ) nod--;
	printf("%i\n", nod+1);
}
void change(int node){
	int stree = homeStree[node];
	streeVec[stree].change( 1, homeIndex[node]);
}
int main(){
	int i,j ,k;
	memset(depth, -1, sizeof(depth));
	scanf("%i %i", &N, &Q);
	for(i=0;i<N-1;i++){
		int a, b;
		scanf("%i %i", &a, &b);a--, b--;
		edges[a].PB(b), edges[b].PB(a);
	}
	dfs(0,-1);
	ind = 0;
	go(0,-1);
	for(i=0;i<Q;i++){
		int op, node;
		scanf("%i %i", &op, &node);
		node--;
		if( op ) query(node);
		else change(node);
	}return 0;
}
