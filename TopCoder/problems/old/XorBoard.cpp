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

class XorBoard {
  public:
  int count(int H, int W, int Rcount, int Ccount, int S);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; int Arg3 = 2; int Arg4 = 4; int Arg5 = 4; verify_case(0, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 0; int Arg3 = 0; int Arg4 = 1; int Arg5 = 0; verify_case(1, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 20; int Arg2 = 50; int Arg3 = 40; int Arg4 = 200; int Arg5 = 333759825; verify_case(2, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 1200; int Arg1 = 1000; int Arg2 = 800; int Arg3 = 600; int Arg4 = 4000; int Arg5 = 96859710; verify_case(3, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arg0 = 555; int Arg1 = 555; int Arg2 = 555; int Arg3 = 555; int Arg4 = 5550; int Arg5 = 549361755; verify_case(4, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

const int MAXN = 1555 * 2 + 100;
int choose[MAXN][MAXN];
const int mod = 555555555;

int XorBoard::count(int H, int W, int Rcount, int Ccount, int S) {
  memset(choose, 0, sizeof choose);
  choose[0][0] = 1;
  for (int i = 1; i < MAXN; ++i) {
    for (int j = 0; j < MAXN; ++j) {
      choose[i][j] = choose[i - 1][j];
      if (j - 1 >= 0) {
        choose[i][j] += choose[i - 1][j - 1];
        choose[i][j] %= mod;
      }
    }
  }

  int ans = 0;
  for (int i = Rcount % 2; i <= H and i <= Rcount; i += 2) {
    for (int j = Ccount % 2; j <= W and j <= Ccount; j += 2) {
      if (i*W + j*H - 2*i*j == S) {
        long long add = choose[H][i];
        add = (1LL * add * choose[W][j]) % mod;
        add = (1LL * add * choose[ (Rcount - i)/2 + H - 1][H - 1]) % mod;
        add = (1LL * add * choose[ (Ccount - j)/2 + W - 1][W - 1]) % mod;        
        ans += add % mod;
        ans %= mod;
      }
    }
  }
  return ans % mod;
}

// BEGIN CUT HERE
int main(){
    XorBoard test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
