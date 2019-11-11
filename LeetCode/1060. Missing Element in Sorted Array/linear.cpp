class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
        nums.push_back(numeric_limits<int>::max());
        for (int i = 1; i < nums.size(); ++i) {
            int missing = nums[i] - nums[i-1] - 1;
            if (missing == 0) continue;

            if (missing < k) {
                k -= missing;
                continue;
            }
            return nums[i-1] + k;
        }
        assert(false);
    }
};
