class Solution {
    vector<string> tokens;
    int at;

    map<string, int> parse() {
        if (at >= tokens.size() or tokens[at] == ")") return {};

        map<string, int> ans;
        if (tokens[at] == "(") {
            assert(tokens[at++] == "(");
            ans = parse();
            assert(tokens[at++] == ")");
        } else {
            ans[tokens[at++]] = 1;
        }
        if (at < tokens.size() and isdigit(tokens[at][0])) {
            ans = multiply(ans, tokens[at++]);
        }
        return add(ans, parse());
    }

    map<string, int> add(map<string, int> a, map<string, int> b) {
        for (auto k : b) {
            a[k.first] += k.second;
        }
        return a;
    }

    map<string, int> multiply(map<string, int> a, string num) {
        stringstream ss(num);
        int x;
        ss >> x;
        for (auto& k : a) {
            k.second *= x;
        }
        return a;
    }

public:
    string countOfAtoms(string s) {
        // K 4 ( O N ( S O 3 ) 2 ) 2
        int n = s.size();
        for (int i = 0; i < n; ) {
            if (s[i] == '(' or s[i] == ')') {
                tokens.push_back(string("") + s[i++]);
            } else if (isalpha(s[i])) {
                assert(isupper(s[i]));
                string t = "";
                t += s[i++];
                while (i < n and islower(s[i])) t += s[i++];
                tokens.push_back(t);
            } else {
                assert(isdigit(s[i]));
                string t = "";
                t += s[i++];
                while (i < n and isdigit(s[i])) t += s[i++];
                tokens.push_back(t);
            }
        }
        auto m = parse();
        string ans = "";
        for (auto k : m) {
            ans += k.first;
            if (k.second > 1) {
                stringstream ss;
                ss << k.second;
                string t;
                ss >> t;
                ans += t;
            }
        }
        return ans;
    }
};
