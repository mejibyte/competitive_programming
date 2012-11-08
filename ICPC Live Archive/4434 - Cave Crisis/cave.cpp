// Andrés Mejía
// Live Archive 4434
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

typedef long double Double;

struct Point {
    Double x, y, z;
    Point(){}
    Point(Double x, Double y, Double z = 0.0) : x(x), y(y), z(z) {}
    
    // Dot product
    Double operator * (const Point &p) const {
        return x*p.x + y*p.y + z*p.z;
    }
        
    Point operator - (const Point &p) const {
        return Point(x - p.x, y - p.y, z - p.z);
    }
    
    Point operator + (const Point &p) const {
        return Point(x + p.x, y + p.y, z + p.z);
    }
    
    Double length() const {
        return sqrtl(*this * *this);
    }
    
    void print() const {
        printf("(%Lf, %Lf, %Lf)", x, y, z);
    }
};

// Scalar * vector product
Point operator * (Double t, const Point &p) {
    return Point(t * p.x, t * p.y, t * p.z);
}

typedef vector<Point> Polygon;


const int MAXN = 110;
Polygon polys[MAXN];
Double g[MAXN][MAXN];


// Returns the shortest distance from point p to the segment from a to b.
// This works on 2D and 3D.
Double distance_point_to_segment(const Point &a, const Point &b, const Point &p) {
    Point u = b - a;
    Point v = p - a;
    Double t = (u * v) / (u * u);
    if (t < 0.0) t = 0.0;
    if (t > 1.0) t = 1.0;
    // Actual intersection point is a + t*(b - a).
    Point boom = a + t*u;
    return (boom - p).length();
}

// Returns the shortest distance between any point in the segment
// from a1 to b1 and any point in the segment from a2 to b2.
// Works in 3D.
Double distance_between_segments(const Point &a1, const Point &b1, const Point &a2, const Point &b2) {
    Point u = b1 - a1;
    Point v = b2 - a2;
    Point w = a1 - a2;

    Double a = u * u;
    Double b = u * v;
    Double c = v * v;
    Double d = u * w;
    Double e = v * w;
    
    Double den = a*c - b*b;
    Double t1, t2;

    if (cmp(den, 0.0) == 0) { // the lines are parallel
        t1 = 0;
        t2 = d / b;
    } else {
        t1 = (b * e - c * d) / den;
        t2 = (a * e - b * d) / den;
    }
    
    // The shortest distance between the two infinite lines happens from
    // p = a1 + t1 * (b1 - a1) on segment 1 and
    // and q = a2 + t2 * (b2 - a2) on segment 2.
    
    if (0 <= t1 and t1 <= 1 and 0 <= t2 and t2 <= 1) {
        // We were lucky, the closest distance between the two infinite
        // lines happens right inside both segments.
        Point p = a1 + t1 * u;
        Point q = a2 + t2 * v;
        return (p - q).length();
    } else {
        Double option1 = min(distance_point_to_segment(a1, b1, a2), distance_point_to_segment(a1, b1, b2));
        Double option2 = min(distance_point_to_segment(a2, b2, a1), distance_point_to_segment(a2, b2, b1));
        return min(option1, option2);
    }
}

Double distance_between_polygons(const Polygon &a, const Polygon &b) {
    Double ans = 1e18;
    for (int i = 0; i < a.size(); ++i) {
        int ii = (i + 1) % a.size();
        for (int j = 0; j < b.size(); ++j) {
            int jj = (j + 1) % b.size();
            ans = min(ans, distance_between_segments(a[i], a[ii], b[j], b[jj]));
        }
    }
    return ans;
}


bool visited[MAXN];
void dfs(int u, Double tolerance, int n) {
    if (visited[u]) return;
    visited[u] = true;
    for (int v = 0; v < n; ++v) {
        if (cmp(g[u][v], tolerance) <= 0) dfs(v, tolerance, n);
    }
}

bool blocked(Double tolerance, int n) {
    fill(visited, visited + n, false);
    dfs(n - 2, tolerance, n);
    return visited[n - 1];
}

#include <iomanip>

int main(){
    int W, N;
    while (cin >> W >> N) {
        if (W == 0 and N == 0) break;
        for (int i = 0; i < N; ++i) {
            int size; cin >> size;
            polys[i].resize(size);
            for (int k = 0; k < size; ++k) {
                cin >> polys[i][k].x >> polys[i][k].y;
                polys[i][k].z = 0.0;
            }
        }
        
        Double h = W / 2.0;
        
        // Ceiling
        polys[N].clear();
        polys[N].push_back(Point(0, h));
        polys[N].push_back(Point(1000, h));
        polys[N].push_back(Point(1000, h + 1));
        polys[N].push_back(Point(0, h + 1));
        N++;
        
        // Floor
        polys[N].clear();
        polys[N].push_back(Point(0, -h - 1));
        polys[N].push_back(Point(1000, -h - 1));
        polys[N].push_back(Point(1000, -h));
        polys[N].push_back(Point(0, -h));
        N++;
        
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                g[i][j] = g[j][i] = distance_between_polygons(polys[i], polys[j]);
            }
            g[i][i] = 0;
        }
        
        
        if (blocked(0.0, N)) {
            cout << "impossible" << endl;
        } else {
            Double low = 0, high = W;
            
            // The robot is forced to start at (0, 0), so he can't start touching anything.
            for (int k = 0; k < N; ++k) {
                for (int i = 0; i < polys[k].size(); ++i) {
                    int ii = (i + 1) % polys[k].size();
                    high = min(high, 2*distance_point_to_segment(polys[k][i], polys[k][ii], Point(0, 0)));
                }
            }
            
            for (int k = 0; k < 150; ++k) {
                Double mid = (low + high) / 2;
                if (blocked(mid, N)) {
                    high = mid;
                } else {
                    low = mid;
                }
            }
            cout << setprecision(2) << fixed << low / 2 << endl;
        }
    }
    
    return 0;
}