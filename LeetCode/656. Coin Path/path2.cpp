// Andrés Mejía
#include <unordered_map>
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

struct Tree {
    const int oo = INT_MAX / 2;
    int n;
    vector<pair<int, int>> data;
    Tree(int n) : n(n), data(2*n, make_pair(oo, -1)) {}

    void set(int i, int value) {
        data[i + n] = make_pair(value, i);
        for (i += n; i > 1; i >>= 1) {
            data[i >> 1] = min(data[i], data[i^1]);
        }
    }

    pair<int, int> get(int l, int r) {
        pair<int, int> best = make_pair(oo, -1);
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l&1) best = min(best, data[l++]);
            if (~r&1) best = min(best, data[r--]);
        }
        return best;
    }
};

class Solution {
public:
    vector<int> cheapestJump(const vector<int>& a, int b) {
        int n = a.size();
        vector<int> ans;
        assert(n > 0);
        if (n == 1) {
            return a[0] == -1 ? ans : vector<int>({1});
        }
        if (a[n - 1] == -1) return ans;

        Tree t(n);
        vector<int> next(n, -1);
        t.set(n - 1, a[n - 1]);
        for (int i = n - 2; i >= 0; --i) {
            int from = i + 1;
            int to = min(n - 1, i + b);
            pair<int, int> best = t.get(from, to);
            next[i] = best.second;

            if (a[i] != -1) {
                t.set(i, best.first + a[i]);
            }
        }
        if (t.get(0, 0).first >= t.oo) return ans;
        for (int at = 0; at != -1; at = next[at]) {
            ans.push_back(at + 1);
        }
        assert(ans.back() == n);
        return ans;

    }
};


int main() {
  Solution s;
  auto ans = s.cheapestJump({1,1,2,1,1}, 2);
  for (auto k : ans) D(k);
  D("");

  ans = s.cheapestJump({1,2,4,-1,2}, 1);
  for (auto k : ans) D(k);
  D("");
  return 0;
}
