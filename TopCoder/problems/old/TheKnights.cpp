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

class TheKnights {
  public:
  double find(int n, int a, int b);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 1; int Arg2 = 1; double Arg3 = 3.3333333333333335; verify_case(0, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 47; int Arg1 = 7; int Arg2 = 74; double Arg3 = 2.0; verify_case(1, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 1; double Arg3 = 4.888888888888889; verify_case(2, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 9999; int Arg1 = 999; int Arg2 = 99; double Arg3 = 16.25885103191273; verify_case(3, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 10; int Arg1 = 1; int Arg2 = 6; double Arg3 = 7.636363636363637; verify_case(4, Arg3, find(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

int A, B, N;

int can_attack(int i, int j) {
    int ans = 0;
    int di[] = {-A, -A, -B, +B, +A, +A, -B, +B};
    int dj[] = {-B, +B, +A, +A, -B, +B, -A, -A};
    for (int k = 0; k < 8; ++k) {
        int ni = i + di[k];
        int nj = j + dj[k];
        if (ni < 0 or ni >= N) continue;
        if (nj < 0 or nj >= N) continue;
        ans++;
    }
    return ans;
}

double choose2(int k) {
    return 1.0 * k * (k - 1) / 2;
}

double TheKnights::find(int n, int a, int b) {
    if (a >= n or b >= n) return 2.0;
    
    N = n;
    A = a;
    B = b;
    
    double ans = 0.0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", can_attack(i, j));
            
            int q = can_attack(i, j) + 1;
            double bad = (n*n - q) / (n*n) * (n*n - q - 1) / (n*n - 1) / 2.0;
            ans += (1.0 - bad);
        }
        printf("\n");
    }
    
    return ans;
}

// BEGIN CUT HERE
int main(){
    TheKnights test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
