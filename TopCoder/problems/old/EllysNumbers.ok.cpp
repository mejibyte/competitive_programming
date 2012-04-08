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

vector<int> masks;
map<int, int> fact;
vector<int> b;
long long memo[2][1 << 16];

long long ways() {
    memset(memo, 0, sizeof memo);
    memo[0][0] = 1;
    int n = masks.size();
    int all = (1 << fact.size()) - 1;
    for (int i = 1; i <= n; ++i) {
        int a = masks[i - 1];
        
        int cur = i & 1;
        int prev = cur ^ 1;

        for (int remain = 0; remain <= all; ++remain) {
            memo[cur][remain] = memo[prev][remain];
            if ( (remain & a) == a ) {
                memo[cur][remain] += memo[prev][remain - a];
            }
        }
    }
    return memo[n & 1][all];
}

long long solve() {
    int index = 0;
    foreach(f, fact) f->second = index++;
    for (int i = 0; i < b.size(); ++i) {
        int mask = 0;
        foreach(f, fact) {
            if (b[i] % f->first == 0) mask |= (1 << f->second);
        }
        masks.push_back(mask);
    }
    return ways();
}


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
    vector<int> a;
    for (int x; sin >> x; ) {
        if (n % x == 0) a.push_back(x);
    }
    
    vector<int> presentPrimes;
    // Factorize each number
    for (int i = 0; i < a.size(); ++i) {
        int x = a[i];
        for (int j = 0; x > 1 and j < primes.size() and primes[j] <= x; ++j) {
            if (x % primes[j] == 0) presentPrimes.push_back(primes[j]);
            while (x % primes[j] == 0) x /= primes[j];
        }
        if (x > 1) {
            presentPrimes.push_back(x);
        }
    }
    sort(presentPrimes.begin(), presentPrimes.end());
    presentPrimes.resize( unique(presentPrimes.begin(), presentPrimes.end()) - presentPrimes.begin() );
    
    // check that n is composed of only those
    long long m = n;
    for (int i = 0; i < presentPrimes.size(); ++i) {
        while (m % presentPrimes[i] == 0) m /= presentPrimes[i], fact[presentPrimes[i]]++;
    }
    if (m > 1) return 0;
    
    // b is survivors of a
    for (int i = 0; i < a.size(); ++i) {
        bool valid = true;
        int x = a[i];
        for (int j = 0; j < presentPrimes.size(); ++j) {
            int p = presentPrimes[j];
            if (x % p != 0) continue;
            int cnt = 0;
            while (x % p == 0) cnt++, x /= p;
            if (fact.find(p) == fact.end() or cnt != fact[p]) {
                valid = false;
                break;
            }
        }
        if (valid) b.push_back(a[i]);
    }
    
    if (b.size() == 0) return 0;
    assert(fact.size() < 16);
    
    return solve();
}

// BEGIN CUT HERE
int main(){
    for (int i = 0; i < 10; ++i) {
        EllysNumbers ___test;
        masks.clear();
        fact.clear();
        b.clear();
        ___test.run_test(i);
    }
    return 0;
}
// END CUT HERE
