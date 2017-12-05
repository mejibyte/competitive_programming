class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int n = s.size(), m = t.size();
        if (n > m) {
            swap(n, m);
            swap(s, t);
        }
        assert(n <= m);
        if (m - n > 1) return false;
        if (m == n) {
            int diff = 0;
            for (int i = 0; i < n; ++i) diff += (s[i] != t[i]);
            return diff == 1;
        } else {
            assert(n + 1 == m);
            // One extra character to delete in t.
            int l = 0, r = n - 1;
            while (l < n and s[l] == t[l]) {
                l++;
            }
            while (r >= 0 and s[r] == t[r + 1]) {
                r--;
            }
            return l >= r + 1;
        }
    }
};
