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

class TheLuckyGameDivOne {
  public:
  int find(long long a, long long b, long long jLen, long long bLen);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 1LL; long long Arg1 = 10LL; long long Arg2 = 2LL; long long Arg3 = 1LL; int Arg4 = 0; verify_case(0, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { long long Arg0 = 1LL; long long Arg1 = 100LL; long long Arg2 = 100LL; long long Arg3 = 100LL; int Arg4 = 6; verify_case(1, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { long long Arg0 = 4LL; long long Arg1 = 8LL; long long Arg2 = 3LL; long long Arg3 = 2LL; int Arg4 = 1; verify_case(2, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { long long Arg0 = 1LL; long long Arg1 = 100LL; long long Arg2 = 75LL; long long Arg3 = 50LL; int Arg4 = 2; verify_case(3, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

vector<long long> lucky;
long long A, B;

void generate(long long x) {
    if (x > B) return;
    if (A <= x) lucky.push_back(x);
    generate(10*x + 4);
    generate(10*x + 7);
}

int TheLuckyGameDivOne::find(long long a, long long b, long long jlen, long long blen) {
    A = a;
    B = b;
    lucky.clear();
    generate(0);
    sort(lucky.begin(), lucky.end());
    
    foreach(l, lucky) cout << *l << " "; cout << endl;
    
    printf("A = %lld, B = %lld\njlen = %lld, blen = %lld\n", a, b, jlen, blen);
    
    int ans = 0;
    for (int i = 0; i < lucky.size(); ++i) {
        for (int j = i; j < lucky.size(); ++j) {
            int score = j - i + 1;
            long long p = lucky[i];
            long long q = lucky[j];

            long long l = q - blen + 1, r = p;

            long long low = l, high = r;
            
            low = max(low, l - jlen + blen);
            high = min(high, r - jlen + blen);
            
            low = max(low, a);
            high = min(high, b);
            
            low = max(low, a - jlen + 1);
            high = min(high, b - jlen + 1);
            
            if (low <= high) {
                if (score > ans) {
                    ans = score;
//                    printf("from p=%lld to q=%lld\n", p, q);    
//                    printf("[%lld, %lld]\n", l, r);
                }
            }
        }
    }
    
    return ans;
}

// BEGIN CUT HERE
int main(){
    TheLuckyGameDivOne test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
