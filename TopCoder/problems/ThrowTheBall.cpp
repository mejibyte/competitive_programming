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

class ThrowTheBall {
  public:
  int timesThrown(int N, int M, int L);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 3; int Arg2 = 2; int Arg3 = 10; verify_case(0, Arg3, timesThrown(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 1; int Arg2 = 3; int Arg3 = 0; verify_case(1, Arg3, timesThrown(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 3; int Arg2 = 5; int Arg3 = 4; verify_case(2, Arg3, timesThrown(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 15; int Arg1 = 4; int Arg2 = 9; int Arg3 = 15; verify_case(3, Arg3, timesThrown(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

int ThrowTheBall::timesThrown(int N, int M, int L) {
    int ans = 0;
    vector<int> p(N, 0);
    int cur = 0;
    p[cur]++;
    while (p[cur] < M) {
        ans++;
        if (p[cur] % 2 == 0){
            cur = (cur + L) % N;
        }else{
            cur = ((cur - L) % N + N) % N;
        }
        p[cur]++;
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    ThrowTheBall ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
