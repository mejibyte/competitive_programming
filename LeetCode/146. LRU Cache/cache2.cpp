// Andrés Mejía
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

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cerr << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

struct Item {
  int value;
  list<int>::iterator p;
};

class LRUCache {
public:
    int capacity;
    unordered_map<int, Item> cache;
    list<int> queue; // All keys in the cache in the order in which they will be evicted.

    LRUCache(int capacity) : capacity(capacity) {
      assert(capacity >= 1);
    }

    int get(int key) {
      if (cache.count(key) > 0) {
        refresh_time(key);
        return cache[key].value;
      }
      return -1;
    }

    void put(int key, int new_value) {
      if (cache.count(key) > 0) {
        cache[key].value = new_value;
        refresh_time(key);
      } else {
        if (cache.size() >= capacity) {
          evict();
        }
        list<int>::iterator p = queue.insert(queue.end(), key);
        cache[key] = {new_value, p};
      }
      assert(cache.size() <= capacity);
    }

private:
  void evict() {
    int key = queue.front();
    queue.pop_front();
    cache.erase(key);
  }

  void refresh_time(int key) {
    queue.erase(cache[key].p);
    cache[key].p = queue.insert(queue.end(), key);
  }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

int main() {
  LRUCache cache( 2 /* capacity */ );

  cache.put(1, 1);
  cache.put(2, 2);
  D(cache.get(1));       // returns 1
  cache.put(3, 3);    // evicts key 2
  D(cache.get(2));       // returns -1 (not found)
  cache.put(4, 4);    // evicts key 1
  D(cache.get(1));       // returns -1 (not found)
  D(cache.get(3));       // returns 3
  D(cache.get(4));       // returns 4
  return 0;
}


