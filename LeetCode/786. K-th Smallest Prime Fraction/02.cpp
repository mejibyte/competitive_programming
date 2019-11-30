// https://leetcode.com/problems/k-th-smallest-prime-fraction/
// Idea: problem becomes finding K-th element across Q sorted lists
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


struct List {
  int in; // index of numerator
  int id; // index of denominator

  int size() const {
    return id - in;
  }
};

struct Fraction {
  int numerator, denominator;

  bool operator<(const Fraction& other) const {
    return numerator * other.denominator < other.numerator * denominator;
  }
};

class Solution {
// Naive solution, just generate all pairs and sort.
public:
    vector<int> kthSmallestPrimeFraction(vector<int> A, int K) {
      list<List> lists;
      for (int i = 1; i < A.size(); ++i) {
        lists.push_back({0, i});
        dprintf("pushed %d/%d\n", A[0], A[i]);
      }
      K--;
      while (K > 0) {
        assert(lists.size() > 0);

        int take = max(1UL, K / lists.size());
        assert((take - 1) * lists.size() < K);

        optional<Fraction> smallest;
        list<List>::iterator smallestList;
        int smallestOffset;

        for (auto p = lists.begin(); p != lists.end(); ++p) {
          const auto& list = *p;
          assert(list.size() > 0);
          int offset = min(take, list.size()) - 1;
          Fraction candidate = {A[list.in + offset], A[list.id]};
          dprintf("take = %d, Candidate: %d/%d\n", take, candidate.numerator, candidate.denominator);
          if (!smallest.has_value() or candidate < smallest) {
            smallest = candidate;
            smallestList = p;
            smallestOffset = offset;
          }
        }
        assert(smallest.has_value());
        dprintf("winner: %d/%d, offset=%d\n", smallest.value().numerator, smallest.value().denominator, smallestOffset);

        K -= (smallestOffset + 1);
        smallestList->in += smallestOffset + 1;
        if (smallestList->size() <= 0) {
          dprintf("erasing list for /%d\n", A[smallestList->id]);
          lists.erase(smallestList);
        }
      }
      // Find Kth
      dprintf("k=%d\n", K);
      vector<Fraction> answer;
      for (const auto& list : lists) {
        answer.push_back({A[list.in], A[list.id]});
      }
      sort(answer.begin(), answer.end());
      assert(K < answer.size());

      dprintf("answer = %d/%d\n", answer[K].numerator, answer[K].denominator);
      return {answer[K].numerator, answer[K].denominator};
    }
};


#ifdef LOCAL
int main() {
  Solution s;
  vector<int> v;

  // v = s.kthSmallestPrimeFraction({1, 2, 3, 5, 7}, 1);
  // for (auto k : v) cout << k << ","; cout << endl;

  v = s.kthSmallestPrimeFraction({1, 2, 3, 5}, 3);
  // for (auto k : v) cout << k << ","; cout << endl;


  return 0;
}
#endif