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

class FlipGame {
  public:
  int minOperations(vector <string> board);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1000",
 "1110",
 "1111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, minOperations(Arg0)); }
	void test_case_1() { string Arr0[] = {"1111",
 "1111",
 "1111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, minOperations(Arg0)); }
	void test_case_2() { string Arr0[] = {"00",
 "00",
 "00"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, minOperations(Arg0)); }
	void test_case_3() { string Arr0[] = {"00000000",
 "00100000",
 "01000000",
 "00001000",
 "00000000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(3, Arg1, minOperations(Arg0)); }
	void test_case_4() { string Arr0[] = {"000000000000001100000000000000",
 "000000000000011110000000000000",
 "000000000000111111000000000000",
 "000000000001111111100000000000",
 "000000000011111111110000000000",
 "000000000111111111111000000000",
 "000000001100111111001100000000",
 "000000011000011110000110000000",
 "000000111100111111001111000000",
 "000001111111111111111111100000",
 "000011111111111111111111110000",
 "000111111111000000111111111000",
 "001111111111100001111111111100",
 "011111111111110011111111111110",
 "111111111111111111111111111111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 29; verify_case(4, Arg1, minOperations(Arg0)); }

// END CUT HERE

};

const int MAXN = 55;
int b[MAXN][MAXN];
int rows, cols;

bool done() {
    for (int i = 0; i < rows; ++i) 
        for (int j = 0; j < cols; ++j)
            if (b[i][j]) return false;
    return true;
}

void toggle(int col, int row) {
    for (int r = row; r < rows; ++r) {
        b[r][col] ^= 1;
    }
}

int FlipGame::minOperations(vector <string> board) {
    rows = board.size(), cols = board[0].size();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            b[i][j] = board[i][j] - '0';
        }
    }
    
    int ans = 0;
    while (!done()) {
        ans++;
        for (int from = 0; from < cols; ) {
            int tallest = rows + 5, which = -1;
            for (int c = from; c < cols; ++c) {
                int score = 0;
                while (score < rows and b[score][c] == 0) score++;
                if (score <= tallest) {
                    tallest = score;
                    which = c;
                }
            }
            assert(which != -1);
            for (int c = from; c <= which; ++c) {
                toggle(c, tallest);
            }
            
            from = which + 1;
        }
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    FlipGame test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
