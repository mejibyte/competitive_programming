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

class PageNumbers {
  public:
  vector <int> getCounts(int N);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 7; int Arr1[] = {0, 1, 1, 1, 1, 1, 1, 1, 0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, getCounts(Arg0)); }
	void test_case_1() { int Arg0 = 11; int Arr1[] = {1, 4, 1, 1, 1, 1, 1, 1, 1, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, getCounts(Arg0)); }
	void test_case_2() { int Arg0 = 19; int Arr1[] = {1, 12, 2, 2, 2, 2, 2, 2, 2, 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, getCounts(Arg0)); }
	void test_case_3() { int Arg0 = 999; int Arr1[] = {189, 300, 300, 300, 300, 300, 300, 300, 300, 300 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, getCounts(Arg0)); }
	void test_case_4() { int Arg0 = 543212345; int Arr1[] = {429904664, 541008121, 540917467, 540117067, 533117017, 473117011, 429904664, 429904664, 429904664, 429904664 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, getCounts(Arg0)); }

// END CUT HERE

};

vector <int> PageNumbers::getCounts(int N) {
  
}

// BEGIN CUT HERE
int main(){
    PageNumbers ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
