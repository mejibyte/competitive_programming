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

class DengklekBuildingRoads {
  public:
  int numWays(int N, int M, int K);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 4; int Arg2 = 1; int Arg3 = 3; verify_case(0, Arg3, numWays(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 3; int Arg2 = 3; int Arg3 = 4; verify_case(1, Arg3, numWays(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 1; int Arg2 = 1; int Arg3 = 0; verify_case(2, Arg3, numWays(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 5; int Arg1 = 0; int Arg2 = 3; int Arg3 = 1; verify_case(3, Arg3, numWays(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 10; int Arg1 = 20; int Arg2 = 5; int Arg3 = 26964424; verify_case(4, Arg3, numWays(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

#define bit(k) (1 << (k))

int N, M, K;
int memo[35][35][10][1 << 10];

const int mod = 1000 * 1000 * 1000 + 7;

int f(int i, int m, int from, int parity) {
    if (i == N) {
        int ans = (m == 0 and parity == 0);
        return ans;
    }

    int &ans = memo[i][m][from][parity];
    if (ans != -1) return ans;
    
    if (from == 0){
        if (parity & bit(K)) ans = 0;
        else ans = f(i + 1, m, K, parity << 1);
    } else {
        assert(from >= 1);
        ans = f(i, m, from - 1, parity);
        if (m > 0 and i - from >= 0) ans += f(i, m - 1, from, parity ^ 1 ^ bit(from));
    }
    ans %= mod;
    return ans;
}

int DengklekBuildingRoads::numWays(int _N, int _M, int _K) {
    N = _N, M = _M, K = _K;
    memset(memo, -1, sizeof memo);
    return f(0, M, K, 0);
}

// BEGIN CUT HERE
int main(){
    DengklekBuildingRoads ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
