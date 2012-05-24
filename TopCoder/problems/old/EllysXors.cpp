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

class EllysXors {
  public:
  long long getXor(long long L, long long R);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 3LL; long long Arg1 = 10LL; long long Arg2 = 8LL; verify_case(0, Arg2, getXor(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 5LL; long long Arg1 = 5LL; long long Arg2 = 5LL; verify_case(1, Arg2, getXor(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 13LL; long long Arg1 = 42LL; long long Arg2 = 39LL; verify_case(2, Arg2, getXor(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 666LL; long long Arg1 = 1337LL; long long Arg2 = 0LL; verify_case(3, Arg2, getXor(Arg0, Arg1)); }
	void test_case_4() { long long Arg0 = 1234567LL; long long Arg1 = 89101112LL; long long Arg2 = 89998783LL; verify_case(4, Arg2, getXor(Arg0, Arg1)); }

// END CUT HERE

};

long long get(long long bound) {
    if (bound == 0) return 0;
    long long ans = 0;
    for (int bit = 1; bit < 63; ++bit) {
        long long mask = 1LL << bit;
        if (bound & mask) {
            long long times = bound & (mask - 1);
            times++;
            
            ans += (times & 1LL) << bit;
        }
    }
    
    return ans;
}

long long EllysXors::getXor(long long L, long long R) {
    long long ans = get(R) ^ get(L - 1);
    if (L & 1LL) L--;
    if (R & 1LL) R++;
    long long first = (R - L + 1) / 2;
    ans += (first & 1LL);
    return ans;
}

// BEGIN CUT HERE

long long get_buggy(long long bound) {
    if (bound == 0) return 0;
    long long ans = 0;
    for (int bit = 1; bit < 63; ++bit) {
        long long mask = 1 << bit;
        if (bound & mask) {
            long long times = bound & (mask - 1);
            times++;
            
            ans += (times & 1) << bit;
        }
    }
    
    return ans;
}

long long range(long long a) {
    if (a == 0)     return 0;
    long long ret =0;
    if (a%4 ==1 or a %4 ==2) ret++;
    a++;
    for(int i=1;i<40;++i){
        long long t= 2ll<<i;
        long long w=a%t;
        w -= t/2;
        if (w > 0 and w % 2) ret += 1LL<<i;
    }
    return ret;
}

long long buggy(long long L, long long R) {
    long long a = range(L - 1);
    long long b = range(R);
    return a ^ b;
}

long long brute(long long a, long long b) {
    long long ans = 0;
    for (long long i = a; i <= b; ++i) ans ^= i;
    
//    ans = b ^ (a - 1);
    return ans;
}

int main(){
    EllysXors test;
    
    D((long long)(1<<32)); return 0;
    
    for (int i = 0; i < 10000; ++i) {
        printf(".");
        
        long long a = 1LL * rand()  % 4000000000LL + 1;
        long long b = 1LL * rand()  % 4000000000LL + 1;
        
        //a = 4000000000LL - 123;
        //b = 4000000000LL;
        
        if (b < a) swap(a, b);
        
        D(a); D(b);
        
        if (buggy(a, b) != test.getXor(a, b)) {
            D(a); D(b);
            assert(brute(a, b) == test.getXor(a, b));
        }

    }
    
    test.run_test(-1);
    return 0;
}
// END CUT HERE
