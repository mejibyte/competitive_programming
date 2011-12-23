// Andrés Mejía
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

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-10;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
const double PI = 2 * acos(0);
const double E = exp(1.0);

////////////////////////// Solution starts below. //////////////////////////////

struct Point {
	double x, y, z;
	Point(){}
	Point(double x, double y, double z) : x(x), y(y), z(z) {}
	Point plus(Point p) const { return Point(x + p.x, y + p.y, z + p.z); }
	Point minus(Point p) const { return Point(x - p.x, y - p.y, z - p.z); }
	double dot(Point p) const { return x * p.x + y * p.y + z * p.z; }
	Point cross(Point p) const { return Point(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x );}
	double norm() const { return sqrt(dot(*this)); }
	Point scale(double a) const { return Point(x * a, y * a, z * a); }
	double normM() { 
        Point magic(E, PI, E * PI);
	    return dot(*this) * cmp(dot(magic), 0); 
	}

	double angle(Point c, Point base) const {
		Point p = minus(c);
		return atan2(p.cross(base).normM(), p.dot(base));
	}
	
	bool operator == (const Point &p) const {
        return cmp(x, p.x) == 0 and cmp(y, p.y) == 0 and cmp(z, p.z) == 0;
	}
	
	bool operator < (const Point &p) const {
        return cmp(x, p.x) < 0 ||
               cmp(x, p.x) == 0 and cmp(y, p.y) < 0 ||
               cmp(x, p.x) == 0 and cmp(y, p.y) == 0 and cmp(z, p.z) < 0;
	}
};


struct Averager {
    Point p;
    double w;
    
    Averager() : p(0, 0, 0), w(0) {}
    
    void add(Point dp, double dw) {
        p = p.plus(dp.scale(dw));
        w += dw;
    }
    
    Point get(double a) {
        return p.scale(a / w);
    }
};

Point normal(Point p1, Point p2, Point p3) {
	return p1.minus(p2).cross(p3.minus(p2));
}

vector<Point> on(vector<Point> points, int i, int j, int k) {
    Point norm = normal(points[j], points[i], points[k]);
    double d = norm.dot(points[i]);
    bool neg = false;
    bool pos = false;
    vector<Point> on;
    for (int q = 0; q < points.size(); q++) {
        double dist = norm.dot(points[q]) - d;
        if (abs(dist) < EPS) {
            on.push_back(points[q]);
        } else if ((neg |= dist < 0) & (pos |= dist > 0)) {
            return vector<Point>();
        }
    }
    return on;
}



struct AngleComparator {
    Point c, base;
    AngleComparator(Point c, Point base) : c(c), base(base) {}
    bool operator () (const Point &p1, const Point &p2) const {
        return cmp( p1.angle(c, base), p2.angle(c, base) ) < 0;
    }
};


double calcDist() {
    int n; scanf("%d", &n);
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        int x, y, z; scanf("%d %d %d", &x, &y, &z);
        points[i] = Point(x, y, z);
    }
    vector< vector<Point> > faces;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                vector<Point> face = on(points, i, j, k);
                if (face.size() > 0 && face[2] == points[k]) {
                    faces.push_back(face);
                }
            }
        }
    }
    Point first = points[0];
    Averager mma;
    for (int k = 0; k < faces.size(); ++k) {
        vector<Point> face = faces[k];
        Averager ca;
        for (int kk = 0; kk < face.size(); ++kk) {
            ca.add(face[kk], 1);
        }
        Point c = ca.get(1);
        Point base = face[0].minus(c);
        AngleComparator angleComparator(c, base);
        sort(face.begin(), face.end(), angleComparator);

        int f = face.size();
        Averager ma;
        for (int q = 0; q < f; q++) {
            Point p1 = face[q].minus(c);
            Point p2 = face[(q + f - 1) % f].minus(c);
            ma.add(p1.plus(p2), p1.cross(p2).norm());
        }
        
        Point mc = ma.get(1.0 / 3).plus(c).minus(first);
        Point norm = normal(face[0], face[1], face[2]);
        mma.add(mc, abs(ma.w * norm.dot(mc)) / norm.norm());
    }
    Point mmc = mma.get(3.0 / 4).plus(first);
    // printf("mmc = (%.0lf, %.0lf, %.0lf)\n", mmc.x, mmc.y, mmc.z);
    
    double ans = 1e100;
    for (int k = 0; k < faces.size(); ++k) {
        const vector<Point> &face = faces[k];
        Point norm = normal(face[0], face[1], face[2]);
        ans = min(ans, abs(norm.dot(mmc) - norm.dot(face[0])) / norm.norm());
    }
    return ans;
}


int main(){
    double ans = calcDist() + calcDist();
    printf("%.10lf\n", ans);
    return 0;
}