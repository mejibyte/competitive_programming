using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

#define D(x) cout << #x " = " << (x) << endl

typedef long double Double;

struct Point {
    long double x, y;
    Point(){}
    Point(long double x, long double y) : x(x), y(y) {}
    
    void print() {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};

long double distsqr(const Point &a, const Point &b) {
    long double dx = a.x - b.x;
    long double dy = a.y - b.y;
    return dx * dx + dy * dy;
}

Point reflect(Point p, const Point a, const Point b) {
    // refleja el punto p al otro lado de la recta ab
    long double u = ((p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y)) / distsqr(a, b);
    Point v; // Intersection
    v.x = a.x + u*(b.x - a.x);
    v.y = a.y + u*(b.y - a.y);
    
    p.x += 2*(v.x - p.x);
    p.y += 2*(v.y - p.y);
    return p;
}

struct Segment {
    Point a, b;
} s[8];

set<int> ans;
int n;

const long double pi = 2 * acos(0);

vector<Segment> crash; vector<int> crashID;

const double EPS = 1e-9;

pair<bool, long double> segment_intersection(Point p0, Point p1, Point p2, Point p3) {
    double t0 = (p3.y - p2.y)*(p0.x - p2.x)-(p3.x-p2.x)*(p0.y - p2.y);
    double t1 = (p1.x - p0.x)*(p2.y - p0.y)-(p1.y-p0.y)*(p2.x - p0.x);
    double det = (p1.y -p0.y)*(p3.x - p2.x)-(p3.y-p2.y)*(p1.x - p0.x);
    if (fabs(det) < EPS){ 
        return make_pair(false, -1);
    }
    t0 /= det;
    t1 /= det;

    if (t1 < 0 or t1 > 1) return make_pair(false, -1);
    return make_pair(true, t0);
}

pair<int, Point> getNext(Point p, Point q) {
    
    long double minT = 1e100;
    int who = -1;
        
    for (int i = 0; i < n; ++i) {
        pair<bool, long double> boom = segment_intersection(p, q,  s[i].a, s[i].b);
        if (!boom.first) continue;
        if (boom.second < minT) {
            minT = boom.second;
            who = i;
        }
    }
    return who;    
}

void simulate(double angle) {
    Point p(0, 0);
    Point q(cos(angle), sin(angle));

    int next = 0;
    while (next < crashID.size()) {
        int who = getNext(p, q);
        if (who != crashID[next]) return;
    
        
    }
    
}

void shoot() {
    
    Point origin(0, 0);
    for (int i = 0; i < crash.size(); ++i) {
        Segment axis = crash[i];

        for (int j = i + 1; j < crash.size(); ++j) {
            crash[j].a = reflect(crash[j].a, axis.a, axis.b);
            crash[j].b = reflect(crash[j].b, axis.a, axis.b);            
        }
        origin = reflect(origin, axis.a, axis.b);
    }
    
    double angle = atan2(origin.y, origin.x);
    while (angle < 0) angle += 2*pi;
    while (angle > 2*pi) angle -= 2*pi;
    
    double degrees = angle * 180 / pi;
    //ans.insert((int)round(degrees));
    simulate(angle);
}

void recurse() {
    if (crash.size() > 0) {
        assert(crash.size() <= 7);
        shoot();
    }
    
    if (crash.size() + 1 < 7) {
        for (int i = 0; i < n; ++i) {
            crash.push_back(s[i]);
            crashID.push_back(i);
            recurse();
            crash.pop_back();
            crashID.pop_back();
        }
    }
}

int main(){
    //Point p = reflect(Point(0, 5), Point(-1, 6), Point(+1, 5));
    //p.print();

    while (cin >> n and n > 0) {
        for (int i = 0; i < n; ++i) cin >> s[i].a.x >> s[i].a.y >> s[i].b.x >> s[i].b.y;
        ans.clear();
        crash.clear();
        recurse();
        for (set<int>::iterator i = ans.begin(); i != ans.end(); ++i) {
            cout << *i << endl;
        }
    }
    return 0;
}
