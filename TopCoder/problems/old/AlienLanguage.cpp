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

class AlienLanguage {
  public:
  int getNumberOfWords(int P, int Q, int N, int M);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; int Arg3 = 9; int Arg4 = 8; verify_case(0, Arg4, getNumberOfWords(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 3; int Arg2 = 2; int Arg3 = 1000; int Arg4 = 577; verify_case(1, Arg4, getNumberOfWords(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1000000000; int Arg3 = 1000000000; int Arg4 = 0; verify_case(2, Arg4, getNumberOfWords(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 123; int Arg1 = 456; int Arg2 = 789; int Arg3 = 987654321; int Arg4 = 345494202; verify_case(3, Arg4, getNumberOfWords(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

int AlienLanguage::getNumberOfWords(int P, int Q, int N, int M) {
  
}

// BEGIN CUT HERE
int main(){
    AlienLanguage ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
