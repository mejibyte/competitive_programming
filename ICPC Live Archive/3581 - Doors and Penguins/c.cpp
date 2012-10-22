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

# define foreach (x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
# define D(x) cout << #x " = " << (x) << endl
# define For(i, a,  b) for (int i = (a); i < (b); i++)

const double eps = 1e-9;

struct Point {
	int x, y;	
	Point(){}
	Point (int xx, int yy) : x(xx), y(yy){}
	
	bool operator < (const Point &t) const {
		return x < t.x or (x == t.x and y < t.y);
	}
	
	void print() const {
		printf("(%d, %d)\n", x, y);
	}
};

long long cross(const Point &o, const Point &a, const Point &b) {
	return 1LL*(a.x-o.x)*(b.y-o.y) - 1LL*(a.y-o.y)*(b.x-o.x);
}

vector<Point> convex_hull(vector<Point> p) {
	int n = p.size(), k = 0;
	vector<Point> h(2*n);
	sort(p.begin(), p.end());
	for (int i = 0; i < n; ++i) {
		while (k >= 2 and cross(h[k-2], h[k-1], p[i]) <= 0) k--;
		h[k++] = p[i];
	}
	for (int i = n - 2, t = k + 1; i >= 0; --i) {
		while (k >= t and cross(h[k-2], h[k-1], p[i]) <= 0) k--;
		h[k++] = p[i];
	}
	h.resize(k);
	return h;
}

int point_in_box(int x, int y, int x0, int y0, int x1, int y1) {
	return min(x0, x1) <= x and x <= max(x0, x1) and
	       min(y0, y1) <= y and y <= max(y0, y1);
}

int direction(int x1, int y1, int x2, int y2, int x3, int y3) {
	return (x3-x1)*(y2-y1)-(y3-y1)*(x2-x1);
}

bool hit(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	int d1 = direction(x3, y3,  x4, y4,  x1, y1);
	int d2 = direction(x3, y3,  x4, y4,  x2, y2);
	int d3 = direction(x1, y1,  x2, y2,  x3, y3);
	int d4 = direction(x1, y1,  x2, y2,  x4, y4);
	bool b1 = d1 > 0 and d2 < 0 or d1 < 0 and d2 > 0;
	bool b2 = d3 > 0 and d4 < 0 or d3 < 0 and d4 > 0;
	if (b1 and b2) return true;
	if (d1 == 0 and point_in_box(x1, y1, x3, y3, x4, y4)) return true;
	if (d2 == 0 and point_in_box(x2, y2, x3, y3, x4, y4)) return true;
	if (d3 == 0 and point_in_box(x3, y3, x1, y1, x2, y2)) return true;
	if (d4 == 0 and point_in_box(x4, y4, x1, y1, x2, y2)) return true;			
	return false;
}

double polarAngle(const Point &p) {
	if ( p.x == 0 and p.y == 0 ) return -1.0;
	if (p.x == 0) return (p.y > 0 ? 1.0 : 3.0) * acos(0);
	double theta = atan(1.0 * p.y / p.x);
	if (p.x > 0) return (p.y >= -0 ? theta : (4*acos(0) + theta));
	return (2*acos(0) + theta);
}

bool pointInPoly(const Point &p, vector<Point> &poly) {
	int n = poly.size();
	double ang = 0.0;
	for (int i = n - 1, j = 0; j < n; i = j++) {
		Point v(poly[i].x - p.x, poly[i].y - p.y);
		Point w(poly[j].x - p.x, poly[j].y - p.y);
		double va = polarAngle(v);
		double wa = polarAngle(w);
		double xx = wa - va;
		if (va < -0.5 or wa < -0.5 or fabs(fabs(xx)-2*acos(0)) < eps) {
            return true;
			assert(false);
		}	
		if (xx < -2*acos(0)) ang += xx + 4*acos(0);
		else if (xx > 2*acos(0)) ang += xx - 4*acos(0);
		else ang += xx;
	}
	return (ang * ang > 1.0 );
}

int main(){
	int D, P, run = 1;
	
	while (cin >> D >> P) {
		if (D == 0 and P == 0) break;
		
		if (run > 1) puts("");

		printf("Case %d: ", run++);
		
		
		vector<Point> a, b;
		
		for (int i = 0; i < D; ++i) {
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			a.push_back(Point(x1, y1));
			a.push_back(Point(x1, y2));
			a.push_back(Point(x2, y1));
			a.push_back(Point(x2, y2));
		}
		
		for (int i = 0; i < P; ++i) {
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			b.push_back(Point(x1, y1));
			b.push_back(Point(x1, y2));
			b.push_back(Point(x2, y1));
			b.push_back(Point(x2, y2));			
		}
		
		a = convex_hull(a);
		b = convex_hull(b);
		
        bool valid = true;
        for (int i = 0; i + 1 < a.size() and valid; ++i) {
         for (int j = 0; j + 1 < b.size() and valid; ++j) {
             const Point &p1 = a[i], &p2 = a[i + 1];
             const Point &q1 = b[j], &q2 = b[j + 1];
             if (hit(p1.x, p1.y, p2.x, p2.y,      q1.x, q1.y, q2.x, q2.y)) {
                 valid = false;
                 //printf(" choque de (%d,%d)--(%d,%d) con (%d,%d)--(%d,%d)\n", p1.x, p1.y, p2.x, p2.y,      q1.x, q1.y, q2.x, q2.y);
             }
             
         }
        }
        
        //puts("b es:");
        //For(i, 0, b.size()) b[i].print();
        
        for (int i = 0; i < a.size() and valid; ++i) {
         if (pointInPoly(a[i], b)) {
             //printf("(%d, %d) esta en b\n", a[i].x, a[i].y);
             valid = false;
         }
        }
        for (int i = 0; i < b.size() and valid; ++i) {
         if (pointInPoly(b[i], a)) {
             //printf("(%d, %d) esta en a\n", b[i].x, b[i].y);               
             valid = false;
         }
        }
		
		if (valid) {
			puts("It is possible to separate the two groups of vendors.");
		} else {
			puts("It is not possible to separate the two groups of vendors.");
		}
	}
	return 0;
}


