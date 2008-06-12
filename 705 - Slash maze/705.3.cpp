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

char m[75][75];

map<node, int> d;

void dfs(const node &u){
  set<node> &vecinos = g[u];
  for (set<node>::iterator i = vecinos.begin(); i != vecinos.end(); ++i){
    if (d.count(*i)){
      if (d[*i] + 1 < d[u]){
	//printf("Cycle from (%d, %d) to (%d, %d)\n", i->first, i->second, u.first, u.second);
	qty++;
	longest = max(longest, d[u] - d[*i] + 1);
      }
    }else{
      d[*i] = d[u] + 1;
      dfs(*i);
    }
  }
}

void connect(const node &u, const node &v){
  g[u].insert(v);
  g[v].insert(u);
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
	cin >> m[i][j];
      }
    }

    for (int i=0; i<w; ++i){
      for (int j=0; j<h; ++j){

	//laterales
	connect(node(i, 2*j), node(i, 2*j-1));
	connect(node(i, 2*j+1), node(i, 2*j+2));


	char c = m[i][j];
	if (c == '\\'){
	  int ni, nj;
	  
	  //arriba
	  ni = i-1;
	  nj = j;
	  if (0 <= ni && ni < w && 0 <= nj && nj < h &&
	      m[ni][nj] != m[i][j]){
	    
	    connect(node(i, 2*j+1), node(ni, 2*nj+1));
	  }

	  //abajo
	  ni = i+1;
	  nj = j;
	  if (0 <= ni && ni < w && 0 <= nj && nj < h &&
	      m[ni][nj] != m[i][j]){
	    
	    connect(node(i, 2*j), node(ni, 2*nj));
	  }

	}else if (c == '/'){
	  int ni, nj;
	  
	  //arriba
	  ni = i-1;
	  nj = j;
	  if (0 <= ni && ni < w && 0 <= nj && nj < h &&
	      m[ni][nj] != m[i][j]){
	    connect(node(i, 2*j), node(ni, 2*nj));
	  }	    

	  //abajo
	  ni = i+1;
	  nj = j;
	  if (0 <= ni && ni < w && 0 <= nj && nj < h &&
	      m[ni][nj] != m[i][j]){
	    connect(node(i, 2*j+1), node(ni, 2*nj+1));
	  }	    


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

