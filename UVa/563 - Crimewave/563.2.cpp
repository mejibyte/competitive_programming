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

/////////////// Maximum flow for sparse graphs ///////////////
///////////////    Complexity: O(V * E^2)      ///////////////

/*
  Usage:
  Call initialize_max_flow();
  Create graph using add_edge(u, v, c);
  max_flow(source, sink);

  WARNING: The algorithm writes on the cap array. The capacity
  is not the same after having run the algorithm.  If you need
  to run the algorithm several times on the same graph, backup
  the cap array.
 */

namespace Flow {
    // Maximum number of nodes
    const int MAXN = 51 * 51 * 2;
    // Maximum number of edges
    // IMPORTANT: Remember to consider the backedges. For
    // every edge we actually need two! That's why we have
    // multiply by two at the end.
    const int MAXE = MAXN * 6 * 2;
    const int oo = INT_MAX / 4;
    int first[MAXN];
    int next[MAXE];
    int adj[MAXE];
    int cap[MAXE];
    int current_edge;

    /*
      Builds a directed edge (u, v) with capacity c.
      Note that actually two edges are added, the edge
      and its complementary edge for the backflow.
     */
    int add_edge(int u, int v, int c){
      adj[current_edge] = v;
      cap[current_edge] = c;
      next[current_edge] = first[u];
      first[u] = current_edge++;

      adj[current_edge] = u;
      cap[current_edge] = 0;
      next[current_edge] = first[v];
      first[v] = current_edge++;
    }

    void initialize_max_flow(){
      current_edge = 0;
      memset(next, -1, sizeof next);
      memset(first, -1, sizeof first);
    }

    int q[MAXN];
    int incr[MAXN];
    int arrived_by[MAXN];
    //arrived_by[i] = The last edge used to reach node i
    int find_augmenting_path(int src, int snk){
      /*
        Make a BFS to find an augmenting path from the source
        to the sink.  Then pump flow through this path, and
        return the amount that was pumped.
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
        //Remove capacity from the edge used to reach
        //node "cur", and add capacity to the backedge
        cap[arrived_by[cur]] -= neck;
        cap[arrived_by[cur] ^ 1] += neck;
        //move backwards in the path
        cur = adj[arrived_by[cur] ^ 1];
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
}
int rows, cols;
inline int in(int u){ return 2*u; }
inline int out(int u){ return 2*u + 1; }
inline int number(int r, int c){ return r * cols + c; }

void print_edges(int u){
  printf("Edges going out from %d:\n", u);
  for (int e = Flow::first[u]; e != -1; e = Flow::next[e]){
    printf("(v = %d, cap = %d)\n", Flow::adj[e], Flow::cap[e]);
  }
}

int main(){
  int cases;
  for(scanf("%d", &cases); cases--; ){
    int banks;
    if (scanf("%d %d %d", &rows, &cols, &banks) != 3) break;

    int source = rows * cols, sink = source + 1;
    
    Flow::initialize_max_flow();
    
    for (int k=0; k<banks; ++k){
      int r, c;
      scanf("%d %d", &r, &c);
      r--, c--;
      Flow::add_edge(out(number(r, c)), in(sink), 1);
    }

    for (int i=0; i<rows; ++i){
      for (int j=0; j<cols; ++j){
        if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1){ //node lies on the border
          Flow::add_edge(out(source), in(number(i, j)), 1);
        }
        if (i - 1 >= 0){
          Flow::add_edge(out(number(i, j)), in(number(i-1, j)), 1);
        }
        if (i + 1 < rows){
          Flow::add_edge(out(number(i, j)), in(number(i+1, j)), 1);
        }
        if (j - 1 >= 0){
          Flow::add_edge(out(number(i, j)), in(number(i, j-1)), 1);
        }
        if (j + 1 < cols){
          Flow::add_edge(out(number(i, j)), in(number(i, j+1)), 1);
        }
      }
    }

    for (int i=0; i<rows; ++i){
      for (int j=0; j<cols; ++j){
        Flow::add_edge(in(number(i, j)), out(number(i, j)), 1);
      }
    }
    Flow::add_edge(in(source), out(source), Flow::oo);
    Flow::add_edge(in(sink), out(sink), Flow::oo);

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

    int f = Flow::max_flow(in(source), out(sink));

    printf("%s\n", f == banks ? "possible" : "not possible");
  }
  return 0;
}
