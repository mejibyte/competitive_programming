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

class PatrolRoute {
  public:
  int countRoutes(int X, int Y, int minT, int maxT);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 1; int Arg3 = 20000; int Arg4 = 6; verify_case(0, Arg4, countRoutes(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 4; int Arg3 = 7; int Arg4 = 0; verify_case(1, Arg4, countRoutes(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 6; int Arg2 = 9; int Arg3 = 12; int Arg4 = 264; verify_case(2, Arg4, countRoutes(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 7; int Arg1 = 5; int Arg2 = 13; int Arg3 = 18; int Arg4 = 1212; verify_case(3, Arg4, countRoutes(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 4000; int Arg1 = 4000; int Arg2 = 4000; int Arg3 = 14000; int Arg4 = 859690013; verify_case(4, Arg4, countRoutes(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

const int MAXS = 8005;

long long C[MAXS];
const int mod = 1000000007;

int PatrolRoute::countRoutes(int X, int Y, int minT, int maxT) {
    memset(C, 0, sizeof C);
    long long ans = 0;
    
    for (int x1 = 0; x1 < X; ++x1) {
        for (int x3 = x1 + 2; x3 < X; ++x3) {
            int sum = 2 * (x3 - x1);
            assert(sum < MAXS);
            C[sum] += (x3 - x1 - 1);
            C[sum] %= mod;
        }
    }
    for (int i = 1; i < MAXS; ++i) {
        (C[i] += C[i - 1]) %= mod;
    }
    
    for (int y1 = 0; y1 < Y; ++y1) {
        for (int y3 = y1 + 2; y3 < Y; ++y3) {
            int sum = 2 * (y3 - y1);
            assert(sum < MAXS);
            
            int low = max(0, minT - sum);
            int high = min(maxT - sum, MAXS - 1);

            if (low <= high and 0 <= high and high < MAXS) {
                long long add = C[high];
                if (low - 1 >= 0) add -= C[low - 1];
                add = (add % mod + mod) % mod;
            
                ans += (1LL * add * (y3 - y1 - 1)) % mod;
                ans %= mod;
            }
        }
    }
    
    (ans *= 6) %= mod;
    return ans;
}

// BEGIN CUT HERE
int main(){
    PatrolRoute test;
//    test.run_test(0);
//    return 0;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
