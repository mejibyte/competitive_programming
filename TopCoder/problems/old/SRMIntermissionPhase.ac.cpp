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
#include <bitset>
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

class SRMIntermissionPhase {
  public:
  int countWays(vector <int> points, vector <string> description);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {25000, 50000, 100000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"YNN",
 "NNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 25000; verify_case(0, Arg2, countWays(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {30000, 60000, 90000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NYN",
 "NYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 799969993; verify_case(1, Arg2, countWays(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {25000, 45000, 110000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNN",
 "YYY"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(2, Arg2, countWays(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {25600, 51200, 102400}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NYY",
 "YNY",
 "YYY",
 "YNN",
 "YYN",
 "NNY",
 "NYN",
 "NNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 867560805; verify_case(3, Arg2, countWays(Arg0, Arg1)); }

// END CUT HERE

};

const int MAXS = 200005; 
int ways[20][MAXS];
int dp[2][MAXS];
int sum[MAXS];
const int mod = 1000000007;

int SRMIntermissionPhase::countWays(vector <int> points, vector <string> description) {
    memset(ways, 0, sizeof ways);
    const int n = description.size();
    
    // ways[i][s] = In how many different ways can contestant i get a score of s.
    for (int i = 0; i < n; ++i) {
        ways[i][0] = 1;
        
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < MAXS; ++k) {
                sum[k] = ways[i][k];
                if (k - 1 >= 0) {
                    sum[k] += sum[k - 1];
                    sum[k] %= mod;
                }
            }
            
            int a, b;
            if (description[i][j] == 'Y') a = 1, b = points[j];
            else a = b = 0;

            for (int s = 0; s < MAXS; ++s) {
                ways[i][s] = 0;
                
                int from = s - b;
                int to = s - a;
                if (to < 0) continue;
                from = max(from, 0);
                ways[i][s] = sum[to];
                if (from - 1 >= 0) {
                    ways[i][s] -= sum[from - 1];
                    if (ways[i][s] < 0) ways[i][s] += mod;
                }
            }
        }
    }
    
    memset(dp, 0, sizeof dp);
    dp[1][MAXS - 1] = 1;

    // dp[i][s] = How many different scoreboards there exist considering only 
    // contestants [0..i] such that the last one got a score of s.
    for (int i = 0; i < n; ++i) {
        int cur = i & 1;
        int prev = cur ^ 1;

        for (int k = MAXS - 1; k >= 0; --k) {
            sum[k] = dp[prev][k] % mod;
            if (k + 1 < MAXS) {
                sum[k] += sum[k + 1];
                sum[k] %= mod;
            }
        }
        for (int k = 0; k < MAXS; ++k) {
            dp[cur][k] = 0;
            if (k + 1 < MAXS) {
                long long add = 1LL * ways[i][k] * sum[k + 1];
                add %= mod;
                dp[cur][k] += add;
                dp[cur][k] %= mod;
            }
            
            assert(0 <= cur and cur <= 1 and 0 <= k and k < MAXS);
        }
    }
    
    int ans = 0;
    int last = (n - 1) & 1;
    for (int s = 0; s < MAXS; ++s) {
        ans += dp[last][s];
        ans %= mod;
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    SRMIntermissionPhase test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
