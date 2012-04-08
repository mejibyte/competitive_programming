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

class DropCoins {
  public:
  int getMinimum(vector <string> board, int K);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {".o.."
,"oooo"
,"..o."}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 2; verify_case(0, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {".....o"
,"......"
,"oooooo"
,"oooooo"
,"......"
,"o....."}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; int Arg2 = 3; verify_case(1, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"...."
,".oo."
,".oo."
,"...."}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = -1; verify_case(2, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"......."
,"..ooo.."
,"ooooooo"
,".oo.oo."
,"oo...oo"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; int Arg2 = 4; verify_case(3, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"................."
,".ooooooo...oooo.."
,".ooooooo..oooooo."
,".oo.......oo..oo."
,".oo.......oo..oo."
,".ooooo.....oooo.."
,".ooooooo...oooo.."
,".....ooo..oo..oo."
,"......oo..oo..oo."
,".ooooooo..oooooo."
,".oooooo....oooo.."
,"................."}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 58; int Arg2 = 6; verify_case(4, Arg2, getMinimum(Arg0, Arg1)); }

// END CUT HERE

};

const int MAXN = 35;

int sum[MAXN][MAXN];

int get(int r1, int r2, int c1, int c2) {
    return sum[r2+1][c2+1] - sum[r1][c2+1] - sum[r2+1][c1] + sum[r1][c1];
}

int DropCoins::getMinimum(vector <string> board, int K) {
    int rows = board.size();
    int cols = board[0].size();
    int totalCoins = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sum[i+1][j+1] = sum[i+1][j] + sum[i][j+1] - sum[i][j] + (board[i][j] == 'o');
            totalCoins += (board[i][j] == 'o');
        }
    }
    if (totalCoins == K) return 0;
    if (K == 0 and totalCoins > 0) return min(rows, cols);
    
    // for (int i = 0; i < rows + 1; ++i) {
    //     for (int j = 0; j < cols + 1; ++j) {
    //         printf("%d ", sum[i][j]);
    //     }
    //     puts("");
    // }
    int ans = 1 << 30;
    for (int r1 = 0; r1 < rows; ++r1) {
        for (int r2 = r1; r2 < rows; ++r2) {
            for (int c1 = 0; c1 < cols; ++c1) {
                for (int c2 = c1; c2 < cols; ++c2) {
                    int s = get(r1, r2, c1, c2);
                    //printf("r1 = %d, r2 = %d, c1 = %d, c2 = %d, s = %d\n", r1, r2, c1, c2, s);                    
                    assert(s >= 0);
                    if (s != K) continue;
                    int moves = r1 + c1 + (rows - 1 - r2) + (cols - 1 - c2) + min(r1, rows - 1 - r2) + min(c1, cols - 1 - c2);
                    ans = min(ans, moves);
                }
            }
        }
    }
    
    if (ans >= (1 << 30)) return -1;
    return ans;
}

// BEGIN CUT HERE
int main(){
    DropCoins ___test;
    //___test.run_test(0); return 0;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
