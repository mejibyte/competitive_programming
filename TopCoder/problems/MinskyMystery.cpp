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

class MinskyMystery {
  public:
  int computeAnswer(long long N);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 2LL; int Arg1 = 9; verify_case(0, Arg1, computeAnswer(Arg0)); }
	void test_case_1() { long long Arg0 = 3LL; int Arg1 = 27; verify_case(1, Arg1, computeAnswer(Arg0)); }
	void test_case_2() { long long Arg0 = 4LL; int Arg1 = 16; verify_case(2, Arg1, computeAnswer(Arg0)); }
	void test_case_3() { long long Arg0 = 2401LL; int Arg1 = 59058; verify_case(3, Arg1, computeAnswer(Arg0)); }
	void test_case_4() { long long Arg0 = 24LL; int Arg1 = 86; verify_case(4, Arg1, computeAnswer(Arg0)); }

// END CUT HERE

};

long long b[5];
long long ans;

void add(int bag, int count) {
    b[bag] += count;
    ans += count;
}

// Add a marble into bag 1.
//     Repeat forever:
//         Add a marble into bag 1.
//         Empty bag 4.
//         While there are marbles in bag 0:
//             While there are marbles both in bag 0 and in bag 1:
//                 Remove a marble from bag 0.
//                 Remove a marble from bag 1.
//                 Add a marble into bag 2.
//                 Add a marble into bag 3.
//             End While
//             Add a marble into bag 4.
//             If bags 0 and 1 are both empty:
//                 Move all marbles from bag 3 to bag 4.
//                 TERMINATE THE GAME
//             End If
//             Move all marbles from bag 3 to bag 1.
//         End While
//         Move all marbles from bag 2 to bag 0.
//     End Repeat

int MinskyMystery::computeAnswer(long long N) {
    if (N <= 1) return -1;
    
    memset(b, 0, sizeof b);
    b[0] = N;
    
    ans = 1;
    b[1] = 1;
    while (true) {
        ans++;
        b[1]++;
        int k = b[0];
        
        while (b[0] > 0) {
            int m = min(b[0], b[1]);
            ans += 3 * m + 1;
            
            if (b[0] == b[1]) {
                return ans;
            }
            b[0] -= m;
        }
        ans += k;
        b[0] = k;
        k = 0;
    }
    
    return -1;
}

// BEGIN CUT HERE
int main(){
    MinskyMystery test;
    test.run_test(-1);
    
    int big = 100000;
    for (int i = big - 100; i <= big; ++i) {
        printf("N = %d -> ans = %d\n", i, test.computeAnswer(i));
    }
    return 0;
}
// END CUT HERE
