using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <numeric>
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
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

const int MAXN = 105;

vector<pair<int, int> > g[MAXN];
int d[MAXN];

int main(){
  int n, m;
  while (cin >> n >> m && n){
    n++;
    for (int i=0; i<n; ++i) g[i].clear();
    while (m--){
      int si, ni, a, b, c; string op;
      cin >> si >> ni >> op >> c;
      a = si + ni;
      b = si - 1;
      if (op == "lt"){
        g[b].push_back(make_pair(a, c-1));
      }else{
        g[a].push_back(make_pair(b, -c-1));
      }
    }

    int dummy = n+1;
    for (int i=0; i<n; ++i) g[dummy].push_back(make_pair(i, 0));

    fill(d, d+n, INT_MAX / 3);
    d[dummy] = 0;
    for (int repeat = true, cota = n; repeat && --cota; ){
      repeat = false;
      for (int u=0; u<n; ++u){
        for (int k=0; k<g[u].size(); ++k){
          int v = g[u][k].first, w = g[u][k].second;
          if (d[u] + w < d[v]){
            d[v] = d[u] + w;
            repeat = true;
          }
        }
      }
    }

    bool solvable = true;
    for (int u=0; u<n; ++u){
      for (int k=0; k<g[u].size(); ++k){
        int v = g[u][k].first, w = g[u][k].second;
        if (d[u] + w < d[v]){
          solvable = false;
          u = n; break; //ultrabreak
        }
      }
    }

    if (solvable) puts("lamentable kingdom");
    else puts("successful conspiracy");
  }

return 0;
}
