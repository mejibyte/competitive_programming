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

class BricksN {
  public:
  int countStructures(int w, int h, int k);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 3; int Arg3 = 13; verify_case(0, Arg3, countStructures(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 3; int Arg3 = 83; verify_case(1, Arg3, countStructures(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 5; int Arg2 = 1; int Arg3 = 6; verify_case(2, Arg3, countStructures(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 10; int Arg2 = 3; int Arg3 = 288535435; verify_case(3, Arg3, countStructures(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

const int MAXW = 55, mod = 1000000007;

int line[MAXW];
int ways[MAXW][MAXW];


// Top down approach
bool been[MAXW][MAXW];
long long memo[MAXW][MAXW];
long long solve(int w, int h) {
    if (w <= 0) return 1;
    if (h == 0) return 1;
    
    if (been[w][h]) return memo[w][h];
    
    long long ans = 0;
    for (int hole = 0; hole <= w; ++hole) {
        long long left = (solve(hole, h - 1) * line[hole]) % mod;
        long long right = solve(w - hole - 1, h);
        
        ans += (left * right) % mod;
        ans %= mod;
    }
    memo[w][h] = ans;
    been[w][h] = true;
    return ans;
}

int BricksN::countStructures(int W, int H, int K) {
    // Shared
    line[0] = 1;
    for (int i = 1; i <= W; ++i) {
        line[i] = 0;
        for (int piece = 1; piece <= K and piece <= i; ++piece) {
            line[i] += line[i - piece];
            line[i] %= mod;
        }
    }
    
    // Bottom up approach
    for (int w = 0; w <= W; ++w) {
        for (int h = 0; h <= H; ++h) {
            ways[w][h] = 0;
            if (w == 0 or h == 0) ways[w][h] = 1;
        }
    }
    
    for (int w = 1; w <= W; ++w) {
        for (int h = 1; h <= H; ++h) {
            int ans = 0;
            for (int hole = 0; hole <= w; ++hole) {
                int left = (1LL * ways[hole][h - 1] * line[hole]) % mod;
                int right = w - hole - 1 >= 0 ? ways[w - hole - 1][h] : 1;
                ans += (1LL * left * right) % mod;
                ans %= mod;
            }
            ways[w][h] = ans;
        }
    }
    
    memset(been, false, sizeof been);
    int ans = solve(W, H);
    
    // Both approaches should yield the same answer
    assert(ans == ways[W][H]);
    
    return ways[W][H];
}

// BEGIN CUT HERE
int main(){
    BricksN ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
