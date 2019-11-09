class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        int busy_until = numeric_limits<int>::min();
        for (const auto& m : intervals) {
            if (m[0] < busy_until) return false;
            busy_until = max(busy_until, m[1]);
        }
        return true;
    }
};
