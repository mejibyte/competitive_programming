// Optimization when all numbers are <= 100.

// How to optimize when MOST (99.9%) numbers are in [0, 100]?
// Keep three structures:
// - nums < 0
// - counts in [0, 100]
// - nums > 100
// To find Kth, check if it is in one of the two extremes (O(1)).
// If it is in the middle, just adjust index (k -= |nums < 0|) and look it up just as before.

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


class MedianFinder {
public:
    const int MAX = 100;
    /** initialize your data structure here. */
    MedianFinder() {
      count.assign(MAX+1, 0);
    }

    void addNum(int num) {
      assert(num <= MAX);
      count[num]++;
    }

    // Find k-th element (0-based, so k == 0 is the first element).
    int findKth(int k) {
      int seen = 0;
      // Find the smallest i such that sum(count[0..i]) > k.
      for (int i = 0; i < count.size(); ++i) {
        seen += count[i];
        if (seen - 1 >= k) {
          assert(i == findKthBinarySearch(k)); // Sanity check to make sure both are correct :)
          return i;
        }
      }
      assert(false); // No kth element found.
    }

    int findKthBinarySearch(int k) {
      int low = 0, high = MAX;
      while (low < high) {
        int mid = (low + high) / 2;
        int sum = accumulate(count.begin(), count.begin() + mid + 1, 0); // This part is O(n) but could be O(log n) with a Fenwick tree.
        // sum is count[0] + ... + count[mid]
        if (sum > k) {
          // Mid is a valid option, but there might be a smaller one as well.
          high = mid;
        } else {
          // Mid is not a valid option. If there is one, it must be larger than mid.
          low = mid + 1;
        }
      }
      assert(low == high);
      return low;
    }

    double findMedian() {
      // n=1, median=0
      // n=2, median=0,1
      // n=3, median=1
      // n=4, median=1,2
      int n = accumulate(count.begin(), count.end(), 0);
      int left = (n - 1) / 2;
      int right = n / 2;
      return 0.5 * (findKth(left) + findKth(right));
    }

    vector<int> count;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */


#ifdef LOCAL

void check(double got, double want) {
  cout << (got == want ? "PASS" : "FAIL") << ": got " << got << " want " << want << endl;
}


int main() {
  {
    MedianFinder mf;
    mf.addNum(1);
    mf.addNum(2);
    check(mf.findKth(0), 1);
    check(mf.findKth(1), 2);
    check(mf.findMedian(), 1.5);
    mf.addNum(3);
    check(mf.findKth(2), 3);
    check(mf.findMedian(), 2);
    mf.addNum(2);
    mf.addNum(100);
    check(mf.findKth(0), 1);
    check(mf.findKth(1), 2);
    check(mf.findKth(2), 2);
    check(mf.findKth(3), 3);
    check(mf.findKth(4), 100);
  }

  {
    MedianFinder mf;
    mf.addNum(1);
    check(mf.findMedian(), 1);
    mf.addNum(1);
    check(mf.findMedian(), 1);
    mf.addNum(1);
    check(mf.findMedian(), 1);
    mf.addNum(2);
    check(mf.findMedian(), 1);
    mf.addNum(2);
    check(mf.findMedian(), 1);
    mf.addNum(2);
    check(mf.findMedian(), 1.5);
    mf.addNum(2);
    check(mf.findMedian(), 2);
  }

  return 0;
}
#endif