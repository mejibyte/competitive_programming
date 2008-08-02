/*
  Problem: 10004 - Bicoloring
  UVa online judge

  Andrés Mejía-Posada
  Algorithm: Depth-first search

 */
#include <iostream>
#include <vector>

using namespace std;

bool dfs(int u, int c, int * color, vector<int> * g){
  //printf("u = %d, c = %d, color[%d] = %d\n", u, c, u, color[u]);
  if (color[u] != 0) return (c == color[u]);

  color[u] = c;
  for (int i=0; i<g[u].size(); ++i){
    int nc = (c == 1 ? 2 : 1);
    if (dfs(g[u][i], nc, color, g) == false){
      return false;
    }
  }
  return true;
}

int main(){
  int n, l;
  while (cin >> n && n){
    cin >> l;
    vector<int> g[n];
    int color[n];
    memset(color, 0, sizeof color);

    while (l--){
      int u, v;
      cin >> u >> v;
      g[u].push_back(v);
      g[v].push_back(u);
    }

    cout << (dfs(0, 1, color, g) ? "" : "NOT ") << "BICOLORABLE." << endl;
  }
  return 0;
}
