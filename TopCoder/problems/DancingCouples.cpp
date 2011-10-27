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

class DancingCouples {
  public:
  int countPairs(vector <string> canDance, int K);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"YYYY", 
 "YYYY",
 "YYYY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 24; verify_case(0, Arg2, countPairs(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"YYNN", 
 "NYYN", 
 "NNYY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 4; verify_case(1, Arg2, countPairs(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"YY", 
 "YY", 
 "YY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 0; verify_case(2, Arg2, countPairs(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"YYNNNN",
 "NYYNNN",
 "NNYYNN",
 "NNNYYN",
 "NNNNYY",
 "YNNNNY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 112; verify_case(3, Arg2, countPairs(Arg0, Arg1)); }

// END CUT HERE

};

const int MAXN = 11;

// dp[n][k][mask]
long long int dp[MAXN][MAXN][1 << MAXN];

int DancingCouples::countPairs(vector <string> canDance, int K) {
    for (int i = 0; i < MAXN; ++i){
        for (int k = 0; k < MAXN; ++k){
            for (int m = 0; m < (1 << MAXN); ++m){
                dp[i][k][m] = 0LL;
            }
        }
    }
    dp[0][0][0] = 1LL;
    
    for (int i = 1; i <= canDance.size(); ++i){
        const string &row = canDance[i - 1];
        for (int k = 0; k <= K; ++k){
            for (int m = 0; m < (1 << MAXN); ++m){
                dp[i][k][m] = dp[i-1][k][m];
                if (k == 0) continue;
                for (int j = 0; j < row.size(); ++j){
                    if (row[j] == 'Y' && (m & (1 << j))){
                        dp[i][k][m] += dp[i-1][k-1][m & ~(1 << j)];
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int m = 0; m < (1 << MAXN); ++m){
        ans += dp[canDance.size()][K][m];
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    DancingCouples ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
