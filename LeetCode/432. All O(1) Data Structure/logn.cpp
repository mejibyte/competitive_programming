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
#include <unordered_set>
#include <unordered_map>
using namespace std;

typedef string Key;
typedef int Value;

class AllOne {
public:
    /** Initialize your data structure here. */
    AllOne() {

    }

    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    // O(log n)
    void inc(string key) {
      int oldFreq = freq.count(key) > 0 ? freq[key] : 0;
      if (freq.count(key) > 0) {
        // Erase old one
        erase(key);
      }
      // Insert new one
      insert(key, oldFreq + 1); // O(log n)
    }


    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    // O(log n)
    void dec(string key) {
      int oldFreq = freq.count(key) > 0 ? freq[key] : 0;
      if (freq.count(key) > 0) {
        // Erase old one
        erase(key);
      }
      if (oldFreq - 1 >= 1) {
        // Insert new one
        insert(key, oldFreq - 1); // O(log n)
      }
    }

    // Precondition: key has been inserted before.
    void erase(const string& key) {
        assert(freq.count(key) > 0 and freq[key] >= 1);
        int f = freq[key];
        freq.erase(key);
        assert(keys.count(f) > 0 and keys[f].count(key) > 0);
        keys[f].erase(key);
        if (keys[f].size() == 0) {
          keys.erase(f);
        }
    }

    // O(log n)
    void insert(const string& key, int value) {
      freq[key] = value; // O(1)
      keys[value].insert(key); // O(log n) because keys is a TreeMap.
    }

    /** Returns one of the keys with maximal value. */
    // O(log n)
    string getMaxKey() {
      if (keys.size() > 0) {
        auto p = --keys.end();
        assert(p->second.size() > 0);
        return *p->second.begin();
      }
      return "";
    }

    /** Returns one of the keys with Minimal value. */
    // O(log n)
    string getMinKey() {
      if (keys.size() > 0) {
        auto p = keys.begin();
        assert(p->second.size() > 0);
        return *p->second.begin();
      }
      return "";
    }

    unordered_map<Key, Value> freq;
    map<Value, unordered_set<Key>> keys;
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */

#ifdef LOCAL
void check(string want, string got) {
  cout << (want == got ? "PASS" : "FAIL") << ": got " << got << " want " << want << endl;
}

void case1() {
  AllOne ds;
  ds.inc("a");

  check("a", ds.getMaxKey());
  check("a", ds.getMinKey());

  ds.inc("b");
  ds.inc("a");

  check("a", ds.getMaxKey());
  check("b", ds.getMinKey());

  ds.inc("c");

  check("c", ds.getMinKey());
  check("a", ds.getMaxKey());

  ds.inc("c");
  ds.inc("c");

  check("b", ds.getMinKey());
  check("c", ds.getMaxKey());

  ds.inc("c");
  ds.inc("c");
  ds.inc("c");
  ds.inc("c");
  check("c", ds.getMaxKey());
  ds.dec("c");
}

void case2() {
  AllOne ds;
  ds.inc("a");
  ds.dec("a");
  ds.inc("a");
  ds.inc("a");
  ds.inc("a");
  ds.inc("b");
  ds.dec("a");
  ds.dec("a");
  ds.dec("a");
  check("b", ds.getMinKey());
  check("b", ds.getMaxKey());
  ds.inc("a");
  ds.inc("a");
  ds.inc("a");
  ds.inc("a");
  ds.inc("a");
  ds.inc("a");
  ds.inc("b");
  ds.inc("c");
  ds.inc("c");
  ds.inc("c");
}

void case3() {
  AllOne ds;
  ds.inc("hello");
  ds.inc("hello");
  ds.inc("world");
  ds.inc("world");
  ds.inc("hello");
  ds.dec("world");
  ds.getMaxKey();
  ds.getMinKey();
  ds.inc("world");
  ds.inc("world");
  ds.inc("leet");
  ds.getMaxKey();
  ds.getMinKey();
  ds.inc("leet");
  ds.inc("leet");
  ds.getMinKey();
}

int main() {
  //case1();
  case2();
  //case3();

  return 0;
}
#endif