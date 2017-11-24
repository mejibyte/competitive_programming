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

void add(vector<int> &t, int at, int v = 1) {
  for (at++; at < t.size(); at += at & -at) {
    t[at] += v;
  }
}

int get(vector<int> &t, int at) {
  int ans = 0;
  for (at++; at > 0; at -= at & -at) {
    ans += t[at];
  }
  return ans;
}

class Solution {
public:
    vector<int> countSmaller(vector<int>& a) {
      vector<int> b = a;
      // Compress coordinates to make all numbers be in [0, n).
      sort(b.begin(), b.end());
      for (int i = 0; i < a.size(); ++i) {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
      }
      // At this point, all a[i]'s are between [0, n).

      // Now do the work (re-using b for the answer.)
      int n = a.size();
      vector<int> t(n + 1);
      for (int i = n - 1; i >= 0; --i) {
        b[i] = a[i] > 0 ? get(t, a[i] - 1) : 0;
        add(t, a[i]);
      }
      return b;
    }
};

int main(){
    Solution s;
    vector<int> v = {5, 2, 6, 1};
    auto ans = s.countSmaller(v);
    for (auto k : ans) D(k);
    return 0;
}
