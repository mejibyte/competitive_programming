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

class EscapingJail {
  public:
  int getMaxDistance(vector <string> chain);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0568",
 "5094",
 "6903",
 "8430"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(0, Arg1, getMaxDistance(Arg0)); }
	void test_case_1() { string Arr0[] = {"0 ",
 " 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(1, Arg1, getMaxDistance(Arg0)); }
	void test_case_2() { string Arr0[] = {"0AxHH190",
 "A00f3AAA",
 "x00     ",
 "Hf 0  x ",
 "H3  0   ",
 "1A   0  ",
 "9A x  0Z",
 "0A    Z0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 43; verify_case(2, Arg1, getMaxDistance(Arg0)); }
	void test_case_3() { string Arr0[] = {"00",
 "00"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, getMaxDistance(Arg0)); }

// END CUT HERE

};

int d[55][55];

int EscapingJail::getMaxDistance(vector <string> chain) {
    int n = chain.size();
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            char c = chain[i][j];
            if ('0' <= c and c <= '9') d[i][j] = c - '0';
            else if ('a' <= c and c <= 'z') d[i][j] = c - 'a' + 10;
            else if ('A' <= c and c <= 'Z') d[i][j] = c - 'A' + 36;
            else d[i][j] = 1 << 28;
        }
    }
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    
    int ans = INT_MIN;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ans = max(ans, d[i][j]);
        }
    }
    if (ans == 1 << 28) ans = -1;
    return ans;
}

// BEGIN CUT HERE
int main(){
    EscapingJail ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
