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

class Solution {
public:
    vector<int> cheapestJump(const vector<int>& a, int b) {
        int n = a.size();
        vector<int> ans;
        assert(n > 0);
        if (n == 1) {
            return a[0] == -1 ? ans : vector<int>({1});
        }
        if (a[0] == -1 || a[n - 1] == -1) return ans;
        const int oo = INT_MAX / 2;
        vector<int> d(n, oo);
        d[n - 1] = a[n - 1];
        priority_queue< pair<int, int> > q;
        vector<int> from(n, -1);
        q.push(make_pair(-d[n - 1], n - 1));
        while (q.size() > 0) {
            int w = -q.top().first;
            int at = q.top().second;
            q.pop();
            if (w > d[at]) continue;
            assert(w == d[at]);
            for (int to = at - 1; to >= at - b and to >= 0; --to) {
                if (a[to] == -1) continue;
                int new_w = d[at] + a[to];
                if (new_w < d[to] || new_w == d[to] and at < from[to]) {
                    d[to] = new_w;
                    from[to] = at;
                    q.push(make_pair(-new_w, to));
                }
            }
        }
        if (d[0] == oo) return {};
        for (int at = 0; at != -1; at = from[at]) {
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
  return 0;
}
