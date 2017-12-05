enum { CLOSE, OPEN };

class MyCalendarThree {

    multiset<pair<int, int>> events;
public:
    MyCalendarThree() {

    }

    int book(int start, int end) {
        events.insert(make_pair(start, OPEN));
        events.insert(make_pair(end, CLOSE));
        int best = 1;
        int seen = 0;
        for (auto &e : events) {
            if (e.second == OPEN) seen++;
            if (e.second == CLOSE) seen--;
            best = max(best, seen);
        }
        return best;
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree obj = new MyCalendarThree();
 * int param_1 = obj.book(start,end);
 */
