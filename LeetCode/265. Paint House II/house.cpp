const int oo = INT_MAX / 2;
class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        int n = costs.size();
        if (n == 0) return 0;
        int k = costs[0].size();
        assert(n == 1 || k >= 2);
        if (k == 1) {
            assert(n == 1);
            return costs[0][0];
        }

        // dp[i][c] = min cost of painting houses [i, n) assuming house i was painted with color c.
        // dp[i][c] = min(
        //     cost[i][c] + min(dp[i+1][q]) for all q != c
        // )
        vector<vector<int>> dp(n + 1, vector<int>(k, oo));
        for (int c = 0; c < k; ++c) {
            dp[n][c] = 0;
        }
        for (int i = n-1; i >= 0; --i) {
            vector<int> left(k, oo), right(k, oo);
            // left[c] = min(dp[i+1][q]) for 0 <= q < c
            // right[c] = min(dp[i+1][q]) for c < q <= k-1
            for (int c = 1; c < k; ++c) {
                left[c] = min(dp[i+1][c-1], left[c-1]);
            }
            for (int c = k-2; c >= 0; --c) {
                right[c] = min(dp[i+1][c+1], right[c+1]);
            }

            for (int c = 0; c < k; ++c) {
                int here = costs[i][c] + min(left[c], right[c]);
                dp[i][c] = min(dp[i][c], here);
            }
        }
        int ans = oo;
        for (int c = 0; c < k; ++c) {
            ans = min(ans, dp[0][c]);
        }
        return ans;
    }
};
