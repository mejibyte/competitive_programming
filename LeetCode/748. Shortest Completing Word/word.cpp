class Solution {
public:
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        map<char, int> need;
        for (char c : licensePlate) {
            if (isalpha(c)) need[tolower(c)]++;
        }

        string best = "";
        for (const string &w : words) {
            map<char, int> have;
            for (char c : w) have[c]++;

            bool works = true;
            for (const pair<char, int> p : need) {
                if (have[p.first] < p.second) {
                    works = false;
                    break;
                }
            }

            if (works and (best == "" or w.size() < best.size())) {
                best = w;
            }
        }
        return best;
    }
};
