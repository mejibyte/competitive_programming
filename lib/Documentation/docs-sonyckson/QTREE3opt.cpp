// SEGMENT TREES VERY SIMPLE'S!!! :D...
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
	int off;
	vector<int> vec;
	STREE(int x){
		size = x-1;
		int pot = 1;
		while( pot < x ) pot *=2;
		off = pot;
		pot *= 2;
		vec.resize(pot+1,-1);
	}
	// indexado en 0...
	void change(int node, int pos){
		if( vec[pos+off] >= 0 ) vec[pos+off] = -1;
		else vec[pos+off] = pos;
// 		printf("%i %i\n", pos, vec[pos+off]);
		for(int x = (off+pos)/2;x>=1;x/=2){
			if( vec[2*x] >= 0 ) vec[x] = vec[2*x];
			else if( vec[2*x+1] >= 0 ) vec[x] = vec[2*x+1];
			else vec[x] = -1;
// 			printf("%i %i\n", x, vec[x]);
		}
	}
	int query(int node,int end,int begin, int a, int b){
// 		printf("%i %i %i %i %i %i\n", node, begin, end, a, b, vec[node]);
		if( a > end  || b < begin ) return -1;
		if( a >= begin && b <= end) return vec[node];
		int r = query(node*2,end,begin,a,(a+b)/2);
		int s = query(node*2+1,end,begin,(a+b)/2+1,b);
		if( r >= 0 ) return r;
		if( s >= 0 ) return s;
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
	int f = streeVec[stree].query( 1,  homeIndex[node],0,0,streeVec[stree].off-1);
	int nod = -1;
	if( f >= 0 ) nod = nodosVec[stree][f];
	int last = prevStree[node];
// 	printf("%i %i %i\n", stree, f, last);
// 	return;
	while( last != -1 ){
// 		printf("ENTERS\n");
		stree = homeStree[last];
		int aux = streeVec[stree].query( 1,  homeIndex[last] ,0,0,streeVec[stree].off-1);
// 		printf("stree %i.. last %i ... ax %i\n", stree, last, aux);
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
