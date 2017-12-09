class RandomizedCollection {
    vector<int> data;
    unordered_map<int, unordered_set<int>> index;

public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        data.clear();
        index.clear();
    }

    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        index[val].insert(data.size());
        data.push_back(val);
        return index[val].size() == 1;
    }

    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if (index[val].size() == 0) return false;

        int k = *index[val].begin();
        assert(data[k] == val);
        swap(data[k], data.back());

        index[val].erase(k);
        index[data[k]].insert(k);
        index[data[k]].erase(data.size() - 1);
        data.pop_back();
        return true;
    }

    /** Get a random element from the collection. */
    int getRandom() {
        assert(data.size() > 0);
        return data[rand() % data.size()];
    }
};


/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
