enum EventType {
  CLOSE = 0,
  OPEN = 1,
};

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        vector<pair<int, int>> events;
        for (const auto &m : intervals) {
            events.push_back(make_pair(m[0], OPEN));
            events.push_back(make_pair(m[1], CLOSE));
        }
        sort(events.begin(), events.end());
        int answer = 0;
        int active = 0;
        for (const auto& e : events) {
            if (e.second == CLOSE) {
                assert(active >= 0);
                active--;
            } else {
                active++;
            }
            answer = max(answer, active);
        }
        return answer;
    }
};
