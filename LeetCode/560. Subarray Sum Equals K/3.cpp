// O(n)
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) return 0;
        vector<int> sum(n);
        for (int i = 0; i < n; ++i) {
            sum[i] = nums[i];
            if (i - 1 >= 0) {
                sum[i] += sum[i - 1];
            }
        }

        unordered_map<int, int> seen;
        int answer = 0;
        for (int i = n - 1; i >= 0; --i) {
            seen[sum[i]]++;

            int need = k;
            if (i - 1 >= 0) {
                need += sum[i - 1];
            }

            answer += seen[need];
        }
        return answer;
    }

};
