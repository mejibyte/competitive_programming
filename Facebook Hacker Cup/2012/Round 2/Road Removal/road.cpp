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

const int MAXN = 10005;

int p[MAXN], rank[MAXN];

void make_set(int x){
    p[x] = x, rank[x] = 0;
}
void link(int x, int y){
  if (rank[x] > rank[y]) p[y] = x;
  else { 
      p[x] = y; 
      if (rank[x] == rank[y]) rank[y]++;
  }
}

int find_set(int x){
  return x != p[x] ? p[x] = find_set(p[x]) : p[x];
}

void merge(int x, int y){
    link(find_set(x), find_set(y));
}


void solve() {
    int n, m, k; scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; ++i) make_set(i);
    int ans = 0;
    vector< pair<int, int> > remain;
    for (int i = 0; i < m; ++i) {
        int u, v; scanf("%d %d", &u, &v);
        if (u >= k and v >= k) {
            if (find_set(u) != find_set(v)) merge(u, v);
        } else {
            remain.push_back( make_pair(u, v) );
        }
    }
    for (int i = 0; i < remain.size(); ++i) {
        int u = remain[i].first, v = remain[i].second;
        if (find_set(u) != find_set(v)) {
            merge(u, v);
        } else {
            ans++;
        }
    }
    printf("%d\n", ans);
}

int main(){
    int T; scanf("%d", &T); for (int run = 1; run <= T; ++run) {
        printf("Case #%d: ", run);
        solve();
    }
    return 0;
}