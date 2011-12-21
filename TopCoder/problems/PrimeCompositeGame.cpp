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

class PrimeCompositeGame {
  public:
  int theOutcome(int N, int K);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 1; verify_case(0, Arg2, theOutcome(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 58; int Arg1 = 1; int Arg2 = 0; verify_case(1, Arg2, theOutcome(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 30; int Arg1 = 3; int Arg2 = -2; verify_case(2, Arg2, theOutcome(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 6; int Arg1 = 3; int Arg2 = 1; verify_case(3, Arg2, theOutcome(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 526; int Arg1 = 58; int Arg2 = 19; verify_case(4, Arg2, theOutcome(Arg0, Arg1)); }

// END CUT HERE

};

bool isPrime(int x) {
    if (x <= 1) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;
    for (int i = 3; 1LL * i * i <= x; i += 2) {
        if (x % i == 0) return false;
    }
    return true;
}

vector<int> primes;

const int MAXN = 474747 + 10;
bool been[2][MAXN];
bool memo[2][MAXN];

bool IWin(int n, int k);

bool HeWins(int n, int k) {
    if (n <= 2) return false;
    if (n == 3) return true;
    
    if (been[0][n]) return memo[0][n];
    
    been[0][n] = true;
    
    for (int take = 1; take <= k; ++take) {
        if (!binary_search(primes.begin(), primes.end(), n - take)) {
            if (!IWin(n - take, k)) {
                return memo[0][n] = true;
            }
        }
    }
    return memo[0][n] = false;
}


bool IWin(int n, int k) {
    if (n <= 2) return false;
    if (n == 3) return true;
    
    if (been[1][n]) return memo[1][n];
    been[1][n] = true;
    
    int where = upper_bound(primes.begin(), primes.end(), n) - primes.begin() - 1;
    assert( primes[where] < n );
    if (primes[where] < n - k) return memo[1][n] = false;
    while (where > 0 and primes[where] >= n - k) {
        if (!HeWins(primes[where], k)) return memo[1][n] = true;
        where--;
    }
    return memo[1][n] = false;
}


int f(int n, int k) {
    int ans = 0;
    int turn = 0;
    int cur = n;
    
    while (true) {
        if (!turn) { // me
            int where = upper_bound(primes.begin(), primes.end(), n) - primes.begin() - 1;                            
            if (primes[where] < n - k) break;
            if (IWin(cur, k)) {
                int where = upper_bound(primes.begin(), primes.end(), n) - primes.begin() - 1;                
                cur = primes[where];
            } else {
                int where = upper_bound(primes.begin(), primes.end(), n - k) - primes.begin();                
                cur = primes[where];
            }
        } else { // him
            if (binary_search(primes.begin(), primes.end(), n - 1)) break;
            if (HeWins(cur, k)) {
            }
        }
        
        ans++;
        turn = !turn;
    }
}

int PrimeCompositeGame::theOutcome(int N, int K) {
    if (N <= 2) return 0;
    
    for (int i = 0; i <= N; ++i) {
        if (isPrime(i)) primes.push_back(i);
    }
    
    memset(been, 0, sizeof been);
    memset(memo, 0, sizeof memo);
    return f(N, K);
    // return f(N, K);
}

// BEGIN CUT HERE
int main(){
    PrimeCompositeGame ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
