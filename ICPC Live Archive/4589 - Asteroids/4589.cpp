// Andrés Mejía
// Accepted on Live Archive.

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
#include <iomanip>
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
inline int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

#define assert(...)

struct Point {
    double x, y, z;
    Point(){} Point(double x, double y, double z) : x(x), y(y), z(z) {}
    
    static Point read() {
        double x, y, z;
        scanf("%lf %lf %lf", &x, &y, &z);
        return Point(x, y, z);
    }
    
    Point operator - (const Point &t) const {
        return Point(x - t.x, y - t.y, z - t.z);
    }
    Point operator * (const Point &t) const {
        double nx = +(y * t.z - t.y * z);
        double ny = -(x * t.z - t.x * z);
        double nz = +(x * t.y - t.x * y);
        return Point(nx, ny, nz);
    }
    
    double operator ^ (const Point &t) const {
        return x * t.x + y * t.y + z * t.z;
    }
    
    Point operator -() const {
        return Point(-x, -y, -z);
    }

    double length() const {
        return sqrt(x * x + y * y + z * z);
    }
    void normalize() {
        double m = length();
        x /= m, y /= m, z /= m;
    }
};

struct Plane {
    double a, b, c, d;
    Plane(){}
    Plane(const Point &p1, const Point &p2, const Point &p3) {
        Point normal = (p2 - p1) * (p3 - p1);
        normal.normalize();
        if (cmp(normal.x, 0) < 0 or
            cmp(normal.x, 0) == 0 and cmp(normal.y, 0) < 0 or
            cmp(normal.x, 0) == 0 and cmp(normal.y, 0) == 0 and cmp(normal.z, 0) < 0) {
                normal = -normal;
        }
        
        a = normal.x, b = normal.y, c = normal.z;
        d = -(normal ^ p1);
        assert(cmp(d, -(normal ^ p2)) == 0);
        assert(cmp(d, -(normal ^ p3)) == 0);
    }
    
    bool operator < (const Plane &t) const {
        int k = cmp(a, t.a);
        if (k != 0) return k < 0;
        k = cmp(b, t.b);
        if (k != 0) return k < 0;
        k = cmp(c, t.c);
        if (k != 0) return k < 0;
        k = cmp(d, t.d);
        return k < 0;
    }
    
    double distance(const Point &p) {
        return (Point(a, b, c) ^ p) + d;
    }
    
    int side(const Point &p) {
        return cmp(distance(p), 0);
    }
};

typedef vector<Point> Face;

struct AngleComparator {
    Point pivot;
    AngleComparator(const Point &pivot) : pivot(pivot) {}
    bool operator() (const Point &p1, const Point &p2) {
        Point u = p1 - pivot;
        Point v = p2 - pivot;
        double cross = +(u.y * v.z - v.y * u.z)
                       -(u.x * v.z - v.x * u.z)
                       +(u.x * v.y - v.x * u.y);
        
        int k = cmp(cross, 0);

        return k > 0;
    }
};

struct Polyhedron {
    vector<Point> v; // vertices
    
    static Polyhedron read() {
        int n;
        if (scanf("%d", &n) != 1) exit(0);
        Polyhedron p;
        p.v.resize(n);
        for (int i = 0; i < n; ++i) {
            p.v[i] = Point::read();
        }
        return p;
    }
    
    vector<Face> buildFaces() {
        set<Plane> seen;
        int n = v.size();
        
        vector<Face> ans;
        
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    Plane p(v[i], v[j], v[k]);
                    if (seen.count(p) > 0) continue;

                    seen.insert(p);
                    Face f;
                    bool positive = false, negative = false;
                    for (int l = 0; l < n; ++l) {
                        int side = p.side(v[l]);
                        positive |= (side > 0);
                        negative |= (side < 0);
                        if (side == 0) {
                            f.push_back( v[l] );
                        }
                    }
                    
                    if (not (positive and negative)) {
                        assert(f.size() >= 3);
                        AngleComparator comp(f[0]);
                        sort(f.begin() + 1, f.end(), comp);
                        ans.push_back( f );
                    }
                }
            }
        }
        return ans;
    }
    
    double tetrahedronVolume(const Point &p1, const Point &p2, const Point &p3, const Point &p4) {
        Point u = p2 - p1;
        Point v = p3 - p1;
        Point w = p4 - p1;
        double vol = abs((w ^ (u * v))) / 6.0;
        assert(cmp(vol, 0) >= 0);
        return vol;
    }
    
    Point tetrahedronCentroid(const Point &p1, const Point &p2, const Point &p3, const Point &p4) {
        return Point((p1.x + p2.x + p3.x + p4.x) / 4.0, 
                     (p1.y + p2.y + p3.y + p4.y) / 4.0, 
                     (p1.z + p2.z + p3.z + p4.z) / 4.0);
    }
    
    Point centerOfMass(const vector<Face> &faces) {
        Point p1 = v[0];
        double cx = 0, cy = 0, cz = 0;
        double totalVolume = 0;
        
        int m = faces.size();
        for (int k = 0; k < m; ++k) {
            const Face &f = faces[k];
            Point p2 = f[0];
            
            for (int i = 1; i + 1 < f.size(); ++i) {
                Point p3 = f[i];
                Point p4 = f[i + 1];
                double v = tetrahedronVolume(p1, p2, p3, p4);
                Point c = tetrahedronCentroid(p1, p2, p3, p4);
                
                cx += c.x * v;
                cy += c.y * v;
                cz += c.z * v;
                totalVolume += v;
            }
        }
        
        assert(cmp(totalVolume, 0) > 0);
        cx /= totalVolume;
        cy /= totalVolume;
        cz /= totalVolume;
        
        return Point(cx, cy, cz);
    }
    
    double minDistance() {
        vector<Face> faces = buildFaces();
        assert(faces.size() > 2);
        Point c = centerOfMass(faces);
        // printf("Center of mass = (%.0lf, %.0lf, %.0lf)\n", c.x, c.y, c.z);
        double ans = 1e100;
        
        for (int k = 0; k < faces.size(); ++k) {
            const Face &f = faces[k];
            
            Plane p(f[0], f[1], f[2]);
            ans = min(ans, abs(p.distance(c)));
        }
        return ans;
    }
};

int main(){
    while (true) {
        Polyhedron a = Polyhedron::read(), b = Polyhedron::read();
        printf("%.5lf\n", a.minDistance() + b.minDistance());
    }
    return 0;
}