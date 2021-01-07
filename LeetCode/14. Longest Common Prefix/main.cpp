class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.size() == 0) return "";
        string best = strs[0];
        for (int i = 1; i < strs.size(); i++) {
            string s = strs[i];
            int match = 0;
            while (match < best.size() and match < s.size() and best[match] == s[match]) {
                match++;
            }
            best = best.substr(0, match);
        }
        return best;
    }
};