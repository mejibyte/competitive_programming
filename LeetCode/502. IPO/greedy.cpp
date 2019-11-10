// Greedy works!
class Solution {
public:
    int findMaximizedCapital(int k, int have, vector<int>& P, vector<int>& C) {
        int n = P.size();
        assert(n == C.size());
        vector<pair<int, int>> projects;
        for (int i = 0; i < n; ++i) {
            projects.push_back({C[i], P[i]});
        }
        sort(projects.begin(), projects.end());

        // Projects are now sorted by ascending capital needed.
        int next = 0;
        priority_queue<int> q;
        while (k > 0) { // While I still can invest in more projects...
            // Figure out with projects are "unlocked" with the capital I have.
            // Since they are sorted by needed capital, this can be done linearly.
            while (next < n && have >= projects[next].first) {
                q.push(projects[next].second);
                next++;
            }
            if (q.size() == 0) break;

            // From all the projects that I can afford, choose the one that
            // gives me the most profit (be greedy). This might unlock new
            // better projects on the next round.
            int new_profit = q.top();
            q.pop();
            have += new_profit;
            k--;
        }
        return have;
    }
};
