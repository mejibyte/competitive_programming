// https://leetcode.com/problems/k-th-smallest-prime-fraction/
// TLE
#include <unordered_set>
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

#define DEBUG false
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

    vector<int> kthSmallestPrimeFraction(vector<int> primes, int K) {
      A = primes;

      priority_queue<Fraction, vector<Fraction>, Compare> q(A);
      set<Fraction> seen;

      q.push({0, A.size() - 1});
      seen.insert({0, A.size() - 1});

      K--;
      while (K > 0) {
        assert(q.size() >= 0);
        const Fraction at = q.top();
        q.pop();
        dprintf("popped %d/%d\n", A[at.first], A[at.second]);
        K--;

        Fraction next;

        if (at.first + 1 < at.second) {
          next = {at.first + 1, at.second};
          if (seen.count(next) == 0) {
            q.push(next);
            seen.insert(next);
          }
        }

        if (at.second - 1 > at.first) {
          next = {at.first, at.second - 1};
          if (seen.count(next) == 0) {
            q.push(next);
            seen.insert(next);
          }
        }
      }
      assert(q.size() > 0);
      vector<int> ans = {A[q.top().first], A[q.top().second]};
      dprintf("ans = %d/%d\n", ans[0], ans[1]);
      return ans;
    }



    vector<int> A;
};


#ifdef LOCAL
int main() {
  Solution s;
  vector<int> v;

  v = s.kthSmallestPrimeFraction({1, 2, 3, 5, 7}, 10);


  return 0;
}
#endif