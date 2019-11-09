// Date: Sat Dec 2 15:07:11 2017

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

bool operator < (const Interval& a, const Interval& b) {
    if (a.start != b.start) return a.start < b.start;
    return a.end < b.end;
}
class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        int n = intervals.size();
        vector<Interval> ans;
        if (n == 0) return ans;
        sort(intervals.begin(), intervals.end());
        int from = intervals[0].start;
        int to = intervals[0].end;

        for (int i = 0; i < n; ++i) {
            const Interval& k = intervals[i];
            if (k.start > to) {
                // Close previous one.
                ans.push_back(Interval(from, to));
                from = k.start;
                to = k.end;
            } else {
                assert(k.start >= from);
                to = max(to, k.end);
            }
        }
        ans.push_back(Interval(from, to));
        return ans;
    }
};
