class Solution {
public:
    bool canPermutePalindrome(string s) {
        map<char, int> count;
        for (char c : s) count[c]++;
        int odd = 0;
        for (auto p : count) {
            odd += (p.second % 2);
        }
        return odd <= 1;
    }
};
