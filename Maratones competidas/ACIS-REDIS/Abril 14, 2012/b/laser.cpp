// Andrés Mejía

// Accepted, but trying to make it faster.

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
    double x, y;
    Point(){}
    Point(double x, double y) : x(x), y(y) {}
    
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
    double operator ^(const Point &b) const {
        return  x * b.x + y * b.y;
    }
    
    double length() {
        return sqrt(x * x + y * y);
    }
    
    void normalize() {
        double d = length();
        x /= d;
        y /= d;
    }
    
    Point normal() const {
        Point ans(-y, x);
        ans.normalize();
        return ans;
    }
};

Point operator * (double scalar, const Point &a) {
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
    double t0, t1;
    Point where;
};

ostream &operator << (ostream &out, const Intersection &boom) {
    out << "(valid = " << boom.valid << ", t0 = " << boom.t0 << ", t1 = " << boom.t1 << ", where = " << boom.where << ")";
    return out;
}



void reflect(Point &p, const Point &a, const Point &b) {
    // refleja el punto p al otro lado de la recta ab
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double u = ((p.x - a.x) * dx + (p.y - a.y) * dy) / (dx * dx + dy * dy);
    p.x += 2*(a.x + u * dx - p.x);
    p.y += 2*(a.y + u * dy - p.y);
}


Segment s[7];
int crash[7], crashSize;
bool ans[360];
int n;

const double pi = 2 * acos(0);

Intersection get_intersection(const Point &p0, const Point &p1, const Point &p2, const Point &p3) {
    Intersection ans;
    
    double p10x = p1.x - p0.x;
    double p10y = p1.y - p0.y;
    double p32x = p3.x - p2.x;
    double p32y = p3.y - p2.y;
    
    ans.t0 = p32y * (p0.x - p2.x) - p32x * (p0.y - p2.y);
    ans.t1 = p10x * (p2.y - p0.y) - p10y * (p2.x - p0.x);
    double det = (p1.y - p0.y) * p32x - p32y * (p1.x - p0.x);
    if (cmp(det, 0) == 0){ 
        ans.valid = false;
    } else {
        ans.t0 /= det;
        ans.t1 /= det;
        ans.where.x = p0.x + ans.t0 * p10x;
        ans.where.y = p0.y + ans.t0 * p10y;
        ans.valid = true;
    }
    return ans;
}

void reflect_ray(Point &dir, const Segment &mirror) {
    Point normal = (mirror.b - mirror.a);
    swap(normal.x, normal.y);
    normal.x *= -1;
    normal.normalize();
    
    long double dot = 2 * (dir ^ normal);
    dir.x -= dot * normal.x;
    dir.y -= dot * normal.y;
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
    // assert(cmp(direction.length(), 1) == 0); // commented out for efficiency
    
    for (int i = 0; i < crashSize; ++i) {
        // shoot the ray from here and check it hits the mirror
        const Segment &mirror = s[crash[i]];
        Intersection boom = get_intersection(pos, pos + direction, mirror.a, mirror.b);
        
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
        reflect_ray(direction, mirror);
    }
    // finally check that the path back home is free
    if (obstacle_in_the_way(pos, Point(0, 0), 1 << crash[crashSize - 1])) {
        return false;
    }
    
    // (0, 0), pos and pos + dir must be collinear
    //assert( cmp( (pos.x - direction.x) * pos.y - (pos.y - direction.y) * pos.x, 0) == 0 ); // commented out for efficiency
    
    // now (0, 0) must be along the ray (pos, pos + direction). The parameter must be positive to travel forward.
    double t = cmp(direction.x, 0) > 0 ? -pos.x / direction.x : -pos.y / direction.y;
    if (t < 0) return false; // would have to travel backwards
    
    return true;
}

void shoot() {
    Point origin(0, 0);
    for (int i = crashSize - 1; i >= 0; --i) {
        const Segment &axis = s[crash[i]];
        reflect(origin, axis.a, axis.b);
    }
        
    double angle = atan2(origin.y, origin.x);
    while (angle < 0) angle += 2*pi;
    while (angle >= 2*pi) angle -= 2*pi;

    double degrees = angle * 180 / pi;
    int rounded = (int)round(degrees);
    rounded %= 360;
    if (ans[rounded]) return; // we checked it already, let's move on.
    if (check(angle)) {
        ans[rounded] = true;
    }
}

void recurse() {
    if (crashSize > 0) {
        // assert(crash.size() <= 7);
        shoot();
    }

    if (crashSize < 7) {
        for (int i = 0; i < n; ++i) {
            if (crashSize > 0 and crash[crashSize - 1] == i) continue; // do not add the same mirror consecutively
            crash[crashSize++] = i;
            recurse();
            crashSize--;
        }
    }
}

int main(){
    assert( freopen("laser.in", "r", stdin) != NULL );
    while (scanf("%d", &n) == 1 and n > 0) {
        for (int i = 0; i < n; ++i) assert(scanf("%lf %lf %lf %lf", &s[i].a.x, &s[i].a.y, &s[i].b.x, &s[i].b.y) == 4);
        
        memset(ans, 0, sizeof ans);
        crashSize = 0;
        recurse();

        bool first = true;
        int cnt = 0;
        for (int i = 0; i < 360; ++i) if (ans[i]) {
            if (!first) printf(" ");
            first = false;
            printf("%d", i);
            cnt++;
        }
        if (cnt == 0) printf("no danger");
        puts("");
    }
    return 0;
}