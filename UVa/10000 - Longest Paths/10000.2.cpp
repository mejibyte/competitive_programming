/*
  Time limit exceeded
 */
#include <queue>
#include <iostream>
#include <vector>

using namespace std;

int n, end, length;

void dfs(int u, int w, vector<int> * g){
  if (w > length){
    length = w;
    end = u;
  }
  vector<int> &vecinos = g[u];
  for (int i=0; i<vecinos.size(); ++i){
    dfs(vecinos[i], w + 1, g);
  }
}

int main(){
  int C = 1;
  while (cin >> n && n){
    int start;
    cin >> start, --start;

    vector<int> g[n];
    int p, q;
    while (cin >> p >> q && (p+q)){
      --p, --q;
      g[p].push_back(q);
    }
    for (int i=0; i<n; ++i){
      sort(g[i].begin(), g[i].end());
    }

    end = -1, length = -1;
    dfs(start, 0, g);

    cout << "Case " << C++ << ": The longest path from " << start + 1 << " has length ";
    cout  << length << ", finishing at " << end + 1 << "." << endl << endl;
  }
  return 0;
}
