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


map<long long, int> memo;

int f(int bound, int last) {
    int ans = (last > 0);
    if (bound == 0) return ans;
    
    long long key = 10LL * bound + last;
    if (memo.count(key)) return memo[key];
    
    for (int place = 0; place <= 9 and place <= bound; ++place) {
        if (abs(last - place) >= 2) {
            ans += f((bound - place) / 10, place);
        }
    }
    return memo[key] = ans;
}

int count(int bound) {
    if (bound == 0) return 0;
    int ans = 0;
    memo.clear();
    for (int place = 0; place <= 9 and place <= bound; ++place) ans += f((bound - place) / 10, place);
    return ans;
}

int JumpyNum::howMany(int low, int high) {
    return count(high) - count(low - 1);
}

// BEGIN CUT HERE
int main(){
    JumpyNum test;
    test.howMany(1, 100);
    
    for (int i = 0; i < 100; ++i) {
        int a = rand() % 100 + 1;
        int b = rand() % 100 + 1;
        if (b < a) swap(a, b);
        printf(".");
        test.howMany(a, b);
    }
    puts("");
    
    test.run_test(-1);
    
    
    return 0;
}
// END CUT HERE
