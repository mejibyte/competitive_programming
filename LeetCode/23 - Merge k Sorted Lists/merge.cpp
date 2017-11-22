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

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

// left: 2*i + 1
// right: 2*i + 2
// parent: (i - 1)/2
//
//    0
//  1   2
// 3 4 5 6
template <class T>
class MinHeap {
  public:
    int size() { return data.size(); }
    T pop_min();
    void add(const T& t);

  private:
    vector<T> data;
};

template <class T>
void MinHeap<T>::add(const T& t) {
  data.emplace_back(t);
  int at = size() - 1;
  while (at > 0 and data[at] < data[(at - 1) / 2]) {
    swap(data[at], data[(at - 1) / 2]);
    at = (at - 1) / 2;
  }
}


template <class T>
T MinHeap<T>::pop_min() {
  assert(size() > 0);
  T min = data[0];

  swap(data[0], data[size() - 1]);
  data.resize(size() - 1);
  // Now push it down.
  int at = 0;
  while (true) {
    if (2*at + 1 >= size()) break; // no children

    int next = -1;
    if (2*at + 2 < size() and data[at] > data[2*at + 2]) {
      next = 2*at + 2;
    }

    if (2*at + 1 < size() and data[at] > data[2*at + 1] and
        (next == -1 or data[2*at + 1] < data[next])) {
      next = 2*at + 1;
    }
    if (next == -1) break; // already in right place.
    swap(data[at], data[next]);
    at = next;
  }
  return min;
}


class Solution {
public:
    ListNode* mergeKLists(const vector<ListNode*>& lists) {
      if (lists.size() == 0) return nullptr;
      assert(lists.size() > 0);
      MinHeap< pair<int, ListNode*> > heap;
      for (ListNode* head : lists) {
        if (head == nullptr) continue;
        heap.add(make_pair(head->val, head));
      }

      ListNode* head = nullptr;
      ListNode *tail = nullptr;
      while (heap.size() > 0) {
        ListNode* popped = heap.pop_min().second;
        if (head == nullptr) head = popped;
        if (tail != nullptr) {
          tail->next = popped;
        }
        tail = popped;

        if (popped->next != nullptr) {
          ListNode* add = popped->next;
          heap.add(make_pair(add->val, add));
        }
      }
      return head;
    }
};



int main(){
    Solution s;

    ListNode a(2), b(1), c(3), d(10);
    a.next = &d;

    auto m = s.mergeKLists({&a, &b, &c});
    while (m != nullptr) {
      D(m->val);
      m = m->next;
    }
    return 0;
}
