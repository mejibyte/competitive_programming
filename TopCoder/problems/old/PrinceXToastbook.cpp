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

class PrinceXToastbook {
  public:
  double eat(vector <int> prerequisite);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {-1, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.5; verify_case(0, Arg1, eat(Arg0)); }
	void test_case_1() { int Arr0[] = {-1, 0, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.6666666666666667; verify_case(1, Arg1, eat(Arg0)); }
	void test_case_2() { int Arr0[] = {1, -1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 2.0; verify_case(2, Arg1, eat(Arg0)); }
	void test_case_3() { int Arr0[] = {1, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.0; verify_case(3, Arg1, eat(Arg0)); }
	void test_case_4() { int Arr0[] = {-1, -1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 2.0; verify_case(4, Arg1, eat(Arg0)); }

// END CUT HERE

};

const int MAXN = 55;
double dp[MAXN][MAXN];

void compute() {
    for (int k = 1; k < MAXN; ++k) dp[0][k] = 0.0;
    dp[0][0] = 1.0;
    for (int n = 1; n < MAXN; ++n) {
        for (int k = 0; k < MAXN; ++k) {
            dp[n][k] = 1.0*(n-k)/n * dp[n-1][k];
            if (k - 1 >= 0) {
                dp[n][k] += 1.0/n*dp[n-1][k-1];
            }
        }
    }
}

double PrinceXToastbook::eat(vector <int> prev) {
    compute();
    
    double ans = 0;
    int n = prev.size();
    for (int i = 0; i < n; ++i) {
        vector<bool> visited(n, false);
        bool valid = true;

        int cnt = 0; // how many prerequisites I have, transitively
        for (int cur = i; cur != -1; cur = prev[cur]) {
            if (visited[cur]) {
                valid = false;
                break;
            }
            visited[cur] = true;
            cnt++;
        }
        if (!valid) continue;
        ans += 1.0 * dp[n][cnt];
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    PrinceXToastbook test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
