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

struct Event {
    enum Type {
        OPEN = 0,
        CLOSE = 1,
    };

    Type type;
    int time, person;

    Event(int person, int time, Type type) :
        person(person), time(time), type(type) {}

    bool operator < (const Event& e) const {
        if (time != e.time) return time < e.time;
        if (type != e.type) return type < e.type;
        return person < e.person;
    }
};


class Solution {
public:
    vector<Interval*> employeeFreeTime(vector<vector<Interval*>> schedule) {
        int num_people = schedule.size();
        vector<Event> events;
        for (int i = 0; i < num_people; ++i) {
            for (const auto& busy_time : schedule[i]) {
                events.push_back(Event(i, busy_time->start, Event::OPEN));
                events.push_back(Event(i, busy_time->end, Event::CLOSE));
            }
        }
        sort(events.begin(), events.end());

        vector<Interval*> ans;
        int busy = 0;
        int latest_close = -1;
        for (const auto& e : events) {
            if (e.type == Event::OPEN) {
                if (busy == 0 and latest_close >= 0) {
                    // Memory leak unless LeetCode deletes these :)
                    ans.push_back(new Interval(latest_close, e.time));
                }
                busy++;
            } else {
                busy--;
                latest_close = e.time;
            }
        }

        return ans;
    }
};
