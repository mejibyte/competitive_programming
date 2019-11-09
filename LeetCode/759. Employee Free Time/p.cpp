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

const int oo = numeric_limits<int>::max();

bool comparator(const Interval* a, const Interval* b) {
    if (a->start != b->start) return a->start < b->start;
    return a->end < b->end;
}

// Given list of busy times for a single person, returns list
// of free times for this person.
vector<pair<int, int>> available(vector<Interval*>& v) {
    vector<pair<int, int>> answer;

    sort(v.begin(), v.end(), comparator);
    int busy_until = -oo;
    for (auto m : v) {
        if (m->start > busy_until) {
            answer.push_back({busy_until, m->start});
        }
        busy_until = max(busy_until, m->end);
    }
    answer.push_back({busy_until, oo});
    return answer;
}


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

// Given the free times for each person, returns the intersection (times where
// everyone is free).
vector<pair<int,int>> intersection(const vector<vector<pair<int,int>>>& free_times) {
    int num_people = free_times.size();
    vector<Event> events;
    for (int i = 0; i < num_people; ++i) {
        for (const auto& free_time : free_times[i]) {
            events.push_back(Event(i, free_time.first, Event::OPEN));
            events.push_back(Event(i, free_time.second, Event::CLOSE));
        }
    }
    sort(events.begin(), events.end());

    vector<pair<int,int>> intersection;
    set<int> active;
    int from;
    for (const auto& e : events) {
        if (e.type == Event::OPEN) {
            active.insert(e.person);
            from = e.time;
        } else {
            if (active.size() == num_people and from < e.time) { // use <= here for empty intervals, e.g. [5,5]
                intersection.push_back({from, e.time});
            }
            active.erase(e.person);
        }
    }
    return intersection;
}

class Solution {
public:
    vector<Interval*> employeeFreeTime(vector<vector<Interval*>> schedule) {
        // Convert each employee to free times
        vector<vector<pair<int,int>>> free_times;
        for (auto& e : schedule) {
            free_times.push_back(available(e));
        }
        // Find intersection
        vector<pair<int,int>> times = intersection(free_times);

        vector<Interval*> ans;
        for (const auto& m : times) {
            if (m.first == -oo or m.second == oo) continue;
            ans.push_back(new Interval(m.first, m.second)); // Memory leak unless LeetCode deletes these :)
        }
        return ans;
    }
};
