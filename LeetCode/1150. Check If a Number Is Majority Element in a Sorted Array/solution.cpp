class Solution {
public:
    bool isMajorityElement(vector<int>& nums, int target) {
        int count = upper_bound(nums.begin(), nums.end(), target) - lower_bound(nums.begin(), nums.end(), target);
        return 2 * count > nums.size();
    }
};