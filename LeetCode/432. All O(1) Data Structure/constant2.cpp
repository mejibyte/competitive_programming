// Everything O(1)
// A slightly cleaner version of constant.cpp
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
  struct Bucket {
    int value;
    unordered_set<string> keys;

    Bucket(int value) : value(value) {}
  };

public:
    /** Initialize your data structure here. */
    AllOne() {

    }

    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
      if (bucket.count(key) == 0) {
        bucket[key] = buckets.insert(buckets.begin(), Bucket(0));
      }
      auto oldBucket = bucket[key];
      assert(oldBucket != buckets.end());
      // Create empty new bucket if necessary.
      if (next(oldBucket) == buckets.end() or next(oldBucket)->value > oldBucket->value + 1) {
          buckets.insert(next(oldBucket), Bucket(oldBucket->value + 1));
      }

      // Insert into new bucket, which is guaranteed to exist.
      auto newBucket = next(oldBucket);
      assert(newBucket->value == oldBucket->value + 1);
      newBucket->keys.insert(key);
      bucket[key] = newBucket;

      // Erase from old bucket.
      oldBucket->keys.erase(key);
      if (oldBucket->keys.empty()) {
        buckets.erase(oldBucket);
      }
    }


    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
      if (bucket.count(key) == 0) return; // nothing to do.

      auto oldBucket = bucket[key];
      assert(oldBucket != buckets.end());
      bucket.erase(key); // Will assign new bucket below, if needed.
      if (oldBucket->value - 1 >= 1) {
        // Create new bucket if needed.
        if (oldBucket == buckets.begin() or prev(oldBucket)->value < oldBucket->value - 1) {
          buckets.insert(oldBucket, Bucket(oldBucket->value - 1));
        }

        // Insert into new bucket, which is guaranteed to exist.
        assert(oldBucket != buckets.begin());
        auto newBucket = prev(oldBucket);
        assert(newBucket->value == oldBucket->value - 1);
        newBucket->keys.insert(key);
        bucket[key] = newBucket;
      }

      // Erase from old bucket.
      oldBucket->keys.erase(key);
      if (oldBucket->keys.empty()) {
        buckets.erase(oldBucket);
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
  case1();
  case2();
  case3();

  return 0;
}
#endif