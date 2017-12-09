struct Item {
    string word;
    int count;
};

bool operator < (const Item &a, const Item &b) {
    if (a.count != b.count) return b.count < a.count;
    return b.word > a.word;
}

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
       map<string, int> count;
        for (const string &w : words) count[w]++;
        priority_queue<Item> q;
        for (auto p : count) {
            Item i = {p.first, p.second};
            q.push(i);
            if (q.size() > k) q.pop();
        }
        vector<string> ans;
        while (k--) {
            ans.push_back(q.top().word);
            q.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
