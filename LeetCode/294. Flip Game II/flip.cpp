class Solution {
public:
    bool canWin(string s) {
        for (int i = 0; i + 1 < s.size(); ++i) {
            if (s[i] == '+' and s[i + 1] == '+') {
                string t = s;
                t[i] = '-';
                t[i+1] = '-';
                if (!canWin(t)) return true;
            }
        }
        return false;
    }
};
