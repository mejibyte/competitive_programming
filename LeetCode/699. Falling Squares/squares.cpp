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

// Operations I need:
// - Get max between [l, r)
// - Set all elements between [l, r) to be X.

// Get max between [l, r).
int get(const vector<int> &t, int l, int r) {
  assert(l < r);
  int best = t[l];
  for (int i = l + 1; i < r; ++i) {
    best = max(best, t[i]);
  }
  return best;
}

void update(vector<int> &t, int l, int r, int value) {
  assert(l < r);
  for (int i = l; i < r; ++i) {
    t[i] = value;
  }
}

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
      vector<int> t(2*m, 0);

      vector<int> ans;
      for (int i = 0; i < n; ++i) {
        int left = positions[i].first;
        int side = positions[i].second;

        int l = compress(x, left);
        int r = compress(x, left + side);

        int base = get(t, l, r);
        update(t, l, r, base + side);

        ans.push_back(get(t, 0, m));
      }
      return ans;
    }
};

int main(){

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

    //for (auto k : ans) D(k);
    return 0;
}
