#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

typedef int node;
typedef pair<int, pair<node, node> > edge;
typedef map<node, vector<edge> > graph;

vector<int> maximum;
graph g;

int maxCapacity(const node& start, const node& destiny){
  priority_queue<edge> q(g[start].begin(), g[start].end());
  set<node> visited;
  visited.insert(start);
  while (!q.empty()){
    edge e = q.top();
    q.pop();
    node w = e.second.second;
    if (visited.count(w) == 0){
      maximum[w] = min(maximum[w], min(e.first, maximum[e.second.first]));
      if (w == destiny){
	return maximum[w];
      }
      visited.insert(w);
      vector<edge> neighbors = g[w];
      for (int i=0; i<neighbors.size(); ++i){
	q.push(neighbors[i]);
      }
    }
  }
  return -1;
}

int main(){
  int n, r, c = 1;
  while (cin >> n >> r && n > 0 && r > 0){
    maximum = vector<int>(n+1, INT_MAX);
    g.clear();
    while (r--){
      int x, y, d;
      cin >> x >> y >> d;
      g[x].push_back( edge(d, make_pair(x, y)) );
      g[y].push_back( edge(d, make_pair(y, x)) );
    }

    node start, destiny;
    int people;
    cin >> start >> destiny >> people;
    cout << "Scenario #" << c++ << endl;
    if (start == destiny){
      cout << "Minimum Number of Trips = 0" << endl;
    }else{
      cout << "Minimum Number of Trips = ";
      int result = 0;
      int temp = maxCapacity(start, destiny);
      while (people > 0){
	people -= temp - 1;
	++result;
      }
      cout << result << endl;
      //cout << "MaxCapacity: " << maxCapacity(start, destiny) << endl;
    }
    cout << endl;
  }
  return 0;  
}
