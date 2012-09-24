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

class AdjacentSwaps {
  public:
  int theCount(vector <int> p);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 2, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, theCount(Arg0)); }
	void test_case_1() { int Arr0[] = {0, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, theCount(Arg0)); }
	void test_case_2() { int Arr0[] = {2, 0, 3, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, theCount(Arg0)); }
	void test_case_3() { int Arr0[] = {1, 0, 3, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, theCount(Arg0)); }
	void test_case_4() { int Arr0[] = {1, 3, 0, 5, 2, 7, 4, 8, 10, 6, 12, 9, 14, 11, 16, 13, 18, 15, 19, 17}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 716743312; verify_case(4, Arg1, theCount(Arg0)); }

// END CUT HERE

};

vector<int> p;
const int MAXN = 55;
const int mod = (int)(1e9 + 7);
int choose[MAXN][MAXN];
int memo[MAXN][MAXN];
int mix[MAXN][MAXN];

int ways(int i, int j) {
    if (i == j) return 1;
    if (memo[i][j] != -1) return memo[i][j];
    
    int ans = 0;
    for (int last = i; last + 1 <= j; ++last) {
        vector<int> t = p;
        // sort t[i, last]
        sort(t.begin() + i, t.begin() + last + 1);
        // sort t[last + 1, j]
        sort(t.begin() + last + 1, t.begin() + j + 1);
        swap(t[last], t[last + 1]);
        bool sorted = true;
        for (int k = i; k + 1 <= j; ++k) {
            if (t[k] > t[k + 1]) {
                sorted = false;
                break;
            }
        }
        if (sorted) {
            int l = ways(i, last);
            int r = ways(last + 1, j);
            
            int a = last - i, b = j - last - 1;
            int m = choose[a + b][a];
            
            long long add = 1LL * l * r % mod;
            add = add * m % mod;
            ans += add;
            ans %= mod;
        }
    }
    
    return memo[i][j] = ans;
}

int AdjacentSwaps::theCount(vector <int> _p) {
    p = _p;
    for (int i = 0; i < MAXN; ++i) mix[i][0] = mix[0][i] = 1;
    for (int i = 1; i < MAXN; ++i) {
        for (int j = 1; j < MAXN; ++j) {
            mix[i][j] = (mix[i - 1][j] + mix[i][j - 1]) % mod;
        }
    }
    
    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j < MAXN; ++j) {
            if (i == 0 and j == 0) choose[i][j] = 1;
            else {
                choose[i][j] = 0;
                if (i - 1 >= 0) {
                    choose[i][j] += choose[i - 1][j];
                    if (j - 1 >= 0) {
                        choose[i][j] += choose[i - 1][j - 1];
                        choose[i][j] %= mod;
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j < MAXN; ++j) {
            if (i + j < MAXN) {
                assert(choose[i + j][i] == choose[i + j][j]);
                assert(choose[i + j][i] == mix[i][j]);
            }
        }
    }
    
    memset(memo, -1, sizeof memo);
    return ways(0, p.size() - 1);
}

// BEGIN CUT HERE
int main(){
    AdjacentSwaps test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
