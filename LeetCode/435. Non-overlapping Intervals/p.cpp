bool sort_by_second(const vector<int>& a, const vector<int>& b) {
    if (a[1] != b[1]) return a[1] < b[1];
    return a[0] < b[0];
}

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), sort_by_second);
        int busy_until = numeric_limits<int>::min() + 1;
        int answer = 0;
        for (const auto& p : intervals) {
            if (p[0] < busy_until) {
                answer++;
            } else {
                assert(p[1] >= busy_until);
                busy_until = p[1];
            }
        }
        return answer;
    }
};
