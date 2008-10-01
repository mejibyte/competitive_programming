#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
#define NN 210
#define MM 500000
#define INF 2100004
int edges[NN][NN*2], deg[NN], cap[NN][NN];
int q[NN], prev[NN];
void addEdge(int from, int to, int C, int flow){
	edges[from][deg[from]++] = to;
	cap[from][to] = C;
	edges[to][deg[to]++] = from;
}
int dinic(int s, int t){
	int flow = 0;
	while(1){
		memset(prev, -1, sizeof(prev));
		int qb =0, qe =0;
		prev[q[qe++] = s ] = -2;
		while( qb < qe && prev[t] == -1 )
			for(int u = q[qb++], v, i = 0;i<deg[u]; i++ )
				if( prev[v=edges[u][i]] == -1 && cap[u][v] )prev[q[qe++] = v] = u;
		
		if( prev[t] == -1 ) break;
		prev[s] = s;
		for(int z = 0; z < t ; z ++ )if( cap[z][t] && prev[z] != -1 ){
			int mf = INT_MAX;
			for(int u = t, v = prev[u]; u != v; u = v, v = prev[u])
				mf = min ( mf, cap[v][u] );
			if( !mf ) continue;
			for(int u = t, v = prev[u]; u != v; u = v, v = prev[u])
				cap[v][u] -= mf, cap[u][v] += mf;
			flow += mf;
		}
	}return flow;
}
int main(){
	int i,j ,k;
	int N, M;
	while(scanf("%i", &N)!=EOF){
		memset(deg, 0, sizeof(deg));
		memset(cap, 0, sizeof(cap));
		for(i=0;i<N;i++){
			scanf("%i", &k);
			addEdge(i+1, i+1+N,k,0);
		}
		scanf("%i", &M);
		int a, b, c;
		for(i=0;i<M;i++){
			scanf("%i %i %i", &a, &b, &c);
			addEdge(a+N,b,c,0);
		}
		int B, D;
		scanf("%i %i", &B, &D);
		for(i=0;i<B;i++){
			scanf("%i", &c);
			addEdge(0,c,INF,0);
		}
		for(i=0;i<D;i++){
			scanf("%i", &c);
			addEdge(N+c,2*N+1,INF,0);
		}
// 		printf("%i\n", indice);
		int flow = dinic(0,2*N+1);
		printf("%i\n", flow);
	}return 0;
}
