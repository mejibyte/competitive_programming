class RandomizedSet {
    vector<int> data;
    unordered_map<int, int> index;

public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        srand(2017);
        data.clear();
        index.clear();
    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (index.count(val)) return false;
        index[val] = data.size();
        data.push_back(val);
        return true;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (index.count(val) == 0) return false;
        int k = index[val];
        swap(data[k], data.back());
        data.pop_back();
        index[data[k]] = k;
        index.erase(val);
        return true;
    }

    /** Get a random element from the set. */
    int getRandom() {
        assert(data.size() > 0);
        return data[rand() % data.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
