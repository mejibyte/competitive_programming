// https://leetcode.com/problems/lfu-cache/

// Idea:
// #1) Keep map<Key, Value> "value" with values.
// #2) Keep linked list "buckets" of buckets sorted by ascending number of frequency
// Each bucket has:
//    - frequency: how many times the keys in this bucket have been used
//    - list<key>: list of keys that have been accessed "frequency" times, sorted from oldest to newest for ties.
// #3) Keep a map<Key, BucketPointer> "pointer" where BucketPointer contains two things:
//    - pointer to bucket in "buckets"
//    - pointer to location in list<Key> inside this bucket

// On access:
//    - Use pointer to find old bucket
//    - Delete key from old bucket
//    - If necessary, insert new bucket right after old bucket with frequency + 1
//    - Insert key at the end of new bucket
//    - Update "pointer" to point key to new bucket and location
//    - If old bucket is empty, delete old bucket

// On expire:
//    - Delete oldest key from first bucket in "buckets"
//    - Delete this key from "pointer" and "value"
//    - Delete first bucket if it becomes empty
