// UN DIJKSTRA QUE GUARDA CAMINOS.... NO ES TAN TIVIAL COMO APARENTA... IMP


#include <algorithm>
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
#define MX 1000000
int main(){
	int i,j ,k;
	int N, M;
	while(1){
		VI edges[101];
		int cost[101][101];
		scanf("%i", &N);if( N < 0 ) return 0;
		for(i=0;i<=N;i++)for(j=0;j<=N;j++) cost[i][j] = MX;
		scanf("%i", &M);int a, b, c;
		for(i=0;i<M;i++){
			scanf("%i %i %i", &a, &b, &c);
			if( a > N || b > N ) continue;
			edges[a].PB(b), edges[b].PB(a);
			cost[a][b] = min(cost[a][b], c);
			cost[b][a] = min(cost[b][a],c);
		}
		VI res;
		int sum = INT_MAX;
		for(i=1;i<=N;i++)for(j=i+1;j<=N;j++){
			if( cost[i][j] == MX ) continue;
			set<pair<int,int> > Q;
			Q.insert(make_pair(0, i));
			int visited[102];
			memset(visited, 0, sizeof(visited));
			int mark[102];
			for(k=0;k<102;k++) mark[k] = MX;
			int padre[102];
			memset(padre, -1, sizeof(padre));
			while(!Q.empty()){
				pair<int,int> par = *(Q.begin()); Q.erase(Q.begin());
				if( par.second == j ) break;
				if( cost[i][j] + par.first >= sum ) break;
				if( visited[par.second] || par.first > mark[par.second] ) continue;
				visited[par.second] = 1;
				for(k=0;k<edges[par.second].size();k++){
					if( par.second ==  i ){
						if( edges[par.second][k] == j ) continue;
					}if( edges[par.second][k] == i ){
						if( par.second == j ) continue;
					}
					int dist = cost[par.second][edges[par.second][k]] + par.first;
					if( dist < mark[edges[par.second][k]] ){
						mark[edges[par.second][k]] = dist;
						Q.insert(make_pair(dist, edges[par.second][k]));
						padre[edges[par.second][k]] = par.second;
					}
				}
			}
			int tot = mark[j] + cost[i][j];
			if( tot < sum && padre[j] > 0){
				VI aux;
				int ind = j;
				while(ind != i){
					aux.PB(ind);
					ind = padre[ind];
				}
				aux.PB(i);
				res = aux;
				sum = tot;
			}
		}
		if( sum < MX ){
			int first = 1;
			for(i=0;i<res.size();i++){
				if( first ) first = 0; else printf(" ");
				printf("%i", res[i]);
			}
			printf("\n");
		}else printf("No solution.\n");
	}
	return 0;
}
