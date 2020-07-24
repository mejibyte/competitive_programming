class ValidWordAbbr {
public:
    ValidWordAbbr(vector<string>& dictionary) {
        for (const auto& s : dictionary) {
            if (dict.count(s) > 0) continue;
            dict.insert(s);
            count[abbr(s)]++;
        }
    }

    bool isUnique(string word) {
        string key = abbr(word);
        if (count[key] == 0) return true;
        if (count[key] == 1 and dict.count(word) == 1) return true;
        return false;
    }

    string abbr(const string& s) {
        if (s.size() <= 2) return s;
        stringstream sin;
        sin << s[0];
        sin << s.size() - 2;
        sin << s[s.size() - 1];
        return sin.str();
    }

    set<string> dict;
    map<string, int> count;
};

/**
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr* obj = new ValidWordAbbr(dictionary);
 * bool param_1 = obj->isUnique(word);
 */