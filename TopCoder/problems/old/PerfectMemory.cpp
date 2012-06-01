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

class PerfectMemory {
  public:
  double getExpectation(int N, int M);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 2; double Arg2 = 1.0; verify_case(0, Arg2, getExpectation(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 2; double Arg2 = 2.6666666666666665; verify_case(1, Arg2, getExpectation(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 3; double Arg2 = 4.333333333333334; verify_case(2, Arg2, getExpectation(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 4; int Arg1 = 4; double Arg2 = 12.392984792984793; verify_case(3, Arg2, getExpectation(Arg0, Arg1)); }

// END CUT HERE

};

const int MAXN = 2505;
double memo[MAXN][MAXN];

// c = How many known cards I have (they are all different).
// n = How many pending cards I have (they need not be different).
double f(int c, int n) {
    if (c == 0 and n == 0) return 0.0;
    
    if (n < c) return 0.0; // bad!
    
    if (memo[c][n] > -0.5) {
        return memo[c][n];
    }
    
    double ans = 0.0;
    if (c-1 >= 0 and n-1 >= 0) {
        ans += 1.0*c/n*(1 + f(c-1, n-1));
    }
    if (n-2 >= 0 and n-c >= 0) {
        ans += 1.0*(n-c)/n/(n-1)*(1 + f(c, n-2));
    }
    if (n-2 >= 0) {
        ans += 1.0*(n-c)*c/n/(n-1)*(2 + f(c, n-2));
    }
    if (n-2 >= 0 and n-c-2 >= 0) {
        ans += 1.0*(n-c)*(n-c-2)/n/(n-1)*(1 + f(c+2, n-2));
    }
    return memo[c][n] = ans;
}

double PerfectMemory::getExpectation(int N, int M) {
    for (int i = 0; i < MAXN; ++i)
        for (int j = 0; j < MAXN; ++j)
            memo[i][j] = -1.0;
    
    return f(0, N*M);
}

// BEGIN CUT HERE
int main(){
    PerfectMemory test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
