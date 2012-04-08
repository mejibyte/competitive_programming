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
bool visited[MAXN][MAXN];
int rows, cols;
vector<string> b;

void dfs(int i, int j) {
    if (visited[i][j]) return;
    visited[i][j] = true;
    for (int r = 0; r < rows; ++r)
        if (i != r and b[r][j] == '#') dfs(r, j);
    for (int c = 0; c < cols; ++c)
        if (j != c and b[i][c] == '#') dfs(i, c);
}

string MagicBoard::ableToUnlock(vector <string> board) {
    memset(visited, false, sizeof visited);
    
    rows = board.size(), cols = board[0].size();
    b = board;
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (b[i][j] == '#') {
                dfs(i, j);
                i = rows, j = cols; // super break
            }
        }
    }
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (b[i][j] == '#' and !visited[i][j]) {
                return "NO"; 
            }
        }
    }
            
    vector<int> inRow(rows), inCol(cols);
    int total = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (b[i][j] == '#') {
                total++;
                inRow[i]++;
                inCol[j]++;
            }
        }
    }
    if (total == 1) return "YES";
    
    if (total % 2 == 0) {
        for (int i = 0; i < rows; ++i) if (inRow[i] % 2 == 1) return "NO";
        int odd = 0;
        for (int j = 0; j < cols; ++j) if (inCol[j] % 2 == 1) odd++;
        return (odd == 0 or odd == 2 ? "YES" : "NO");
    } else {
        int odd = 0;
        for (int j = 0; j < cols; ++j) if (inCol[j] % 2 == 1) odd++;
        if (odd != 1) return "NO";
        
        odd = 0;
        for (int i = 0; i < rows; ++i) if (inRow[i] % 2 == 1) odd++;
        return (odd == 1 ? "YES" : "NO");
    }
    
    return "YES";
}

// BEGIN CUT HERE
int main(){
    MagicBoard ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
