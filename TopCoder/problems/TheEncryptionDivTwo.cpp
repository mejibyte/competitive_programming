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

class TheEncryptionDivTwo {
  public:
  string encrypt(string message);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "hello"; string Arg1 = "abccd"; verify_case(0, Arg1, encrypt(Arg0)); }
	void test_case_1() { string Arg0 = "abcd"; string Arg1 = "abcd"; verify_case(1, Arg1, encrypt(Arg0)); }
	void test_case_2() { string Arg0 = "topcoder"; string Arg1 = "abcdbefg"; verify_case(2, Arg1, encrypt(Arg0)); }
	void test_case_3() { string Arg0 = "encryption"; string Arg1 = "abcdefghib"; verify_case(3, Arg1, encrypt(Arg0)); }

// END CUT HERE

};

string TheEncryptionDivTwo::encrypt(string message) {
    char next = 'a';
    map<char, char> m;
    string ans = "";
    for (int i = 0; i < message.size(); ++i) {
        if (m.count(message[i]) == 0) m[message[i]] = next++;
        ans += m[message[i]];
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    TheEncryptionDivTwo ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
