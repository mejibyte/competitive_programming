class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int best = 0, i = 0, n = s.size();
        map<char, int> seen;
        for (int j = 0; j < n; ++j) {
            // Add s[j]
            while (seen[s[j]] > 0 && i < j) {
                seen[s[i++]]--;
            }
            seen[s[j]]++;
            best = max(best, j - i + 1);
        }
        return best;
    }
};
