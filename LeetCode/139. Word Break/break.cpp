class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        sort(wordDict.begin(), wordDict.end());
        int n = s.size();
        vector<bool> dp(n + 1, false);
        dp[n] = true;
        for (int i = n - 1; i >= 0; --i) {
          for (const string &w : wordDict) {
              if (s.find(w, i) == i) {
                  dp[i] = dp[i] || dp[i + w.size()];
              }
          }
        }
        return dp[0];
    }
};
