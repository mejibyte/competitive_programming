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

class NextNumber {
  public:
  int getNextNumber(int N);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1717; int Arg1 = 1718; verify_case(0, Arg1, getNextNumber(Arg0)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 8; verify_case(1, Arg1, getNextNumber(Arg0)); }
	void test_case_2() { int Arg0 = 7; int Arg1 = 11; verify_case(2, Arg1, getNextNumber(Arg0)); }
	void test_case_3() { int Arg0 = 12; int Arg1 = 17; verify_case(3, Arg1, getNextNumber(Arg0)); }
	void test_case_4() { int Arg0 = 555555; int Arg1 = 555557; verify_case(4, Arg1, getNextNumber(Arg0)); }

// END CUT HERE

};

#define popcount(x) __builtin_popcount(x)

int assemble(vector<int> v){
    int ans = 0;
    for (int i = 0; i < v.size(); ++i) {
        ans += (1 << i) * v[i];
    }
    return ans;
}

void p(vector<int> v) {
    for (int i = v.size() - 1; i >= 0; --i){
        printf("%d", v[i]);
    }
    puts("");
}

int NextNumber::getNextNumber(int N) {
    int zeros = 0, ones = popcount(N);
    vector<int> v;
    for (int i = 0; N > 0 ; ++i){
        v.push_back(!!(N & (1 << i)));
        N &= ~(1 << i);
        zeros += (v.back() == 0);
    }

    for (int i = 0; i < v.size() - 1; ++i) {
        if (v[i] == 1 and v[i + 1] == 0){
            // other solution
            swap(v[i], v[i+1]);
            sort(v.begin(), v.begin() + i, greater<int>());
            return assemble(v);
        }
    }
    
    v.clear();
    for (int i = 0; i < ones - 1; ++i){
        v.push_back(1);
    }
    for (int i = 0; i < zeros + 1; ++i){
        v.push_back(0);
    }
    v.push_back(1);
    return assemble(v);
}

// BEGIN CUT HERE
int main(){
    NextNumber ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
