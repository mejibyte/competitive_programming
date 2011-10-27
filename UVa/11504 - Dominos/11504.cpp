/*
  Problem: 11504 - Dominos
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

 */

using namespace std;
#include <iostream>
#include <vector>
#include <cassert>

const int N = 100005;

vector<int> g[N];
int color[N];

enum { standing, tiled, handed };

void dfs(int u, int root){
  if (color[u] != standing) return;

  if (u == root) color[u] = handed;
  else color[u] = tiled;

  vector<int> &out = g[u];
  for (int k=0, m=out.size(); k<m; ++k){
    int v = out[k];
    if (color[v] == handed && v != root) color[v] = tiled;
    else if (color[v] == standing) dfs(v, root);
  }
}

int main(){
  int t;
  for(cin >> t; t--;){
    int n, m; cin >> n >> m;

    assert(n < N && m < N);

    for (int i=0; i<=n; ++i) g[i].clear(), color[i] = standing;
    for (int u, v, i=0; i<m && cin >> u >> v; ++i) g[u].push_back(v);
    for (int i=1; i<=n; ++i) if (color[i] == standing) /*printf("Calling dfs(%d)...\n", i),*/ dfs(i, i);

    int ans = 0;
    for (int i=1; i<=n; ++i){
      //if (color[i] == handed) printf("Knock down tile %d\n", i);
      ans += (color[i] == handed);
    }

    cout << ans << endl;
  }
  return 0;
}
