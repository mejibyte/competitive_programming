/*
  Problem: 610 - Street directions (UVa online judge)

  Author: Andrés Mejía-Posada (http://github.com/andmej/acm)
  Algorithm: Depth-first search
 */
#include <iostream>

using namespace std;

const int MAXN = 1000;

bool g[MAXN][MAXN], visited[MAXN];
int n, p[MAXN]; //p[i] = nodo predecesor que me llevó al nodo i.

void dfs(int u){
  visited[u] = true;
  for (int v=0; v<n; ++v){
    if (g[u][v]){ //hay arista
      if (visited[v] && v != p[u]){ //encontre un ciclo
        g[v][u] = false;
        int previous = u;
        while(previous != v){ //Volver de una sola vía todas las aristas del ciclo
          g[previous][p[previous]] = false;
          previous = p[previous];
        }
      }else if (!visited[v]){
        p[v] = u;
        dfs(v);
      }
    }
  }
}

int main(){
  int m, C=1;
  while (scanf("%d %d", &n, &m) == 2 && (n+m)){
    for (int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
        g[i][j] = false;
      }
      visited[i] = false;
      p[i] = -1;
    }

    int u, v;
    while (m--){
      scanf("%d %d", &u, &v);
      --u, --v;
      g[u][v] = g[v][u] = true;
    }

    dfs(0);
    printf("%d\n\n", C++);
    for(int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
        if (g[i][j]){
          printf("%d %d\n", i+1, j+1);
        }
      }
    }
    printf("#\n");

  }
  return 0;
}
