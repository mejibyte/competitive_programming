// Everything O(1)
// Follow up: how to write this more elegantly? Still lots of corner cases.
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
        // Just insert at the beginning and carry on.
        insertInc(buckets.begin(), key, 1);
      } else {
        // Insert at next one, and delete from previous.
        insertInc(next(bucket[key]), key, bucket[key]->value + 1);

        // Delete from previous bucket.
        assert(bucket[key] != buckets.begin());
        erase(prev(bucket[key]), key);
      }
    }

    void insertInc(list<Bucket>::iterator at, const string& key, int f) {
        if (at == buckets.end() or at->value != f) {
          at = buckets.insert(at, Bucket(f));
        }
        at->keys.insert(key);
        bucket[key] = at;
    }

    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
      if (bucket.count(key) == 0) return; // nothing to do

      if (bucket[key]->value == 1) {
        // Just delete from existing bucket.
        erase(bucket[key], key);
        // Delete from main data structure.
        bucket.erase(key);
      } else {
        // Insert into previous one, then delete from existing one.
        if (bucket[key] == buckets.begin() or prev(bucket[key])->value != bucket[key]->value - 1) {
          // Make sure previous bucket exists.
          buckets.insert(bucket[key], Bucket(bucket[key]->value - 1));
        }
        assert(bucket[key] != buckets.begin() and prev(bucket[key])->value == bucket[key]->value - 1);
        auto at = prev(bucket[key]);
        at->keys.insert(key);

        // Delete from current one.
        erase(bucket[key], key);

        // Update main data structure.
        bucket[key] = at;
      }
    }

    void erase(list<Bucket>::iterator b, const string& key) {
      assert(b->keys.count(key) > 0);
      b->keys.erase(key);
      if (b->keys.size() == 0) {
        buckets.erase(b);
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
  //case3();

  return 0;
}
#endif