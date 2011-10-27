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

class PointErasingTwo {
  public:
  int getMaximum(vector <int> y);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = { 1, 2, 1, 1, 0, 4, 3 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, getMaximum(Arg0)); }
	void test_case_1() { int Arr0[] = { 0, 1 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, getMaximum(Arg0)); }
	void test_case_2() { int Arr0[] = { 0, 1, 2, 3, 4 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(2, Arg1, getMaximum(Arg0)); }
	void test_case_3() { int Arr0[] = { 10, 19, 10, 19 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, getMaximum(Arg0)); }
	void test_case_4() { int Arr0[] = { 0, 23, 49, 50, 32, 0, 18, 50, 0, 28, 50, 27, 49, 0 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(4, Arg1, getMaximum(Arg0)); }

// END CUT HERE

};

int PointErasingTwo::getMaximum(vector <int> y) {
    int best = 0;
    for (int i = 0; i < y.size(); ++i){
        for (int j = i + 1; j < y.size(); ++j) {
            int option = 0;
            for (int k = i + 1; k < j; ++k) {
                if (min(y[i], y[j]) < y[k] and  y[k] < max(y[i], y[j]) ) option++;
            }
            best = max(best, option);
        }
    }
    return best;
}

// BEGIN CUT HERE
int main(){
    PointErasingTwo ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
