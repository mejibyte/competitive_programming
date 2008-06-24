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
    priority_queue<pair<int, int> > Q; //First = distance, second = destiny
    int visited[n];
    for (int i=0; i<n; ++i) visited[i] = -1;
    Q.push(make_pair(0, -start));
    while (Q.size()){
      int u = -Q.top().second;
      int w = Q.top().first;
      //cout << "Saque " << u + 1 << " " << w << endl;
      Q.pop();

      if (visited[u] > w) continue;

      if (w > length || (w == length && u < answer)){ //En esta línea estaba el bug...
        answer = u;
        length = w;
      }
      vector<int> &vecinos = g[u];
      for (int i=0; i<vecinos.size(); ++i){
        if (visited[vecinos[i]] < w + 1){
          visited[vecinos[i]] = w + 1;
          Q.push(make_pair(w + 1, -vecinos[i]));
        }
      }
    }
    cout << "Case " << C++ << ": The longest path from " << start + 1 << " has length ";
    cout  << length << ", finishing at " << answer + 1 << "." << endl << endl;
  }
  return 0;
}
