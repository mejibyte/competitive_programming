#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

typedef string node;
typedef pair<node, node> edge;
typedef map<node, vector<node> > graph;

bool dfs(node v, node destiny, set<node> visited, const graph &g, const set<node> &forbidden){
  vector<node> neighbors = (*(g.find(v))).second;
  for (int i=0; i<neighbors.size(); ++i){
    if (neighbors[i] == destiny) return true;
    if (!(visited.count(neighbors[i])) && !(forbidden.count(neighbors[i]))){
      set<node> temp = visited;
      temp.insert(v);
      if (dfs(neighbors[i], destiny, temp, g, forbidden)){
	return true;
      }
    }
  }
  return false;
}

bool validate(edge e, const graph &g, const set<node> &forbidden){
  set<node> visited;
  return (dfs(e.first, e.second, visited, g, forbidden));
}

int main(){
  string name1, name2;
  while (getline(cin, name1) && name1 != "END"){
    graph g;
    set<node> forbidden;
    string line;
    vector<edge> streets;
    while (getline(cin, line) && line != "* * *"){
      stringstream sin;
      sin << line;
      edge e;
      sin >> e.first >> e.second;
      streets.push_back(e);
      forbidden.insert(e.first);
      forbidden.insert(e.second);
    }

    getline(cin, name2);
    while (getline(cin, line) && line != "* * *"){
      stringstream sin;
      sin << line;
      edge e;
      sin >> e.first >> e.second;
      vector<node> v;
      if (g.count(e.first) == 0){
	g[e.first] = v;
      }
      if (g.count(e.second) == 0){
	g[e.second] = v;
      }
      g[e.first].push_back(e.second);
      g[e.second].push_back(e.first);
    }

    //Terminé la lectura
    for (set<node>::iterator it = forbidden.begin(); it != forbidden.end(); ++it){
      if (g.count((*it)) == 0){
	cout << "NO: " << name2 <<" is not a more detailed version of " << name1 << endl;
	continue;
      }
    }
    bool impossible = false;
    for (int i=0; i<streets.size(); ++i){
      if (!validate(streets[i], g, forbidden)){
	impossible = true;
	break;
      }
    }
    if (impossible){
      cout << "NO: " << name2 <<" is not a more detailed version of " << name1 << endl;
    }else{
      cout << "YES: " << name2 <<" is a more detailed version of " << name1 << endl;
    }
  }
  return 0;
}
