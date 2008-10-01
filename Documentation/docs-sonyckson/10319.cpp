// 2 SAT :)

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stack>
using namespace std;
#define MED 50
#define N 100
vector<int> edges[2*N + 30];
int CC[210], id[210];
int tipo[210];
stack<int> pila;
int ID;
int SCC = 0;


int DFS3(int node){
	id[node] = ID++;
	int minid = id[node];
	tipo[node] = 1;
	pila.push(node);
	for(int i = 0 ; i < edges[node].size() ; i++ ){
		int w = edges[node][i];
		if( tipo[w] == 0 ) minid = min ( minid, DFS3(w));
		else if( tipo[w] == 1 ) minid = min ( minid, id[w]);
	}
	if( minid == id[node] ){
		SCC++;
		while(1){
			int n = pila.top(); CC[n] = SCC;pila.pop(); 
			if( n == node ) break;
		}
	}
	tipo[node] = 2;
	return minid;
}


int main(){
	int i,j ,k;
	int casos;
	scanf("%i", &casos);
	for(int h = 0; h < casos; h ++){
		for(i=0;i<2*N+30;i++) edges[i].clear();
		SCC = 0;
		int row, col, cant;
		scanf("%i %i %i", &row, &col, &cant);
		int f1, c1, f2, c2;
		for(i=0;i<cant;i++){
			scanf("%i %i %i %i", &f1, &c1, &f2, &c2);
			c1 = MED + c1;
			c2 = MED + c2;
			if( c1 == c2 ){
				if( f1 < f2 ){
					// agrego c1 o c1...
					edges[N+c1].push_back(c1);
				}else if( f2 < f1 ){
// 					printf("col = %i %i %i %i\n", f1, c1, f2, c2);
					edges[c1].push_back(N+c1);
				}
				continue;
			}
			if( f1 == f2 ){
				if( c1 < c2 ){
					// agrego f1 o f1...
					edges[N+f1].push_back(f1);
				}else if( c2 < c1 ){
// 					printf("fila = %i %i %i %i\n", f1, c1, f2, c2);
					edges[f1].push_back(N+f1);
				}
			}else if( f1 < f2 ){
				if( c1 < c2 ){
					edges[N+f1].push_back(f2);
					edges[N+f1].push_back(c1);
					edges[N+c2].push_back(f2);
					edges[N+c2].push_back(c1);
					edges[N+f2].push_back(f1);
					edges[N+f2].push_back(c2);
					edges[N+c1].push_back(f1);
					edges[N+c1].push_back(c2);
				}else{
					edges[f1].push_back(N+f2);
					edges[f1].push_back(c1);
					edges[N+c2].push_back(N+f2);
					edges[N+c2].push_back(c1);
					edges[f2].push_back(N+f1);
					edges[f2].push_back(c2);
					edges[N+c1].push_back(N+f1);
					edges[N+c1].push_back(c2);
				}
			}else{
				if( c1 < c2 ){
					edges[N+f1].push_back(f2);
					edges[N+f1].push_back(N+c1);
					edges[c2].push_back(f2);
					edges[c2].push_back(N+c1);
					edges[N+f2].push_back(f1);
					edges[N+f2].push_back(N+c2);
					edges[c1].push_back(f1);
					edges[c1].push_back(N+c2);
				}else{
					edges[f1].push_back(N+f2);
					edges[f1].push_back(N+c1);
					edges[c2].push_back(N+f2);
					edges[c2].push_back(N+c1);
					edges[f2].push_back(N+f1);
					edges[f2].push_back(N+c2);
					edges[c1].push_back(N+f1);
					edges[c1].push_back(N+c2);
				}
			}
		}
		int ID = 1;
		int vale = 1;
		memset(CC, -1, sizeof(CC));
		memset(id, -1, sizeof(id));
		memset(tipo, 0, sizeof(tipo));
		for(i=1;i<=row;i++){
			if( CC[i] < 0 ) DFS3(i);
			if( CC[i + N] < 0 ) DFS3(i + N);
			if( CC[i] == CC[i+N] ) vale = 0;
		}
		
		for(i=MED+1;i<= MED + col;i++){
			if( CC[i] < 0 ) DFS3(i);
			if( CC[i + N]< 0 ) DFS3(i + N);
			if( CC[i] == CC[i+N] ) vale = 0;
		}
		
		if( vale ) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
