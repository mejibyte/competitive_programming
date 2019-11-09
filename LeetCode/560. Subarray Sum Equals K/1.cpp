// O(n^2)
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        int answer = 0;
        for (int i = 0; i < n; ++i) {
            int sum = 0;
            for (int j = i; j < n; ++j) {
                sum += nums[j];
                if (sum == k) {
                    answer++;
                }
            }
        }
        return answer;
    }
};
