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

class EllysNumbers {
  public:
  long long getSubsets(long long n, vector <string> special);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 12LL; string Arr1[] = {"4 2 5 6 3"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 1LL; verify_case(0, Arg2, getSubsets(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 42LL; string Arr1[] = {"1 2 3 4 5 6 7 13 14 21 42"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 10LL; verify_case(1, Arg2, getSubsets(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 1337LL; string Arr1[] = {"1 13 42 666 2674"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(2, Arg2, getSubsets(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 1073741824LL; string Arr1[] = {"1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 1",
 "6384 32768 65536 131072 262144 524288 1048576 2097",
 "152 4194304 8388608 16777216 33554432 67108864 134",
 "217728 268435456 536870912"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(3, Arg2, getSubsets(Arg0, Arg1)); }
	void test_case_4() { long long Arg0 = 7420738134810LL; string Arr1[] = {"435 625199055 4199 33263 17 222870 284870433 72093",
 "2379 7 11 31 247110827 23 1771 81809 851968487 13 ", 
 "476379795 1001 5 435274114 38264554 7429 239906525",
 " 3 227183706 887045414 606786670 3795 797605175 29",
 " 30 747186719 19 2 562347843 74 2294 588002688 743",
 "6429 703 591740547 36657492 37 444178205 1002001 2",
 "17626404"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 110LL; verify_case(4, Arg2, getSubsets(Arg0, Arg1)); }

// END CUT HERE

};

const int MAXN = 31701;
bool prime[MAXN];

map<int, int> fact;
vector<int> a;
long long memo[1 << 16];

long long EllysNumbers::getSubsets(long long n, vector <string> special) {
    memset(prime, true, sizeof prime);
    vector<int> primes;
    for (int i = 2; i < MAXN; ++i) {
        if (!prime[i]) continue;
        primes.push_back(i);
        for (int j = i * i; j < MAXN; j += i) {
            prime[j] = false;
        }
    }

    string s; foreach(k, special) s += *k;
    stringstream sin(s);
    for (long long x; sin >> x; ) {
        if (n % x == 0 and __gcd(x, n / x) == 1) a.push_back(x);
    }

    // Factorize each number
    for (int i = 0; i < a.size(); ++i) {
        int x = a[i];
        for (int j = 0; j < primes.size(); ++j) {
            while (x % primes[j] == 0) x /= primes[j];
        }
        if (x > 1) primes.push_back(x);
    }

    for (int i = 0, index = 0; i < primes.size(); ++i) {
        if (n % primes[i] == 0 and fact.count(primes[i]) == 0) fact[primes[i]] = index++;
        while (n % primes[i] == 0) n /= primes[i];
    }
    if (n  > 1) return 0;
    assert(fact.size() < 16);

    for (int i = 0; i < a.size(); ++i) {
        int mask = 0;
        foreach(f, fact) {
            if (a[i] % f->first == 0) mask |= (1 << f->second);
        }
        a[i] = mask;
    }
    
    memset(memo, 0, sizeof memo);
    memo[0] = 1;
    int all = (1 << fact.size()) - 1;
    for (int i = 0; i < a.size(); ++i) {
        for (int remain = all; remain >= 0; --remain) {
            if ( (remain & a[i]) == a[i] ) {
                memo[remain] += memo[remain - a[i]];
            }
        }
    }
    return memo[all];
}

// BEGIN CUT HERE
int main(){
    for (int i = 0; i < 10; ++i) {
        EllysNumbers ___test;
        fact.clear();
        a.clear();
        ___test.run_test(i);
    }
    return 0;
}
// END CUT HERE
