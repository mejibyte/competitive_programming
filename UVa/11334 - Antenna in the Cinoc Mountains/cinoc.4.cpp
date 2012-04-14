// Andrés Mejía

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


template<typename T> struct Point {
    T x, y, z;
    
    Point(T x, T y, T z) : x(x), y(y), z(z) {}
    Point(){}
    
    void print() {
        cout << "(" << x << ", " << y << ", " << z << ")" << endl;
    }
    
    // dot product
    T operator ^(const Point<T> other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    
    // sum
    Point<T> operator +(const Point<T> other) const {
        Point<T> ans(x + other.x, y + other.y, z + other.z);
        return ans;
    }
    
    // difference
    Point<T> operator -(const Point<T> other) const {
        Point<T> ans(x - other.x, y - other.y, z - other.z);
        return ans;
    }
    
    
    Point<T> operator *=(T scalar) {
        x *= scalar; y *= scalar; z *= scalar;
    }
    
    Point<T> operator -() const {
        Point<T> ans(-x, -y, -z);
        return ans;
    }
    
};

template<typename T> Point<T> operator * (T scalar, Point<T> p) {
    return Point<T>(p.x * scalar, p.y * scalar, p.z * scalar);
}

const int MAXN = 55;

struct Cone {
    int x, y, z, r;
    
    void print() {
        printf("(x = %d, y = %d, z = %d, r = %d)\n", x, y, z, r);
    }
} cones[MAXN];

struct Antenna {
    int x, y, z;
    
    // difference
    Antenna operator -(const Antenna &other) const {
        Antenna ans;
        ans.x = x - other.x;
        ans.y = y - other.y;
        ans.z = z - other.z;
        return ans;
    }
    
    void print() {
        printf("(x = %d, y = %d, z = %d)\n", x, y, z);
    }
    
};

inline long double sqr(long double x) {
    return x * x;
}

bool coneSegmentIntersection(Cone C, Point<long double> A, Point<long double> B) {
    // printf("Intersecting cone: "); C.print();
    // printf("  with segment A = "); A.print();
    // printf("               B = "); B.print();
    
    long double height = C.z;
    
    A.x -= C.x, A.y -= C.y, A.z -= C.z;
    B.x -= C.x, B.y -= C.y, B.z -= C.z;
    
    // printf("After moving the segment:\n");
    // printf("    A = "); A.print();
    // printf("    B = "); B.print();

    long double u = C.r / height;
    
    long double dx = B.x - A.x, dy = B.y - A.y, dz = B.z - A.z;
    
    double aa = dx*dx + dy*dy - u*u*dz*dz;
    double bb = 2*dx*A.x + 2*dy*A.y - 2*u*u*dz*A.z;
    double cc = A.x*A.x + A.y*A.y - u*u*A.z*A.z;

    // Now we have a quadratic equation.
    
    // If the three are zero, it means the segment is coincident with the cone.
    assert(cmp(aa, 0) != 0 or cmp(bb, 0) != 0 or cmp(cc, 0) != 0);
    
    double det = bb * bb - 4.0 * aa * cc;
    
    if (cmp(det, 0) < 0) return false; // no intersection
    
    vector< long double > solutions;
    
    if (cmp(det, 0) == 0) { // only one solution
        long double t0 = -bb / (2 * aa);
        solutions.push_back(t0);
    } else {    
        long double t0 = (-bb + sqrt(det)) / (2 * aa);
        long double t1 = (-bb - sqrt(det)) / (2 * aa);
        solutions.push_back(t0);
        solutions.push_back(t1);
    }
    
    for (int i = 0; i < solutions.size(); ++i) {
        long double t = solutions[i];
        if (cmp(0, t) <= 0 and cmp(t, 1) <= 0) { // inside the segment
            Point<long double> inter = A + t * (B - A);
            if (cmp(-height, inter.z) <= 0 and cmp(inter.z, 0) <= 0) {
                return true;
            }
        }
    }
    
    return false;
}

bool insideCone(Cone c, Antenna a) {
    long double dx = a.x - c.x;
    long double dy = a.y - c.y;
    
    long double d = sqrt(dx * dx + dy * dy);

    if (cmp(d, c.r) > 0) return false; // The distance from the antenna to the center of the cone is more than the radius
    
    long double p = (c.r - d) / c.r * c.z;
    
    return cmp(a.z, p) <= 0;
}

int main(){
    int n;
    while (cin >> n) {
        if (n == -1) break;
        
        for (int i = 0; i < n; ++i) {
            cin >> cones[i].x >> cones[i].y >> cones[i].z >> cones[i].r;
        }
        Antenna a, b;
        cin >> a.x >> a.y >> a.z >> b.x >> b.y >> b.z;

        if (a.z == 0 or b.z == 0) { // One of the antennas touches the floor
            puts("No");
            continue;
        }
        
        assert(a.x != b.x or a.y != b.y); // The antennas must be at different places

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                assert(cones[i].x != cones[j].x or cones[i].y != cones[j].y); // The cones have different centers
            }
        }
        
        for (int i = 0; i < n; ++i) {
            assert(cones[i].r > 0); // All mountains have positive radius
            assert(cones[i].z > 0);
        }
        
        Point<long double> pa, pb;
        pa.x = a.x, pa.y = a.y, pa.z = a.z;
        pb.x = b.x, pb.y = b.y, pb.z = b.z;

        bool good = true;
        
        for (int i = 0; i < n; ++i) {
            if (insideCone(cones[i], a) or insideCone(cones[i], b)) {
                good = false;
            }
        }
        
        for (int i = 0; i < n and good; ++i) {
            if (coneSegmentIntersection(cones[i], pa, pb)) {
                //puts("Boom!");
                good = false;
                break;
            }            
        }
        
        puts(good ? "Yes" : "No");
    }

    
    return 0;
}