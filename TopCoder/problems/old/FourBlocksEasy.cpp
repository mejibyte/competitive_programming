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

class FourBlocksEasy {
  public:
  int maxScore(vector <string> grid);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {".....1..1..",
 "..1.....1.."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 70; verify_case(0, Arg1, maxScore(Arg0)); }
	void test_case_1() { string Arr0[] = {"....................",
 "...................."}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 160; verify_case(1, Arg1, maxScore(Arg0)); }
	void test_case_2() { string Arr0[] = {".1.........11.........",
 "..1.1......11........."}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 128; verify_case(2, Arg1, maxScore(Arg0)); }
	void test_case_3() { string Arr0[] = {"......1.....1...1.",
 ".................."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 108; verify_case(3, Arg1, maxScore(Arg0)); }

// END CUT HERE

};

int FourBlocksEasy::maxScore(vector <string> grid) {
    int rows = 2;
    int cols = grid[0].size();
    for (int j = 0; j + 1 < cols; ++j) {
        if (grid[0][j] == '.' and grid[1][j] == '.' and grid[0][j + 1] == '.' and grid[1][j + 1] == '.') {
            grid[0][j] = grid[1][j] = grid[0][j + 1] = grid[1][j + 1] = '4';
        }
    }
    int ans = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == '4') ans += 4;
            else ans += 1;
        }
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    FourBlocksEasy test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
