class Solution {
public:
    vector<string> generatePossibleNextMoves(string s) {
        vector<string> ans;
        for (int i = 0; i + 1 < s.size(); ++i) {
            if (s[i] == '+' and s[i + 1] == '+') {
                ans.push_back(s);
                ans.back()[i] = '-';
                ans.back()[i+1] = '-';
            }
        }
        return ans;
    }
};
