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

class BinaryCards {
  public:
  long long largestNumber(long long A, long long B);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 6LL; long long Arg1 = 6LL; long long Arg2 = 6LL; verify_case(0, Arg2, largestNumber(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 6LL; long long Arg1 = 7LL; long long Arg2 = 7LL; verify_case(1, Arg2, largestNumber(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 6LL; long long Arg1 = 8LL; long long Arg2 = 15LL; verify_case(2, Arg2, largestNumber(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 1LL; long long Arg1 = 11LL; long long Arg2 = 15LL; verify_case(3, Arg2, largestNumber(Arg0, Arg1)); }
	void test_case_4() { long long Arg0 = 35LL; long long Arg1 = 38LL; long long Arg2 = 39LL; verify_case(4, Arg2, largestNumber(Arg0, Arg1)); }
	void test_case_5() { long long Arg0 = 1125899906842630LL; long long Arg1 = 1125899906842632LL; long long Arg2 = 1125899906842639LL; verify_case(5, Arg2, largestNumber(Arg0, Arg1)); }

// END CUT HERE

};

long long assemble(vector<int> v) {
    long long ans = 0;
    for (int i = 0; i < v.size(); ++i) {
        if (v[i]) {
            ans |= (1LL << i);
        }
    }
    return ans;
}

long long BinaryCards::largestNumber(long long A, long long B) {
    vector<int> a, b;
    while (A) { a.push_back(A & 1); A /= 2; }
    while (B) { b.push_back(B & 1); B /= 2; }
    if (b.size() > a.size()) {
        return assemble(vector<int>(b.size(), 1));
    }
    assert(b.size() == a.size());
    vector<int> c(1, 1);
    for (int i = b.size() - 2; i >= 0; --i) {
        if (b[i] == 1 and a[i] == 0) {
            while (i >= 0) { c.push_back(1); i--; }
        } else {
            c.push_back(b[i]);
        }
    }
    
    reverse(c.begin(), c.end());
    return assemble(c);
}

// BEGIN CUT HERE
int main(){
    BinaryCards ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
