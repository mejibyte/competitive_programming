// CALCULAR EL LEXICOGRAF FIRST PATH EULERIANO DE UN GRAFO...
// SI LEN != C+1 ENTONCES; NO EXISTE DICHO CAMINO :)
/*
ID: edestef1
LANG: C++
TASK: fence
*/
#include <set>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <utility>
#include <stack>
using namespace std;
FILE *fin, *fout;


int main(){
	int i,j ,k;
	fin = fopen("fence.in", "r"); fout = fopen("fence.out", "w");
	vector<pair<int,int> > edge[501];
	int C;
	fscanf(fin, "%i", &C);
	for(i=0;i<C;i++){
		int a, b;
		fscanf(fin,"%i %i", &a, &b);
		edge[a].push_back(make_pair(b,i)), edge[b].push_back(make_pair(a,i));
	}
	int len = 0;
	int path[2000];
	stack<int> S;
	int location= 1;
	if( edge[1].size() %2 ==0)
	for(i=2;i<=500;i++) if(edge[i].size() % 2 ){
		location = i; break;
	}
	for(i=1;i<=500;i++) sort(edge[i].begin(), edge[i].end());
// 	path[len++] = location;
	int valor[2000];memset(valor, 0, sizeof(valor));
	
	while(1){
		int bu = 0;
		for(i=0;i<edge[location].size();i++){
			int nodo = edge[location][i].first;
			if( valor[edge[location][i].second] ) continue;

			valor[edge[location][i].second] = 1;
			
// 			path[len++] = nodo;
			S.push(location);
			location = nodo;
			bu = 1;
			break;
		}
		if( ! bu ){
// 			printf("Holanda\n");
			path[len++] = location;
			if( S.size() == 0 ) break;
			location = S.top(); S.pop();
		}
	}
// 	printf("SIIIIIIII mmmm\n");
	printf("%i\n", len);
	for(i=len-1;i>=0;i--) fprintf(fout, "%i\n", path[i]);
// 	if( len == C+1 ){
// 		for(i=0;i<len;i++) fprintf(fout, "%i\n", path[i]);
// 		for(i=0;i<len;i++) printf("%i\n", path[i]);
// 	}
	return 0;
}
