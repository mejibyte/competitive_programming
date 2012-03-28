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

class LeftOrRight {
  public:
  int maxDistance(string program);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "LLLRLRRR"; int Arg1 = 3; verify_case(0, Arg1, maxDistance(Arg0)); }
	void test_case_1() { string Arg0 = "R???L"; int Arg1 = 4; verify_case(1, Arg1, maxDistance(Arg0)); }
	void test_case_2() { string Arg0 = "??????"; int Arg1 = 6; verify_case(2, Arg1, maxDistance(Arg0)); }
	void test_case_3() { string Arg0 = "LL???RRRRRRR???"; int Arg1 = 11; verify_case(3, Arg1, maxDistance(Arg0)); }
	void test_case_4() { string Arg0 = "L?L?"; int Arg1 = 4; verify_case(4, Arg1, maxDistance(Arg0)); }

// END CUT HERE

};

int get(string s) {
    int cur = 0;
    int ans = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'L') cur--; else cur++;
        ans = max(abs(cur), ans);
    }
    return ans;
}

int LeftOrRight::maxDistance(string program) {
    string s = program;
    for (int i = 0; i < s.size(); ++i) if (s[i] == '?') s[i] = 'L';
    int ans = get(s);
    s = program;
    for (int i = 0; i < s.size(); ++i) if (s[i] == '?') s[i] = 'R';
    ans = max(ans, get(s));
    return ans;
}

// BEGIN CUT HERE
int main(){
    LeftOrRight ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
