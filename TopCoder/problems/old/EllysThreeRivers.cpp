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

class EllysThreeRivers {
  public:
  double getMin(int length, int walk, vector <int> width, vector <int> swim);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 10; int Arg1 = 8; int Arr2[] = {5, 2, 3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {5, 2, 7}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 3.2063518370413364; verify_case(0, Arg4, getMin(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 1000; int Arg1 = 100; int Arr2[] = {91, 911, 85}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {28, 97, 19}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 21.549321613601297; verify_case(1, Arg4, getMin(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 666; int Arg1 = 4; int Arr2[] = {777, 888, 999}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {11, 12, 13}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 228.26633673141083; verify_case(2, Arg4, getMin(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 6; int Arg1 = 100; int Arr2[] = {2, 3, 4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {77, 88, 99}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 0.12049782476139667; verify_case(3, Arg4, getMin(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 873; int Arg1 = 54; int Arr2[] = {444, 588, 263}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {67, 97, 26}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 26.365540023205206; verify_case(4, Arg4, getMin(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

int n, length, walk;
vector<double> w, s;

double square(double x) {
    return x * x;
}

double best_time(int i, double h) {
    if (i == 3) {
        return (length - h) / walk; // just walk
    }
    
    double low = 0, high = length - h;
    for (int k = 0; k < 120; ++k) {
        double m0 = (2*low + high) / 3; // low + (high - low) / 3;
        double m1 = (low + 2*high) / 3; // low + (high - low) * 2 / 3;
        double t0 = best_time(i + 1, h + m0) + sqrt(square(w[i]) + square(m0)) / s[i];
        double t1 = best_time(i + 1, h + m1) + sqrt(square(w[i]) + square(m1)) / s[i];
        if (t0 < t1) {
            high = m1;
        } else {
            low = m0;
        }
    }
    
    double m = (low + high) / 2;
    return best_time(i + 1, h + m) + sqrt(square(w[i]) + square(m)) / s[i];
}

double EllysThreeRivers::getMin(int _length, int _walk, vector <int> width, vector <int> swim) {
    n = width.size();
    length = _length;
    walk = _walk;
    w.resize(n);
    s.resize(n);
    for (int i = 0; i < n; ++i) {
        w[i] = width[i];
        s[i] = swim[i];
    }
    return best_time(0, 0.0);
}

// BEGIN CUT HERE
int main(){
    EllysThreeRivers test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
