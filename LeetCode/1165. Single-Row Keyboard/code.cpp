class Solution {
public:
    int calculateTime(string keyboard, string word) {
        int moves = 0;
        int at = 0;
        for (const char c : word) {
            int to = keyboard.find(c);
            moves += abs(to - at);
            at = to;
        }
        return moves;
    }
};