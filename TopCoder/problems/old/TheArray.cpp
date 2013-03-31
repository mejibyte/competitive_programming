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

class TheArray {
  public:
  int find(int n, int d, int first, int last);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 5; int Arg2 = 2; int Arg3 = 4; int Arg4 = 7; verify_case(0, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 10; int Arg1 = 100; int Arg2 = 999; int Arg3 = 100; int Arg4 = 999; verify_case(1, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 1000000; int Arg1 = 0; int Arg2 = 474; int Arg3 = 474; int Arg4 = 474; verify_case(2, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 97; int Arg1 = 53; int Arg2 = -92; int Arg3 = 441; int Arg4 = 2717; verify_case(3, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 99; int Arg1 = 3; int Arg2 = -743; int Arg3 = -619; int Arg4 = -535; verify_case(4, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

int TheArray::find(int n, int d, int first, int last) {
    if (last < first) swap(first, last);
    assert(first <= last);

    int ans = last;
    int have = first;
    for (int i = 1; i < n - 1; ++i) {
        have = min( have + d, last + (n-1-i) * d );
        
//        if (have + d <= last + (n - 1 - i) * d) have += d;
        ans = max(have, ans);
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    TheArray test;
    test.run_test(-1);
    
    D(test.find(5, 2, 2, 5));
    
    return 0;
}
// END CUT HERE
