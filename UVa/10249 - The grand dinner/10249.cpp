/*
  Problem: 10249 - The grand dinner
  Andrés Mejía-Posada (andmej@gmail.com)

  Time limit exceeded
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

#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " is " << x << endl
#define For(i, a, b) for (int i=(a); i<(b); ++i)

const int MAXN = 205;

int cap[MAXN][MAXN];
int flow[MAXN][MAXN];
int prev[MAXN];

bool findPath(int n, int src, int sink){
  fill(prev, prev+n, -1);
  queue<int> q;
  q.push(src);
  while (q.size()){
    int u = q.front(); q.pop();
    if (u == sink) return true;
    for (int v = 0; v<n; ++v){
      if (v != src && prev[v] == -1 && flow[u][v] < cap[u][v]){
        prev[v] = u;
        q.push(v);
      }
    }
  }
  return false;
}

int maxFlow(int n, int src, int sink){
  memset(flow, 0, sizeof flow);
  int ans = 0;
  while (findPath(n, src, sink)){
    int neck = INT_MAX;
    for (int u = sink; prev[u] != -1; u = prev[u]){
      neck = min(neck, cap[prev[u]][u] - flow[prev[u]][u]);
    }
    for (int u = sink; prev[u] != -1; u = prev[u]){
      flow[prev[u]][u] += neck;
      flow[u][prev[u]] -= neck;
    }
    ans += neck;
  }
  return ans;
}

int main(){
  int nteams, ntables;
  while (scanf("%d %d", &nteams, &ntables)==2 && nteams && ntables){
    int people = 0;
    const int source = nteams + ntables, sink = source + 1;
    memset(cap, 0, sizeof cap);
    for (int i=0, c; i<nteams; ++i){
      scanf("%d", &c);
      cap[source][i] = c;
      people += c;
    }
    for (int i=0, c; i<ntables; ++i){
      scanf("%d", &c);
      cap[nteams+i][sink] = c;
    }
    for (int i=0; i<nteams; ++i){
      for (int j=0; j<ntables; ++j){
        cap[i][nteams+j] = 1;
      }
    }
    int f = maxFlow(nteams + ntables + 2, source, sink);
    if (f < people){
      printf("0\n");
    }else{
      printf("1\n");
      for (int i=0; i<nteams; ++i){
        bool first = true;
        for (int j=0; j<ntables; ++j){
          if (flow[i][nteams+j] > 0){
            if (!first) printf(" ");
            first = false;
            printf("%d", j+1);
          }
        }
        printf("\n");
      }
    }
  }
  return 0;
}
