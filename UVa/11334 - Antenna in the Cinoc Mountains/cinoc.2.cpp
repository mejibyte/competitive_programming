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

bool coneSegmentIntersection(const Cone &C, const Antenna &A, const Antenna &B) {
    assert(C.x == 0 and C.y == 0);

    long double u = 1.0 * C.r / C.z;
    // standard cone equation
    long double a, b, c, d, e, f, g, h, i, j, k;
    a = b = 1.0 / (u * u);
    c = -1.0;
    d = e = f = g = h = i = 0.0;
    j = C.z;
    k = -1.0 * C.z * C.z;
    
    long double x1 = B.x, y1 = B.y, z1 = B.z,
                x0 = A.x, y0 = A.y, z0 = A.z;
    
            double aa = a*x1*x1 + b*y1*y1 + c*z1*z1 + 2*d*x1*y1 + 2*e*y1*z1 + 2*f*x1*z1;
            double bb = a*2*x0*x1 + b*2*y0*y1 + c*2*z0*z1 + 2*d*(x1*y0 + x0*y1) + 2*e*(y0*z1 + y1*z0) + 2*f*(x0*z1 + x1*z0) + 2*g*x1 + 2*h*y1 + 2*j*z1;
            double cc = a*x0*x0 + b*y0*y0 + c*z0*z0 + 2*d*x0*y0 + 2*e*y0*z0 + 2*f*x0*z0 + 2*g*x0 + 2*h*y0 + 2*j*z0 + k;

    

    // Now we have a quadratic equation.
    
    // If the three are zero, it means the segment is coincident with the cone.
    assert(cmp(aa, 0) != 0 or cmp(bb, 0) != 0 or cmp(cc, 0) != 0);
    
    double det = bb * bb - 4.0 * aa * cc;
    
    if (cmp(det, 0) < 0) return false;
    
    if (cmp(det, 0) == 0) { // only one solution
        double t0 = -bb / (2 * aa);
        if (cmp(0, t0) <= 0 and cmp(t0, 1) <= 0) return true;
        return false;
    } 
    
    long double t0 = (-bb + sqrt(det)) / (2 * aa);
    long double t1 = (-bb - sqrt(det)) / (2 * aa);
    
    
    if (cmp(0, t0) <= 0 and cmp(t0, 1) <= 0) {
        Point<long double> left(A.x, A.y, A.z);
        Point<long double> right(B.x, B.y, B.z);
        Point<long double> inter = left + t0 * (right - left);
        inter.print();
        return true;
    }
    if (cmp(0, t1) <= 0 and cmp(t1, 1) <= 0) return true;

    return false;
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
            puts("NO");
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
        
        bool good = true;
        for (int i = 0; i < n; ++i) {
            int x = cones[i].x, y = cones[i].y;
            
            cones[i].x -= x, cones[i].y -= y;
            a.x -= x, a.y -= y;
            b.x -= x, b.y -= y;
            
            if (coneSegmentIntersection(cones[i], a, b)) {
                good = false;
                break;
            }
            
            cones[i].x += x, cones[i].y += y;
            a.x += x, a.y += y;
            b.x += x, b.y += y;
            
        }
        
        puts(good ? "YES" : "NO");
    }

    
    return 0;
}