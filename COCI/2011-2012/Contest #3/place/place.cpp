// Andrés Mejía
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
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
 
////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl
 
const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////
 
#define SIZE(t) ((int)((t).size()))
 
struct FenwickTree {
    int N;
    vector<int> d;
    FenwickTree(int length) : N(length + 1), d(N) { }
    
    void update(int at, int by) {
        for (at++; at < N; at += at & -at) {
            d[at] += by;
        }
    }
    
    long long query(int at) {
        int ans = 0;
        for (at++; at > 0; at -= at & -at) {
            ans += d[at];
        }
        return ans;
    }
    
    // returns sum[from, to]
    long long query(int from, int to) {
        int ans = query(to);
        if (from - 1 >= 0) ans -= query(from - 1);
        return ans;
    }
};
 
// the original tree
int N;
vector<vector<int> > G; 
 
// rooted tree as parent/child edges
vector<vector<int> > children;
vector<int> parent;
 
vector<int> subtree_size;
 
// heavy-light decomposition of the tree into paths
vector< vector<int> > paths;
vector<int> path_id, path_offset;
 
// sum for each path
vector< FenwickTree > trees;
 
void dfs() {
  parent.clear(); parent.resize(N);
  children.clear(); children.resize(N);
  subtree_size.clear(); subtree_size.resize(N);
  paths.clear();
  vector<bool> visited(N,false);
  vector<int> walk;
  int time = 0;
 
  // run the DFS to compute lots of information
  stack<int> vertex, edge;
  visited[0]=true; parent[0]=0;
  vertex.push(0); edge.push(0);
  while (!vertex.empty()) {
    ++time;
    int kde = vertex.top(); vertex.pop();
    int e = edge.top(); edge.pop();
    if (e == SIZE(G[kde])) {
      walk.push_back(kde);
      subtree_size[kde] = 1;
      for (int i=0; i<SIZE(children[kde]); ++i) subtree_size[kde] += subtree_size[children[kde][i]];
    } else {
      vertex.push(kde); edge.push(e+1);
      int kam = G[kde][e];
      if (!visited[kam]) { 
        visited[kam]=true; parent[kam]=kde; children[kde].push_back(kam);
        vertex.push(kam); edge.push(0);
      }
    }
  }
 
  // compute the heavy-light decomposition
  vector<bool> parent_edge_processed(N,false);
  parent_edge_processed[0] = true;
  for (int i=0; i<SIZE(walk); ++i) {
    int w = walk[i];
    if (parent_edge_processed[w]) continue;
    vector<int> this_path;
    this_path.push_back(w); 
    while (1) {
      bool is_parent_edge_heavy = (2*subtree_size[w] >= subtree_size[parent[w]]);
      parent_edge_processed[w] = true;
      w = parent[w];
      this_path.push_back(w);
      if (!is_parent_edge_heavy) break;
      if (parent_edge_processed[w]) break;
    }
    paths.push_back(this_path);
  }
    
  path_id.clear(); path_id.resize(N);
  path_offset.clear(); path_offset.resize(N);
 
  paths.push_back(vector<int>());
  paths.back().push_back(0);
  paths.back().push_back(-1);
 
  for (int i=0; i<SIZE(paths); ++i) 
    for (int j=0; j<SIZE(paths[i])-1; ++j) {
      path_id[ paths[i][j] ] = i;
      path_offset[ paths[i][j] ] = j;
    }
  
  trees.clear();
  for (int i=0; i<SIZE(paths); ++i) trees.push_back( FenwickTree( SIZE(paths[i]) + 5 ) );
}
 
vector< int > initial_salary;
 
void update(int node, int by) {
    int p = path_id[node];
    int at = path_offset[node];
    trees[p].update(at, by);
}
 
 
int get(int node) {
    int ans = initial_salary[node];
    int p = path_id[node];
    int at = path_offset[node];
    ans -= trees[p].query(at, at);
    
    //printf("started on node = %d. Initial = %d, removed = %lld\n", node, initial_salary[node], trees[p].query(at, at) );
    
    while (node >= 0) {
        p = path_id[node];
        at = path_offset[node];
        int len = paths[p].size();
        ans += trees[p].query(at, len);
        node = paths[p].back();
    }
    return ans;
}
 
int main(){
    int Q;
    cin >> N >> Q;
    G.clear(); G.resize(N);
    initial_salary.resize(N);
    cin >> initial_salary[0];
        
    for (int i=1; i<N; ++i) {
        int parent;
        cin >> initial_salary[i] >> parent;
        parent--;
        G[i].push_back(parent);
        G[parent].push_back(i);
    }
    dfs();
        
    // printf("There are %d paths:\n", paths.size());
    // for (int k = 0; k < paths.size(); ++k) {
    //     vector<int> path = paths[k];
    //     for (int j = 0; j < path.size(); ++j) {
    //         printf("%d ", path[j]);
    //     }
    //     puts("");
    // }
    
    // for (int i = 0; i < N; ++i) {
    //     printf("time_[%d] = [%d, %d], subtree_size = %d\n", i, time_in[i], time_out[i], subtree_size[i]);
    // }
    // 
    // for (int i = 0; i < N; ++i) {
    //     printf("path_id[i=%d] = %d\n", i, path_id[i]);
    //     printf("path_offset[i=%d] = %d\n", i, path_offset[i]);
    // }
    
    for (int q = 0; q < Q; ++q) {
           char type; scanf(" %c ", &type);
           if (type == 'p') { // increase
               int u, delta;
               scanf("%d %d", &u, &delta);
               u--;
               update(u, delta);
           } else { // how much?
               int u; scanf("%d", &u);
               u--;
               printf("%d\n", get(u));
           }
       }
    
 
    return 0;
}