// 2019-08-11

// TODO: Also try to solve this using <open, close> events (line sweep).

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> ans;

        int busy_until = numeric_limits<int>::min();
        int start = numeric_limits<int>::min();
        for (const auto& p : intervals) {
            if (busy_until < p[0]) {
                ans.push_back({start, busy_until});
                start = p[0];
            }
            busy_until = max(busy_until, p[1]);
        }
        ans.push_back({start, busy_until});
        ans.erase(ans.begin());
        return ans;
    }
};
