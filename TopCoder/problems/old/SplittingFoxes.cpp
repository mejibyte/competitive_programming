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

class SplittingFoxes {
  public:
  int sum(long long n, int S, int L, int R);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 58LL; int Arg1 = 2; int Arg2 = 0; int Arg3 = 0; int Arg4 = 0; verify_case(0, Arg4, sum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { long long Arg0 = 3LL; int Arg1 = 1; int Arg2 = 1; int Arg3 = 0; int Arg4 = 1; verify_case(1, Arg4, sum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { long long Arg0 = 5LL; int Arg1 = 1; int Arg2 = 3; int Arg3 = 2; int Arg4 = 34; verify_case(2, Arg4, sum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { long long Arg0 = 5LL; int Arg1 = 1; int Arg2 = 2; int Arg3 = 3; int Arg4 = 999999973; verify_case(3, Arg4, sum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { long long Arg0 = 123456789LL; int Arg1 = 987654321; int Arg2 = 544; int Arg3 = 544; int Arg4 = 0; verify_case(4, Arg4, sum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { long long Arg0 = 65536LL; int Arg1 = 1024; int Arg2 = 512; int Arg3 = 4096; int Arg4 = 371473914; verify_case(5, Arg4, sum(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

int SplittingFoxes::sum(long long n, int S, int L, int R) {
  
}

// BEGIN CUT HERE
int main(){
    SplittingFoxes test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
