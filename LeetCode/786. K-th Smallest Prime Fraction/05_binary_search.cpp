// https://leetcode.com/problems/k-th-smallest-prime-fraction/
// Accepted
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

#ifdef LOCAL
#define DEBUG true
#else
#define DEBUG false
#endif
#define dprintf DEBUG && printf

const double eps = 1e-9;

class Solution {

public:
    // Count how many fractions there are < bound.
    int countStrictlyBelow(const vector<int>& primes, int K, double bound) {
      int count = 0;
      // Fix the denominator (primes[b]) and count how many numerators a
      // we can find such that primes[a]/primes[b] < bound.
      for (int b = 0, a = 0; b < primes.size(); ++b) {
        // Find smallest a such that primes[a]/primes[b] >= bound.
        // Any pair of primes[i]/primes[b] with i < a will satisfy
        // primes[i]/primes[b] < bound.
        // In other words, a points to one past the largest i such that
        // primes[i]/primes[b] < bound.
        while (a < b and primes[a] < bound * primes[b]) {
          a++;
        }

        // Any i = 0, 1, 2, ... a-1 satisfies primes[a]/primes[b] < bound.
        // There are exactly a of those.
        count += a;
      }
      return count;
    }

    vector<int> kthSmallestPrimeFraction(vector<int> primes, int K) {
      // Find smallest bound such that there are exactly K fractions < bound.
      double low = 0.0, high = 1.0;
      while (low + eps < high) {
        double mid = low + (high - low) / 2;
        int count = countStrictlyBelow(primes, K, mid);
        if (count < K) {
          low = mid;
        } else {
          high = mid;
        }
      }

      // Find greatest fraction < bound. That is the answer.
      optional<pair<int,int>> greatest;
      for (int b = 0, a = 0; b < primes.size(); ++b) {
          while (a < b and primes[a] < high * primes[b]) {
            a++;
          }
          if (a - 1 < 0) continue; // no solutions with primes[b] as denominator.
          if (!greatest.has_value() or primes[a-1] * greatest->second > greatest->first * primes[b]) {
            greatest = make_pair(primes[a-1], primes[b]);
          }
      }
      assert(greatest.has_value());
      dprintf("%d/%d\n", greatest->first, greatest->second);
      return {greatest->first, greatest->second};
    }


};


#ifdef LOCAL
int main() {
  Solution s;
  vector<int> v;

  //v = s.kthSmallestPrimeFraction({1, 2, 3, 5, 7}, 10);

  v = s.kthSmallestPrimeFraction({1, 2, 3, 5}, 1);
  v = s.kthSmallestPrimeFraction({1, 2, 3, 5}, 2);
  v = s.kthSmallestPrimeFraction({1, 2, 3, 5}, 3);
  v = s.kthSmallestPrimeFraction({1, 2, 3, 5}, 4);
  v = s.kthSmallestPrimeFraction({1, 2, 3, 5}, 5);
  v = s.kthSmallestPrimeFraction({1, 2, 3, 5}, 6);

  return 0;
}
#endif