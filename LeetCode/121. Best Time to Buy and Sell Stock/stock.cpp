class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int best = 0, sell = 0;
        for (int i = prices.size() - 1; i >= 0; --i) {
            best = max(best, sell - prices[i]);
            sell = max(sell, prices[i]);
        }
        return best;
    }
};
