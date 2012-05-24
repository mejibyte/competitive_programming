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

class WorkingRabbits {
  public:
  double getEfficiency(vector <string> profit);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = { "071", 
  "702", 
  "120" }
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 3.3333333333333335; verify_case(0, Arg1, getEfficiency(Arg0)); }
	void test_case_1() { string Arr0[] = { "00", 
  "00" }
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.0; verify_case(1, Arg1, getEfficiency(Arg0)); }
	void test_case_2() { string Arr0[] = { "0999", 
  "9099", 
  "9909", 
  "9990" }
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 9.0; verify_case(2, Arg1, getEfficiency(Arg0)); }
	void test_case_3() { string Arr0[] = { "013040", 
  "100010", 
  "300060", 
  "000008", 
  "416000", 
  "000800" }
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.5333333333333334; verify_case(3, Arg1, getEfficiency(Arg0)); }
	void test_case_4() { string Arr0[] = { "06390061", 
  "60960062", 
  "39090270", 
  "96900262", 
  "00000212", 
  "00222026", 
  "66761201", 
  "12022610" }
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 3.2142857142857144; verify_case(4, Arg1, getEfficiency(Arg0)); }

// END CUT HERE

};

double WorkingRabbits::getEfficiency(vector <string> profit) {
    double p = 0, q = 0;
    for (int i = 0; i < profit.size(); ++i) {
        for (int j = i + 1; j < profit.size(); ++j) {
            p += profit[i][j] - '0';
            q += 1;
        }
    }
    return p / q;
}

// BEGIN CUT HERE
int main(){
    WorkingRabbits test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
