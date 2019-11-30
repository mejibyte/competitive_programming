// https://leetcode.com/problems/k-th-smallest-prime-fraction/
// TLE
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <iterator>
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
#include <numeric>
#include <list>
#include <map>
#include <set>
using namespace std;

#ifdef LOCAL
#define DEBUG true
#else
#define DEBUG false
#endif
#define dprintf DEBUG && printf

typedef pair<int, int> Fraction;

class Solution {
// Naive solution, just generate all pairs and sort.
public:

    struct Compare {
      Compare(const vector<int>& primes) : primes(primes) {}
      bool operator()(const Fraction& a, const Fraction& b) {
        return primes[a.first] * primes[b.second] > primes[b.first] * primes[a.second];
      }
      const vector<int>& primes;
    };

    vector<int> kthSmallestPrimeFraction(vector<int> A, int K) {
      priority_queue<Fraction, vector<Fraction>, Compare> q(A);
      for (int b = 1; b < A.size(); ++b) {
        q.push({0, b});
      }

      while (K > 1) {
        dprintf("k=%d\n", K);
        assert(q.size() > 0);
        const Fraction at = q.top();
        q.pop();
        dprintf("popped %d/%d\n", A[at.first], A[at.second]);
        K--;
        if (at.first + 1 < at.second) {
          q.push({at.first + 1, at.second});

        }
      }
      assert(q.size() > 0);
      vector<int> ans = {A[q.top().first], A[q.top().second]};
      dprintf("ans = %d/%d\n", ans[0], ans[1]);
      return ans;
    }
};


#ifdef LOCAL
int main() {
  Solution s;
  vector<int> v;

  v = s.kthSmallestPrimeFraction({1, 2, 3, 5, 7}, 10);


  return 0;
}
#endif