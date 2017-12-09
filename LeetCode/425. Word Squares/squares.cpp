class Solution {
    set<vector<string>> solutions;
    vector<string> words;

    map<string, vector<int>> prefix;
    int n;

    void search(int next, const vector<string> &board) {
        if (next == n) {
            solutions.insert(board);
            return;
        }
        for (const int &candidate : prefix[board[next]]) {
            vector<string> new_board = board;
            new_board[next] = words[candidate];
            for (int k = next + 1; k < n; ++k) {
                new_board[k] += words[candidate][k];
            }

            search(next + 1, new_board);
        }
    }

public:
    vector<vector<string>> wordSquares(vector<string>& w) {
        words = std::move(w);
        assert(words.size() > 0);
        n = words[0].size();

        for (int i = 0; i < words.size(); ++i) {
            assert(words[i].size() == n);
            for (int k = 0; k <= n; ++k) {
                string p = words[i].substr(0, k);
                prefix[p].push_back(i);
            }
        }

        search(0, vector<string>(n, ""));
        vector<vector<string>> ans(solutions.begin(), solutions.end());
        return ans;
    }
};
