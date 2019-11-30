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

struct Fraction {
  int numerator, denominator;

  bool operator<(const Fraction& other) const {
    return numerator * other.denominator < other.numerator * denominator;
  }
};

class Solution {
// Naive solution, just generate all pairs and sort.
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
      vector<Fraction> fractions;
      for (int i = 0; i < A.size(); ++i) {
        for (int j = i + 1; j < A.size(); ++j) {
          fractions.push_back({A[i], A[j]});
        }
      }
      sort(fractions.begin(), fractions.end());
      const auto& ans = fractions[K-1];
      return {ans.numerator, ans.denominator};
    }
};