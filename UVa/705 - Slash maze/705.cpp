#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <set>

using namespace std;

typedef pair<int, int> node;
typedef map<node, set<node> > graph;

int longest;
int qty;

graph g;

map<node, int> d;

void dfs(const node &u){
  set<node> &vecinos = g[u];
  for (set<node>::iterator i = vecinos.begin(); i != vecinos.end(); ++i){
    if (d.count(*i)){
      if (d[*i] + 1 < d[u]){
	printf("Cycle from (%d, %d) to (%d, %d)\n", i->first, i->second, u.first, u.second);
	qty++;
	longest = max(longest, d[u] - d[*i] + 1);
      }
    }else{
      d[*i] = d[u] + 1;
      dfs(*i);
    }
  }
}

int main(){
  int w,h;
  int mazeNo = 1;
  while (cin >> w >> h && w && h){
    g.clear();
    d.clear();

    longest = -1;
    qty = 0;

    for (int i=0; i<w; ++i){
      for (int j=0; j<h; ++j){
	
	  g[node(2*i, j)].insert(node(2*i-1, j));
	  g[node(2*i-1, j)].insert(node(2*i, j));
	
	  g[node(2*i+1, j)].insert(node(2*i+2, j));
	  g[node(2*i+2, j)].insert(node(2*i+1, j));


	char c;
	cin >> c;
	if (c == '\\'){
	  
	    g[node(2*i, j)].insert(node(2*i, j+1));
	    g[node(2*i, j+1)].insert(node(2*i, j));


	    g[node(2*i+1, j)].insert(node(2*i+1, j-1));
	    g[node(2*i+1, j-1)].insert(node(2*i+1, j));

	  
	}else if (c == '/'){
	    g[node(2*i,j)].insert(node(2*i, j-1));
	    g[node(2*i,j-1)].insert(node(2*i, j));


	    g[node(2*i+1,j)].insert(node(2*i+1, j+1));
	    g[node(2*i+1,j+1)].insert(node(2*i+1, j));


	}else{
	  cerr << "Unrecognized char in input" << endl;
	}       
      }
    }

    /*for (map<node, set<node> >::iterator i = g.begin(); i != g.end(); ++i){
      printf("Vecinos de (%d, %d):\n", i->first.first, i->first.second);
      set<node> v = i->second;
      for (set<node>::iterator j = v.begin(); j != v.end(); ++j){
	printf("(%d, %d) ", j->first, j->second);
      }
      cout << endl;
      }*/

    for (map<node, set<node> >::iterator i = g.begin(); i != g.end(); ++i){
      if (d.count(i->first) == 0){
	d[i->first] = 0;
	dfs(i->first);
      }
    }

    printf("Maze #%d:\n", mazeNo++);
    if (qty == 0){
      printf("There are no cycles.\n");
    }else{
      printf("%d Cycles; the longest has length %d\n", qty, longest);
    }
    printf("\n");

    

  }
  return 0;
}

