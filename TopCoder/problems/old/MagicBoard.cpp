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

class MagicBoard {
  public:
  string ableToUnlock(vector <string> board);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"##",
 ".#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YES"; verify_case(0, Arg1, ableToUnlock(Arg0)); }
	void test_case_1() { string Arr0[] = {"#.",
 ".#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "NO"; verify_case(1, Arg1, ableToUnlock(Arg0)); }
	void test_case_2() { string Arr0[] = {"##",
 "##",
 "##"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YES"; verify_case(2, Arg1, ableToUnlock(Arg0)); }
	void test_case_3() { string Arr0[] = {"###",
 "###",
 "###"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "NO"; verify_case(3, Arg1, ableToUnlock(Arg0)); }
	void test_case_4() { string Arr0[] = {"###",
 "..#",
 "###",
 "#..",
 "###"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "NO"; verify_case(4, Arg1, ableToUnlock(Arg0)); }
	void test_case_5() { string Arr0[] = {"................",
 ".######..######.",
 ".######..######.",
 ".##......##..##.",
 ".##......##..##.",
 ".######..######.",
 ".######..######.",
 ".....##..##..##.",
 ".....##..##..##.",
 ".######..######.",
 ".######..######.",
 "................"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YES"; verify_case(5, Arg1, ableToUnlock(Arg0)); }
	void test_case_6() { string Arr0[] = {"#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YES"; verify_case(6, Arg1, ableToUnlock(Arg0)); }

// END CUT HERE

};

const int MAXN = 55;
bool visited[2 * MAXN];
int rows, cols;
vector<int> g[2 * MAXN];

void dfs(int i) {
    if (visited[i]) return;
    visited[i] = true;
    foreach(v, g[i]) dfs(*v);
}

string MagicBoard::ableToUnlock(vector <string> board) {
    memset(visited, false, sizeof visited);
    rows = board.size(), cols = board[0].size();
    for (int i = 0; i < rows + cols; ++i) g[i].clear();
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board[i][j] == '#') {
                g[i].push_back(rows + j);
                g[rows + j].push_back(i);
            }
        }
    }
    
    int odd = 0;
    for (int i = 0; i < rows + cols; ++i) {
        odd += (g[i].size() % 2 == 1);
    }
    if (odd != 0 and odd != 2) return "NO";

    //need to start on the right side
    if (odd == 2) {
        bool canStart = false;
        for (int j = 0; j < cols; ++j) {
            if (g[rows + j].size() % 2 == 1) canStart = true;
        }
        if (!canStart) return "NO";
    }
    
    int components = 0;
    for (int i = 0; i < rows + cols; ++i) {
        if (g[i].size() > 0 and !visited[i]) {
            components++;
            dfs(i);
        }
    }
    if (components > 1) return "NO";
    return "YES";
    
}

// BEGIN CUT HERE
int main(){
    MagicBoard ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
