class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> count;
        for (auto x : nums) {
          if (++count[x] > nums.size() / 2) {
            return x;
          }
        }
        assert(false);
    }
};