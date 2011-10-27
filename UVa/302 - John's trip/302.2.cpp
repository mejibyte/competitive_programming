/*
  Problem: 302 - John's trip
  Andrés Mejía-Posada (andmej@gmail.com)

  Accepted!
*/
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

#define D(x) cout << #x " is " << x << endl


struct edge{
  int to, id;
  edge(){}
  edge(int to, int id) : to(to), id(id) {}
  bool operator < (const edge &t) const {
    return id < t.id || id == t.id && to < t.to;
  }
};

const int MAXN = 45, MAXE = 1995;
vector<edge> g[MAXN];
int degree[MAXN];
bool used[MAXE];
deque<int> ans;


void dfs(int u, int last_id = -1){
  for (int k=0; k<g[u].size(); ++k){ //edges are sorted in increasing order of id
    int v = g[u][k].to, id = g[u][k].id;
    if (!used[id]){
      used[id] = true;
      dfs(v, id);
    }
  }
  ans.push_front(last_id);
}


int main(){
  int u, v, id;
  while (scanf("%d %d", &u, &v)==2 && u && v){
    for (int i=0; i<MAXN; ++i) g[i].clear();
    bzero(used, sizeof used);
    bzero(degree, sizeof degree);
    ans.clear();

    int home = min(u, v);
    scanf("%d", &id);
    g[u].push_back(edge(v, id));
    g[v].push_back(edge(u, id));
    degree[u]++, degree[v]++;

    while (scanf("%d %d", &u, &v)==2 && u && v){
      scanf("%d", &id);
      g[u].push_back(edge(v, id));
      g[v].push_back(edge(u, id));
      degree[u]++, degree[v]++;
    }

    bool ok = true;
    for (int i=0; i<MAXN; ++i){
      sort(g[i].begin(), g[i].end());
      if (degree[i] % 2) { ok = false; break; }
    }

    if (!ok){
      printf("Round trip does not exist.\n\n");
    }else{
      dfs(home);
      printf("%d", ans[1]);
      for (int i=2; i<ans.size(); ++i){
        printf(" %d", ans[i]);
      }
      printf("\n\n");
    }

  }
  return 0;
}
