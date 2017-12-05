class Solution {
    vector<int> p;
    map<pair<int, int>, int> index;

public:
    vector<int> numIslands2(int rows, int cols, vector<pair<int, int>>& positions) {
        int next = 0;
        int components = 0;
        vector<int> ans;

        for (int i = 0; i < positions.size(); ++i) {
            if (index.count(positions[i])) continue;
            index[positions[i]] = next;
            p.push_back(next++);

            components++;
            int r = positions[i].first, c = positions[i].second;
            components -= merge(r, c, r - 1, c);
            components -= merge(r, c, r + 1, c);
            components -= merge(r, c, r, c + 1);
            components -= merge(r, c, r, c - 1);
            ans.push_back(components);
        }
        return ans;
    }

    int merge(int r, int c, int p, int q) {
        auto p1 = make_pair(r, c);
        auto p2 = make_pair(p, q);
        assert(index.count(p1) > 0);
        if (index.count(p2) > 0) {
            int a = index[p1];
            int b = index[p2];
            return merge(a, b);
        }
        return 0;
    }

    int find(int u) {
        if (p[u] == u) return u;
        return p[u] = find(p[u]);
    }

    int merge(int a, int b) {
        int pa = find(a), pb = find(b);
        if (pa != pb) {
            p[pa] = pb;
            return 1;
        }
        return 0;
    }
};
