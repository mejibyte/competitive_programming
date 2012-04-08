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

class KingXMagicSpells {
  public:
  double expectedNumber(vector <int> ducks, vector <int> spellOne, vector <int> spellTwo, int K);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {5, 3, 7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 7, 4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 0, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; double Arg4 = 3.5; verify_case(0, Arg4, expectedNumber(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {5, 8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {53, 7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; double Arg4 = 21.5; verify_case(1, Arg4, expectedNumber(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {123, 456, 789, 1234, 56789}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 0, 0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 1, 2, 3, 4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 50; double Arg4 = 123.0; verify_case(2, Arg4, expectedNumber(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {83291232, 3124231, 192412, 3813249, 629231, 9998989}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {58, 37, 44, 66, 72, 19}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 0, 1, 5, 4, 3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 11; double Arg4 = 2.888186784716797E7; verify_case(3, Arg4, expectedNumber(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

double dp[51][51];

double KingXMagicSpells::expectedNumber(vector <int> ducks, vector <int> spellOne, vector <int> spellTwo, int K) {
    double ans = 0.0;
    
    for (int bit = 1; bit > 0; bit <<= 1) {
        for (int i = 0; i < ducks.size(); ++i) {
            dp[0][i] = (ducks[i] & bit) ? 1.0 : 0.0;
        }
        
        for (int k = 0; k < K; ++k) {
            for (int i = 0; i < ducks.size(); ++i) dp[k + 1][i] = 0.0;

            for (int i = 0; i < ducks.size(); ++i) {
                // spell one
                if (spellOne[i] & bit) {
                    dp[k + 1][i] += 0.5 * (1 - dp[k][i]);
                } else {
                    dp[k + 1][i] += 0.5 * dp[k][i];
                }
                // spell two
                dp[k + 1][spellTwo[i]] += 0.5 * dp[k][i];
            }
        }
        ans += dp[K][0] * bit;
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    KingXMagicSpells ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
