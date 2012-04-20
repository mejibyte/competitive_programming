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

class SPartition {
  public:
  long long getCount(string s);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "oxox"; long long Arg1 = 2LL; verify_case(0, Arg1, getCount(Arg0)); }
	void test_case_1() { string Arg0 = "oooxxx"; long long Arg1 = 0LL; verify_case(1, Arg1, getCount(Arg0)); }
	void test_case_2() { string Arg0 = "xoxxox"; long long Arg1 = 4LL; verify_case(2, Arg1, getCount(Arg0)); }
	void test_case_3() { string Arg0 = "xo"; long long Arg1 = 0LL; verify_case(3, Arg1, getCount(Arg0)); }
	void test_case_4() { string Arg0 = "ooooxoox"; long long Arg1 = 8LL; verify_case(4, Arg1, getCount(Arg0)); }
	void test_case_5() { string Arg0 = "ooxxoxox"; long long Arg1 = 8LL; verify_case(5, Arg1, getCount(Arg0)); }

// END CUT HERE

};

int Left[1 << 21], Right[1 << 21];

int toBinary(const string &s) {
    int ans = 1;
    for (int i = 0; i < s.size(); ++i) {
        ans <<= 1;
        ans += (s[i] == 'x' ? 1 : 0);
    }
    return ans;
}

long long SPartition::getCount(string s) {
    memset(Left, 0, sizeof Left);
    memset(Right, 0, sizeof Right);
    
    int n = s.size();
    string t = s.substr(n / 2);
    s = s.substr(0, n / 2);
    n /= 2;
    
    for (int m = 0; m < (1 << n); ++m) {
        int pop = __builtin_popcount(m);
        if (pop >= n - pop) {
            string up, down;
            for (int i = 0; i < n; ++i) {
                if (m & (1 << i)) up += s[i];
                else down += s[i];
            }
            assert(up.size() >= down.size());
            int lcp = 0;
            while (lcp < down.size() and up[lcp] == down[lcp]) lcp++;
            if (lcp == down.size()) {
                string key = up.substr(lcp);
                Left[toBinary(key)]++;
                
                //printf("LEFT: up = %s, down = %s, key = %s\n", up.c_str(), down.c_str(), key.c_str());
            }
        }
    }
    
    for (int m = 0; m < (1 << n); ++m) {
        int pop = __builtin_popcount(m);
        if (pop <= n - pop) {
            string up, down;
            for (int i = 0; i < n; ++i) {
                if (m & (1 << i)) up += t[i];
                else down += t[i];
            }
            assert(up.size() <= down.size());
            int lcs = 0;
            while (lcs < up.size() and up[up.size() - 1 - lcs] == down[down.size() - 1 - lcs]) lcs++;
            if (lcs == up.size()) {
                string key = down.substr(0, down.size() - lcs);
                Right[toBinary(key)]++;

                //printf("RIGHT: up = %s, down = %s, key = %s\n", up.c_str(), down.c_str(), key.c_str());
            }
        }
    }
    
    long long ans = 0;
    for (int i = 0; i < (1 << (n + 1)); ++i) {
        ans += 1LL * Left[i] * Right[i];
    }
    return ans * 2;
    
}

// BEGIN CUT HERE
int main(){
    SPartition ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
