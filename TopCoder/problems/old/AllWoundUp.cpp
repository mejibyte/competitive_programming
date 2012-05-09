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
#define D(x) cout << #x " is " << (x) << endl

class AllWoundUp {
  public:
  int maxWind(vector <int> x, vector <int> y);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-2,9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(0, Arg2, maxWind(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,1,3,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1,0,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(1, Arg2, maxWind(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {0,1,1,0,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,-1,1,-1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(2, Arg2, maxWind(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {   0,1000, 500,   0,1000, 500, 500,1000,   0, 500,1000, 0}   
 ; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] =  {-100,-100, 100,-100,-100, 100, 100,-100,-100, 100,-100,-100}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(3, Arg2, maxWind(Arg0, Arg1)); }

// END CUT HERE

};

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

const double PI = acos(-1);

struct Point {
    double x, y;
    Point(){}
    Point(double x, double y) : x(x), y(y) {}
};

int winding_number(const Point &p, const vector<int> &x, const vector<int> &y) {
    double rotated = 0.0;
    int n = x.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        if (fabs(p.x - x[i]) <= EPS and fabs(p.y - y[i]) <= EPS) { // p is a vertex!
            return 0;
        }
        double delta = atan2(y[j] - p.y, x[j] - p.x) - atan2(y[i] - p.y, x[i] - p.x);
        if (fabs(delta - PI) == 0) { // on the boundary
            return 0;
        }
        while (delta > PI) delta -= 2*PI;
        while (delta < -PI) delta += 2*PI;
        assert(-PI <= delta and delta <= PI);
        rotated += delta;
    }
    return (int)round(rotated / 2 / PI);
}

double intersect(int x1, int y1, int x2, int y2) {
    if (y1 == 0) return x1;
    if (y2 == 0) return x2;
    return x1 - 1.0 * y1 * (x2 - x1) / (y2 - y1);
}

int AllWoundUp::maxWind(vector <int> x, vector <int> y) {
    vector<double> cuts;
    int n = x.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        if (y[i] * y[j] <= 0) { // crosses the X-axis
            cuts.push_back(intersect(x[i], y[i],  x[j], y[j]));
        }
    }
    cuts.push_back(-3000);
    cuts.push_back(+3000);
    sort(cuts.begin(), cuts.end());

    int ans = INT_MIN;
    
    for (int i = 0; i + 1 < cuts.size(); ++i) {
        double xx = (cuts[i + 1] + cuts[i]) / 2.0;
        
        bool ok = true;
        for (int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            if (x[i] + EPS <= xx and xx <= x[j] - EPS and y[i] == 0 and y[j] == 0) ok = false;
        }
        
        if (ok) {
            ans = max(ans, winding_number(Point(xx, 0.0), x, y));
        }
    }
    
    return ans;
}

// BEGIN CUT HERE
int main(){
    AllWoundUp test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
