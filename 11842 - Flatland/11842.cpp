using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

#define DEBUG false
#define dprintf DEBUG and printf
#define dcout DEBUG and cout

inline int cmp(double x, double y = 0, double tol = 1e-9) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

int Width, Height;

struct Vector {
    double x, y;
    Vector() {}
    Vector(double X, double Y) : x(X), y(Y) {}
    inline void normalize() {
        double length = sqrt(x * x + y * y);
        x /= length; y /= length;
    }
    bool operator < (const Vector &o) const { 
        if (cmp(x, o.x) != 0) return cmp(x, o.x) < 0;
        return cmp(y, o.y) < 0;
    }
    bool operator == (const Vector &o) const { 
        return (cmp(x, o.x) == 0 and
                cmp(y, o.y) == 0);
    }    
};

struct Person {
    double x, y;
    Vector d;
    string name;

    Person(){}
    Person(double X, double Y, const Vector &D, string Name) : x(X), y(Y), d(D.x, D.y), name(Name) {}

    bool operator < (const Person &o) { return name < o.name; }

    double timeToFall() const;

    friend ostream &operator<<(ostream &stream, const Person &p);
};

double Person::timeToFall() const {
    double horizontal = cmp(this->d.x, 0) < 0 ? this->x / (-this->d.x) : (Width - this->x) / (this->d.x);
    double vertical   = cmp(this->d.y, 0) < 0 ? this->y / (-this->d.y) : (Height - this->y) / (this->d.y);    
    return min(horizontal, vertical);
}

ostream &operator<<(ostream &stream, const Person &p) {
    stream << p.name << " is at (" << p.x << ", " << p.y << ") moving in direction <" << p.d.x << ", " << p.d.y << "> (Might fall in " << p.timeToFall() << " seconds)";
    return stream;
}

struct Event {
    int type; // 0 = free fall, 1 = collision
    double time;
    Vector point; // point of collision, if any
    vector<int> people; // the guy who fell or the two fellows that collided (contains indexes)
    string name;

    bool operator < (const Event &o) const {
        if (cmp(time, o.time) != 0) return cmp(time, o.time) < 0;
        if (type != o.type) return type < o.type;
        if (type == 0) return name < o.name;
        return point < o.point;
    }
};

double dot(const Vector &a, const Vector &b) {
    return a.x * b.x + a.y * b.y;
}

bool outsideWorld(double x, double y) {
    if (cmp(x, 0) < 0) return true;
    if (cmp(x, Width) > 0) return true;
    if (cmp(y, 0) < 0) return true;
    if (cmp(y, Height) > 0) return true;
    return false;
}

// Returns the time where person A and B would collide, or -1 if they won't.
double timeOfCollision(const Person &a, const Person &b, Vector &pointOfCollision) {
    if (cmp(a.x, b.x) == 0 and cmp(a.y, b.y) == 0) return -1; // They are on the same point, won't collide.
    
    double x0 = a.x, x1 = a.x + a.d.x;
    double y0 = a.y, y1 = a.y + a.d.y;

    double x2 = b.x, x3 = b.x + b.d.x;
    double y2 = b.y, y3 = b.y + b.d.y;

    double t0 = (y3-y2)*(x0-x2)-(x3-x2)*(y0-y2);
    double t1 = (x1-x0)*(y2-y0)-(y1-y0)*(x2-x0);
    double det = (y1-y0)*(x3-x2)-(y3-y2)*(x1-x0);

    if (cmp(det, 0) == 0){
      //parallel
        if (cmp(t0, 0) == 0 || cmp(t1, 0) == 0) {
          // they lie on same line. But they might not collide (if they travel in the same direction)
            if (cmp(dot(a.d, b.d), 1) == 0) { // They travel in the same direction
                return -1;
            }
            pointOfCollision.x = x0 + (x2 - x0) / 2;
            pointOfCollision.y = y0 + (y2 - y0) / 2;
            double dist = hypot(x2 - x0, y2 - y0) / 2;
            if (cmp(x0 + dist * a.d.x, pointOfCollision.x) != 0 or cmp(y0 + dist * a.d.y, pointOfCollision.y) != 0 or
                cmp(x2 + dist * b.d.x, pointOfCollision.x) != 0 or cmp(y2 + dist * b.d.y, pointOfCollision.y) != 0) {
                // they travel in opposite directions, but after traveling half the distance they haven't collided, so they'll never collide
                    return -1;
            }
            return dist; // they'll collide in half their distance because they travel in opposite directions
        }
        //just parallel, no intersection
        return -1;
    }    

    t0 /= det;
    t1 /= det;

    if (cmp(t0, t1) == 0 and cmp(0.0, t0) <= 0 and cmp(0.0, t1) <= 0){
        double x = x0 + t0*(x1-x0);
        double y = y0 + t0*(y1-y0);
        if (outsideWorld(x, y)) return -1;
        pointOfCollision.x = x;
        pointOfCollision.y = y;
        return t0;
    }
    return -1;
}

int main(){
    int Cases; cin >> Cases;
    while (Cases--) {
        dprintf("Begin case:\n");
        int n; cin >> n;
        cin >> Width >> Height;

        vector<Person> people;        
        for (int i = 0; i < n; ++i) {
            Person p;
            cin >> p.x >> p.y >> p.d.x >> p.d.y >> p.name;
            p.d.x -= p.x; p.d.y -= p.y; p.d.normalize();
            people.push_back(p);
            dcout << p << endl;
        }

        double timeOfLastDeath = -1;
        string lastToDie = "";
        while (people.size() > 0) {
            vector< Event > events;
            
            for (int i = 0; i < people.size(); ++i) {
                Event fall;
                fall.type = 0;
                fall.time = people[i].timeToFall();
                fall.people.push_back(i);
                fall.name = people[i].name;
                events.push_back(fall);
                
                
                for (int j = i + 1; j < people.size(); ++j) {
                    Person a = people[i], b = people[j];
                    Vector point;
                    double t = timeOfCollision(a, b, point);

                    if (t < 0) {
                        //printf("%s and %s won't collide\n", a.name.c_str(), b.name.c_str());
                    } else {
                        Event collision;
                        collision.type = 1;
                        collision.time = t;
                        collision.point = point;
                        collision.people.push_back(i); collision.people.push_back(j);
                        events.push_back(collision);
                        dprintf("%s and %s could collide at <%lf, %lf> in %lf seconds\n", a.name.c_str(), b.name.c_str(), point.x, point.y, t);
                    }
                }
            }
            
            assert(events.size() > 0);
            sort(events.begin(), events.end());
            
            if (events[0].type == 0) { // free fall, just remove this guy and try again
                if (cmp(events[0].time, timeOfLastDeath) > 0 or cmp(events[0].time, timeOfLastDeath) == 0 and people[events[0].people[0]].name > lastToDie ) {
                    lastToDie = people[events[0].people[0]].name;
                    timeOfLastDeath = events[0].time;
                }
                people.erase(people.begin() + events[0].people[0]);
                dprintf("%s just fell of at time %lf.\n", lastToDie.c_str(), events[0].time);
                dprintf("Remaining people are:\n");
                for (int i = 0; i < people.size(); ++i){
                    dcout << "      " << people[i] << endl;
                }
                continue;
            } else {
                double timeOfCollision = events[0].time;
                Vector pointOfCollision = events[0].point;
                set< int > peopleWhoCollided;
                for (int i = 0;  i < events.size() and cmp(events[i].time, timeOfCollision) == 0 and events[i].point == pointOfCollision; i++) {
                    peopleWhoCollided.insert(events[i].people.begin(), events[i].people.end());
                }
                dprintf("%d people just collided! Holy bananas!\n", (int)peopleWhoCollided.size());
                if (peopleWhoCollided.size() == 2) { // nothing serious, just swap their directions and try again
                    int a = *peopleWhoCollided.begin(), b = *(--peopleWhoCollided.end());
                    double dist = hypot(pointOfCollision.x - people[a].x, pointOfCollision.y - people[a].y);
                    assert(cmp(dist, hypot(pointOfCollision.x - people[b].x, pointOfCollision.y - people[b].y)) == 0);
                    for (int i = 0; i < people.size(); ++i){
                        people[i].x += dist * people[i].d.x;
                        people[i].y += dist * people[i].d.y;                        
                    }
                    swap(people[a].d, people[b].d);
                    dprintf("Swapped direction between %s and %s\n", people[a].name.c_str(), people[b].name.c_str());
                    dprintf("Remaining people are:\n");
                    for (int i = 0; i < people.size(); ++i){
                        dcout << "      " << people[i] << endl;
                    }                    
                    continue;
                } else {
                    // delete those guys who collided
                    vector< Person > newPeople;
                    for (int i = 0; i < people.size(); ++i) {
                        if (peopleWhoCollided.count(i) > 0) {
                            if (cmp(events[0].time, timeOfLastDeath) > 0 or cmp(events[0].time, timeOfLastDeath) == 0 and people[i].name > lastToDie ) {
                                lastToDie = people[i].name;
                                timeOfLastDeath = events[0].time;
                            }
                            dprintf("   %s died in the collision.\n", people[i].name.c_str());
                        } else {
                            newPeople.push_back(people[i]);
                        }
                    }
                    people = newPeople;
                    dprintf("Remaining people are:\n");
                    for (int i = 0; i < people.size(); ++i){
                        dcout << "      " << people[i] << endl;
                    }                    
                    
                    continue;
                }
            }
            
            
            
            break;
        }
        assert(lastToDie.size() > 0);
        cout << lastToDie << endl;
    }
    return 0;
}