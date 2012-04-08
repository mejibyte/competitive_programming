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

class RollingDiceDivOne {
  public:
  long long mostLikely(vector <int> dice);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {6, 6, 8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 11LL; verify_case(0, Arg1, mostLikely(Arg0)); }
	void test_case_1() { int Arr0[] = {10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 1LL; verify_case(1, Arg1, mostLikely(Arg0)); }
	void test_case_2() { int Arr0[] = {2, 3, 4, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 9LL; verify_case(2, Arg1, mostLikely(Arg0)); }
	void test_case_3() { int Arr0[] = {1, 10, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 3LL; verify_case(3, Arg1, mostLikely(Arg0)); }
	void test_case_4() { int Arr0[] = {382828264, 942663792, 291832707, 887961277, 546603677, 545185615, 146267547, 6938117, 167567032, 84232402,
700781193, 452172304, 816532384, 951089120, 448136091, 280899512, 256093435, 39595226, 631504901, 154772240}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 4366828428LL; verify_case(4, Arg1, mostLikely(Arg0)); }

// END CUT HERE

};

vector <int> dice;



long long RollingDiceDivOne::mostLikely(vector <int> _dice) {
    dice = _dice;
    sort(dice.begin(), dice.end(), greater<int>());
    
    int n = dice.size();
    for (int i = 0; i < n; ++i) dice[i]--;
    long long sum = accumulate(dice.begin(), dice.end(), 0);
    
    if (sum <= 20) {
        static int ways[51][21];
        memset(ways, 0, sizeof ways);
        ways[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int s = 0; s <= sum; ++s) {
                for (int k = 0; k <= s and k <= dice[i - 1]; ++k) {
                    ways[i][s] += ways[i - 1][s - k];
                }
            }
        }
        
        for (int i = 0; i <= n; ++i) {
            printf("dice[%2d] = %4d: ", i, i > 0 ? dice[i - 1] : 0);
            for (int s = 0; s <= sum; ++s) {
                printf("%4d ", ways[i][s]);
            }
            puts("");
        }
    }
    
    int l = 0, r = 0, s = 0;
    for (int i = 0; i < n; ++i) {
        if (dice[i] + 1 >= s + 1) {
            l = s;
            r = dice[i];
        } else if (dice[i] + 1 <= r - l + 1) {
            l += dice[i];
        } else {
            int leftover = (dice[i] + 1) - (r - l + 1);
            if (leftover % 2 == 0) {
                r += leftover / 2;
                l = r;
            } else {
                r += leftover / 2 + 1;
                l = r - 1;
            }
        }
        s += dice[i];
    }
    return l + n;
}

// BEGIN CUT HERE
int main(){
    RollingDiceDivOne ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
