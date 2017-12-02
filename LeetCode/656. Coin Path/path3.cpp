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

const int oo = INT_MAX / 2; // half to avoid overflow. Might not be needed but whatever.

// This is a normal queue extended to allow querying for the minimum element inside it in O(1) time.
template <class T>
struct MinQueue {
    deque<pair<T, int>> data;
    int in, out;
    MinQueue() : in(0), out(0) {};

    // Amortized O(1) because each element is pushed and popped from the queue exactly once.
    void push(const T& t) {
        pair<T, int> next = make_pair(t, in++);
        while (data.size() > 0 and next < data.front()) {
            data.pop_front();
        }
        data.push_front(next);
    }

    // O(1)
    void pop() {
        if (data.back().second == out++) {
            data.pop_back();
        }
    }

    // O(1)
    T min() {
        return data.back().first;
    }
};

class Solution {
public:
    vector<int> cheapestJump(vector<int>& a, int b) {
        int n = a.size();
        assert(n > 0);
        // Degenerate case.
        if (n == 1) {
            return a[0] == -1 ? ans : vector<int>({1});
        }
        // Replace -1's with infinity just to simplify the logic below.
        for (int i = 0; i < n; ++i) {
            if (a[i] == -1) {
                a[i] = oo;
            }
        }

        vector<int> next(n, -1); // To reconstruct the actual path.
        MinQueue<pair<int, int>> q;
        q.push(make_pair(a[n - 1], n - 1));
        for (int i = n - 2; i >= 0; --i) {
            // Invariant: at the start of the loop, the queue contains all elements in range
            // [i + 1, i + b].
            pair<int, int> best = q.min();
            int w = min(best.first + a[i], oo);
            if (w < oo) {
                next[i] = best.second;
            }

            // Update queue so invariant is true for next iteration.
            q.push(make_pair(w, i));
            if (i + b < n) {
                q.pop();
            }
        }
        vector<int> ans;
        for (int at = 0; at != -1; at = next[at]) {
            ans.push_back(at + 1);
        }
        if (ans.back() == n) {
            return ans;
        }
        return {};
    }
};


int main() {
  Solution s;
  vector<int> k;

  auto ans = s.cheapestJump(k = {1,1,2,1,1}, 2);
  for (auto k : ans) D(k);
  D("");

  ans = s.cheapestJump(k = {1,2,4,-1,2}, 1);
  for (auto k : ans) D(k);
  D("");
  return 0;
}
