#include <sstream>
#include <queue>
#include <iostream>
#include <vector>

using namespace std;

struct edge{
  int to, weight, lift;
  edge(int t, int w, int l) : to(t), weight(w), lift(l) {}
  bool operator < (const edge &that) const{
    return weight > that.weight;
  }
};

int main(){
  int n, k;
  while (cin >> n >> k){
    vector<edge> g[100];
    vector<int> floors[n]; //List of floors visited by elevator i-th
    int t[n];
    for (int i=0; i<n; ++i){
      cin >> t[i];
    }
    string line;
    getline(cin, line);
    for (int i=0; i<n; ++i){
      getline(cin, line);
      stringstream ss(line);
      int x, y;
      ss >> x;
      floors[i].push_back(x);
      while (ss >> y){
	floors[i].push_back(y);
	g[x].push_back(edge(y, (y-x)*t[i], i));
	g[y].push_back(edge(x, (y-x)*t[i], i));
	x = y;
      }
    }
     
    int d[100][n];
    for (int i=0; i<100; ++i) for (int j=0; j<n; ++j) d[i][j] = INT_MAX;

    priority_queue<edge> q;
    
    for (int j=0; j<n; ++j){
      if (floors[j].front() == 0){
	//cout << "Starting at elevator " << j << " ends at floor " << floors[j].back() << endl;
	d[0][j] = floors[j].back() * t[j];
	q.push(edge(0, d[0][j], j));
      }
    }
    
    if (k == 0){
      cout << "0" << endl;
      continue;
    }
    
    while (q.size()){
      edge top = q.top(); q.pop();

      if (top.to == k) break;
      if (d[top.to][top.lift] < top.weight) continue;

      for (int i=0; i<g[top.to].size(); ++i){
	edge u = g[top.to][i];
	
	int tmp;
	if ((tmp = top.weight + u.weight + (top.lift != u.lift?(max(top.to - floors[u.lift].front(), floors[u.lift].back() - top.to)*t[u.lift]+5):0)) < d[u.to][u.lift]){
	  d[u.to][u.lift] = tmp;
	  q.push(edge(u.to, tmp, u.lift));
	}
      }
    }
    int a = *min_element(d[k], d[k]+n);
    if (a < INT_MAX)
      cout << a << endl;
    else
      cout << "IMPOSSIBLE" << endl;

    
  }
  return 0;
}
