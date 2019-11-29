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
    /** initialize your data structure here. */
    MedianFinder() {

    }

    void addNum(int num) {
      if (left.empty() or num <= left.top()) {
        left.push(num);
      } else {
        right.push(num);
      }

      // Rebalance until either left.size() == right.size() or left.size() == right.size() + 1
      while (left.size() - 1 > right.size()) {
        right.push(left.top());
        left.pop();
      }

      while (right.size() > left.size()) {
        left.push(right.top());
        right.pop();
      }

      assert(left.size() == right.size() or left.size() - 1 == right.size());
    }

    double findMedian() {
      int n = left.size() + right.size();
      assert(n > 0);
      if (n % 2 == 0) {
        assert(left.size() == right.size());
        return 0.5 * (left.top() + right.top());
      } else {
        return left.top();
      }
    }

    priority_queue<int> left; // max heap
    priority_queue<int, vector<int>, greater<int>> right; // min heap
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
    check(mf.findMedian(), 1.5);
    mf.addNum(3);
    check(mf.findMedian(), 2);
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