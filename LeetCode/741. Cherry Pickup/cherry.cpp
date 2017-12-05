const int MAXN = 50;
int memo[MAXN][MAXN][MAXN][MAXN];

class Solution {
public:
    vector<vector<int>> g;

    int N;

    int f(int r0, int c0, int r1, int c1) {
        if (r0 < 0 or r0 >= N or c0 < 0 or c0 >= N) return INT_MIN;
        if (r1 < 0 or r1 >= N or c1 < 0 or c1 >= N) return INT_MIN;
        if (g[r0][c0] == -1 or g[r1][c1] == -1) return INT_MIN;

        if (memo[r0][c0][r1][c1] != -1) return memo[r0][c0][r1][c1];

        int here = g[r0][c0] + g[r1][c1];
        if (r0 == r1 and c0 == c1 and here == 2) here = 1;

        if (r0 == N-1 and c0 == N-1 and r1 == N-1 and c1 == N-1) return here;
        int best = INT_MIN;
        best = max(best, f(r0 + 1, c0, r1 + 1, c1));
        best = max(best, f(r0, c0 + 1, r1, c1 + 1));
        best = max(best, f(r0 + 1, c0, r1, c1 + 1));
        best = max(best, f(r0, c0 + 1, r1 + 1, c1));

        return memo[r0][c0][r1][c1] = best + here;
    }

    int cherryPickup(vector<vector<int>>& grid) {
        g = std::move(grid);
        N = g.size();
        memset(memo, -1, sizeof memo);
        int ans = f(0, 0, 0, 0);
        if (ans < 0) return 0;
        return ans;
    }
};
