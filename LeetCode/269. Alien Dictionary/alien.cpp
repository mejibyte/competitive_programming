enum { WHITE, GRAY, BLACK };

class Solution {
    bool g[26][26];
    int color[26];
    string ans = "";

    bool sort(char at) {
        color[at-'a'] = GRAY;
        for (char next = 'a'; next <= 'z'; ++next) {
            if (!g[at-'a'][next-'a']) continue;
            if (color[next-'a'] == BLACK) continue;
            if (color[next-'a'] == GRAY) return false;
            if (!sort(next)) return false;
        }
        color[at-'a'] = BLACK;
        ans = at + ans;
        return true;
    }

public:
    string alienOrder(vector<string>& words) {
        memset(g, 0, sizeof g);
        memset(color, WHITE, sizeof color);

        set<char> letters;
        for (const string &w : words) {
            for (char c : w) {
                letters.insert(c);
            }
        }

        for (int k = 0; k + 1 < words.size(); ++k) {
            const string &a = words[k];
            const string &b = words[k+1];

            int i = 0;
            while (i < a.size() and i < b.size() and a[i] == b[i]) {
                i++;
            }
            if (i < a.size() and i < b.size()) {
                g[a[i]-'a'][b[i]-'a'] = true;
            }
        }
        for (char c : letters) {
            if (color[c-'a'] == WHITE) {
                if (!sort(c)) return "";
            }
        }
        return ans;
    }
};
