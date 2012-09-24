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

class ElectionFraudDiv1 {
  public:
  int MinimumVoters(vector <int> percentages);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {33, 33, 33}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, MinimumVoters(Arg0)); }
	void test_case_1() { int Arr0[] = {29, 29, 43}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(1, Arg1, MinimumVoters(Arg0)); }
	void test_case_2() { int Arr0[] = {12, 12, 12, 12, 12, 12, 12, 12}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(2, Arg1, MinimumVoters(Arg0)); }
	void test_case_3() { int Arr0[] = {13, 13, 13, 13, 13, 13, 13, 13}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(3, Arg1, MinimumVoters(Arg0)); }
	void test_case_4() { int Arr0[] = {0, 1, 100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 200; verify_case(4, Arg1, MinimumVoters(Arg0)); }
	void test_case_5() { int Arr0[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 97; verify_case(5, Arg1, MinimumVoters(Arg0)); }

// END CUT HERE

};

int ceil(int a, int b) {
    assert(b > 0);
    if (a >= 0) return (a + b - 1) / b;
    return -((-a) / b);

}

int ElectionFraudDiv1::MinimumVoters(vector <int> percentages) {
    int sum = 0;
    foreach(p, percentages) sum += *p;
    int n = percentages.size();
    int positive = 0;
    foreach(p, percentages) positive += (*p > 0);
    if (2*sum - positive <= 200 and 200 < 2*sum + n) {
        for (int g = 1; ; ++g) {
            bool ok = true;
            int at_least = 0, at_most = 0;
            for (int i = 0; i < n and ok; ++i) {
                int p = percentages[i];
                int low = ceil(g * (2 * p - 1), 200);
                int high = ceil(g * (2 * p + 1), 200);
                
                at_least += low;
                at_most += high;
                
                if (low >= high) ok = false;
            }
            if (at_least <= g and g < at_most) {
                // still ok
            } else {
                ok = false;
            }
            
            if (ok) return g;
        }
    } else {
        return -1;
    }
}

// BEGIN CUT HERE
int main(){
    ElectionFraudDiv1 test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
