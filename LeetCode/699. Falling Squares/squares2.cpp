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
  Tree(int n) {
    this->n = n;
    t.assign(2*n, 0);
    d.assign(n, 0);
    p.assign(n, false);
  }

  int n;
  vector<int> t;
  // Whether there are changes pending to be pushed down at node i.
  vector<bool> p;
  // If p[i] is true, d[i] contains the changes pending to be pushed down at node i.
  vector<int> d;

  // Get max between [l, r).
  int get(int l, int r) {
    assert(l < r);
    l += n, r += n;
    push(l);
    push(r - 1);
    int best = INT_MIN;
    for (; l < r; l >>= 1, r >>= 1) {
      if (l&1) best = max(best, t[l++]);
      if (r&1) best = max(t[--r], best);
    }
    return best;
  }

  // Set all elements between [l, r) to be X.
  void update(int l, int r, int value) {
    assert(l < r);
    l += n, r += n;
    int l0 = l, r0 = r;
    push(l0);
    push(r0 - 1);
    for (; l < r; l >>= 1, r >>= 1) {
      if (l&1) overwrite(l++, value);
      if (r&1) overwrite(--r, value);
    }
    refresh(l0);
    refresh(r0 - 1);
  }

private:
  // Pushes down all changes from all ancestors of p.
  void push(int u) {
    if (u > 1) push(u >> 1);
    if (u < n and p[u]) {
      overwrite(u << 1, d[u]);
      overwrite(u << 1 | 1, d[u]);
      p[u] = false;
    }
  }

  // Updates the given node with the given value.
  void overwrite(int u, int value) {
    t[u] = value;
    if (u < n) {
      p[u] = true;
      d[u] = value;
    }
  }

  // Assumes u has changed, so refreshes all of its parents.
  void refresh(int u) {
    for (u >>= 1; u > 0; u >>= 1) {
      if (!p[u]) {
        t[u] = max(t[u << 1], t[u << 1 | 1]);
      }
    }
  }
};


int compress(const vector<int> &x, int value) {
  return lower_bound(x.begin(), x.end(), value) - x.begin();
}

class Solution {
public:
    vector<int> fallingSquares(const vector<pair<int, int>>& positions) {
      int n = positions.size();
      vector<int> x;
      for (int i = 0; i < n; ++i) {
        x.push_back(positions[i].first);
        x.push_back(positions[i].first + positions[i].second);
      }
      sort(x.begin(), x.end());
      unique(x.begin(), x.end());
      int m = x.size();
      Tree t(m);

      vector<int> ans;
      for (int i = 0; i < n; ++i) {
        int left = positions[i].first;
        int side = positions[i].second;

        int l = compress(x, left);
        int r = compress(x, left + side);

        int base = t.get(l, r);
        t.update(l, r, base + side);

        ans.push_back(t.get(0, m));
      }
      return ans;
    }
};

int main(){

    Tree t(16);
    t.update(6, 8, 2);
    t.update(3, 11, 1);
    D(t.get(5, 6));
    return 0;


    t.update(1, 3, 2);
    D(t.get(3, 11));
    t.update(3, 4, 10);
    D(t.get(3, 11));
    t.update(4, 5, 11);
    D(t.get(3, 4));
    D(t.get(4, 5));
    D(t.get(3, 5));
    D(t.get(5, 6));
    return 0;

    Solution s;
    auto ans = s.fallingSquares({{1, 2}, {2, 3}, {6, 1}});
    for (auto p : ans) {
      cout << p << endl;
    }
    cout << endl;

    ans = s.fallingSquares({{100, 100}, {200, 100}});
    for (auto p : ans) {
      cout << p << endl;
    }
    cout << endl;

    ans = s.fallingSquares({{4,9},{8,8},{6,8},{8,2},{1,2}});
    for (auto p : ans) {
      cout << p << endl;
    }
    cout << endl;

    //for (auto k : ans) D(k);
    return 0;
}
