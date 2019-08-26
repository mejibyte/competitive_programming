// A standard <key, value> map that also supports
// getting the min value inside the map in O(log n).
struct MinMap {
    // Sets or overwrites the value for the given key.
    void set(int key, int value) {
        if (m.count(key) > 0) {
            erase(key);
        }
        m[key] = value;
        values.insert(value);
    }

    // Erases the entry for the given key.
    void erase(int key) {
        assert(m.count(key) > 0);
        values.erase(values.find(m[key]));
        m.erase(m.find(key));
    }

    // Returns the smallest value inside the map.
    int minValue() {
        assert(values.size() > 0);
        return *values.begin();
    }

    int size() {
        assert(m.size() == values.size());
        return values.size();
    }

    unordered_map<int, int> m;
    multiset<int> values;
};

class Solution {
public:
    int subarraysWithKDistinct(vector<int>& a, int k) {
        int answer = 0, n = a.size();
        int i = 0; // Left pointer
        MinMap m;
        for (int j = 0; j < n; ++j) {  // Right pointer
            // We are going to count how many subarrays ending in j
            // have exactly k different elements, and add that to the answer.

            // Insert new element from the right. The value is just the index.
            // If a[j] had already been seen with a previous index, it will
            // be overwritten.
            m.set(a[j], j);

            while (m.size() > k) {
                // We have too many elements. Start moving left pointer until
                // we delete enough characters. The map gives us the index of
                // the first character we need to delete to end up with one less
                // unique element.
                // In practice, we will enter this loop at most once.
                int next = m.minValue();
                m.erase(a[next]);
                i = next + 1;
            }

            if (m.size() == k) {
                // We found one or more solutions. At this point, we could keep
                // moving the left pointer until we "lose" one element (similar
                // to what we did above when we had > k elements), so we just
                // find out how far we could go before "breaking" the solution,
                // and all of those to the answer.
                int next = m.minValue();
                assert(next >= i);
                answer += next - i + 1;
            }
        }
        return answer;
    }
};


