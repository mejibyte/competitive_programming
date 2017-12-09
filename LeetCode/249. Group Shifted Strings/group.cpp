class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        map<vector<int>, vector<string>> groups;
        for (auto &s : strings) {
            vector<int> key;
            for (int i = 0; i + 1 < s.size(); ++i) {
                int d = s[i] - s[i + 1];
                d = ((d % 26) + 26) % 26;
                key.push_back(d);
            }
            groups[key].push_back(s);
        }

        vector<vector<string>> ans;
        for (auto &p : groups) {
            ans.emplace_back(p.second);
        }
        return ans;
    }
};
