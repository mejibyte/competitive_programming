/*
  Problem: 11518 - Dominos 2
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

    Accepted
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
#include <map>
#include <set>

#define D(x) cout << #x " is " << x << endl

const int N = 10001;

vector<int> g[N];
bool dead[N];
int ans;

void shoot(int u){
  if (dead[u]) return;

  ans++;
  dead[u] = true;

  for (int i=0; i<g[u].size(); ++i) shoot(g[u][i]);
}

int main(){
  int c;
  for (cin >> c; c--; cout << ans << endl){
    int n, m, l; cin >> n >> m >> l;
    for (int i=0; i<=n; ++i){
      g[i].clear();
      dead[i] = false;
    }
    while(m--){
      int u, v;
      cin >> u >> v;
      g[u].push_back(v);
    }

    ans = 0;
    while (l--){
      int u;
      cin >> u;
      shoot(u);
    }
  }

  return 0;
}
