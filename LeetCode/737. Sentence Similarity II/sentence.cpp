class Solution {
    map<string, string> p;
    int next;

    string find(const string& s) {
        if (p.count(s) == 0) return p[s] = s;
        if (p[s] == s) return s;
        return p[s] = find(p[s]);
    }

    void merge(const string& a, const string& b) {
        const string pa = find(a), pb = find(b);
        if (pa != pb) {
            p[pa] = pb;
        }
    }

public:
    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs) {
        if (words1.size() != words2.size()) return false;
        for (const auto &k : pairs) merge(k.first, k.second);
        for (int i = 0; i < words1.size(); ++i) {
            if (find(words1[i]) != find(words2[i])) {
                return false;
            }
        }
        return true;
    }
};
