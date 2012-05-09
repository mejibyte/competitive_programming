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

class JumpyNum {
  public:
  int howMany(int low, int high);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 10; int Arg2 = 9; verify_case(0, Arg2, howMany(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 9; int Arg1 = 23; int Arg2 = 9; verify_case(1, Arg2, howMany(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 2000000000; int Arg1 = 2000000000; int Arg2 = 0; verify_case(2, Arg2, howMany(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 8000; int Arg1 = 20934; int Arg2 = 3766; verify_case(3, Arg2, howMany(Arg0, Arg1)); }

// END CUT HERE

};

vector<int> limit;

int memo[11][10][2];
int seen = 0;

int f(int pos, int last, bool less) {
    assert(pos < 11 and last < 10);
    
    if (pos == limit.size()) return 1;

    if (memo[pos][last][less] != -1) return memo[pos][last][less];

    int high = less ? 9 : limit[pos];
    
    int ans = 0;
    for (int place = 0; place <= high; ++place) {
        if (abs(place - last) <= 1) continue;
        ans += f(pos + 1, place, less || place < limit[pos]);
    }
    return memo[pos][last][less] = ans;
}

int count(int x) {
    if (x == 0) return 0;
    
    limit.clear();
    while (x > 0) limit.push_back(x % 10), x /= 10;
    reverse(limit.begin(), limit.end());
    memset(memo, -1, sizeof memo);
    
    //for (int i = 0; i < limit.size(); ++i) printf("%d ", limit[i]);

    int ans = 0;
    for (int d = 1; d <= limit[0]; ++d) ans += f(1, d, d < limit[0]);
    
    for (int i = 1; i < limit.size(); ++i) {
        for (int d = 1; d <= 9; ++d) {
            ans += f(i + 1, d, true);
        }
    }
    return ans;
}

int JumpyNum::howMany(int low, int high) {
    return count(high) - count(low - 1);
}

// BEGIN CUT HERE
int main(){
    JumpyNum ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
