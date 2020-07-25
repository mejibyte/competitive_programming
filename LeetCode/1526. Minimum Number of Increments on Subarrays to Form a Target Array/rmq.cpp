const int MAXN = 100005;
int * height;
int N;

namespace RMQ {
    const int L = 18; // 1 + log2(MAXN)
    int p[MAXN][L];

    int better(int a, int b) {
        assert(0 <= a and a < N and 0 <= b and b < N);
        return height[a] <= height[b] ? a : b;
    }

    void build() {
        for (int i = 0; i < N; ++i) {
            p[i][0] = i;
        }
        for (int j = 1; j < L; ++j) {
            for (int i = 0; i < N; ++i) {
                p[i][j] = p[i][j - 1];
                int length = 1 << (j - 1);
                if (i + length < N) {
                    p[i][j] = better(p[i][j - 1], p[i + length][j - 1]);
                }
            }
        }
    }
    // Returns the index of the best value in range [from, to]
    int get(int from, int to) {
        int length = to - from + 1;
        int j = 0;
        while ((1 << (j + 1)) < length) j++;
        assert(j < L);
        return better(p[from][j], p[to - (1 << j) + 1][j]);
    }
};

class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        height = target.data();
        N = target.size();
        RMQ::build();
        return flood(target, 0, target.size() - 1, 0);
    }

    int flood(const vector<int>& h, int i, int j, int w) {
        if (i > j) return 0;

        int smallest = RMQ::get(i, j);

        int ans = h[smallest] - w;
        ans += flood(h, i, smallest - 1, h[smallest]);
        ans += flood(h, smallest + 1, j, h[smallest]);
        return ans;
    }
};
