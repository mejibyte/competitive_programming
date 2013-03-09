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
#include <bitset>
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

class CentersOfSymmetry {
  public:
  int lineConfigurations(vector <int> x1, vector <int> y1, vector <int> x2, vector <int> y2);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, -1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 1; verify_case(0, Arg4, lineConfigurations(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 1; verify_case(1, Arg4, lineConfigurations(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {0, 1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1, -1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, -1, 0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(2, Arg4, lineConfigurations(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {-10, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10, -10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {-10, 10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {-10, 10}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = -1; verify_case(3, Arg4, lineConfigurations(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = {-50, -50, -50, -50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-50, -49, -48, -46}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {50, 49, 48, 46}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {50, 50, 50, 50}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(4, Arg4, lineConfigurations(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arr0[] = {10, -35, -8, 7, -5, -8, -9, -50, -17, -18, -17, -26, -5, 23, 18, -7, -8, -6,
 -8, -12, 22, -7, 17, -48, -6, -16, -12, -14, 13, 30, 11, 17, -3, -5, -27, -30}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-27, -25, -17, -26, -3, -19, -20, -33, -22, -21, -23, -38, -2, -32, -27, -8, -2, -5,
 -21, -7, -15, -15, -5, -27, 0, -19, -25, 1, -22, -11, -13, -38, -1, -6, -17, -32}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {16, -32, -11, 11, -3, -9, -8, -45, -16, -15, -19, -29, -2, 20, 24, -1, 4, -7,
 -5, -13, 16, -9, 29, -43, 2, -17, -15, -15, 17, 24, 23, 14, -7, -3, -24, -33}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {-35, -23, -26, -32, -3, -21, -18, -30, -20, -15, -27, -42, -5, -28, -35, 2, -5, -6,
 -15, -7, -13, -19, -9, -24, -12, -21, -34, 1, -28, -9, -17, -34, -9, 0, -15, -36}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 1; verify_case(5, Arg4, lineConfigurations(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};


const long double eps = 1e-9;

struct Intersection {
  double x, y;
  double t0, t1;
  bool valid;
  
  Intersection(bool v) : valid(v) {}
  Intersection(double x, double y, double t0, double t1) : x(x), y(y), t0(t0), t1(t1), valid(true) { }
};

Intersection line_line_intersection(double x0, double y0,
                                    double x1, double y1,

                                    double x2, double y2,
                                    double x3, double y3){
  double t0 = (y3-y2)*(x0-x2)-(x3-x2)*(y0-y2);
  double t1 = (x1-x0)*(y2-y0)-(y1-y0)*(x2-x0);
  double det = (y1-y0)*(x3-x2)-(y3-y2)*(x1-x0);
  if (fabs(det) < eps){
    //parallel
    if (fabs(t0) < eps || fabs(t1) < eps){
      //same line
      return Intersection(false);
    }else{
      //just parallel
      return Intersection(false);
    }
  }else{
      t0 /= det;
    t1 /= det;
    double x = x0 + t0*(x1-x0);
    double y = y0 + t0*(y1-y0);
    //intersection is point (x, y)
    return Intersection(x, y, t0, t1);
  }
}

int parallel(vector <int> x1, vector <int> y1, vector <int> x2, vector <int> y2) {
  return -2;
}

int CentersOfSymmetry::lineConfigurations(vector <int> x1, vector <int> y1, vector <int> x2, vector <int> y2) {
  int n = x1.size();
  if (n == 1) return -1;
  
  vector< pair<double, double> > points;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      Intersection boom = line_line_intersection(x1[i], y1[i], x2[i], y2[i],
                                                 x1[j], y1[j], x2[j], y2[j]);
      if (boom.valid) points.push_back( make_pair(boom.x, boom.y) );
    }
  }
  if (points.size() == 0) return parallel(x1, y1, x2, y2);
  sort(points.begin(), points.end());
  // either all points are the same, 1
  // or there are at least 2 different points, 0
  for (int i = 0; i + 1 < points.size(); ++i) {
    if (fabs(points[i].first - points[i + 1].first) > eps) return 0;
    if (fabs(points[i].second - points[i + 1].second) > eps) return 0;
  }
  return 1;
}

// BEGIN CUT HERE
int main(){
    CentersOfSymmetry test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
