class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(4, INT_MIN / 2)), choice(n + 1, vector<int>(4, INT_MAX / 2));

        // dp[i][r] = max{
        //     dp[i+1][r]
        //     dp[i+k][r-1] + sum[i..i+k-1]
        // }

        vector<int> sum(nums);
        for (int i = 1; i < n; ++i) sum[i] += sum[i-1];

        dp[n][0] = 0;
        for (int r = 0; r <= 3; ++r) {
            for (int i = n - 1; i >= 0; --i) {
                dp[i][r] = dp[i+1][r];
                choice[i][r] = choice[i+1][r];

                if (i+k <= n and r-1 >= 0) {
                    int maybe = dp[i+k][r-1] + sum[i+k-1] - (i-1 >= 0 ? sum[i-1] : 0);
                    if (maybe >= dp[i][r]) {
                        dp[i][r] = maybe;
                        choice[i][r] = i;
                    }
                }
            }
        }

        vector<int> ans;
        int i = 0;
        for (int r = 3; r > 0; --r) {
          ans.push_back(choice[i][r]);
          i = choice[i][r] + k;
        }
        return ans;
    }
};
