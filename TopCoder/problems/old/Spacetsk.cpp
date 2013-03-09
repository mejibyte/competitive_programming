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

class Spacetsk {
  public:
  int countsets(int L, int H, int K);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 2; int Arg3 = 4; verify_case(0, Arg3, countsets(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; int Arg3 = 4; verify_case(1, Arg3, countsets(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 1; int Arg3 = 9; verify_case(2, Arg3, countsets(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; int Arg3 = 23; verify_case(3, Arg3, countsets(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 5; int Arg1 = 5; int Arg2 = 3; int Arg3 = 202; verify_case(4, Arg3, countsets(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 561; int Arg1 = 394; int Arg2 = 20; int Arg3 = 786097180; verify_case(5, Arg3, countsets(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

const int MAXN = 2005;
const int mod = int(1e9+7);
long long choose[MAXN][MAXN];
bool used[MAXN][MAXN];

int Spacetsk::countsets(int L, int H, int K) {
    if (K == 1) {
        return (1LL * (H + 1) * (L + 1)) % mod;
    }
    
    memset(used, 0, sizeof used);
    
    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j < MAXN; ++j) {
            choose[i][j] = 0;
            
            if (i == 0 and j == 0) {
                choose[i][j] = 1;
            } else {
                if (i - 1 >= 0) {
                    choose[i][j] += choose[i - 1][j];
                    if (j - 1 >= 0) {
                        choose[i][j] += choose[i - 1][j - 1];
                        choose[i][j] %= mod;
                    }
                }
            }
        }
    }
    
    long long ans = 0;
    // vertical
    ans += (1LL * (L + 1) * choose[H + 1][K]) % mod;

    // positive
    for (int dy = 1; dy < MAXN; ++dy) {
        for (int dx = 1; dx < MAXN; ++dx) {
            if (used[dx][dy]) continue;
            for (long long t = 0; t * dx < MAXN and t * dy < MAXN; ++t) {
                used[t*dx][t*dy] = true;
            }
            
            vector<int> x;
            
            int xx = 0, yy = 0;
            while (xx <= L and yy <= H) {
                x.push_back(xx);
                
                xx += dx;
                yy += dy;
            }
            
            if (x.size() < K) continue;
            assert(x.back() <= L);
            
            int j = x.size() - 1;
            for (int cur = 0; j >= 0; --j) {
                int next = L - x[j];
                if (cur <= next) {                    
                    long long times = next - cur + 1;
                    int size = j + 1;
                    
                    if (size >= K) {
                        ans += (times * choose[size][K]) % mod;
                        ans %= mod;
                        ans += (times * choose[size][K]) % mod;
                        ans %= mod;
                    }
                }
                cur = next + 1;
            }
        }
    }

    return ans % mod;
}

// BEGIN CUT HERE
int main(){
    Spacetsk test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
