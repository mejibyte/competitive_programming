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

class LeftRightDigitsGame {
  public:
  string minNumber(string digits);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "565"; string Arg1 = "556"; verify_case(0, Arg1, minNumber(Arg0)); }
	void test_case_1() { string Arg0 = "9876543210"; string Arg1 = "1234567890"; verify_case(1, Arg1, minNumber(Arg0)); }
	void test_case_2() { string Arg0 = "8016352"; string Arg1 = "1086352"; verify_case(2, Arg1, minNumber(Arg0)); }

// END CUT HERE

};

string memo[55][55][2];
bool been[55][55][2];
string s;

string best(int i, int j, int lowest) {
  if (i > j) return "";
  if (been[i][j][lowest]) return memo[i][j][lowest];
  int len = j - i + 1;
  string ans(len, '9' + 1);
  for (int k = i; k <= j; ++k) {
    if (s[k] - '0' >= lowest) {
      ans = min(ans, s.substr(k, 1) + best(i, k - 1, 0) + s.substr(k + 1, j - (k + 1) + 1) );
    }
  }
  been[i][j][lowest] = true;
  memo[i][j][lowest] = ans;
  return ans;
}

string LeftRightDigitsGame::minNumber(string digits) {
  s = digits;
  memset(been, 0, sizeof been);
  return best(0, s.size() - 1, 1);
}

// BEGIN CUT HERE
int main(){
    LeftRightDigitsGame test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
