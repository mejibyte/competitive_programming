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

class MagicalGirlLevelTwoDivOne {
  public:
  int theCount(vector <string> palette, int n, int m);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"12",
 "2."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 2; int Arg3 = 5; verify_case(0, Arg3, theCount(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"21",
 "1."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 2; int Arg3 = 4; verify_case(1, Arg3, theCount(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"...",
 "...",
 "..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; int Arg3 = 1953125; verify_case(2, Arg3, theCount(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"..58..",
 "..47.."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 3; int Arg3 = 0; verify_case(3, Arg3, theCount(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"...1.2.3",
 "4.5.6...",
 "...7.8.9",
 "1.2.3..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 4; int Arg3 = 886073030; verify_case(4, Arg3, theCount(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arr0[] = {"....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "...................."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; int Arg2 = 10; int Arg3 = 240076532; verify_case(5, Arg3, theCount(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

int MagicalGirlLevelTwoDivOne::theCount(vector <string> palette, int n, int m) {
  
}

// BEGIN CUT HERE
int main(){
    MagicalGirlLevelTwoDivOne test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
