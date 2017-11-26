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

// Gets the max value in position at.
int get(const vector<int> &t, int at) {
  int n = t.size() / 2;
  int best = INT_MIN;
  for (at += n; at > 0; at >>= 1) {
    best = max(best, t[at]);
  }
  return best;
}

// Updates the interval [l, r).
void update(vector<int>& t, int l, int r, int value) {
  int n = t.size() / 2;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) { t[l] = max(t[l], value); l++; }
    if (r&1) { --r; t[r] = max(t[r], value); }
  }
}

class Solution {
public:
    vector<pair<int, int>> getSkyline(const vector<vector<int>>& buildings) {
      int n = buildings.size();
      vector<int> L(n), R(n), H(n), C;
      for (int i = 0; i < n; ++i) {
        const auto& b = buildings[i];
        L[i] = b[0];
        R[i] = b[1];
        H[i] = b[2];
        C.push_back(L[i]);
        C.push_back(R[i]);
      }
      sort(C.begin(), C.end());
      unique(C.begin(), C.end());
      int m = C.size();
      vector<int> tree(2*m, 0);

      for (int i = 0; i < n; ++i) {
        int l = lower_bound(C.begin(), C.end(), L[i]) - C.begin();
        int r = lower_bound(C.begin(), C.end(), R[i]) - C.begin();
        update(tree, l, r, H[i]);
      }

      vector<pair<int, int>> ans;
      for (int last = 0, i = 0; i < m; ++i) {
        int h = get(tree, i);
        if (h != last) {
          ans.push_back(make_pair(C[i], h));
        }
        last = h;
      }
      return ans;
    }
};

int main(){
    Solution s;
    auto ans = s.getSkyline({ {2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8} });
    for (auto p : ans) {
      cout << p.first << " " << p.second << endl;
    }
    //for (auto k : ans) D(k);
    return 0;
}
