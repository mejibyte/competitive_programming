// Accepted
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

struct Death {
    string name;
    double time;
    Death(){}
    Death(const string &Name, double Time) : name(Name), time(Time) {}
    bool operator < (const Death &o) const {
        if (cmp(time, o.time) != 0) return cmp(time, o.time) < 0;
        return name < o.name;
    }
};

struct Collision {
    double time;
    Vector point; // point of collision, if any
    vector<int> people; // the guy who fell or the two fellows that collided (contains indexes)

    Collision(){}
    Collision(double Time) : time(Time) {}
    Collision(double Time, double x, double y, int personA, int personB) : time(Time), point(x, y) {
        people = vector<int>(2); people[0] = personA; people[1] = personB;
    }

    bool operator < (const Collision &o) const {
        if (cmp(time, o.time) != 0) return cmp(time, o.time) < 0;
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
Collision collisionBetween(const Person &a, const int indexOfA, const Person &b, const int indexOfB) {
    if (Vector(a.x, a.y) == Vector(b.x, b.y)) {
        return Collision(-1.0); // They are on the same point, won't collide.
    }

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
                return Collision(-1.0);
            }
            Vector pointOfCollision(x0 + (x2 - x0) / 2,
                y0 + (y2 - y0) / 2);

            double dist = hypot(x2 - x0, y2 - y0) / 2;
            if (cmp(x0 + dist * a.d.x, pointOfCollision.x) != 0 or cmp(y0 + dist * a.d.y, pointOfCollision.y) != 0 or
            cmp(x2 + dist * b.d.x, pointOfCollision.x) != 0 or cmp(y2 + dist * b.d.y, pointOfCollision.y) != 0) {
                // they travel in opposite directions, but after traveling half the distance they haven't collided, so they'll never collide
                return Collision(-1.0);
            }
            return Collision(dist, pointOfCollision.x, pointOfCollision.y, indexOfA, indexOfB); // they'll collide in half their distance because they travel in opposite directions
        }
        //just parallel, no intersection
        return Collision(-1.0);
    }    

    t0 /= det;
    t1 /= det;

    if (cmp(t0, t1) == 0 and cmp(0.0, t0) <= 0 and cmp(0.0, t1) <= 0){
        double x = x0 + t0*(x1-x0);
        double y = y0 + t0*(y1-y0);
        if (outsideWorld(x, y)) return Collision(-1.0);
        return Collision(t0, x, y, indexOfA, indexOfB);
    }
    return Collision(-1.0);
}

bool collidesWithSomeone(const vector< Person > &people, int i) {
    for (int j = 0; j < people.size(); ++j) {
        if (i == j) continue;
        Collision c = collisionBetween(people[i], i, people[j], j);
        dprintf("Colission between %s and %s:\n    Time = %lf, x=%lf, y=%lf\n", people[i].name.c_str(), people[j].name.c_str(), c.time, c.point.x, c.point.y);
        assert(cmp(c.time, 0) != 0); // if they collided, assert it wasn't at time 0
        if (cmp(c.time, 0) > 0) { // Bang!
            return true;
        }
    }
    return false;
}


// If there's someone who doesn't collide, it's added to the deaths vector and removed from the people vector.
vector< Person > killOrBouncePeople(vector< Person > people, vector < Death > &deaths, double &elapsedTime) {
    for (int i = 0; i < people.size(); ++i) {
        if (!collidesWithSomeone(people, i)) {
            dcout << people[i].name << " doesn't collide with anyone. Killing!" << endl;
            deaths.push_back( Death(people[i].name, elapsedTime + people[i].timeToFall()) );
            vector < Person > ans;
            for (int j = 0; j < people.size(); ++j) {
                if (i != j) ans.push_back(people[j]);
            }
            return ans;
        }
    }
    
    // Everybody collides here
    for (int i = 0; i < people.size(); ++i) assert(collidesWithSomeone(people, i));
    
    // Now process collisions, by time.
    vector< Collision > collisions;
    for (int i = 0; i < people.size(); ++i) {
        for (int j = i + 1; j < people.size(); ++j) {
            Collision c = collisionBetween(people[i], i, people[j], j);
            if (cmp(c.time, 0) > 0) {
                collisions.push_back( c );
            }
        }
    }
    assert(collisions.size() > 0);
    sort(collisions.begin(), collisions.end());
    
    int i = 0, n = collisions.size();
    set<int> peopleWhoDiedInCollisions;
    
    while (i < n and cmp(collisions[0].time, collisions[i].time) == 0) {
        int j = i;
        while (j < n and cmp(collisions[i].time, collisions[j].time) == 0 and collisions[i].point == collisions[j].point) {
            j++;
        }
        // collisions[i..j) have the same point and time)
        dprintf("Processing slice [i=%d, j=%d) of collisions:\n", i, j);
        for (int k = i; k < j; ++k) {
            dprintf("    Collision[k=%d]: time = %lf, x = %lf, y = %lf, people.size() = %d\n", k, collisions[k].time, collisions[k].point.x, collisions[k].point.y, (int)collisions[k].people.size());
        }
        
        if (j - i == 1) { // two people
            // just swap their names
            int personA = collisions[i].people[0], personB = collisions[i].people[1];
            dprintf("Two people collided: %s and %s\n", people[personA].name.c_str(), people[personB].name.c_str());
            swap(people[personA].name, people[personB].name);
        } else { // more than two people
            for (int k = i; k < j; ++k) {
                peopleWhoDiedInCollisions.insert( collisions[k].people.begin(), collisions[k].people.end()  );
            }
        }
        
        i = j;
    }
    
    vector< Person > newPeople;
    for (i = 0; i < people.size(); ++i) {
        if (peopleWhoDiedInCollisions.count(i) > 0) {
            deaths.push_back( Death(people[i].name, elapsedTime + collisions[0].time) );
        } else {
            Person p = people[i];
            p.x += collisions[0].time * p.d.x;
            p.y += collisions[0].time * p.d.y;
            newPeople.push_back( p );
        }
    }
    elapsedTime += collisions[0].time; 
    dprintf("Elapsed time: %lf\n", elapsedTime);
    return newPeople;
}

int main(){
    int Cases; cin >> Cases;
    while (Cases--) {
        dprintf("\n\n\n\nBegin case:\n");
        int n; cin >> n;
        cin >> Width >> Height;

        vector<Person> people;        
        for (int i = 0; i < n; ++i) {
            Person p;
            cin >> p.x >> p.y >> p.d.x >> p.d.y >> p.name;
            assert(cmp(floor(p.x), p.x) == 0 and cmp(floor(p.y), p.y) == 0); // people lie on integer coordinates
            p.d.x -= p.x; p.d.y -= p.y; p.d.normalize();
            people.push_back(p);
            dcout << p << endl;
        }

        vector< Death > deaths;
        double elapsedTime = 0;        
        while (people.size() > 0) {
            people = killOrBouncePeople(people, deaths, elapsedTime);
            dprintf("Remaining people:\n");
            for (int i = 0; i < people.size(); ++i) {
                dcout << "       " << people[i] << endl;
            }
        }
        sort(deaths.begin(), deaths.end());
        for (int i = 0; i < deaths.size(); ++i) {
            dprintf("%s died at %lf\n", deaths[i].name.c_str(), deaths[i].time);
        }
        printf("%s\n", deaths.back().name.c_str());
    }
    return 0;
}