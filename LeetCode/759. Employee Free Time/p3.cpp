/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/

class Solution {
public:
    vector<Interval*> employeeFreeTime(vector<vector<Interval*>> schedule) {
        vector<pair<int,int>> times;

        int num_people = schedule.size();
        for (int i = 0; i < num_people; ++i) {
            for (const auto& busy_time : schedule[i]) {
                times.push_back({busy_time->start, busy_time->end});
            }
        }
        sort(times.begin(), times.end());

        vector<Interval*> ans;
        int busy_until = -1;
        for (const auto& t :times) {
            if (busy_until < t.first) {
                if (busy_until > 0) { // corner case the first time.
                    ans.push_back(new Interval(busy_until, t.first));
                }
            }
            busy_until = max(busy_until, t.second);
        }
        return ans;
    }
};
