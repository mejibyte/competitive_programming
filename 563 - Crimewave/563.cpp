using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>

#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

/*
  Maximum number of edges is around 55*55*2*6*2.  There are less than
  55*55 nodes. We split each node in two (in and out) hence
  55*55*2. We assume each node is connected to 6 neighbors: 4 partners
  in the grid plus the source and sink, hence 55*55*2*6. But for each
  edge there are actually two edges (counting its complementary for
  the backflow).  This is actually and upper bound because I'm too
  lazy to find out the exact number of edges.
*/
const int MAXE = 55*55*2*6*2;

int cap[MAXE];
int first[MAXE];
int next[MAXE];
int adj[MAXE];
int current_edge;
int rows, cols;


const int oo = INT_MAX / 2 - 1;

int add_edge(int u, int v, int c){
  adj[current_edge] = v;
  cap[current_edge] = c;
  next[current_edge] = first[u];
  first[u] = current_edge;
  current_edge++;

  adj[current_edge] = u;
  cap[current_edge] = 0;
  next[current_edge] = first[v];
  first[v] = current_edge;
  current_edge++;
}

inline int in(int u){ return 2*u; }
inline int out(int u){ return 2*u + 1; }
inline int number(int r, int c){ return r * cols + c; }

void print_edges(int u){
  printf("Edges going out from %d:\n", u);
  for (int e = first[u]; e != -1; e = next[e]){
    printf("(v = %d, cap = %d)\n", adj[e], cap[e]);
  }
}

int q[MAXE];
int incr[MAXE];
int arrived_by[MAXE]; //arrived_by[i] = The last edge that I used to reach node i
int find_augmenting_path(int src, int snk){
  /*
    Make a BFS to find an augmenting path from the source to the sink.
    Then pump flow through this path, and return the amount that was pumped.
  */
  memset(arrived_by, -1, sizeof arrived_by);
  int h = 0, t = 0;
  q[t++] = src;
  arrived_by[src] = -2;
  incr[src] = oo;
  while (h < t && arrived_by[snk] == -1){ //BFS
    int u = q[h++];
    for (int e = first[u]; e != -1; e = next[e]){
      int v = adj[e];
      if (arrived_by[v] == -1 && cap[e] > 0){
        arrived_by[v] = e;
        incr[v] = min(incr[u], cap[e]);
        q[t++] = v;
      }
    }
  }

  if (arrived_by[snk] == -1) return 0;

  int cur = snk;
  int neck = incr[snk];
  while (cur != src){
    //Remove capacity from the edge used to reach node "cur"
    //Add capacity to the backedge
    cap[arrived_by[cur]] -= neck;
    cap[arrived_by[cur] ^ 1] += neck;

    cur = adj[arrived_by[cur] ^ 1]; //move backwards in the path
  }
  return neck;
}

int max_flow(int src, int snk){
  int ans = 0, neck;
  while ((neck = find_augmenting_path(src, snk)) != 0){
    ans += neck;
  }
  return ans;
}


int main(){
  int cases;
  for(scanf("%d", &cases); cases--; ){
    int banks;
    if (scanf("%d %d %d", &rows, &cols, &banks) != 3) break;

    int source = rows * cols, sink = source + 1;
    current_edge = 0;
    memset(next, -1, sizeof next);
    memset(first, -1, sizeof first);

    for (int k=0; k<banks; ++k){
      int r, c;
      scanf("%d %d", &r, &c);
      r--, c--;
      add_edge(out(number(r, c)), in(sink), 1);
    }

    for (int i=0; i<rows; ++i){
      for (int j=0; j<cols; ++j){
        if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1){ //node lies on the border
          add_edge(out(source), in(number(i, j)), 1);
        }
        if (i - 1 >= 0){
          add_edge(out(number(i, j)), in(number(i-1, j)), 1);
        }
        if (i + 1 < rows){
          add_edge(out(number(i, j)), in(number(i+1, j)), 1);
        }
        if (j - 1 >= 0){
          add_edge(out(number(i, j)), in(number(i, j-1)), 1);
        }
        if (j + 1 < cols){
          add_edge(out(number(i, j)), in(number(i, j+1)), 1);
        }
      }
    }

    for (int i=0; i<rows; ++i){
      for (int j=0; j<cols; ++j){
        add_edge(in(number(i, j)), out(number(i, j)), 1);
      }
    }
    add_edge(in(source), out(source), oo);
    add_edge(in(sink), out(sink), oo);

    /*
    printf("in nodes:\n");
    for (int i=0; i<rows; ++i){
      for (int j=0; j<cols; ++j){
        print_edges(in(number(i, j)));
      }
    }
    printf("out nodes:\n");
    for (int i=0; i<rows; ++i){
      for (int j=0; j<cols; ++j){
        print_edges(out(number(i, j)));
      }
    }

    print_edges(in(source));
    print_edges(out(source));

    print_edges(in(sink));
    print_edges(out(sink));
    */

    int f = max_flow(in(source), out(sink));

    printf("%s\n", f == banks ? "possible" : "not possible");
  }
  return 0;
}
