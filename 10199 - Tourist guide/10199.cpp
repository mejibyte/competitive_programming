#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

typedef string node;
typedef map<node, vector<node> > graph;
typedef char color;

const color WHITE = 0, GRAY = 1, BLACK = 2;

graph g;
map<node, color> colors;

set<node> dfs(node v, set<node> visited, const node& ignore){
  colors[v] = GRAY;
  vector<node> neighbors = g[v];
  visited.insert(v);
  for (int i=0; i<neighbors.size(); ++i){
    if (visited.count(neighbors[i]) == 0 && neighbors[i] != ignore){
      set<node> temp = dfs(neighbors[i], visited, ignore);
      
      for (set<node>::iterator j = temp.begin(); j != temp.end(); ++j){
	visited.insert(*j);
      }
      
    }
  }
  colors[v] = BLACK;
  return visited;
}

int main(){
  int n;
  int map = 1;
  while (cin >> n && n > 0){
    if (map > 1) cout << endl;
    g.clear();
    colors.clear();
    while (n--){
      node v;
      cin >> v;
      colors[v] = WHITE;
      g[v] = vector<node>();
    }
    
    cin >> n;
    while (n--){
      node v,u;
      cin >> v >> u;
      g[v].push_back(u);
      g[u].push_back(v);
    }
    
    vector<node> cameras;
    
    for (graph::iterator i = g.begin(); i != g.end(); ++i){
      if (colors[(*i).first] == WHITE){
	set<node> full;
	full = dfs((*i).first, full, "");
	if (full.size() == 1) continue;
	for (set<node>::iterator j = full.begin(); j != full.end(); ++j){
	  set<node>::iterator initial = full.begin();
	  while ((*j) == (*initial)) ++initial;
	  set<node> temp = dfs((*initial), set<node>(), (*j));
	  if (temp.size() + 1 < full.size()){ //El +1 es por el nodo que ignoré
	    cameras.push_back(*j);
	  }
	}
      }
    }
    

    sort(cameras.begin(), cameras.end());
    cout << "City map #"<<map<<": " << cameras.size() << " camera(s) found" << endl;
    copy(cameras.begin(), cameras.end(), ostream_iterator<node>(cout,"\n"));
    
    ++map;
  }
  return 0;
}
