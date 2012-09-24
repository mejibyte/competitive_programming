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

class TheLuckyGameDivTwo {
  public:
  int find(int a, int b, int jLen, int bLen);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 10; int Arg2 = 2; int Arg3 = 1; int Arg4 = 0; verify_case(0, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 100; int Arg2 = 100; int Arg3 = 100; int Arg4 = 6; verify_case(1, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 8; int Arg2 = 3; int Arg3 = 2; int Arg4 = 1; verify_case(2, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 1; int Arg1 = 100; int Arg2 = 75; int Arg3 = 50; int Arg4 = 2; verify_case(3, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

bool is_lucky(int x) {
    if (x < 10) return (x == 4 or x == 7);
    if (x % 10 != 4 and x % 10 != 7) return false;
    return is_lucky(x / 10);
}

const int MAXN = 5005;
int lucky[MAXN];

int TheLuckyGameDivTwo::find(int a, int b, int jlen, int blen) {
    for (int i = 0; i < MAXN; ++i) {
        lucky[i] = is_lucky(i);
        if (i - 1 >= 0) lucky[i] += lucky[i - 1];
    }
    
    int ans = 0;
    for (int e = a; ; ++e) {
        int f = e + jlen - 1;
        if (f > b) break;
        
        int best = INT_MAX;
        for (int p = e; p + blen - 1 <= f; ++p) {
            best = min(best, lucky[p + blen - 1] - lucky[p - 1]);
        }
        ans = max(ans, best);
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    TheLuckyGameDivTwo test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
