// Accepted

using namespace std;
#include <iostream>
#include <algorithm>
#include <iterator>
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
#include <map>
#include <set>
#include <stack>

#define D(x) cout << #x " = " << (x) << endl
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); x++)
#define For (i, a, b) for (int i = (a); i < (b); i++)

struct Point {
    int x, y;
    
    void read() {
        cin >> x >> y;
    }
    
    void print() const {
        printf("(%d, %d)\n", x, y);
    }
};

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS){
return( x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

double dist(const Point &a, const Point &b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

bool hit(const Point &a, const Point &b, const Point &p, const Point &q) {
    
    double x0 = a.x, y0 = a.y;
    double x1 = b.x, y1 = b.y;
    double x2 = p.x, y2 = p.y;
    double x3 = q.x, y3 = q.y;
    
//    a.print();
//    b.print();
//    p.print();
//    q.print();
    
    double t0 = (y3-y2)*(x0-x2)-(x3-x2)*(y0-y2);
    double t1 = (x1-x0)*(y2-y0)-(y1-y0)*(x2-x0);
    double det = (y1-y0)*(x3-x2)-(y3-y2)*(x1-x0);
    
    //D(t0);
    //D(t1);
    
    if (cmp(t0, 0) == 0 or cmp(t1, 0) == 0) { // paralelas
        return false;
    }
    t0 /= det;
    t1 /= det;

    
    if (cmp(0.0, t0) <= 0 and cmp(t0, 1.0) <= 0 and cmp(0.0, t1) <= 0 and cmp(t1, 1.0) <= 0) {
        return true;
    }
    return false;
}    


int main (){
    int run = 1;
    
    while (true) {
        Point p1, p2;
        p1.read();
        p2.read();
        if (p1.x == 0 and p2.x == 0 and p1.y == 0 and p2.y == 0) break;
        
        Point a, b;
        a.read();
        b.read();
        
        printf("Case %d: ", run++);
        
        //D(hit(p1, p2, a, b));
        
        if (hit(p1, p2, a, b)) {
            double left = dist(p1, a) + dist(p2, a);
            left /= 2;
            double right = dist(p1, b) + dist(p2, b);
            right /= 2;
            double ans = min(left, right);
            printf("%.3lf\n", ans);
        } else {
            double d = dist(p1, p2);
            printf("%.3lf\n", d / 2);
        }
        
    }

    return 0;
}
