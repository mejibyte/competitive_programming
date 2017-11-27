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

class LRUCache {
public:
    int capacity;
    int next_time;

    unordered_map<int, int> key_to_value;
    unordered_map<int, int> key_to_time;
    map<int, int> time_to_key;

    LRUCache(int capacity) : capacity(capacity), next_time(1) {
      assert(capacity >= 1);
    }

    int get(int key) {
      if (key_to_value.count(key) > 0) {
        refresh_time(key);
        return key_to_value[key];
      }
      return -1;
    }

    void put(int key, int new_value) {
      if (key_to_value.count(key) > 0) {
        key_to_value[key] = new_value;
        refresh_time(key);
      } else {
        if (key_to_value.size() >= capacity) {
          erase(oldest_key());
        }
        key_to_value[key] = new_value;
        refresh_time(key);
      }
    }

private:
  int oldest_key() {
    return time_to_key.begin()->second;
  }

  void erase(int key) {
    int old_time = key_to_time[key];
    time_to_key.erase(old_time);
    key_to_time.erase(key);
    key_to_value.erase(key);
  }

  void refresh_time(int key) {
    int old_time = key_to_time[key];
    time_to_key.erase(old_time);

    int new_time = next_time++;
    time_to_key[new_time] = key;
    key_to_time[key] = new_time;
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


