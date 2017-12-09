class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        auto ans = f(n);
        ans.erase(ans.begin());
        return ans;
    }

    vector<vector<int>> f(int n, int first = 2) {
        vector<vector<int>> ans = {{n}};
        for (int d = first; d * d <= n; ++d) {
            if (n % d == 0) {
                auto k = f(n / d, d);
                for (auto &v : k) {
                    v.push_back(d);
                    ans.push_back(v);
                }
            }
        }
        return ans;
    }
};
