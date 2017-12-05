struct Item {
    int value, list;
};

bool operator < (const Item& a, const Item& b) {
    return a.value < b.value;
}

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        vector<Item> items;
        for (int k = 0; k < nums.size(); ++k) {
            for (int x : nums[k]) {
                items.push_back({x, k});
            }
        }
        sort(items.begin(), items.end());
        map<int, int> seen;
        int best = items.back().value - items.front().value;
        int at = items.front().value;

        int i = 0;
        for (int j = 0; j < items.size(); ++j) {
            seen[items[j].list]++;
            while (seen.size() >= nums.size() and i <= j) {
                int length = items[j].value - items[i].value;
                if (length < best) {
                    best = length;
                    at = items[i].value;
                }
                if (--seen[items[i].list] == 0) {
                    seen.erase(items[i].list);
                }
                i++;
            }
        }
        return {at, at + best};
    }
};
