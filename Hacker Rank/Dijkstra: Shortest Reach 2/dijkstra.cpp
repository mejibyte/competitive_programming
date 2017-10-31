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

template <class T>
class MinHeap {
 public:
  // Adds a new item to the heap.
  void add(const T& t);
  // Returns (and removes) the smallest item from the heap. If heap is empty, crashes.
  T pop();
  // Returns the current size.
  int size() { return heap.size(); };

  vector<T> heap;
 private:
  int parent(int i) { return (i - 1) / 2; }
  int left(int i) { return 2 * i + 1; }
  int right(int i) { return 2 * i + 2; }
  void push_down(int i);
};


template <class T>
void MinHeap<T>::add(const T& t) {
  heap.push_back(t);
  int me = heap.size() - 1;
  while (me > 0 && heap[me] < heap[parent(me)]) {
    swap(heap[me], heap[parent(me)]);
    me = parent(me);
  }
}

template <class T>
T MinHeap<T>::pop() {
  T top = heap.at(0);
  swap(heap[0], heap[size() - 1]);
  heap.pop_back();
  // Now push the new element down.
  push_down(0);
  return top;
}


template <class T>
void MinHeap<T>::push_down(int me) {
  if (left(me) >= size()) return; // No children. We're done.

  int smallest_child = left(me);
  if (right(me) < size() and heap[right(me)] < heap[smallest_child]) {
    smallest_child = right(me);
  }

  if (heap[smallest_child] < heap[me]) {
    swap(heap[me], heap[smallest_child]);
    push_down(smallest_child);
  }
}


struct Edge {
  int to;
  long long weight;

  Edge(int to, long long weight) : to(to), weight(weight) {}
};

bool operator < (const Edge &a, const Edge &b) {
  if (a.weight != b.weight) return a.weight < b.weight;
  return a.to < b.to;
}

const int MAXN = 3005;
const long long oo = LLONG_MAX / 2; // Avoid overflow.
vector<Edge> g[MAXN];
long long d[MAXN];


int main(){
  int t;
  cin >> t;
  for(int a0 = 0; a0 < t; a0++){
      int n;
      int m;
      cin >> n >> m;

      for (int i = 0; i < n; ++i) {
        g[i].clear();
        d[i] = oo;
      }
      for(int a1 = 0; a1 < m; a1++){
          int x;
          int y;
          int r;
          cin >> x >> y >> r;
          x--, y--;

          g[x].push_back(Edge(y, r));
          g[y].push_back(Edge(x, r));
      }
      int start;
      cin >> start;
      start--;

      MinHeap<Edge> q;
      q.add(Edge(start, 0));
      d[start] = 0;

      while (q.size() > 0) {
        Edge at = q.pop();

        if (at.weight > d[at.to]) continue; // We've seen better already.
        for (const Edge &out : g[at.to]) {
          Edge maybe(out.to, d[at.to] + out.weight);

          if (maybe.weight < d[maybe.to]) {
            d[maybe.to] = maybe.weight;
            q.add(maybe);
          }
        }
      }

      for (int i = 0, first = true; i < n; i++) {
        if (i != start) {
          if (!first) cout << " ";
          cout << (d[i] < oo ? d[i] : -1);
          first = false;
        }
      }
      cout << endl;

  }
  return 0;
}
