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

// Returns the K-th element of the two sorted arrays a and b.
// na: length of the array a.
// nb: length of the array b.
// K-th is 1-based.
int find_kth(const int a[], int na, const int b[], int nb, int k) {
  assert(k >= 1);
  assert(na + nb >= k);
  // Base case: one of the arrays is empty.
  if (na == 0) {
    return b[k - 1];
  }
  if (nb == 0) {
    return a[k - 1];
  }
  // Base case: we want the smallest one.
  if (k == 1) {
    return min(a[0], b[0]);
  }

  int take_a = min(na, k/2);
  int take_b = min(nb, k/2);
  // You can choose any pair of take_a and take_b as long as
  // take_a + take_b <= k. (E.g. mergesort does the same thing with take_a == 1 and take_b == 1).
  assert(take_a + take_b <= k);

  if (a[take_a - 1] <= b[take_b - 1]) {
    return find_kth(a + take_a, na - take_a, b, nb, k - take_a);
  } else {
    return find_kth(a, na, b + take_b, nb - take_b, k - take_b);
  }
}


class Solution {
public:
    double findMedianSortedArrays(const vector<int>& nums1, const vector<int>& nums2) {
      assert(nums1.size() > 0 or nums2.size() > 0);
      int total = nums1.size() + nums2.size();
      if (total % 2 == 0) {
        int x = find_kth(nums1.data(), nums1.size(), nums2.data(), nums2.size(), total / 2);
        int y = find_kth(nums1.data(), nums1.size(), nums2.data(), nums2.size(), total / 2 + 1);
        return (x + y) / 2.0;
      } else {
        return find_kth(nums1.data(), nums1.size(), nums2.data(), nums2.size(), (total + 1) / 2);
      }
    }
};


int main(){
    Solution s;
    auto m = s.findMedianSortedArrays({1, 3}, {2});
    D(m);
    m = s.findMedianSortedArrays({1, 2}, {3, 4});
    D(m);
    return 0;
}
