#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
#define NN 210
#define INF 2100004
typedef struct{
	int from, to, cap, flow;
}s_ar;
vector<s_ar> salen[NN], llegan[NN];
void addEdge(int from, int to, int cap, int flow){
	s_ar e;
	e.from = from, e.to = to, e.cap = cap, e.flow = flow;
	salen[from].push_back(e);llegan[to].push_back(e);
}
int prev[NN+1];
int dir[NN+1];
bool isPath(int s, int t){
	int i,j ,k;
	int q[2*NN];
	int qb, qe; qb = qe = 0;
	memset(prev, -1, sizeof(prev));
	prev[q[qe++] = s ] = -2;
	while( qb < qe && prev[t] == -1 ){
		for(int v = q[qb++], i=0, u; i<max(salen[v].size(), llegan[v].size() ); i++){
			if(i < salen[v].size() &&  prev[u = salen[v][i].to] == -1
					&& salen[v][i].flow < salen[v][i].cap ){
				prev[q[qe++] = u] = v, dir[u] = 1;;
			}
			if(i<llegan[v].size() && prev[u = llegan[v][i].from] == -1
					&& llegan[v][i].flow ){
				prev[q[qe++] = u] = v, dir[u] = -1;
			}
		}
	}
	return prev[t] != -1;
}
int r(int u, int v, int d){
	if( d == 1 ){
		for(int i = 0; i < salen[u].size();i++)if( salen[u][i].to == v
		 && salen[u][i].flow < salen[u][i].cap ){
			 return salen[u][i].cap-salen[u][i].flow;
		 }
	}
	for(int i = 0; i < llegan[u].size();i++)if( llegan[u][i].from == v 
	 && llegan[u][i].flow ){
		 return llegan[u][i].flow;
	 }
	 return 0;
}
void modify(int uu, int vv, int d, int flow){
	int u, v;
	if( d == 1 ){
		u = uu, v = vv;
		for(int i = 0; i < salen[u].size();i++)if( salen[u][i].to == v
			&& salen[u][i].flow < salen[u][i].cap ){
			salen[u][i].flow += flow;
			break;
		}
		swap(u,v);
		for(int i = 0; i < llegan[u].size();i++)if( llegan[u][i].from == v 
		   && llegan[u][i].flow < llegan[u][i].cap ){
			llegan[u][i].flow += flow;
			return;
		}
	}else{
		u = vv, v = uu;
		for(int i = 0; i < salen[u].size();i++)if( salen[u][i].to == v
			&& salen[u][i].flow ){
			salen[u][i].flow += flow;
			break;
		}
		swap(u,v);
		for(int i = 0; i < llegan[u].size();i++)if( llegan[u][i].from == v 
		   && llegan[u][i].flow ){
			llegan[u][i].flow -= flow;
			return;
		}
	}
}
int augment(int s, int t){
	int flow = INT_MAX;
	prev[s] = s;
	for(int v = t, u = prev[v]; v != u; v = u, u = prev[v]){
		flow = min(flow, r(u,v,dir[v]));
	}
	for(int v = t, u = prev[v]; v != u; v = u, u = prev[v]){
// 		if( v == t || u == s ) continue;
		modify(u,v,dir[v], flow);
	}
	return flow;
}
int edmondsKarp(int s,int t){
	int res = 0;
	while( isPath(s,t) ) res += augment(s,t);
	return res;
}

int main(){
	int i,j ,k;
	int N, M;
	while(scanf("%i", &N)!=EOF){
		for(i=0;i<2*N+4;i++) salen[i].clear(), llegan[i].clear();
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
		int flow = edmondsKarp(0,2*N+1);
		printf("%i\n", flow);
	}return 0;
}
