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

class SmallBricks31 {
  public:
  int countWays(int w, int h);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 3; int Arg2 = 4; verify_case(0, Arg2, countWays(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 13; verify_case(1, Arg2, countWays(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 84; verify_case(2, Arg2, countWays(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 4; int Arg1 = 9; int Arg2 = 132976888; verify_case(3, Arg2, countWays(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 5; int Arg1 = 5; int Arg2 = 11676046; verify_case(4, Arg2, countWays(Arg0, Arg1)); }

// END CUT HERE

};

vector<int> next[1 << 10];
int W;

void fill(int below, int mask, int position, vector<int> &store) {
    if (position == W) {
        store.push_back( mask );
        return;
    }
    
    fill(below, mask, position + 1, store); // place nothing
    if (below & 1 << position) { // place width 1 brick.
        fill(below, mask | (1 << position), position + 1, store);
    }
    if (position + 1 < W) {
        if ((below & 3 << position) == 3 << position) { // place width 2 brick.
            fill(below, mask | 3 << position, position + 2, store);
        }
    }
    
    if (position + 2 < W) {
        if ((below & 5 << position) == 5 << position) { // place width 3 brick.
            fill(below, mask | 7 << position, position + 3, store);
        }
    }
}

int dp[11][1 << 10];
const int mod = 1e9+7;

int SmallBricks31::countWays(int w, int h) {
    W = w;
    for (int below = 0; below < 1 << w; ++below) {
        next[below].clear();
        fill(below, 0, 0, next[below]);
    }
    
    memset(dp, 0, sizeof dp);
    dp[0][(1 << W) - 1] = 1;
    for (int i = 0; i < h; ++i) {
        for (int below = 0; below < 1 << w; ++below) {
            if (dp[i][below] == 0) continue;
            
            foreach(p, next[below]) {
                dp[i + 1][*p] += dp[i][below];
                dp[i + 1][*p] %= mod;
            }
        }
    }
    int ans = 0;
    for (int last = 0; last < 1 << w; ++last) {
        ans += dp[h][last];
        ans %= mod;
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    SmallBricks31 ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
