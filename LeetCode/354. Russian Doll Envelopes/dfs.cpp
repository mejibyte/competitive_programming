class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        e = envelopes;
        n = e.size();
        if (n == 0) return 0;
        depth.assign(n, -1);
        for (int i = 0; i < n; ++i) {
            dfs(i);
        }
        return *max_element(depth.begin(), depth.end());
    }

    int dfs(int i) {
        if (depth[i] != -1) return depth[i];
        depth[i] = 0;
        for (int j = 0; j < n; ++j) {
            if (e[i][0] < e[j][0] and e[i][1] < e[j][1]) {
                depth[i] = max(depth[i], dfs(j));
            }
        }
        depth[i] += 1;
        return depth[i];
    }

    vector<vector<int>> e;
    int n;
    vector<int> depth;
};
