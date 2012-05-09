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

class CucumberWatering {
  public:
  long long theMin(vector <int> x, int K);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 6, 8, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; long long Arg2 = 6LL; verify_case(0, Arg2, theMin(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {-1000000000, 1000000000, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; long long Arg2 = 3000000000LL; verify_case(1, Arg2, theMin(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {58, 2012}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 50; long long Arg2 = 0LL; verify_case(2, Arg2, theMin(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {9, -3, 14, 6, 5, -9, 32, 7, -5, 26, 2, 11}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; long long Arg2 = 58LL; verify_case(3, Arg2, theMin(Arg0, Arg1)); }

// END CUT HERE

};

long long CucumberWatering::theMin(vector <int> x, int K) {
  
}

// BEGIN CUT HERE
int main(){
    CucumberWatering ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
