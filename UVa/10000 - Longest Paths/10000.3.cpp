/*
  Accepted
 */
#include <queue>
#include <iostream>
#include <vector>

using namespace std;

int main(){
  int n;
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

    int answer = -1, length = -1;
    queue<int> Q;

    int d[n];
    for (int i=0; i<n; ++i) d[i] = INT_MIN;
    Q.push(start);
    d[start] = 0;
    while (Q.size()){
      int u = Q.front();
      Q.pop();

      if (d[u] > length || (d[u] == length && u < answer)){
        answer = u;
        length = d[u];
      }
      vector<int> &vecinos = g[u];
      for (int i=0; i<vecinos.size(); ++i){
        int v = vecinos[i];
        if (d[u] + 1 > d[v]){ //Puedo llegar en un camino más largo
          d[v] = d[u] + 1;
          Q.push(v);
        }
      }
    }
    cout << "Case " << C++ << ": The longest path from " << start + 1 << " has length ";
    cout  << length << ", finishing at " << answer + 1 << "." << endl << endl;
  }
  return 0;
}
