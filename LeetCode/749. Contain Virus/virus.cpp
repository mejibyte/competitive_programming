const int MAXN = 55;
int dr[] = {-1, +1,  0,  0};
int dc[] = { 0,  0, -1, +1};

class Solution {


    enum { UP, DOWN, LEFT, RIGHT };
    bool wall[MAXN][MAXN][4];
    int visited[MAXN][MAXN];
    int rows, cols;

    vector<vector<int>> g;

    int total_walls = 0;
    int clock = 1;

public:
    int containVirus(vector<vector<int>>& grid) {
        g = std::move(grid);

        rows = g.size();
        cols = g[0].size();
        memset(wall, 0, sizeof wall);
        memset(visited, 0, sizeof visited);

        for (int c = 0; c < cols; ++c) {
            wall[0][c][UP] = true;
            wall[rows-1][c][DOWN] = true;
        }
        for (int r = 0; r < rows; ++r) {
            wall[r][0][LEFT] = true;
            wall[r][cols-1][RIGHT] = true;
        }

        while (work());
        return total_walls;
    }

    // Simulates one day, and returns true if any changes were made.
    bool work() {
        clock++; // Clean up everything from the previous day.

        // Find most dangerous region.
        int r0, c0;
        int most_danger = -1;

        int first_clock = clock;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (g[r][c] == 0) continue;
                if (visited[r][c] >= first_clock) continue;
                int option = count(r, c, clock++);
                if (option > most_danger) {
                    most_danger = option;
                    r0 = r;
                    c0 = c;
                }
            }
        }

        if (most_danger <= 0) return false; // We are done. Nothing else to infect.

        build_walls(r0, c0, clock++);

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (g[r][c] == 0) continue;
                if (visited[r][c] >= clock) continue;
                grow_virus(r, c, clock);
            }
        }
        return true;
    }

    void grow_virus(int r, int c, int clock) {
        if (r < 0 || r >= rows) return;
        if (c < 0 || c >= cols) return;
        if (visited[r][c] == clock) return;

        visited[r][c] = clock;
        if (g[r][c] == 0) {
            g[r][c] = 1;
        } else {
            for (int k = 0; k < 4; ++k) {
                if (wall[r][c][k]) continue;
                grow_virus(r + dr[k], c + dc[k], clock);
            }
        }
    }

    void build_walls(int r, int c, int clock) {
        assert(0 <= r and r < rows and 0 <= c and c < cols);
        if (visited[r][c] == clock) return;
        assert(g[r][c] == 1);
        visited[r][c] = clock;

        for (int k = 0; k < 4; ++k) {
            if (wall[r][c][k]) continue;
            int nr = r + dr[k];
            int nc = c + dc[k];
            if (0 <= nr and nr < rows and 0 <= nc and nc < cols) {
                if (g[nr][nc] == 1) {
                    build_walls(nr, nc, clock);
                } else {
                    wall[r][c][k] = true;
                    wall[nr][nc][k^1] = true;
                    total_walls++;
                }
            }
        }
    }

    int count(int r, int c, int clock) {
        if (r < 0 || r >= rows) return 0;
        if (c < 0 || c >= cols) return 0;
        if (visited[r][c] == clock) return 0;

        visited[r][c] = clock;
        if (g[r][c] == 0) {
            return 1;
        } else {
            int ans = 0;
            for (int k = 0; k < 4; ++k) {
                if (wall[r][c][k]) continue;
                ans += count(r + dr[k], c + dc[k], clock);
            }
            return ans;
        }
    }
};
