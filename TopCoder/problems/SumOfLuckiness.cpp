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

class SumOfLuckiness {
  public:
  long long theSum(int A, int B);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 10; long long Arg2 = 2LL; verify_case(0, Arg2, theSum(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 40; int Arg1 = 47; long long Arg2 = 8LL; verify_case(1, Arg2, theSum(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 58; int Arg1 = 526; long long Arg2 = 231LL; verify_case(2, Arg2, theSum(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 4444; int Arg1 = 7777; long long Arg2 = 2338LL; verify_case(3, Arg2, theSum(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 585858585; int Arg1 = 858585858; long long Arg2 = 287481025LL; verify_case(4, Arg2, theSum(Arg0, Arg1)); }

// END CUT HERE

};

long long memo[10][10][10][2];

vector<int> num;

long long f(int cur, int fours, int sevens, bool equal) {
    if (cur == -1) return abs(fours - sevens);
    if (memo[cur][fours][sevens][equal] != -1) return memo[cur][fours][sevens][equal];
    
    long long ans = 0;
    for (int next = 0; next <= 9; ++next) {
        if (!equal || next <= num[cur]) {
            ans += f(cur - 1, fours + (next == 4), sevens + (next == 7), equal and next == num[cur]);
        }
    }
    memo[cur][fours][sevens][equal] = ans;
    return ans;
}

long long count(int bound) {
    if (bound <= 3) return 0;
    num.clear();
    while (bound > 0) {
        num.push_back(bound % 10);
        bound /= 10;
    }
    memset(memo, -1, sizeof memo);
    return f(num.size() - 1, 0, 0, true);
}

long long SumOfLuckiness::theSum(int A, int B) {
    return count(B) - count(A - 1);
}

// BEGIN CUT HERE
int main(){
    SumOfLuckiness ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
