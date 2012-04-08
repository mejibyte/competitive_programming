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

class FoxAndBusiness {
  public:
  double minimumCost(int K, int totalWork, vector <int> a, vector <int> p);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 10; int Arr2[] = {10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {20}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 3800.0; verify_case(0, Arg4, minimumCost(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 100; int Arr2[] = {50, 60}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1000, 2000}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 107200.0; verify_case(1, Arg4, minimumCost(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 300; int Arr2[] = {10, 20, 47}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {15, 20, 98765}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 77500.0; verify_case(2, Arg4, minimumCost(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 4; int Arg1 = 1000; int Arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {20, 30, 40, 58, 60, 70, 80, 90, 100, 150}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 531764.705882353; verify_case(3, Arg4, minimumCost(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

const int MAXS = 5000005;
int dp[2][MAXS];

double FoxAndBusiness::minimumCost(int K, int totalWork, vector <int> a, vector <int> p) {
    int n = a.size();
    const int oo = (1 << 30);
     for (int s = 0; s < MAXS; ++s) dp[0][s] = dp[0][s] = oo;
    dp[0][0] = 0;
     for (int i = 0; i < n; ++i) {
         for (int k = 1; k <= K; ++k) {
             for (int w = MAXS - 1; w >= 0; --w) {
                 dp[k & 1][w]
                 
                 if (dp[w - a[i]] < oo) {
                     dp[w] = min(dp[w], dp[w - a[i]] + p[i]);
                 }
             }
         }
     }
    return 0;
}

// BEGIN CUT HERE
int main(){
    FoxAndBusiness ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
