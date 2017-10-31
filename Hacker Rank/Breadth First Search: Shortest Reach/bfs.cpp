// Andrés Mejía
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
#include <bitset>
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
using namespace std;

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cerr << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

const int MAXN = 3005;
const long long oo = LLONG_MAX / 2; // Avoid overflow.
vector<int> g[MAXN];
long long d[MAXN];


int main(){
  int t;
  cin >> t;
  for(int a0 = 0; a0 < t; a0++){
      int n;
      int m;
      cin >> n >> m;

      for (int i = 0; i < n; ++i) {
        g[i].clear();
        d[i] = oo;
      }
      for(int a1 = 0; a1 < m; a1++){
          int x;
          int y;
          int r;
          cin >> x >> y;
          x--, y--;

          g[x].push_back(y);
          g[y].push_back(x);
      }
      int start;
      cin >> start;
      start--;

      queue<int> q;
      q.push(start);
      d[start] = 0;

      while (q.size() > 0) {
        int at = q.front();
        q.pop();

        for (const int &out : g[at]) {
          if (d[at] + 1 < d[out]) {
            d[out] = d[at] + 1;
            q.push(out);
          }
        }
      }

      for (int i = 0, first = true; i < n; i++) {
        if (i != start) {
          if (!first) cout << " ";
          cout << (d[i] < oo ? 6 * d[i] : -1);
          first = false;
        }
      }
      cout << endl;

  }
  return 0;
}
