#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
#define NN 224
#define MM 500000
#define INF 2100004
/* EDMONDS KARP para grafos dispersos... V  ~<< E. */
typedef struct{
    int from, to, cap, flow;
}s_ar;
s_ar aristas[2*MM];
vector<int> vec[NN];
vector<int> ind[NN];
// Siempre hay que inicializar esta variable:
int indice = 0;
void addEdge(int from, int to, int cap, int flow){
	for(int i = 0 ;i < vec[from].size() ; i ++ )if( vec[from][i] == to ){
		aristas[ind[from][i]].cap = cap; return;
	}
	vec[from].push_back(to), ind[from].push_back(indice);
	aristas[indice].from = from, aristas[indice].to = to;
	aristas[indice].cap = cap, aristas[indice++].flow = 0;
	vec[to].push_back(from), ind[to].push_back(indice);
	aristas[indice].from = to, aristas[indice].to = from;
	aristas[indice].cap = 0, aristas[indice++].flow = 0;
}
int prev[NN];
int q[NN+1];
bool isPath(int s, int t){
	memset(prev, -1, sizeof(prev));
	int qb, qe; qb = qe = 0;
	prev[q[qe++] = s ] = -2;
	while( qb < qe && prev[t] == -1 ){
		for(int u = q[qb++], i=0, v; i < vec[u].size(); i++){
			if( prev[v = vec[u][i]] != -1 ) continue;
			if( aristas[ind[u][i]].flow < aristas[ind[u][i]].cap ) prev[q[qe++]=v] = u;
			else if( aristas[ind[u][i]+(ind[u][i]&1?-1:1)].flow ) prev[q[qe++]=v] = u;
		}
	}
	return prev[t] != -1;
}
int r(int v, int u){
	for(int i =0 ;i < vec[v].size() ; i++ )if( vec[v][i] == u ){
		if( aristas[ind[v][i]].cap > aristas[ind[v][i]].flow ){
			return aristas[ind[v][i]].cap-aristas[ind[v][i]].flow;
		}
		return aristas[ind[v][i]+(ind[v][i]&1?-1:1)].flow;
		}
}
void modify(int v, int u, int flow){
	for(int i = 0; i < vec[v].size() ; i++) if( vec[v][i] == u ){
		if( aristas[ind[v][i]].cap > aristas[ind[v][i]].flow ){
			aristas[ind[v][i]].flow += flow;
		}else aristas[ind[v][i]+(ind[v][i]&1?-1:1)].flow -= flow;
		return;
	}
}
int augment(int s,int t){
	int flow = INT_MAX;
	prev[s] = s;
	for(int u = t, v = prev[u]; v != u; u = v, v = prev[u]) flow = min( flow, r(v,u));
	for(int u = t, v = prev[u]; v != u; u = v, v = prev[u]){
		 modify(v,u,flow);
	}
	return flow;
}
int edmondsKarp2(int s, int t){
	int flow = 0;
	while( isPath(s,t) )flow += augment(s,t);
	return flow;
}

int main(){
	int i,j ,k;
	int N, M;
	while(scanf("%i", &N)!=EOF){
		for(i=0;i<220;i++) vec[i].clear(), ind[i].clear();
		indice = 0;
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
		int flow = edmondsKarp2(0,2*N+1);
		printf("%i\n", flow);
	}return 0;
}
