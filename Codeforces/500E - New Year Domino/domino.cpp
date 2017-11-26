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


// TIME LIMIT EXCEEDED
// Just testing the boilerplate.

vector<int> X;

struct Tree {
  Tree(int n) : n(n), t(2*n, 0), covered(2*n, false), p(n, false) {}

  int n;
  vector<int> t, p;
  vector<bool> covered;

  void update(int l, int r) {
    //printf("update(%d, %d)\n", l, r);

    for (int i = l; i <= r; ++i) {
      covered[i] = true;
    }
  }

  int get(int l, int r) {
    int ans = 0;
    for (int i = l; i <= r; ++i) {
      if (covered[i]) {
        assert(i + 1 < X.size());
        ans += X[i + 1] - X[i];
      }
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
  vector<int> L(n), R(n);
  X.clear();
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
  Tree t(m);
  vector<int> answer(queries.size());
  for (const Query &q : queries) {
    //printf("processing query %d from %d to %d\n", q.index, q.l, q.r);
    for (; i >= 0 and L[i] >= q.l; i--) {
      //printf("pushed domino %d\n", i);
      t.update(L[i], R[i] - 1);
    }
    answer[q.index] = X[q.r] - X[q.l] - t.get(q.l, q.r - 1);
  }
  for (int a : answer) {
    cout << a << endl;
  }
  return 0;
}
