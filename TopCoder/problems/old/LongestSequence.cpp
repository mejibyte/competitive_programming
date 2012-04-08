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

class LongestSequence {
  public:
  int maxLength(vector <int> C);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {-2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, maxLength(Arg0)); }
	void test_case_1() { int Arr0[] = {524}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(1, Arg1, maxLength(Arg0)); }
	void test_case_2() { int Arr0[] = {1, -1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, maxLength(Arg0)); }
	void test_case_3() { int Arr0[] = {11,-7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 16; verify_case(3, Arg1, maxLength(Arg0)); }
	void test_case_4() { int Arr0[] = {-227,690,590,-524}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 713; verify_case(4, Arg1, maxLength(Arg0)); }

// END CUT HERE

};

vector<int> visited;

void dfs(int u, int n, const vector<int> &c) {
    if (visited[u]) return;
    visited[u] = true;
    for (int i = 0; i < c.size(); ++i) {
        int next = u - c[i];
        if (0 <= next and next <= n) dfs(next, n, c);
    }
}

bool works(int n, const vector<int> &c) {
    visited.assign(n + 1, false);
    for (int i = 0; i < c.size(); ++i) {
        if (c[i] < 0) dfs(-c[i], n, c);
    }
    return !visited[0];
}


int LongestSequence::maxLength(vector <int> c) {
    sort(c.begin(), c.end());
    if (c[0] < 0 and c.back() < 0 or c[0] > 0 and c.back() > 0) return -1;
    int low = 0, high = 2001;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (works(mid, c)) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }

    return low;
}

// BEGIN CUT HERE
int main(){
    LongestSequence ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
