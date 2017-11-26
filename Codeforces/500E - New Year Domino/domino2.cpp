// Accepted
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
  Tree(int n, const vector<int> &X) : n(n), length(2*n, 0), covered(2*n, 0) {
    for (int i = 2*n - 1; i > 0; --i) {
      if (i >= n) { // leaf
        int p = i - n;
        assert(p < X.size());
        length[i] = (p + 1 < X.size() ? X[p + 1] : X[p]) - X[p];
      }
      else {
        length[i] = length[i << 1] + length[i << 1 | 1];
      }
    }
  }

  int n;
  vector<int> length;
  vector<int> covered;

  void update(int l, int r) {
    assert(l <= r);
    l += n, r += n;
    int l0 = l, r0 = r;
    for (; l <= r; l >>= 1, r >>= 1) {
      if (l&1) apply(l++);
      if (~r&1) apply(r--);
    }
    pull(r0), pull(l0);
  }

  void apply(int i) {
    covered[i] = length[i];
  }

  void pull(int i) {
    for (i >>= 1; i > 0; i >>= 1) {
      covered[i] = max(covered[i], covered[i << 1] + covered[i << 1 | 1]);
    }
  }

  void push(int i) {
    if (i > 1) push(i >> 1);
    if (i < n and covered[i] == length[i]) {
      apply(i << 1);
      apply(i << 1 | 1);
    }
  }

  int get(int l, int r) {
    l += n, r += n;
    push(l), push(r);
    int ans = 0;
    for (; l <= r; l >>= 1, r >>= 1) {
      if (l&1) ans += covered[l++];
      if (~r&1) ans += covered[r--];
    }
    return ans;
  }
};

struct Query {
  int l, r, index;
};

bool operator < (const Query& a, const Query& b) {
  return a.l > b.l;
}


int main() {
  int n;
  cin >> n;
  vector<int> L(n), R(n), X;
  for (int i = 0; i < n; ++i) {
    cin >> L[i] >> R[i];
    X.push_back(L[i]);
    X.push_back(L[i] + R[i]);
  }
  sort(X.begin(), X.end());
  X.resize(unique(X.begin(), X.end()) - X.begin());
  for (int i = 0; i < n; ++i) {
    R[i] = lower_bound(X.begin(), X.end(), L[i] + R[i]) - X.begin();
    L[i] = lower_bound(X.begin(), X.end(), L[i]) - X.begin();
  }

  int q;
  cin >> q;
  vector<Query> queries;
  for (int i = 0; i < q; ++i) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    assert(a < b);
    queries.push_back({L[a], L[b], i});
  }
  sort(queries.begin(), queries.end());

  int m = X.size();
  int i = n - 1;
  Tree t(m, X);

  vector<int> answer(queries.size());
  for (const Query &q : queries) {
    for (; i >= 0 and L[i] >= q.l; i--) {
      t.update(L[i], R[i] - 1);
    }
    answer[q.index] = X[q.r] - X[q.l] - t.get(q.l, q.r - 1);
  }
  for (int a : answer) {
    cout << a << endl;
  }
  return 0;
}
