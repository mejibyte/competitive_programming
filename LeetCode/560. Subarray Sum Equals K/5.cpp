class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> seen;
        int sum = 0, answer = 0;
        for (int j = 0; j < nums.size(); ++j) {
            seen[sum]++;
            sum += nums[j];
            answer += seen[sum - k];
        }
        return answer;
    }
};
