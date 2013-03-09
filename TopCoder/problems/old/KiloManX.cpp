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

class KiloManX {
  public:
  int leastShots(vector <string> damageChart, vector <int> bossHealth);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"070","500","140"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {150,150,150}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 218; verify_case(0, Arg2, leastShots(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"1542", "7935", "1139", "8882"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {150,150,150,150}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 205; verify_case(1, Arg2, leastShots(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"07", "40"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {150,10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 48; verify_case(2, Arg2, leastShots(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"198573618294842",
 "159819849819205",
 "698849290010992",
 "000000000000000",
 "139581938009384",
 "158919111891911",
 "182731827381787",
 "135788359198718",
 "187587819218927",
 "185783759199192",
 "857819038188122",
 "897387187472737",
 "159938981818247",
 "128974182773177",
 "135885818282838"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {157, 1984, 577, 3001, 2003, 2984, 5988, 190003,
9000, 102930, 5938, 1000000, 1000000, 5892, 38}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 260445; verify_case(3, Arg2, leastShots(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"02111111", "10711111", "11071111", "11104111",
 "41110111", "11111031", "11111107", "11111210"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {28,28,28,28,28,28,28,28}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 92; verify_case(4, Arg2, leastShots(Arg0, Arg1)); }

// END CUT HERE

};

int dp[1 << 15];

int KiloManX::leastShots(vector <string> damageChart, vector <int> bossHealth) {
    int n = bossHealth.size();
    for (int i = 0; i < 1 << n; ++i) dp[i] = INT_MAX;
    dp[0] = 0;
    for (int dead = 0; dead < 1 << n; ++dead) {
        for (int next_kill = 0; next_kill < n; ++next_kill) {
            if (dead & (1 << next_kill)) continue;
            int best_weapon = 1;
            for (int i = 0; i < n; ++i) if (dead & (1 << i)) {
                best_weapon = max(best_weapon, damageChart[i][next_kill] - '0');
            }
            int new_dead = dead | (1 << next_kill);
            int new_cost = dp[dead] + (bossHealth[next_kill] + best_weapon - 1) / best_weapon;
            dp[new_dead] = min(dp[new_dead], new_cost);
        }
    }
    return dp[(1 << n) - 1];
}

// BEGIN CUT HERE
int main(){
    KiloManX test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
