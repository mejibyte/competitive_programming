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

class DengklekMakingChains {
  public:
  int maxBeauty(vector <string> chains);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {".15", "7..", "402", "..3"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 19; verify_case(0, Arg1, maxBeauty(Arg0)); }
	void test_case_1() { string Arr0[] = {"..1", "7..", "567", "24.", "8..", "234"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 36; verify_case(1, Arg1, maxBeauty(Arg0)); }
	void test_case_2() { string Arr0[] = {"...", "..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, maxBeauty(Arg0)); }
	void test_case_3() { string Arr0[] = {"16.", "9.8", ".24", "52.", "3.1", "532", "4.4", "111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 28; verify_case(3, Arg1, maxBeauty(Arg0)); }
	void test_case_4() { string Arr0[] = {"..1", "3..", "2..", ".7."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(4, Arg1, maxBeauty(Arg0)); }
	void test_case_5() { string Arr0[] = {"412", "..7", ".58", "7.8", "32.", "6..", "351", "3.9", "985", "...", ".46"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 58; verify_case(5, Arg1, maxBeauty(Arg0)); }

// END CUT HERE

};

int sumRight(string s){
    assert(s.size() == 3);
    assert(s.find(".") != string::npos);
    int option = 0;
    for (int j = 2; s[j] != '.'; --j) option += s[j] - '0';
    return option;
}

int sumLeft(string s){
    assert(s.size() == 3);
    assert(s.find(".") != string::npos);
    int option = 0;
    for (int j = 0; s[j] != '.'; ++j) option += s[j] - '0';
    return option;
}

int DengklekMakingChains::maxBeauty(vector <string> chains) {
    vector<string> c;
    int ans = 0;
    for (int i = 0; i < chains.size(); ++i) {
        string s = chains[i];
        if (s.find(".") != string::npos) {
            c.push_back(s);
        } else {
            ans += s[0] + s[1] + s[2] - 3 * '0';
        }
    }
    
    int extra = 0;
    for (int i = 0; i < c.size(); ++i) {
        // place to the left
        if (c[i][2] == '.') continue;
        extra = max(extra, sumRight(c[i]));
        for (int j = 0; j < c.size(); ++j) if (i != j) {
            // place to the right
            if (c[j][0] == '.') continue;
            extra = max(extra, sumRight(c[i]) + sumLeft(c[j]));
        }
    }

    for (int i = 0; i < c.size(); ++i) {
        if (c[i][0] == '.') continue;
        extra = max(extra, sumLeft(c[i]));
        for (int j = 0; j < c.size(); ++j) if (i != j) {
            if (c[j][2] == '.') continue;
            extra = max(extra, sumLeft(c[i]) + sumRight(c[j]));
        }
    }
    
    ans += extra;

    for (int i = 0; i < c.size(); ++i) if (c[i][0] == '.' and c[i][2] == '.') ans = max(ans, c[i][1] - '0');

    return ans;
}

// BEGIN CUT HERE
int main(){
    D('.' - '0');
    DengklekMakingChains ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
