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
    void inc(string key) {
      int oldFreq = 0;
      if (bucket.count(key) > 0) {
        // Delete old version.
        oldFreq = bucket[key]->value;
        erase(key);
      }
    }


    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    // O(log n)
    void dec(string key) {

    }

    // Precondition: key has been inserted before.
    void erase(const string& key) {
      assert(bucket.count(key) > 0);
      bucket[key]->keys.erase(key);
      if (bucket[key]->keys.size() == 0) {
        buckets.erase(bucket[key]);
      }
    }

    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
      if (buckets.size() > 0) return *buckets.rbegin()->keys.begin();
      return "";
    }

    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
      if (buckets.size() > 0) return *buckets.begin()->keys.begin();
      return "";
    }

    struct Bucket {
      int value;
      unordered_set<string> keys;
    };

    list<Bucket> buckets;
    unordered_map<Key, list<Bucket>::iterator> bucket;
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