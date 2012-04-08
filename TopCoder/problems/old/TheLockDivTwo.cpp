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
#include <bitset>

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

class TheLockDivTwo {
  public:
  string password(int n, int k);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 4; string Arg2 = "10"; verify_case(0, Arg2, password(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 6; string Arg2 = "0100"; verify_case(1, Arg2, password(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 1; string Arg2 = "0000000000"; verify_case(2, Arg2, password(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 7; int Arg1 = 100; string Arg2 = "1100001"; verify_case(3, Arg2, password(Arg0, Arg1)); }

// END CUT HERE

};

string TheLockDivTwo::password(int n, int k) {
    bitset<1 << 10> seen;
    unsigned int cur = 0;
    for (int i = 1; i < k; ++i) {
        seen[cur] = true;
        int next = 1 << 30;
        // turn off some ones
        for (unsigned int turn_off = cur; turn_off > 0; turn_off = (turn_off - 1) & cur) {
            int option = cur & ~turn_off;
            if (option < 1 << n and !seen[option]) next = min(next, option);
        }
        
        // turn on some ones
        for (unsigned int turn_on = (1 << n + 1) - 1 & ~cur; turn_on > 0; turn_on = (turn_on - 1) & ~cur) {
            int option = cur | turn_on;
            if (option < 1 << n and !seen[option]) next = min(next, option);
        }
        
        cur = next;
    }
    
    string ans(n, '*');
    for (int i = 0; i < n; ++i) {
        ans[n-1-i] = !!(cur & 1 << i) + '0';
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    TheLockDivTwo ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
