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

struct Tree {
  Tree(int n) : n(n), t(2*n, 0), p(n, false) {}

  int n;
  vector<int> t, p;

  // Overwrites all elements in range [l, r] to be value.
  void set(int l, int r, int value) {
    l += n, r += n;
    push(l), push(r);
    for (; l <= r; l >>= 1, r >>= 1) {
      if (l & 1) overwrite(l++, value);
      if (~r & 1) overwrite(r--, value);
    }
  }

  // Returns the value at index i.
  int get(int i) {
    i += n;
    push(i);
    return t[i];
  }

  // Pushes down all lazy propagation from ancestors of i.
  void push(int i) {
    if (i > 1) push(i >> 1);
    if (i < n and p[i]) {
      overwrite(i << 1, t[i]);
      overwrite(i << 1 | 1, t[i]);
      p[i] = false;
    }
  }

  void overwrite(int i, int value) {
    t[i] = value;
    if (i < n) {
      p[i] = true;
    }
  }
};


int main() {
  int cases;
  cin >> cases;
  while (cases--) {
    int n;
    cin >> n;
    vector<int> l(n), r(n), x;
    for (int i = 0; i < n; ++i) {
      cin >> l[i] >> r[i];
      x.push_back(l[i]);
      x.push_back(r[i]);
    }

    sort(x.begin(), x.end());
    x.resize(unique(x.begin(), x.end()) - x.begin());

    Tree t(x.size());

    for (int i = 0; i < n; ++i) {
      int a = lower_bound(x.begin(), x.end(), l[i]) - x.begin();
      int b = lower_bound(x.begin(), x.end(), r[i]) - x.begin();
      t.set(a, b, i + 1);
    }

    set<int> ans;
    for (int i = 0; i < x.size(); ++i) {
      int p = t.get(i);
      if (p > 0) {
        ans.insert(p);
      }
    }
    cout << ans.size() << endl;
  }
  return 0;
}
