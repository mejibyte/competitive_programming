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

class FoxAndSorting {
  public:
  long long get(long long idx);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 10LL; long long Arg1 = 100000000LL; verify_case(0, Arg1, get(Arg0)); }
	void test_case_1() { long long Arg0 = 1000000000000000000LL; long long Arg1 = 999999999999999999LL; verify_case(1, Arg1, get(Arg0)); }
	void test_case_2() { long long Arg0 = 58LL; long long Arg1 = 100000000100LL; verify_case(2, Arg1, get(Arg0)); }
	void test_case_3() { long long Arg0 = 314159265358979LL; long long Arg1 = 646003042230121105LL; verify_case(3, Arg1, get(Arg0)); }
	void test_case_4() { long long Arg0 = 271828182845904523LL; long long Arg1 = 132558071125756493LL; verify_case(4, Arg1, get(Arg0)); }

// END CUT HERE

};

bool been[20][170][2];
long long memo[20][170][2];

long long ways(int len, int sum, bool canStartWithZero) {
    if (sum < 0) return 0;
    if (sum == 0) {
        assert(canStartWithZero);
        return 1 + len;
    }
    if (len <= 0) return 0;
    if (been[len][sum][canStartWithZero]) return memo[len][sum][canStartWithZero];
    long long ans = 0;
    for (int place = canStartWithZero ? 0 : 1; place <= 9; ++place) {
        ans += ways(len - 1, sum - place, true);
    }
    been[len][sum][canStartWithZero] = true;
    memo[len][sum][canStartWithZero] = ans;
    return ans;
}

long long FoxAndSorting::get(long long idx) {
    if (idx-- == 1) return 0;

    int sum;
    for (sum = 1; sum <= 9 * 18; ++sum) {
        long long k = ways(18, sum, false);
        if (k >= idx) break;
        idx -= k;
    }
    
    long long ans = 0;
    int len = 18;
    
    bool first = true;
    while (sum > 0 or idx > 1) {
        if (sum == 0) idx--;
        for (int i = first; i <= 9; ++i) {
            long long k = ways(len - 1, sum - i, true);
            if (k >= idx) {
                ans = 10 * ans + i;
                sum -= i;
                len--;
                break;
            }
            else idx -= k;
        }
        first = false;
    }

    return ans;
}

// BEGIN CUT HERE
int main(){
    FoxAndSorting ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
