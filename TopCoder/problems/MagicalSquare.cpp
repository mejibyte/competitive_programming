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

class MagicalSquare {
  public:
  long long getCount(vector <string> rowStrings, vector <string> columnStrings);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"f", "o", "x"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"f", "o", "x"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 1LL; verify_case(0, Arg2, getCount(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"x", "x", "x"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"x", "", "xx"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 3LL; verify_case(1, Arg2, getCount(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"cd", "cd", "cd"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"dvd", "dvd", "dvd"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(2, Arg2, getCount(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"abab", "ab", "abab"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"abab", "ab", "abab"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 11LL; verify_case(3, Arg2, getCount(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"qwer", "asdf", "zxcv"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"qaz", "wsx", "erdfcv"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 1LL; verify_case(4, Arg2, getCount(Arg0, Arg1)); }

// END CUT HERE

};

int x[9], r[3], c[3];
string s[9];
    
vector <string> rows, cols;

int valid() {
    for (int i = 0; i < 9; ++i) if (x[i] < 0) return 0;
    for (int i = 0; i + 2 < 9; i += 3) {
        assert (x[i] + x[i + 1] + x[i + 2] != r[i / 3]);
    }
    for (int i = 0; i < 3; ++i) {
        assert (x[i] + x[i + 3] + x[i + 6] != c[i]);
    }

    for (int i = 0; i < 3; ++i) {
        s[i + 0] = cols[i].substr(0, x[i]);
        s[i + 3] = cols[i].substr(x[i],  x[i + 3]);
        s[i + 6] = cols[i].substr(x[i] + x[i + 3], x[i + 6]);
    }
    for (int i = 0; i < 9; i += 3) {
        if (s[i] + s[i + 1] + s[i + 2] != rows[i / 3]) return 0;
    }
    for (int i = 0; i < 3; ++i) {
        if (s[i] + s[i + 3] + s[i + 6] != cols[i]) return 0;
    }
    return 1;
}

long long MagicalSquare::getCount(vector <string> rows, vector <string> cols) {
    ::rows = rows;
    ::cols = cols;
    for (int i = 0; i < 3; ++i) {
        r[i] = rows[i].size();
        c[i] = cols[i].size();
    }
    
    int ans = 0;
    for (x[0] = 0; x[0] <= r[0] and x[0] <= c[0]; ++x[0]) {
        for (x[1] = 0; x[0] + x[1] <= r[0] and x[1] <= c[1]; ++x[1]) {
            for (x[3] = 0; x[3] <= r[1] and x[0] + x[3] <= c[0]; ++x[3]) {
                for (x[4] = 0; x[1] + x[4] <= c[1] and x[3] + x[4] <= r[1]; ++x[4]) {
                    
                    x[2] = r[0] - x[0] - x[1];
                    x[5] = r[1] - x[4] - x[3];
                    x[6] = c[0] - x[0] - x[3];
                    x[7] = c[1] - x[4] - x[1];
                    x[8] = r[2] - x[7] - x[6];
                    
                    if (valid()) {
                        //For(i, 0, 3) { For(j, 0, 3) { printf("%d ", x[i * 3 + j]); } puts(""); } puts("");
                        //For(i, 0, 3) { For(j, 0, 3) { printf("'%s' ", s[i * 3 + j].c_str()); } puts(""); } puts("");
                        ans++;
                    }
                }
            }
        }
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    MagicalSquare ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
