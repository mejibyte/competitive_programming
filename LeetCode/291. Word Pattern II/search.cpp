class Solution {
    string pattern, text;
    map<char, string> assign;
    set<string> taken;

    bool search(int pi, int ti) {
        if (pi >= pattern.size()) return ti >= text.size();
        if (ti >= text.size()) return pi >= pattern.size();

        if (assign.count(pattern[pi]) == 0) {
            // Assign it for the first time.
            for (int len = 1; ti+len-1 < text.size(); ++len) {
                const string& prefix = text.substr(ti, len);
                if (taken.count(prefix)) continue;

                assign[pattern[pi]] = prefix;
                taken.insert(prefix);
                if (search(pi+1, ti+len)) {
                    return true;
                }
                assign.erase(pattern[pi]);
                taken.erase(prefix);
            }
        } else {
            // Just match it.
            const string& need = assign[pattern[pi]];
            int k = text.find(need, ti);
            if (k != ti) return false;
            if (search(pi+1, ti+need.size())) {
                return true;
            }
        }
        return false;
    }
public:
    bool wordPatternMatch(string p, string t) {
        pattern = std::move(p);
        text = std::move(t);
        return search(0, 0);

    }
};
