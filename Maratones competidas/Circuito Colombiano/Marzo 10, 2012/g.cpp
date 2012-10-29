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
#include <map>
#include <set>

#define For (i, a, b) for (int i = (a); i < (b); i++)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); x++)
#define D(x) cout << #x " = " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS){
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

struct point {
    double x, y;
    point(double x, double y) : x(x), y(y) {}
    point (){}
    
    void print() {
        printf("(%.lf, %.lf)\n", x, y);
    }
};

point midpoint (point a, point b){
    point ans;
    ans.x = (a.x + b.x) / 2.0;
    ans.y = (a.y + b.y) / 2.0;
    return ans;
}

point inter (point a, point b, point c, point d){
    double x0 = a.x; double y0 = a.y;
    double x1 = b.x; double y1 = b.y;  
    double x2 = c.x; double y2 = c.y;  
    double x3 = d.x; double y3 = d.y;
    
    double t0 = (y3 - y2) * (x0 - x2) - (x3 - x2) * (y0 - y2);
    double t1 = (x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0);
    double det = (y1 - y0) * (x3 - x2) - (y3 - y2) * (x1 - x0);
    
    if (fabs(det) < EPS){
        D("PARALELAS");
        assert(false);
    }else{
        t0 /= det;
        t1 /= det;
        long double x = x0 + t0 * (x1 - x0);
        long double y = y0 + t0 * (y1 - y0);
        point ans (x, y);
        //ans.print();
        return ans;
    }
    
}


double area (const vector <point> &p){
    double r = 0.0;
    for (int i = 0; i < p.size(); i++){
        int j = (i + 1) % p.size();
        r += p[i].x * p[j].y - p[j].x * p[i].y;    
    }
    return abs(r) / 2.0;
}

double dist(point a, point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    int cases; cin >> cases;
    while (cases--){
        int N; cin >> N;
        point a (0.0, 0.0);
        point b;
        b.y = 0.0;
        point c, d;
        cin >> b.x >> c.x >> c.y >> d.x >> d.y;
        
//        a.print();
//        b.print();
//        c.print();
//        d.print();
        
        point ap = midpoint(b, c);
        point bp = midpoint(c, d);   
        point cp = midpoint(d, a);   
        point dp = midpoint(a, b);
        
//        ap.print();
//        bp.print();
//        cp.print();
//        dp.print();
        
        point p1 = inter (a, ap, b, bp);
        point p2 = inter (b, bp, c, cp);
        point p3 = inter (c, cp, d, dp);
        point p4 = inter (d, dp, a, ap);
        
        
        
        vector <point> tmp;
        tmp.push_back(a); tmp.push_back(b); tmp.push_back(p1);
        double areaA = area(tmp) / 160.0;
        
        tmp.clear();
        tmp.push_back(b); tmp.push_back(c); tmp.push_back(p2);
        double areaB = area(tmp) / 160.0;
        
        tmp.clear();
        tmp.push_back(c); tmp.push_back(d); tmp.push_back(p3);
        double areaC = area(tmp) / 160.0;
        
        tmp.clear(); 
        tmp.push_back(d); tmp.push_back(a); tmp.push_back(p4);
        double areaD = area(tmp) / 160.0;
        
        tmp.clear();  
        tmp.push_back(p1); tmp.push_back(p2); tmp.push_back(p3); tmp.push_back(p4); 
        double areaE = area(tmp) / 160.0;
        
        double per = dist(p1, p2) + dist(p2, p3) + dist(p3, p4) + dist(p4, p1);        
        per *= 16.5;

        per = ceil(per);

        
        //D(areaA); D(areaB); D(areaC); D(areaD); D(areaE);
        printf("%d %.3lf %.3lf %.3lf %.3lf %.3lf %.0lf\n", N, areaA, areaB, areaC, areaD, areaE, per);
    }
    
    return 0;
}
