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

class IntegerPalindrome {
  public:
  long long findByIndex(int K);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 8; long long Arg1 = 9LL; verify_case(0, Arg1, findByIndex(Arg0)); }
	void test_case_1() { int Arg0 = 9; long long Arg1 = 11LL; verify_case(1, Arg1, findByIndex(Arg0)); }
	void test_case_2() { int Arg0 = 19; long long Arg1 = 111LL; verify_case(2, Arg1, findByIndex(Arg0)); }
	void test_case_3() { int Arg0 = 235; long long Arg1 = 13731LL; verify_case(3, Arg1, findByIndex(Arg0)); }
	void test_case_4() { int Arg0 = 23746; long long Arg1 = 137484731LL; verify_case(4, Arg1, findByIndex(Arg0)); }

// END CUT HERE

};

long long IntegerPalindrome::findByIndex(int K) {
    K++;
    int len = 1;
    whle ()
}

// BEGIN CUT HERE
int main(){
    IntegerPalindrome test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
