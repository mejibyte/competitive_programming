struct One {
    int r, c;
};

class Solution {
public:
    int countCornerRectangles(vector<vector<int>>& grid) {
        long long ans = 0;
        int rows = grid.size();
        if (rows == 0) return 0;
        int cols = grid[0].size();

        vector<vector<One>> by_row(rows);
        vector<vector<One>> by_col(cols);

        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j] == 1) {
                    by_row[i].push_back({i, j});
                    by_col[j].push_back({i, j});
                }
            }
        }

        for (int r0 = 0; r0 < rows; ++r0) {
            for (int k1 = 0; k1 < by_row[r0].size(); ++k1) {
                int c0 = by_row[r0][k1].c;
                for (int k2 = k1 + 1; k2 < by_row[r0].size(); ++k2) {
                    int c1 = by_row[r0][k2].c;
                    assert(c0 < c1);
                    for (int k3 = 0; k3 < by_col[c1].size(); ++k3) {
                        int r1 = by_col[c1][k3].r;
                        if (r1 <= r0) continue;

                        if (grid[r0][c0] + grid[r0][c1] + grid[r1][c0] + grid[r1][c1] == 4) {
                            ans++;
                        }

                    }
                }
            }
        }
        return ans;
    }
};
