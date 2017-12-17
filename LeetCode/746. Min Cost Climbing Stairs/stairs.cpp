class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        if (cost.size() == 0) return 0;
        if (cost.size() == 1) return cost[0];
        if (cost.size() == 2) return min(cost[0], cost[1]);

        int n = cost.size();
        vector<int> dp(n + 1);
        dp[n] = 0;
        for (int i = n - 1; i >= 0; --i) {
            dp[i] = cost[i] + dp[i + 1];
            if (i + 2 <= n) {
                dp[i] = min(dp[i], cost[i] + dp[i + 2]);
            }
        }
        return min(dp[0], dp[1]);
    }
};
