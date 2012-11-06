// Accepted
using namespace std;
#include <algorithm>
#include <iostream>
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
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

#define For(i, a, b) for (int i = (a); i < (b); i++)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); x++)
#define D(x) cout << #x " = "  << (x) << endl

typedef long double Double;

const Double EPS = 1e-9;
int cmp (Double x, Double y = 0, Double tol = EPS){
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;    
}

struct Point {
    Double x,y;
    Point (Double x, Double y) {
        this->x = x;
        this->y = y;
    }
    Point(){}
};

typedef vector <Point> Polygon;

bool segment_line_intersection(Double x0, Double y0, Double x1, Double y1,
                               Double x2, Double y2, Double x3, Double y3,   Double &x, Double &y){
    Double t0 = (y3-y2)*(x0-x2) - (x3-x2)*(y0-y2);
    Double t1 = (x1-x0)*(y2-y0) - (y1-y0)*(x2-x0);
    Double det =(y1-y0)*(x3-x2) - (y3-y2)*(x1-x0);
    
    if (fabs(det) < EPS){
        //Paralelas
        return false;
    }else{
        t0 /= det;
        t1 /= det;
        if (cmp(0, t0) <= 0 and cmp(t0, 1) < 0){
            x = x0 + t0 * (x1-x0);
            y = y0 + t0 * (y1-y0);
            return true;
        }
        return false;
    }
}



vector <Point> chips;
vector <Polygon> polys;

vector<Polygon> split(const Polygon &p, Double x0, Double y0, Double x1, Double y1) {
    int hits = 0, side = 0;
    Double x, y;
    vector<Polygon> ans(2);
 
    for (int i = 0; i < p.size(); ++i) {
        int j = (i + 1) % p.size();
        if (segment_line_intersection(p[i].x, p[i].y,    p[j].x, p[j].y,      x0, y0, x1, y1,     x, y)) {
            hits++;
            ans[side].push_back(p[i]);
            if (cmp(p[i].x, x) != 0 or cmp(p[i].y, y) != 0) {
                ans[side].push_back(Point(x, y));
            }
            side ^= 1;
            ans[side].push_back(Point(x, y));
        } else {
            ans[side].push_back(p[i]);
        }
    }
    return hits < 2 ? vector<Polygon>(1, p) : ans;
}


// Returns the area of the not self-intersecting polygon P.
Double area(const Polygon &p) {
    Double ans = 0;
    for (int i = 0; i < p.size(); ++i) {
        int j = (i + 1) % p.size();
        ans += p[i].x*p[j].y - p[i].y*p[j].x;
    }
    if (ans < 0) ans = -ans;
    return ans / 2;
}

Double turn(const Point &a, const Point &b, const Point &c) {
   return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

// Checks if point A is strictly inside the convex polyon P.
bool inside(const Polygon &p, const Point &a) {
    int mask = 0;
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        Double z = turn(p[i], p[j], a);
        if (cmp(z, 0) == 0) return false;
        if (cmp(z, 0) < 0) mask |= 1;
        else mask |= 2;
        if (mask == 3) return false;
    }
    return mask != 0;
}

int main(){
    int l, c, k;
    while (cin >> l >> c >> k){
        if (l == 0 and c == 0 and k == 0) break;
        chips.clear();
        polys.clear();
        for (int i = 0; i < c; i++){
           int x, y; cin >> x >> y;
           chips.push_back(Point(x, y));     
        }
        polys.resize(1);
        polys[0].push_back(Point(0, 0));
        polys[0].push_back(Point(l, 0));
        polys[0].push_back(Point(l, l));
        polys[0].push_back(Point(0, l));
        

        for (int i = 0; i < k; i++){
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;

            vector< Polygon > new_polys;
            for (int i = 0; i < polys.size(); ++i) {
                vector<Polygon> add = split(polys[i], x1, y1, x2, y2);
                new_polys.insert(new_polys.end(), add.begin(), add.end());
            }
            polys = new_polys;
        }
        
        Double best = 0;
        for (int i = 0; i < polys.size(); ++i) {
            const Polygon &p = polys[i];

            
            int score = 0;
            for (int c = 0; c < chips.size(); ++c) {
                if (inside(p, chips[c])) score++;
            }
            
            Double option = score / area(p);
            if (option > best) best = option;
        }
        printf("%.3lf\n", (double)(best + EPS));
    }
    return 0;    
}
