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

const int MAXN = 105;

int X[MAXN], Y[MAXN], Z[MAXN], n;

struct Point {
    double x, y;
    Point(double xx, double yy) : x(xx), y(yy) {}
    Point(){}
    
    bool operator <(const Point &p) const {
		return cmp(x, p.x) < 0 || (cmp(x, p.x) == 0 && cmp(y, p.y) < 0);
	}
};
 
// 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
// Returns a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
double cross(const Point &O, const Point &A, const Point &B) {
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}
 
// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<Point> convex_hull(vector<Point> P) {
	int n = P.size(), k = 0;
	vector<Point> H(2*n);
 
	// Sort points lexicographically
	sort(P.begin(), P.end());
 
	// Build lower hull
	for (int i = 0; i < n; i++) {
		while (k >= 2 && cmp(cross(H[k-2], H[k-1], P[i]), 0) <= 0) k--;
		H[k++] = P[i];
	}
 
	// Build upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cmp(cross(H[k-2], H[k-1], P[i]), 0) <= 0) k--;
		H[k++] = P[i];
	}
 
	H.resize(k);
	return H;
}

double get_area(int z) {
    vector<Point> points;
    
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (Z[i] == Z[j] and Z[i] == z){ // caso especial
                points.push_back(Point(X[i], Y[i]));
                points.push_back(Point(X[j], Y[j]));
                continue;
            }
            
            if ( (Z[i] <= z and Z[j] >= z) or (Z[i] >= z and Z[j] <= z) ) {
                double t = 1.0 * (z - Z[i]) / (Z[j] - Z[i]);
                double x = X[i] + t * (X[j] - X[i]);
                double y = Y[i] + t * (Y[j] - Y[i]);
                points.push_back(Point(x, y));
            }
        }
    }
    
    // Hallar el área del convex hull de points
    points = convex_hull(points);
    
    double ans = 0.0;
    for (int i = 0; i + 1 < points.size(); ++i) {
        int j = i + 1;
        
        ans += points[i].x * points[j].y - points[i].y * points[j].x;
    }
    return fabs(ans) / 2;
}

void solve() {
    int zmin, zmax; cin >> zmin >> zmax;
    for (int i = 0; i < n; ++i) {
        cin >> X[i] >> Y[i] >> Z[i];
    }
    for (int z = zmin; z <= zmax; ++z) {
        double ans = get_area(z);
        printf("%.10lf\n", ans);
    }
}

int main(){
    bool first = true;
    while (cin >> n) {
        if (!first) puts("");
        first = false;
        solve();
    }
    return 0;
}