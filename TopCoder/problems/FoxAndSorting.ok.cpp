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

const int MAXL = 18 + 1;
const int MAXS = 9 * 18 + 1;

long long ways[MAXL][MAXS][2];

long long FoxAndSorting::get(long long idx) {
    if (idx == 1) return 0;
    idx--;
    
    memset(ways, 0, sizeof ways);
    for (int l = 0; l < MAXL; ++l) ways[l][0][true] = l + 1;
    
    // ways[l][s][z] = How many numbers there are of length <= l such that the sum
    //                 of their digits is exactly s. z indicates if it's allowed to
    //                 have leading zeros or not.
    for (int l = 1; l < MAXL; ++l) {
        for (int s = 1; s < MAXS; ++s) {
            for (int z = 0; z < 2; ++z) {
                for (int i = !z; i <= 9 and i <= s; ++i) {
                    ways[l][s][z] += ways[l - 1][s - i][true];
                }
            }
        }
    }
    
    int requiredSum;
    for (requiredSum = 1; requiredSum < MAXS; ++requiredSum) {
        long long k = ways[18][requiredSum][false];
        if (k >= idx) break;
        else idx -= k;
    }
    
    // the sum of digits of the answer is requiredSum
    long long ans = 0;
    for (int len = 18; !(requiredSum == 0 and idx == 1); len--) {
        assert(len >= 1);
        if (requiredSum == 0 and idx > 0) idx--;
        for (int i = (len == 18); i <= 9; ++i) {
            long long k = ways[len - 1][requiredSum - i][true];
            if (k >= idx) { // found next digit
                ans = ans * 10 + i;
                requiredSum -= i;
                break;
            } else {
                idx -= k;
            }
        }
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
