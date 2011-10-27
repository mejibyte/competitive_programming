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
#include <list>
#include <map>
#include <set>

#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " is " << x << endl

const int MAXE = 1000; //Max number of edges
const int oo = INT_MAX / 2 - 1;
int cap[MAXE];
int first[MAXE];
int next[MAXE];
int adj[MAXE];
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

int q[MAXE];
int incr[MAXE];
int arrived_by[MAXE]; //arrived_by[i] = The last edge used to reach node i
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
  int n, Case = 1;
  while (scanf("%d", &n)==1 && n){
    initialize_max_flow();
    int src, snk, e;
    scanf("%d %d %d", &src, &snk, &e);
    while (e--){
      int u, v, c;
      scanf("%d %d %d", &u, &v, &c);
      add_edge(u, v, c);
      add_edge(v, u, c);
    }
    printf("Network %d\n", Case++);
    printf("The bandwidth is %d.\n\n", max_flow(src, snk));
  }
  return 0;
}
