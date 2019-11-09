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
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        vector<Event> events;
        for (const auto& e : A) {
            events.push_back(Event(0, e[0], Event::OPEN));
            events.push_back(Event(0, e[1], Event::CLOSE));
        }
        for (const auto& e : B) {
            events.push_back(Event(1, e[0], Event::OPEN));
            events.push_back(Event(1, e[1], Event::CLOSE));
        }
        sort(events.begin(), events.end());

        vector<vector<int>> intersection;
        set<int> active;
        int from;
        for (const auto& e : events) {
            if (e.type == Event::OPEN) {
                active.insert(e.person);
                from = e.time;
            } else {
                if (active.size() == 2) {
                    intersection.push_back({from, e.time});
                }
                active.erase(e.person);
            }
        }

        return intersection;
    }
};
