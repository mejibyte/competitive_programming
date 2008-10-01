/* ARTICULATION POINTS   */
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
vector<int> edges[101];
int N;
int id[101], color[101];
int ind =0, res;
int back(int node, int father){
	int i,j ,k;
	int low = ind;
	id[node] = ind++;
	color[node] = 1;
	int cant = 0;
	bool isArt = false;int aux;
	for(i=0;i<edges[node].size();i++){
		int v= edges[node][i];
		if( v == father )continue;
		if( color[v] == 0 ){
			cant++, aux = back(v,node);
			if( aux >= id[node] ) isArt = true;
		}else aux = id[v];
		low = min ( low, aux );
	}
	if( node == 1 )if( cant > 1 )res ++;
	else if(isArt )res++;
	return low;
}
int main(){
	int i, j, k;
	bool mat[101][101];
	while(1){
		ind=0;
		scanf("%i", &N); if(!N) return 0;
		while(getchar() !='\n' ) ;
		for(i=1;i<=N;i++) edges[i].clear();
		memset(mat, false, sizeof(mat));
		while(1){
			string s;
			getline(cin, s);
			istringstream iss ( s );
			int a, b;
			iss >> a;
			if(!a) break;
			while( iss >> b ){
				if( !mat[a][b] )
				edges[b].PB(a), edges[a].PB(b);
				mat[a][b] = mat[b][a] = true;
			}
		}
		res=0;
		memset(color, 0, sizeof(color));
		back(1,-1);
		printf("%i\n", res);
	}return 0;
}
