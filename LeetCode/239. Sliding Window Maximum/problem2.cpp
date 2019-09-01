// Andrés Mejía - andr@esmejia.com
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


struct MaxQueue {
  void pushBack(int x) {
    // Since this is a FIFO queue, x will outlive any other element already inserted.
    // Therefore, any element smaller than x will never have a chance to be the max,
    // so we might as well remove them now.
    while (q.size() > 0 and x > q.back().second) {
      q.pop_back();
    }
    q.push_back(make_pair(tail++, x));
  }

  void popFront() {
    assert(q.size() > 0);
    if (head == q.front().first) {
      q.pop_front();
    }
    head++;
  }

  int getMax() {
    assert(q.size() > 0);
    return q.front().second;
  }

  int size() {
    return tail - head;
  }

 private:
  int head = 0, tail = 0;
  // q holds elements sorted by non-ascending values.
  deque<pair<int, int>> q; // <time, value>
};

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
      MaxQueue q;
      vector<int> answer;
      for (int i = 0; i < nums.size(); ++i) {
        q.pushBack(nums[i]);
        while (q.size() > k) {
          q.popFront();
        }
        if (q.size() >= k) {
          answer.push_back(q.getMax());
        }
      }
      return answer;
    }
};


int main(){
  vector<int> v = {1,3,-1,-3,5,3,6,7};
  int k = 3;

  Solution s;
  vector<int> ans = s.maxSlidingWindow(v, k);
  for (auto x : ans) {
    cout << x << " ";
  }
  cout << endl;

  return 0;
}
