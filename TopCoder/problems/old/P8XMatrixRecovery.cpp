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

class P8XMatrixRecovery {
  public:
  vector <string> solve(vector <string> rows, vector <string> columns);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"10?"
,"?11"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"01"
,"10"
,"1?"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"101", "011" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, solve(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"0"
,"?"
,"1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0?1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"0", "0", "1" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, solve(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"10"
,"01"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"10"
,"01"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"10", "01" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, solve(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"??0"
,"11?"
,"?01"
,"1?1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"1???"
,"?111"
,"0?1?"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"010", "110", "101", "101" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, solve(Arg0, Arg1)); }

// END CUT HERE

};

// Maximum Bipartite Matching
// Complexity: O(VE)

// Finds a maximum bipartite matching for two sets of
// size L and R.

// How to use:
// Set g[i][j] to true if element i of the Left set can
// be paired with element j of the Right set.
// Fill the table for all 0 <= i < L and 0 <= j < R.

// matchL[i] will contain i's match in the Right set
// and matchR[j] will contain j's match in the Left set.

const int MAXN = 35;
bool g[MAXN][MAXN], seen[MAXN];
int L, R, matchL[MAXN], matchR[MAXN];

bool assign(int i) { // i is in L
    for (int j = 0; j < R; ++j) {
        if (!g[i][j] or seen[j]) continue;
        seen[j] = true;
        if (matchR[j] == -1 or assign(matchR[j]) ) {
            matchL[i] = j;
            matchR[j] = i;
            return true;
        }
    }
    return false;
}

int maxBipartiteMatching() {
    for (int i = 0; i < L; ++i) matchL[i] = -1;
    for (int j = 0; j < R; ++j) matchR[j] = -1;
    
    int ans = 0;
    for (int i = 0; i < L; ++i) {
        memset(seen, false, sizeof seen);
        if (assign(i)) ans++;
    }
    return ans;
}



vector<string> rows, cols;

bool match(int col, const string &base) {
    for (int i = 0; i < rows.size(); ++i) {
        char here = rows[i][col];
        char there = base[i];
        if (here != '?' and there != '?'and here != there) return false;
    }
    return true;
}

bool solvable() {
    memset(g, 0, sizeof g);
    L = R = cols.size();
    
    for (int i = 0; i < cols.size(); ++i) {
        for (int j = 0; j < cols.size(); ++j) {
            if (match(j, cols[i])) g[i][j] = true;
        }
    }
    
    return maxBipartiteMatching() >= L;
}


vector <string> P8XMatrixRecovery::solve(vector <string> _rows, vector <string> _columns) {
    rows = _rows;
    cols = _columns;
    for (int i = 0; i < rows.size(); ++i) {
        for (int j = 0; j < rows[i].size(); ++j) {
            if (rows[i][j] == '?') {
                rows[i][j] = '0';
                if (!solvable()) rows[i][j] = '1';
            }
        }
    }
    return rows;
}

// BEGIN CUT HERE
int main(){
    P8XMatrixRecovery test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
