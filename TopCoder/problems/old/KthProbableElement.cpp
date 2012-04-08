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

class KthProbableElement {
  public:
  double probability(int M, int lowerBound, int upperBound, int N, int K);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 10; int Arg3 = 3; int Arg4 = 1; double Arg5 = 0.1; verify_case(0, Arg5, probability(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 2; int Arg3 = 2; int Arg4 = 2; double Arg5 = 0.5; verify_case(1, Arg5, probability(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 3; int Arg3 = 2; int Arg4 = 2; double Arg5 = 0.48148148148148145; verify_case(2, Arg5, probability(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 1; int Arg2 = 10; int Arg3 = 1; int Arg4 = 10; double Arg5 = 1.0000000000000003E-10; verify_case(3, Arg5, probability(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arg0 = 4; int Arg1 = 61; int Arg2 = 65; int Arg3 = 62; int Arg4 = 3; double Arg5 = 0.15200000000000002; verify_case(4, Arg5, probability(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

double dp[101][101][101];

double KthProbableElement::probability(int M, int L, int U, int N, int K) {
    memset(dp, 0, sizeof dp);
    
    for (int less = 0; less <= M; ++less) {
        for (int equal = 0; equal <= M; ++equal) {
            dp[0][less][equal] = 0.0;
        }
    }
    dp[0][0][0] = 1.0;
    for (int chosen = 0; chosen < M; ++chosen) {
        for (int less = 0; less <= M; ++less) {
            for (int equal = 0; equal <= M; ++equal) {
                if (dp[chosen][less][equal] == 0.0) continue;
                double here = dp[chosen][less][equal];
                int size = U - L + 1;
                dp[chosen + 1][less + 1][equal] += here * (N - L) / size;
                dp[chosen + 1][less][equal + 1] += here * 1.0 / size;
                dp[chosen + 1][less][equal] += here * (U - N) / size;
            }
        }
    }
    
    double ans = 0;
    for (int less = 0; less <= M; ++less) {
        for (int equal = 1; equal <= M; ++equal) {
            if (less < K and less + equal >= K) ans += dp[M][less][equal];
        }
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    KthProbableElement ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
