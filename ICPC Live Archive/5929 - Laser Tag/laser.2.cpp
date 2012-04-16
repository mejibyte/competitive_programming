// Andrés Mejía

// Accepted.

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
#include <bitset>
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

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

struct Point {
    long double x, y;
    Point(){}
    Point(long double x, long double y) : x(x), y(y) {}
    
    void print() {
        cout << "(" << x << ", " << y << ")" << endl;
    }
    
    Point operator +(const Point &b) const {
        return Point(x + b.x, y + b.y);
    }

    Point operator -(const Point &b) const {
        return Point(x - b.x, y - b.y);
    }
    
    // dot product
    long double operator ^(const Point &b) const {
        return  x * b.x + y * b.y;
    }
    
    long double length() {
        return sqrt(x * x + y * y);
    }
    
    void normalize() {
        long double d = length();
        x /= d;
        y /= d;
    }
    
    Point normal() const {
        Point ans(-y, x);
        ans.normalize();
        return ans;
    }
};

Point operator * (long double scalar, const Point &a) {
    return Point(scalar * a.x, scalar * a.y);
}

struct Segment {
    Point a, b;
};

ostream &operator << (ostream &out, const Point &s) {
    out << "(" << s.x << ", " << s.y << ")";
    return out;
}


ostream &operator << (ostream &out, const Segment &s) {
    out << s.a << "---" << s.b;
    return out;
}


struct Intersection {
    bool valid;
    long double t0, t1;
    Point where;
};

ostream &operator << (ostream &out, const Intersection &boom) {
    out << "(valid = " << boom.valid << ", t0 = " << boom.t0 << ", t1 = " << boom.t1 << ", where = " << boom.where << ")";
    return out;
}


long double distsqr(const Point &a, const Point &b) {
    long double dx = a.x - b.x;
    long double dy = a.y - b.y;
    return dx * dx + dy * dy;
}

Point reflect(Point p, const Point &a, const Point &b) {
    // refleja el punto p al otro lado de la recta ab
    long double u = ((p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y)) / distsqr(a, b);
    Point v; // Intersection
    v.x = a.x + u*(b.x - a.x);
    v.y = a.y + u*(b.y - a.y);
    
    p.x += 2*(v.x - p.x);
    p.y += 2*(v.y - p.y);
    return p;
}


vector<Segment> s;

set<int> ans;
int n;

const long double pi = 2 * acos(0);

vector<int> crash;

Intersection get_intersection(const Point &p0, const Point &p1, const Point &p2, const Point &p3) {
    Intersection ans;
    ans.t0 = (p3.y - p2.y) * (p0.x - p2.x) - (p3.x - p2.x) * (p0.y - p2.y);
    ans.t1 = (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
    long double det = (p1.y - p0.y) * (p3.x - p2.x) - (p3.y - p2.y) * (p1.x - p0.x);
    if (cmp(det, 0) == 0){ 
        ans.valid = false;
    } else {
        ans.t0 /= det;
        ans.t1 /= det;
        ans.where.x = p0.x + ans.t0 * (p1.x - p0.x);
        ans.where.y = p0.y + ans.t0 * (p1.y - p0.y);
        ans.valid = true;
    }
    return ans;
}

Point reflect_ray(const Point &dir, const Segment &mirror) {
    Point normal = (mirror.b - mirror.a).normal();
    assert(cmp(normal.length(), 1) == 0);
    
    if (cmp(dir ^ normal, 0) > 0) normal.x *= -1, normal.y *= -1;
    assert((dir ^ normal) <= 0);

    Point new_dir = dir - 2 * (dir ^ normal) * normal;
    new_dir.normalize();
    return new_dir;
}

// Returns true if there's a mirror that blocks the path from 'from' to 'to'.
// The mirrors indicated in the mask 'ignore' will not be considered.
bool obstacle_in_the_way(const Point &from, const Point &to, int ignore) {
    for (int j = 0; j < n; ++j) {
        if (ignore & (1 << j)) continue;
        // check if the segment from pos to boom.where intersects this mirror
        const Segment &possible_obstacle = s[j];
        Intersection middle = get_intersection(from, to, possible_obstacle.a, possible_obstacle.b);
        if (!middle.valid) continue; // doesn't hit this mirror because it's parallel
        if (middle.t1 < 0 or middle.t1 > 1) continue; // hits, but outside the mirror
        if (0 <= middle.t0 and middle.t0 <= 1) { // Fuck!
            return true;
        }
    }
    return false;
}

bool check(double angle) {
    Point pos(0, 0);
    Point direction(cos(angle), sin(angle));
    assert(cmp(direction.length(), 1) == 0);
    
    for (int i = 0; i < crash.size(); ++i) {
        // shoot the ray from here and check it hits the mirror
        Segment mirror = s[crash[i]];
        Intersection boom = get_intersection(pos, pos + 10*direction, mirror.a, mirror.b);
        
        if (!boom.valid) return false; // the laser is parallel with the mirror!
        if (boom.t1 < 0 or boom.t1 > 1) return false; // It hits the mirror's line, but not within the mirror.
        if (boom.t0 < 0) return false; // it hits the mirror, but behind me.

        int ignore = (1 << crash[i]);
        if (i > 0) ignore |= (1 << crash[i - 1]);
        if (obstacle_in_the_way(pos, boom.where, ignore)) {
            return false;
        }

        // Now move to the point and change direction
        pos = boom.where;
        direction = reflect_ray(direction, mirror);
    }
    // finally check that the path back home is free
    if (obstacle_in_the_way(pos, Point(0, 0), 1 << crash.back())) {
        return false;
    }
    
    // (0, 0), pos and pos + dir must be collinear
    assert( cmp( (pos.x - direction.x) * pos.y - (pos.y - direction.y) * pos.x, 0) == 0 );
    
    // now (0, 0) must be along the ray (pos, pos + direction). The parameter must be positive to travel forward.
    long double t = cmp(direction.x, 0) > 0 ? -pos.x / direction.x : -pos.y / direction.y;
    if (t < 0) return false; // would have to travel backwards
    
    return true;
}

void shoot() {
    Point origin(0, 0);
    vector<Segment> reflected_mirrors;
    
    for (int i = 0; i < crash.size(); ++i) {
        reflected_mirrors.push_back(s[crash[i]]);
    }

    for (int i = 0; i < reflected_mirrors.size(); ++i) {
        Segment axis = reflected_mirrors[i];

        for (int j = i + 1; j < crash.size(); ++j) {
            reflected_mirrors[j].a = reflect(reflected_mirrors[j].a, axis.a, axis.b);
            reflected_mirrors[j].b = reflect(reflected_mirrors[j].b, axis.a, axis.b);
        }
        origin = reflect(origin, axis.a, axis.b);
    }
        
    double angle = atan2(origin.y, origin.x);
    while (angle < 0) angle += 2*pi;
    while (angle >= 2*pi) angle -= 2*pi;

    double degrees = angle * 180 / pi;
    if (check(angle)) {
        int rounded = (int)round(degrees);
        ans.insert(rounded % 360);
    }
}

void recurse() {
    if (crash.size() > 0) {
        assert(crash.size() <= 7);
        shoot();
    }

    if (crash.size() + 1 <= 7) {
        for (int i = 0; i < n; ++i) {
            if (crash.size() > 0 and crash.back() == i) continue; // do not add the same mirror consecutively
            crash.push_back(i);
            recurse();
            crash.pop_back();
        }
    }
}

int main(){
    
    //D(reflect(Point(3, 10), Point(-13, 17), Point(-7, 23)) );
    
    while (cin >> n and n > 0) {
        s.resize(n);
        for (int i = 0; i < n; ++i) cin >> s[i].a.x >> s[i].a.y >> s[i].b.x >> s[i].b.y;
        ans.clear();
        crash.clear();
        recurse();

        
        bool first = true;
        for (set<int>::iterator i = ans.begin(); i != ans.end(); ++i) {
            if (!first) cout << " ";
            first = false;
            cout << *i;
        }
        if (ans.size() == 0) cout << "no danger";
        cout << endl;
    }
    return 0;
}