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

class EllysTSP {
  public:
  int getMax(string places);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "CVVVC"; int Arg1 = 5; verify_case(0, Arg1, getMax(Arg0)); }
	void test_case_1() { string Arg0 = "VVV"; int Arg1 = 1; verify_case(1, Arg1, getMax(Arg0)); }
	void test_case_2() { string Arg0 = "VVVVCVV"; int Arg1 = 3; verify_case(2, Arg1, getMax(Arg0)); }
	void test_case_3() { string Arg0 = "CVCVCVC"; int Arg1 = 7; verify_case(3, Arg1, getMax(Arg0)); }
	void test_case_4() { string Arg0 = "V"; int Arg1 = 1; verify_case(4, Arg1, getMax(Arg0)); }

// END CUT HERE

};

int EllysTSP::getMax(string places) {
    int a = 0, b = 0;
    for (int i = 0; i < places.size(); ++i) {
        a += places[i] == 'C';
        b += places[i] == 'V';
    }
    int c = min(a, b);
    if (c == 0) return 1;
    
    int ans = 2*c;
    a -= c, b -= c;
    assert(a == 0 or b == 0);
    ans += min(a, 1);
    ans += min(b, 1);
    return ans;
}

// BEGIN CUT HERE
int main(){
    EllysTSP test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
