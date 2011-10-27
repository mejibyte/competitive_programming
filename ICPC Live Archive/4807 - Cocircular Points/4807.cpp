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

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

struct point {
    double x, y;
    point(double x, double y) : x(x), y(y) {}
    point(){}
    bool operator < (const point &p) const {
        int t = cmp(this->x, p.x);
        if (t != 0) return t < 0;
        return cmp(this->y, p.y) < 0;
    }
};

point center(const point &p, const point &q, const point &r) {
    double ax = q.x - p.x;
    double ay = q.y - p.y;
    double bx = r.x - p.x;
    double by = r.y - p.y;
    double d = ax*by - bx*ay;
    
    if (cmp(d, 0) == 0) {
        printf("p = <%lf, %lf>, q = <%lf, %lf>, r = <%lf, %lf>\n", p.x, p.y, q.x, q.y, r.x, r.y);
        printf("Points are collinear!\n");
        assert(false);
    }
    
    double cx = (q.x + p.x) / 2;
    double cy = (q.y + p.y) / 2;
    double dx = (r.x + p.x) / 2;
    double dy = (r.y + p.y) / 2;
    
    double t1 = bx*dx + by*dy;
    double t2 = ax*cx + ay*cy;
    
    double x = (by*t2 - ay*t1) / d;
    double y = (ax*t1 - bx*t2) / d;

    return point(x, y);
}

point points[105];

int main(){
    int n;
    while (scanf("%d", &n) == 1) {
        if (n == 0) break;
        
        for (int i = 0; i < n; ++i) {
            scanf("%lf %lf", &points[i].x, &points[i].y);
        }
        
        if (n <= 2) {
            printf("%d\n", n);
            continue;
        }
        
        int ans = 2;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                map<point, int> times;
                for (int k = 0; k < n; ++k) {
                    if (k == i or k == j) continue;
                    double x0 = points[i].x - points[k].x;
                    double y0 = points[i].y - points[k].y;
                    double x1 = points[j].x - points[k].x;
                    double y1 = points[j].y - points[k].y;
                    if ( cmp(x0*y1 - y0*x1, 0) == 0 ) continue; // collinear
                    point c = center(points[i], points[j], points[k]);
                    times[c]++;
                    ans = max(ans, times[c] + 2);
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}