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

class BigAndSmallAirports {
  public:
  long long solve(int Nlo, int Nhi, int Blo, int Bhi, int Slo, int Shi);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 20; int Arg1 = 20; int Arg2 = 3; int Arg3 = 3; int Arg4 = 2; int Arg5 = 2; long long Arg6 = 21LL; verify_case(0, Arg6, solve(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 10; int Arg3 = 10; int Arg4 = 2; int Arg5 = 2; long long Arg6 = 1LL; verify_case(1, Arg6, solve(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 10; int Arg2 = 8; int Arg3 = 8; int Arg4 = 3; int Arg5 = 3; long long Arg6 = 6LL; verify_case(2, Arg6, solve(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 100; int Arg2 = 13; int Arg3 = 15; int Arg4 = 18; int Arg5 = 22; long long Arg6 = 0LL; verify_case(3, Arg6, solve(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_4() { int Arg0 = 30; int Arg1 = 32; int Arg2 = 8; int Arg3 = 10; int Arg4 = 6; int Arg5 = 8; long long Arg6 = 768LL; verify_case(4, Arg6, solve(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }

// END CUT HERE

};

long long BigAndSmallAirports::solve(int Nlo, int Nhi, int Blo, int Bhi, int Slo, int Shi) {
  
}

// BEGIN CUT HERE
int main(){
    BigAndSmallAirports ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
