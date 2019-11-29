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

// https://leetcode.com/problems/lfu-cache/

// Idea:
// #1) Keep "value" = map<Key, Value>, a map with actual cached values for each key.
// #2) Keep "buckets" = doubly-linked list of buckets, a list of all buckets that we'll keep sorted by ascending frequency.
// Each bucket has:
//    - frequency: how many times the keys in this bucket have been used
//    - list<key>: list of keys that have been accessed "frequency" times, sorted from oldest to newest to resolve ties.
// #3) Keep "location" = map<Key, pointer to bucket list> so we can quickly find the bucket that a key belongs to.

// On access (get/put):
//    - Use pointer to find old bucket for this key
//    - Delete key from old bucket
//    - If necessary, insert new bucket right after old bucket with frequency + 1
//    - Insert key at the end of new bucket
//    - Update "location" to point key to new bucket and location
//    - If old bucket is empty, delete old bucket

// On expire (put):
//    - Delete oldest key from first bucket in "buckets"
//    - Delete this key from "location" and "value"
//    - Delete first bucket if it becomes empty

typedef int Key;
typedef int Value;

class LFUCache {
  // A bucket contains all keys that have been accessed with the same frequency.
  // It supports adding and erasing keys in O(1) and also keeps the original order
  // in which keys were inserted. (This is similar to LinkedHashSet in Java).
  class Bucket {
   public:
    Bucket(int freq) : freq(freq) {}

    // Adds a new key.
    // O(1)
    void add(Key key) {
      location[key] = keys.insert(keys.end(), key);
    }

    // Erases an existing key.
    // O(1)
    void erase(Key key) {
      assert(location.count(key) > 0);
      keys.erase(location[key]);
      location.erase(key);
    }

    bool empty() const {
      return keys.size() == 0;
    }

    int freq; // frequency of all keys in this bucket.
    list<Key> keys; // order in which keys were originally inserted.

    unordered_map<Key, list<Key>::iterator> location; // allows quickly finding where keys are in the list to erase them.
  };

public:
    LFUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
      if (value.count(key) == 0) {
        return -1;
      }
      bump(key);
      return value[key];
    }

    void put(int key, int newValue) {
      if (capacity == 0) return;

      if (value.count(key) == 0) {
        // We'll have to create a new entry.
        // Expire least used if we are at full capacity. In case of ties, expire oldest.
        while (value.size() >= capacity) {
          assert(!buckets.empty() and !buckets.front().empty());
          Key expiredKey = buckets.front().keys.front();

          // Delete expired key from its current bucket.
          buckets.front().erase(expiredKey);
          if (buckets.front().empty()) {
            // Bucket is now empty, delete it.
            buckets.pop_front();
          }

          // Delete everything else we know about this key.
          value.erase(expiredKey);
          location.erase(expiredKey);
        }
        assert(value.size() < capacity);

        // Insert new key into new empty bucket.
        location[key] = buckets.insert(buckets.begin(), Bucket(0));
        location[key]->add(key);
      }
      value[key] = newValue;
      bump(key);
    }

    // bump moves key from its current bucket to the next bucket with frequency = originalFrequency + 1.
    // If there is no bucket with originalFrequency + 1, it will be created.
    // If the old bucket becomes empty, it will be deleted.
    // After a call to bump, it is guaranteed that 'buckets' contains non-empty buckets sorted by ascending frequency.
    void bump(int key) {
      assert(location.count(key) > 0);
      auto oldBucket = location[key];

      // Find new bucket. If necessary, create a new bucket.
      if (next(oldBucket) == buckets.end() or next(oldBucket)->freq > oldBucket->freq + 1) {
        buckets.insert(next(oldBucket), Bucket(oldBucket->freq + 1));
      }

      // Add key to new bucket and update location.
      auto newBucket = next(oldBucket);
      assert(newBucket->freq == oldBucket->freq + 1);
      newBucket->add(key);
      location[key] = newBucket;

      // Erase key from old bucket. If bucket becomes empty, delete bucket.
      oldBucket->erase(key);
      if (oldBucket->empty()) {
        buckets.erase(oldBucket);
      }
    }

    int capacity;
    unordered_map<Key, Value> value;
    list<Bucket> buckets;
    unordered_map<Key, list<Bucket>::iterator> location;
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

// Compile with -DLOCAL to run this locally but not on LeetCode. Example:
// clang++ code.cpp -DLOCAL -std=c++17
#ifdef LOCAL
int main() {
  LFUCache cache( 2 /* capacity */ );

  cache.put(1, 1);
  cache.put(2, 2);
  assert(cache.get(1) == 1);       // returns 1
  cache.put(3, 3);    // evicts key 2
  assert(cache.get(2) == -1);       // returns -1 (not found)
  assert(cache.get(3) == 3);       // returns 3.
  cache.put(4, 4);    // evicts key 1.
  assert(cache.get(1) == -1);       // returns -1 (not found)
  assert(cache.get(3) == 3);       // returns 3
  assert(cache.get(4) == 4);       // returns 4
  return 0;
}
#endif