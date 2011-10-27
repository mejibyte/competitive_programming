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

class Chimney {
  public:
  int countWays(long long n);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 1LL; int Arg1 = 24; verify_case(0, Arg1, countWays(Arg0)); }
	void test_case_1() { long long Arg0 = 2LL; int Arg1 = 1088; verify_case(1, Arg1, countWays(Arg0)); }
	void test_case_2() { long long Arg0 = 5LL; int Arg1 = 110198784; verify_case(2, Arg1, countWays(Arg0)); }
	void test_case_3() { long long Arg0 = 6LL; int Arg1 = 138284509; verify_case(3, Arg1, countWays(Arg0)); }
	void test_case_4() { long long Arg0 = 100000LL; int Arg1 = 19900327; verify_case(4, Arg1, countWays(Arg0)); }

// END CUT HERE

};

const int mod = 1000000007;

struct Matrix {
    int m[2][2];
};

Matrix operator * (Matrix left, Matrix right) {
    Matrix ans;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            ans.m[i][j] = 0;
            for (int k = 0; k < 2; ++k) {
                ans.m[i][j] += (1LL * left.m[i][k] * right.m[k][j]) % mod;
                ans.m[i][j] %= mod;
            }
        }
    }
    return ans;
}

Matrix pow(Matrix a, long long n) {
    if (n == 1) return a;
    if (n == 2) return a * a;
    if (n % 2 == 0) {
        Matrix half = pow(a, n / 2);
        return half * half;
    } else {
        return a * pow(a, n - 1);
    }
}

int Chimney::countWays(long long n) {
    Matrix a;
    a.m[0][0] =  0; a.m[0][1] = 1;
    a.m[1][0] = -8; a.m[1][1] = 8;
    a = pow(a, 2LL * n);
    
    int ans = (1LL * a.m[0][0] + 4LL * a.m[0][1]) % mod;
    ans = (ans + mod) % mod;
    return ans;
}

// BEGIN CUT HERE
int main(){
    Chimney ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
