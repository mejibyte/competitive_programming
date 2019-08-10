class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        unordered_map<char, int> seen;
        int i = 0, n = s.size();
        int best = 0;
        for (int j = 0; j < n; ++j) {
            seen[s[j]]++;
            while (seen.size() > k && i <= j) {
                seen[s[i]]--;
                if (seen[s[i]] == 0) {
                    seen.erase(s[i]);
                }
                i++;
            }
            best = max(best, j - i + 1);
        }
        return best;
    }
};
