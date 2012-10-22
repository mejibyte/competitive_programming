// Andrés Mejía

// This gives correct answers, but is too slow.

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

#include <iomanip>

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << setprecision(14) << fixed << #x " is " << (x) << endl

const long double EPS = 1e-9;
int cmp(long double x, long double y = 0, long double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

struct Point {
    int x, y;
    
    Point(int xx, int yy) : x(xx), y(yy) {}
    Point(){}
    
    void read() {
        cin >> x >> y;
    }
    
    void print() const {
        printf("(%d, %d)\n", x, y);
    }
    
    long double length() const {
        return sqrtl(1.0*x*x + 1.0*y*y);
    }
    
    Point operator - (const Point &other) const {
        return Point(x - other.x, y - other.y);
    }
};

long double dot(const Point &a, const Point &b) {
    return 1.0*a.x*b.x + 1.0*a.y*b.y;
}

long double dist(const Point &a, const Point &b) {
    long double dx = a.x - b.x;
    long double dy = a.y - b.y;
    return sqrtl(dx*dx + dy*dy);
}

const long double PI = 2*acos(0);

long double shortcut(const Point &p1, const Point &pivot, const Point &p2, int m) {
    return 0.0;
    
    if (m == 0) return 0.0;

    long double a = dist(p1, pivot), b = dist(p2, pivot);
    if (a > b) swap(a, b);
    
    assert( (p1 - pivot).length() > 0 );
    assert( (p2 - pivot).length() > 0 );
    long double theta = acosl(dot(p1 - pivot, p2 - pivot) / (p1 - pivot).length() / (p2 - pivot).length());

    // the bridge is longer that both sides
    if (cmp(m, b) >= 0) return 0;

    if (cmp(m, dist(p1, p2)) > 0) {
        // My only option is to build the bridge from the longer leg (b) to the shorter leg (a)
        
        // This is the ambiguous case of the law of sines
        long double beta = PI - asinl(b * sinl(theta) / m);
        long double alpha = PI - theta - beta;
        long double d = m * sinl(alpha) / sinl(theta);
        
        assert(cmp(d, a) <= 0);        
        return b + d - m;
    }
    
    if (cmp(m, dist(p1, p2)) == 0) return a + b - m;

    //assert( sinl(theta / 2.0) > 0 );
    long double d = m / 2.0 / sinl(theta / 2.0);
    
    
    if (cmp(d, a) <= 0) {
        return 2*d - m;
    }
    
    long double alpha = asinl( sinl(theta) * a / m );
    long double beta = PI - theta - alpha;
    
    d = sinl(beta) * m / sinl(theta);

    return a + d - m; 
}

long double dp[55][3005];

int main(){
    int n, m, run = 1;
    while (cin >> n >> m) {
        if (n == 0 and m == 0) break;
        
        vector<Point> points(2*n + 1);
        for (int i = 0; i < 2*n + 1; ++i) points[i].read();
        
        
        for (int p = 0; p <= m; ++p) {
            dp[n][p] = 0.0;
        }
        for (int i = n - 1; i >= 0; --i) {
            const Point &a = points[2 * i], &b = points[2 * i + 1], &c = points[2 * i + 2];
            
            for (int p = 0; p <= m; ++p) {
                dp[i][p] = 0.0;
                for (int take = 0; take <= p; ++take) {
                    long double option = dp[i + 1][p - take] + shortcut(a, b, c, take);
                    if (option > dp[i][p]) dp[i][p] = option;
                }
            }
        }
        
        printf("Case %d: ", run++);
        
        long double best = -1; int used = 0;
        for (int p = 0; p <= m; ++p) {
            if (cmp(dp[0][p], best) > 0) {
                best = dp[0][p];
                used = p;
            }
        }
        
        //D(shortcut(points[0], points[1], points[2], 149));
        
        printf("%d meters used saving %.2lf meters\n", used, (double)best);
        
    }
    return 0;
}