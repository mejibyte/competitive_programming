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

class MonochromaticBoard {
  public:
  int theMin(vector <string> board);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"WBWBW",
 "BBBBB",
 "WBWBW",
 "WBWBW"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, theMin(Arg0)); }
	void test_case_1() { string Arr0[] = {"BBBB",
 "BBBB",
 "BBBB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(1, Arg1, theMin(Arg0)); }
	void test_case_2() { string Arr0[] = {"BBBBB",
 "BBBBB",
 "BBBBB",
 "BBBBB",
 "BBBBB",
 "BBBBB",
 "BBBBB",
 "BBBBB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(2, Arg1, theMin(Arg0)); }
	void test_case_3() { string Arr0[] = {"WW",
 "WW"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, theMin(Arg0)); }
	void test_case_4() { string Arr0[] = {"BBBBBBBB",
 "BBBBBBBB",
 "BBBBBBBB",
 "WBWBBBWB",
 "BBBBBBBB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(4, Arg1, theMin(Arg0)); }

// END CUT HERE

};

int MonochromaticBoard::theMin(vector <string> board) {
	int rows = board.size();
	int cols = board[0].size();
	bool all_black = true; For(i, 0, rows) For(j, 0, cols) all_black &= (board[i][j] == 'B');
	if (all_black) return min(rows, cols);
	
	set<int> r, c;
	For (i, 0, rows){
		For (j, 0, cols){
			if (board[i][j] == 'W'){
				For (k, 0, rows){
					if (board[k][j] == 'B') r.insert(k);
				}
				For (k, 0, cols){
					if (board[i][k] == 'B') c.insert(k);
				}
			}
		}
	}
	return r.size() + c.size();
}

// BEGIN CUT HERE
int main(){
    MonochromaticBoard ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
