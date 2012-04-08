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

class EllysFractions {
  public:
  long long getCount(int N);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; long long Arg1 = 0LL; verify_case(0, Arg1, getCount(Arg0)); }
	void test_case_1() { int Arg0 = 2; long long Arg1 = 1LL; verify_case(1, Arg1, getCount(Arg0)); }
	void test_case_2() { int Arg0 = 3; long long Arg1 = 3LL; verify_case(2, Arg1, getCount(Arg0)); }
	void test_case_3() { int Arg0 = 5; long long Arg1 = 9LL; verify_case(3, Arg1, getCount(Arg0)); }
	void test_case_4() { int Arg0 = 100; long long Arg1 = 177431885LL; verify_case(4, Arg1, getCount(Arg0)); }

// END CUT HERE

};

#include <bitset>

const int MAXN = 255;
bitset<MAXN> sieve;
vector<int> primes;
    
long long solve(int n) {
    set<int> divisors;
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j < primes.size(); ++j) {
            if (i % primes[j] == 0) divisors.insert(primes[j]);
        }
    }
    int p = divisors.size();
    assert(1 <= p and p <= 55);
    return 1LL << (p - 1);
}

long long EllysFractions::getCount(int n) {
    if (n == 1) return 0;
    
    sieve.reset();
    primes.clear();
    for (int i = 2; i < MAXN; ++i) {
        if (!sieve[i]) {
            primes.push_back(i);
            for (int j = i * i; j < MAXN; j += i) sieve[j] = true;
        }
    }
    long long ans = 0;
    for (int i = 2; i <= n; ++i) ans += solve(i);
    return ans;
}

// BEGIN CUT HERE
int main(){
    EllysFractions ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
