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

class RotatedClock {
  public:
  string getEarliest(int hourHand, int minuteHand);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 70; int Arg1 = 300; string Arg2 = "08:20"; verify_case(0, Arg2, getEarliest(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 90; int Arg1 = 120; string Arg2 = "11:00"; verify_case(1, Arg2, getEarliest(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 240; int Arg1 = 36; string Arg2 = ""; verify_case(2, Arg2, getEarliest(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 19; int Arg1 = 19; string Arg2 = ""; verify_case(3, Arg2, getEarliest(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 1; int Arg1 = 12; string Arg2 = "00:02"; verify_case(4, Arg2, getEarliest(Arg0, Arg1)); }

// END CUT HERE

};

char s[32];

string RotatedClock::getEarliest(int hourHand, int minuteHand) {
	for (int m = 0; m < 12 * 60; m += 2){
		int ah = (m / 2) % 360;
		int am = (6 * m) % 360;
		
		int th = hourHand, tm = minuteHand;
		for (int i = 0; i <= 12; ++i) {
			th = ((th - 30) % 360 + 360) % 360;
			tm = ((tm - 30) % 360 + 360) % 360;
			if (ah == th and am == tm) {
				sprintf(s, "%.2d:%.2d", m / 60, m % 60);
				return string(s);
			}
		}
	}
	return "";
}

// BEGIN CUT HERE
int main(){
    RotatedClock ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
