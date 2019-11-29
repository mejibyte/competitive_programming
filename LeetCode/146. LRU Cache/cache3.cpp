// 2019-11-28

typedef int Key;
typedef int Value;

class LRUCache {
public:
    LRUCache(int capacity) {
        limit = capacity;
    }

    int get(int key) {
        if (v.count(key) == 0) return -1;
        touch(key);
        return v[key];
    }

    void put(int key, int value) {
        if (v.count(key) > 0) {
            // Touch and update value
            touch(key);
            v[key] = value;
        } else {
            // Evict
            while (q.size() > 0 and q.size() >= limit) {
                v.erase(*q.begin());
                p.erase(*q.begin());
                q.erase(q.begin());
            }

            // Insert
            p[key] = q.insert(q.end(), key);
            v[key] = value;
        }
    }

    // Bring key all the way to the back of the queue.
    void touch(int key) {
        assert(p.count(key) > 0);
        q.erase(p[key]);
        p[key] = q.insert(q.end(), key);
    }

private:

    int limit;
    map<Key, Value> v; // actual value
    map<Key, list<Key>::iterator> p; // pointer in list
    list<Key> q; // most recently used keys. q.begin() is the oldest key.

};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */